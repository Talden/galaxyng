#include "galaxyng.h"

/****i* CLI/CMD_relay
 * NAME 
 *   CMD_relay -- relay a message from one race to another.
 * FUNCTION
 ******
 */

#define SINGLE_PLAYER 0
#define ALL_PLAYERS   1

int CMD_relay( int argc, char **argv ) {
	int   result;
	char* logName;
	char* confirmName;
	int   resNumber;
	game* aGame;
	FILE* confirm;
	emailList* toPlayers;
	emailList* listPlayer;
	
	player* itPlayer;
	player* fromPlayer;
	char* destination;
	char* raceName;
	char* password;
	char* final_orders;
	int theTurnNumber = LG_CURRENT_TURN;
	envelope *anEnvelope;
			
	result = EXIT_FAILURE;
	
	if (argc < 2) {
		usage();
		return result;
	}
	
	logName = createString("%s/log/orders_processed.txt", galaxynghome);
	openLog(logName, "a");
	free(logName);
	plogtime(LBRIEF);

	confirmName = createString("%s/NGconfirm", tempdir);
	if ((confirm = fopen(confirmName, "w")) == NULL) {
	  plog(LBRIEF, "Can't open \"%s\".\n", confirmName);
		fprintf(stderr, "Can't open \"%s\".\n", confirmName);
		free(confirmName);
		return result;
	}

	anEnvelope = readEnvelope(stdin);

	destination = getDestination( anEnvelope->subject );

	raceName = NULL;
	password = NULL;
	final_orders = NULL;
	aGame = NULL;
	resNumber = areValidOrders( stdin, &aGame, &raceName, &password,
								&final_orders, &theTurnNumber );

	plog(LBRIEF, ">CMD_relay(from: \"%s\"  to: \"%s\"), "
	     "confirmation in \"%s\"\n", anEnvelope->to, destination,
	     confirmName);

	setHeader(anEnvelope, MAILHEADER_FROM, "%s", aGame->serverOptions.GMemail);

	/* it's ok to not have a turn number on a relay */
	if (resNumber != RES_OK && resNumber != RES_NO_TURN_NBR) {
		setHeader(anEnvelope, MAILHEADER_SUBJECT, "[GNG] Major Trouble");
		generateErrorMessage(resNumber, aGame, raceName,
							  theTurnNumber, confirm);
		plog(LBRIEF, "relay: error %d\n", resNumber);
		result |= eMail(aGame, anEnvelope, confirmName);
		return result;
	}

	fprintf(confirm, "Relay for game \"%s\"\n", aGame->name);
			
	/* we need to make a list of recipients */
	if (noCaseStrcmp(raceName, "GM") == 0) {
		fromPlayer = (player*)malloc(sizeof (player));
		fromPlayer->name = strdup("GM");
		fromPlayer->addr = strdup(aGame->serverOptions.GMemail);
		fromPlayer->pswd = strdup(aGame->serverOptions.GMpassword);
	}
	else 
		fromPlayer = findElement(player, aGame->players, raceName);

	if (fromPlayer == NULL) {
		setHeader(anEnvelope, MAILHEADER_SUBJECT, "[GNG] Major Trouble");
		generateErrorMessage(RES_PLAYER, aGame, raceName,
							  theTurnNumber, confirm);
		result |= eMail(aGame, anEnvelope, confirmName);
		plog(LBRIEF, "cmd_relay: can't tell who mail is from.\n");
		return result;
	}
	
	if ( destination == NULL ) {
		setHeader(anEnvelope, MAILHEADER_SUBJECT, "[GNG] Major Trouble");
		generateErrorMessage(RES_NODESTINATION, aGame, raceName,
							  theTurnNumber, confirm);
		result |= eMail(aGame, anEnvelope, confirmName);
		plog(LBRIEF, "cmd_relay: can't tell who mail is to.\n");
		return result;
	}
			
	toPlayers = allocStruct(emailList);

	if (noCaseStrcmp(destination, aGame->name) == 0) {
		/* since we are relaying to the game, then the relay goes to
		 * all players and the GM
		 */
	  plog(LBRIEF, "  relaying to all players since destination is the same as the game name\n");
		for (itPlayer = aGame->players; itPlayer; itPlayer = itPlayer->next) {
			/* skip dead players, they dislike getting email about the game :)
			 */
			if (itPlayer->flags & F_DEAD) {
				continue;
			}

			/* don't relay to yourself -- note: this is a bogus check,
			 * but I'm leaving it in to remind myself to fix it. This
			 * is a C ==, not a class ==
			 * */
			if (itPlayer == fromPlayer)
				continue;
			
			listPlayer = allocStruct(emailList);
			listPlayer->name = strdup(itPlayer->name);
			listPlayer->addr = strdup(itPlayer->addr);
			listPlayer->pswd = strdup(itPlayer->pswd);

			plog(LBRIEF, "adding %s to list of players to send message to.\n", listPlayer->name);
			addList(&toPlayers, listPlayer);
		}

		listPlayer = allocStruct(emailList);
		listPlayer->name = strdup("GM");
		listPlayer->addr = strdup(aGame->serverOptions.GMemail);
		listPlayer->pswd = strdup(aGame->serverOptions.GMpassword);
		plog(LBRIEF, "adding %s to list of players to send message to.\n", listPlayer->name);
		addList(&toPlayers, listPlayer);
	}
	else {
		/* if we are only sending to a single player, there are two
		 * possibilities: I've named the GM or I've named a player
		 */
		if (noCaseStrcmp(destination, "GM") == 0) {

		  listPlayer = allocStruct(emailList);
		  listPlayer->name = strdup("GM");
		  listPlayer->addr = strdup(aGame->serverOptions.GMemail);
		  listPlayer->pswd = strdup(aGame->serverOptions.GMpassword);
		  plog(LBRIEF, "adding %s to list of players to send message to.\n", listPlayer->name);
		  addList(&toPlayers, listPlayer);
		}
		else {
			if ((itPlayer =
				 findElement(player, aGame->players, destination)) == NULL) {
				setHeader(anEnvelope, MAILHEADER_SUBJECT,
						  "[GNG] Major Trouble");
				generateErrorMessage(RES_NODESTINATION, aGame, raceName,
									 theTurnNumber, confirm);
				result |= eMail(aGame, anEnvelope, confirmName);
				plog(LBRIEF, "can't find player mail is directed to.\n");
				return result;
			}

			/* is the relay to a dead player? */
			if (itPlayer->flags & F_DEAD) {
				setHeader(anEnvelope, MAILHEADER_SUBJECT,
						  "[GNG] Major Trouble");
				generateErrorMessage(RES_DEAD_PLAYER, aGame, raceName,
									 theTurnNumber, confirm);
				result |= eMail(aGame, anEnvelope, confirmName);
				plog(LBRIEF, "cmd_relay: relay is to a dead player.\n");
				return result;
			}


			listPlayer = allocStruct(emailList);
			listPlayer->name = strdup(itPlayer->name);
			listPlayer->addr = strdup(itPlayer->addr);
			listPlayer->pswd = strdup(itPlayer->pswd);
			plog(LBRIEF, "adding %s to list of players to send message to.\n", listPlayer->name);
			addList(&toPlayers, listPlayer);
		}
	}
				

	for (listPlayer = toPlayers; listPlayer; listPlayer = listPlayer->next) {
	  plog(LBRIEF, "relayMessage(aGame, %s, %s, %s)\n", raceName, fromPlayer->name, listPlayer->name);

		result = relayMessage(aGame, raceName, fromPlayer, listPlayer);
					
		if (result == 0) {
			setHeader(anEnvelope, MAILHEADER_SUBJECT, "[GNG] message sent");
			fprintf(confirm, "Message has been sent to %s.\n", itPlayer->name);
		}
		else {
			setHeader(anEnvelope, MAILHEADER_SUBJECT,
					  "[GNG] message not sent");
			fprintf(confirm, "Due to a server error the message was not "
					"sent to %s!\nPlease contact your Game Master.\n",
					itPlayer->name);
		}
	}
	
			
	fprintf(confirm, "\n\n%s\n", vcid);
	fclose(confirm);
	result |= eMail(aGame, anEnvelope, confirmName);
	if (destination)
		free(destination);
	if (raceName)
		free(raceName);
	if (password)
		free(password);
	destroyEnvelope(anEnvelope);
	plog(LBRIEF, "confirmName: \"%s\"\n", confirmName);

	result |= ssystem("rm %s", confirmName);
	result = result ? EXIT_FAILURE : EXIT_SUCCESS;

	return result;
}
