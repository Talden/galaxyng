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
	struct stat buf;
	int         result;
	long        elapsed_time;
	long        due_time;
	long        tick_time;
	int         msg_count = 0;
	char* gmbody;
	FILE* gmnote;
	
	result = EXIT_FAILURE;
	if ( argc == 3 ) {
		game *aGame;
		int turn;
		char* logName;
		char* next_turn;
		logName = createString( "%s/log/%s.imm", galaxynghome, argv[2] );
		openLog( logName, "w" );
		free( logName );
		
		plogtime( LPART );
		plog( LPART, "Checking to see if game can be run now.\n");
		
		aGame = NULL;
		turn = LG_CURRENT_TURN;
		/* less than GM determined time, see if all orders are in */
		if ( ( aGame = loadgame( argv[2], turn ) ) ) {
			player* aPlayer;
			char* ordersfile;
			int   failed = 0;
      
			loadNGConfig( aGame );
      
			next_turn =
				createString("%s/data/%s/next_turn", galaxynghome, argv[2]);
			stat(next_turn, &buf);
			elapsed_time = time(NULL) - buf.st_mtime;
			free(next_turn);

			tick_time = 3600 * atol(aGame->serverOptions.tick_interval);
			due_time = 3600 * (atol(aGame->serverOptions.tick_interval) -
							   atol(aGame->serverOptions.due));
			
			gmbody = createString("%s/orders_due_%s", tempdir, aGame->name);
			gmnote = GOS_fopen(gmbody, "w");
			
			for ( aPlayer = aGame->players; aPlayer;
				  aPlayer = aPlayer->next ) {
				int no_orders;
				if (aPlayer->flags & F_DEAD)
					continue;
					ordersfile = createString("%s/orders/%s/%s_final.%d",
										  galaxynghome, argv[2],
										  aPlayer->name, aGame->turn+1);
				
				no_orders = access(ordersfile, R_OK);
				
				if (no_orders) {
					char* notify_file;
					failed = 1;
					if (elapsed_time > due_time) {
						notify_file = createString("%s/orders/%s/%s_%d.notify",
												   galaxynghome, argv[2],
												   aPlayer->name, aGame->turn+1);
						if (access(notify_file, R_OK)) {
							envelope* env;
							FILE* fp = fopen(notify_file, "w");
							char* missing_orders_file;
							
							fprintf(fp, "notified\n");
							fclose(fp);

							env = createEnvelope();
							env->to = strdup(aPlayer->addr);
							env->from =
								strdup(aGame->serverOptions.SERVERemail);
							env->subject =
								createString("Turn %d of %s is about to run",
											 aGame->turn+1, argv[2]);
							if (msg_count == 0) {
								FILE* mof_fp;
								fprintf(gmnote, "The following players have "
										"not yet submitted orders for turn %d "
										"of %s\n",
										aGame->turn+1, aGame->name);
						
								missing_orders_file =
									createString("%s/data/%s/missing_"
												 "orders.%d",
												 galaxynghome, aGame->name,
												 aGame->turn+1);
								mof_fp = fopen(missing_orders_file, "w");
								fprintf(mof_fp, "Your orders for turn %d for "
										"%s have not been received.\nOrders "
										"are due in %s hours. Please send "
										"them now.\n",
										aGame->turn+1, aGame->name,
										aGame->serverOptions.due);
								fclose(mof_fp);
							}
							fprintf(gmnote, "%s has not turned in orders.\n",
									aPlayer->name);
							result |= eMail(aGame, env, missing_orders_file);
							destroyEnvelope(env);
							msg_count++;
							unlink(missing_orders_file);
							free(missing_orders_file);
						}
					}
				}
			}
		
			if (failed) {
				envelope* env = createEnvelope();
				env->to=strdup(aGame->serverOptions.GMemail);
				env->from = strdup(aGame->serverOptions.SERVERemail);
				env->subject = createString("Missing orders for %s (%d)",
											argv[2], aGame->turn+1);
				fclose(gmnote);
				eMail(aGame, env, gmbody);
				destroyEnvelope(env);
				plog( LPART, "Not all orders in, skipping tick.\n");
				return result;
			}
			
			
			if (!failed) {
				plog(LPART, "All orders in, running game\n");
			}
			
			closeLog(  );
			freegame( aGame );
			plog(LPART, "elapsed_time: %ld   interval: %ld  due: %ld\n",
				 elapsed_time, tick_time, due_time);
			
			if (!failed || elapsed_time > tick_time) {
				char command_line[1024];
				sprintf(command_line, "%s/run_game %s >> %s/log/%s",
						galaxynghome, argv[2], galaxynghome, argv[2]);
				ssystem(command_line);
			}
		}
		else {
			plog( LBRIEF, "Game \"%s\" does not exist.\n", argv[2] );
			fprintf( stderr, "Game \"%s\" does not exist.\n", argv[2] );
		}
	}
	else {
		usage(  );
	}
	closeLog(  );
	return result;
}
