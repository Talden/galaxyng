#include "galaxyng.h"

/****f* CLI/CMD_immediate
 * NAME
 *   CMD_immediate -- check to see if all orders are in. if so, run
 *   turn and send turn reports 
 * SYNOPSIS
 *   ./galaxyng -immediate <game name>
 * FUNCTION
 *   Check to see if all orders are in - if so, kick off the run_game
 *   process.
 *
 * DIAGNOSTICS
 *   Message to stderr in case of an error.
 *   (Game does not exist, not the right time to run the game,
 *    game structure is corrupted).
 * RESULT
 *   EXIT_FAILURE  or  EXIT_SUCCESS
 * SOURCE
 */

int CMD_immediate( int argc, char **argv) {
	struct stat buf;			/* for checking file existance */
	int         result;			/* return code for the function */
	long        elapsedTime;	/* how much time has elapsed since
								 * last orders */
	long        dueTime;		/* when is this tick due to run */
	long        tickTime;		/* how long is the interval between ticks */
	int         msgCount = 0;	/* count of msgs sent to players */
	char*       gmBody;			/* name of file for GM messages */
	FILE*       gmNote;			/* file written to with GM messages */
	game*       aGame;			/* game information */
	int         turn;			/* which turn are we checking */
	char*       logName;		/* name of log file */
	char*       nextTurn;		/* name of next turn file */
	player*     aPlayer;		/* for looking at players in the game */
	char*       ordersfile;		/* name of each player's orders file */
	int         nbrOrders;		/* how many have final orders */
	int         actvPlayers;	/* how many active players */
	char*       notifyFileName;
	char        command_line[1024];
	
	result = EXIT_FAILURE;		/* assume it's all going to go bad -
								 * mainly because we we do a lot more
								 * checks than we'll run turns */

	/* all arguments present? */
	if (argc != 3) {
		usage();
		return result;
	}

	/* create a log for the GM */
	logName = createString("%s/log/%s.imm", galaxynghome, argv[2]);
	openLog(logName, "w");
	free(logName);

	/* galaxyng logging setup */
	plogtime(LPART);
	plog(LPART, "Checking to see if game can be run now.\n");

	/* get the game information */
	aGame = NULL;
	turn = LG_CURRENT_TURN;
	
	/* less than GM determined time, see if all orders are in */
	if ((aGame = loadgame(argv[2], turn)) == NULL) {
		plog(LBRIEF, "Game \"%s\" does not exist.\n", argv[2]);
		fprintf(stderr, "Game \"%s\" does not exist.\n", argv[2]);
		return result;
	}

	/* load the GM configuration */
	loadNGConfig( aGame );

	/* find when the last turn ran */
	nextTurn = createString("%s/data/%s/next_turn", galaxynghome, argv[2]);
	stat(nextTurn, &buf);
	/* this is how much time has elapsed since then, in seconds */
	elapsedTime = time(NULL) - buf.st_mtime;
	free(nextTurn);

	/* time, in seconds, between game ticks */
	tickTime = 3600 * atol(aGame->serverOptions.tick_interval);

	if (elapsedTime >= tickTime) {
		/* orders status doesn't matter, time to run the turn */
		plog(LPART, "imm: time's up, running game\n");
			
		sprintf(command_line, "%s/run_game %s >> %s/log/%s",
				galaxynghome, argv[2], galaxynghome, argv[2]);
		return ssystem(command_line);
	}
	
	/* what time do we check for orders due? */
	dueTime = 3600 * (atol(aGame->serverOptions.tick_interval) -
					  atol(aGame->serverOptions.due));

	/* now check the players, see if they've turned in orders */
	nbrOrders = 0;
	actvPlayers = 0;
	
	for ( aPlayer = aGame->players; aPlayer; aPlayer = aPlayer->next ) {
		/* dead players don't like getting email */
		if (aPlayer->flags & F_DEAD)
			continue;

		actvPlayers++;

		/* look for the final orders file */
		ordersfile = createString("%s/orders/%s/%s_final.%d",
								  galaxynghome, argv[2],
								  aPlayer->name, aGame->turn+1);

		/* access() returns 0 on success */
		if (access(ordersfile, R_OK) == 0) {
			nbrOrders++;
			continue;
		}

		/* ok, no final orders here */

		/* only send out missing orders message once. we create
		 * the .notify file so we only send out the one email */
		if (elapsedTime < dueTime) {
			continue;
		}

		
		notifyFileName = createString("%s/orders/%s/%s_%d.notify",
									  galaxynghome, argv[2],
									  aPlayer->name, aGame->turn+1);
		
		/* if this GM notify file doesn't exist, then create
		 * it so the GM gets a message */
		
		/* this is the email to the GM about which players are missing
		 * orders at <dueTime> prior to the turn running */
		gmBody = createString("%s/orders/%s/GMnotify_%d", galaxynghome,
							  aGame->name, aGame->turn+1);
		
		if (access(gmBody, R_OK)) {
			gmNote = fopen(gmBody, "w");
		}
		else {
			gmNote = NULL;
		}
		
		if (access(notifyFileName, R_OK)) {
			envelope* env;
			FILE* fp = fopen(notifyFileName, "w");
			char* mofName; /* missing orders file name */
			
			fprintf(fp, "notified\n");
			fclose(fp);
			
			env = createEnvelope();
			env->to = strdup(aPlayer->addr);
			env->from = strdup(aGame->serverOptions.SERVERemail);
			env->subject =
				createString("Turn %d of %s is about to run",
							 aGame->turn+1, argv[2]);
			
			/* if we haven't sent any player notifications
			 * yet, then we need to put the header in the GM
			 * file and create the player file (since it's a
			 * generic message for all players) */
			if (msgCount == 0) {
				FILE* mofFP;
				if (gmNote) {
					fprintf(gmNote, "The following players have "
							"not yet submitted orders for turn %d "
							"of %s\n", aGame->turn+1, aGame->name);
				}
				
				mofName = createString("%s/data/%s/missing_orders.%d",
									   galaxynghome, aGame->name,
									   aGame->turn+1);
				
				mofFP = fopen(mofName, "w");
				fprintf(mofFP, "Your orders for turn %d for "
						"%s have not been received.\nOrders "
						"are due in %s hours. Please send "
						"them now.\n",
						aGame->turn+1, aGame->name,
						aGame->serverOptions.due);
				fclose(mofFP);
			}
			
			/* now email the player and put a note in the GMs
			   file */
			if (gmNote) {
				fprintf(gmNote, "%s has not turned in orders.\n",
						aPlayer->name);
			}
			
			result |= eMail(aGame, env, mofName);
			destroyEnvelope(env);
			msgCount++;
			unlink(mofName);
			free(mofName);
		}
	}

	/* if there were any missing orders and we need to email the GM,
	 * then do so */
	if (nbrOrders != actvPlayers) {
		if (gmNote != NULL) {
			envelope* env = createEnvelope();
			env->to=strdup(aGame->serverOptions.GMemail);
			env->from = strdup(aGame->serverOptions.SERVERemail);
			env->subject = createString("Missing orders for %s (%d)",
										argv[2], aGame->turn+1);
			fclose(gmNote);
			eMail(aGame, env, gmBody);
			destroyEnvelope(env);
		}
		freegame( aGame );
		return EXIT_SUCCESS;
	}
			
	freegame( aGame );

	plog(LPART, "All orders in, running game\n");
			
	sprintf(command_line, "%s/run_game %s >> %s/log/%s",
			galaxynghome, argv[2], galaxynghome, argv[2]);
	return ssystem(command_line);
}
