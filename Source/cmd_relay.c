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
	int result;
	char *logName;
	int mode;
	
	result = EXIT_FAILURE;
	logName = createString( "%s/log/orders_processed.txt", galaxynghome );
	openLog( logName, "a" );
	free( logName );
	plogtime( LBRIEF );
	if ( argc >= 2 ) {
		char *confirmName;
		int resNumber;
		game *aGame;
		FILE *confirm;
		
		confirmName = createString( "%s/NGconfirm", tempdir );
		if ( ( confirm = GOS_fopen( confirmName, "w" ) ) ) {
			player* toPlayer;
			player* fromPlayer;
			char* destination;
			char* returnAddress;
			char* raceName;
			char* password;
			char* final_orders;
			int theTurnNumber = LG_CURRENT_TURN;
			envelope *anEnvelope;
			
			anEnvelope = createEnvelope(  );
			returnAddress = getReturnAddress( stdin );
			setHeader( anEnvelope, MAILHEADER_TO, "%s", returnAddress );
			destination = getDestination( stdin );
			raceName = NULL;
			password = NULL;
			final_orders = NULL;
			aGame = NULL;
			resNumber = areValidOrders( stdin, &aGame, &raceName,
										&password, &final_orders,
										&theTurnNumber );
			
			fprintf(confirm, "Relay for game \"%s\"\n", aGame->name);
			
			if (noCaseStrcmp(raceName, "GM") == 0) {
				fromPlayer = (player*)malloc(sizeof (player));
				fromPlayer->name = strdup("GM");
				fromPlayer->addr = strdup(aGame->serverOptions.GMemail);
				fromPlayer->pswd = strdup(aGame->serverOptions.GMpassword);
			}
			else 
				fromPlayer = findElement(player, aGame->players, raceName);
			
			if ( destination == NULL ) {
				resNumber = RES_NODESTINATION;
			}
			
			if ( resNumber == RES_OK ) {
				if (noCaseStrcmp(destination, aGame->name) == 0) {
					mode = ALL_PLAYERS;
				}
				else {
					mode = SINGLE_PLAYER;
				}
				
				for (toPlayer = aGame->players;
					 toPlayer;
					 toPlayer = toPlayer->next) {
					
					/* skip dead players, they dislike getting email
					 *about the game :)
					 */
					
					if (toPlayer->flags & F_DEAD)
						continue;
					
					if (mode == SINGLE_PLAYER) {
						if (noCaseStrcmp(destination, "GM") == 0) {
							toPlayer = (player*)malloc(sizeof(player));
							toPlayer->name = strdup("GM");
							toPlayer->addr = strdup(aGame->serverOptions.GMemail);
							toPlayer->pswd = strdup(aGame->serverOptions.GMpassword);
						}
						else {
							toPlayer = findElement( player, aGame->players,
													destination );
							
							
							if ( toPlayer == NULL ) {
								resNumber = RES_DESTINATION;
								break;
							}
						}
					}
					
					result = 0;
					
					result |= relayMessage( aGame, raceName,
											fromPlayer, toPlayer );
					
					if ( result == 0 ) {
						setHeader( anEnvelope, MAILHEADER_SUBJECT,
								   "[GNG] message sent" );
						fprintf( confirm, "Message has been sent to %s.\n",
								 toPlayer->name );
					} else {
						setHeader( anEnvelope, MAILHEADER_SUBJECT,
								   "[GNG] message not sent" );
						fprintf( confirm,
								 "Due to a server error the message was not send!\n"
								 "Please contact your Game Master.\n" );
					}
					if (mode == SINGLE_PLAYER)
						break;
				}
			} else {
				setHeader( anEnvelope, MAILHEADER_SUBJECT,
						   "[GNG] Major Trouble." );
				generateErrorMessage( resNumber, aGame, raceName,
									  theTurnNumber, confirm );
			}
			
			if (mode == ALL_PLAYERS) {
				toPlayer = (player*)malloc(sizeof(player));
				toPlayer->name = strdup("GM");
				toPlayer->addr = strdup(aGame->serverOptions.GMemail);
				toPlayer->pswd = strdup(aGame->serverOptions.GMpassword);
				
				result |= relayMessage( aGame, raceName,
										fromPlayer, toPlayer );
				
				if ( result == 0 ) {
					setHeader( anEnvelope, MAILHEADER_SUBJECT,
							   "[GNG] message sent" );
					fprintf( confirm, "Message has been sent to %s.\n",
							 toPlayer->name );
				}
				free(toPlayer);
			}
			
			fprintf( confirm, "\n\n%s\n", vcid );
			fclose( confirm );
			result |= eMail( aGame, anEnvelope, confirmName );
			if ( destination )
				free( destination );
			if ( raceName )
				free( raceName );
			if ( password )
				free( password );
			destroyEnvelope( anEnvelope );
			result |= ssystem( "rm %s", confirmName );
			result = ( result ) ? EXIT_FAILURE : EXIT_SUCCESS;
		}
		else {
			fprintf( stderr, "Can't open \"%s\".\n", confirmName );
		}
		free( confirmName );
	}
	else {
		usage(  );
	}
	closeLog(  );
	return result;
}
