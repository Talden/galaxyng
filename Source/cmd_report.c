#include "galaxyng.h"

/****f* CLI/CMD_report
 * NAME 
 *   CMD_report -- send a copy of a turn report.
 * SYNOPSIS
 *   ./galaxyng -check < file_with_email
 *   int CMD_report(int argc, char **argv) 
 * FUNCTION
 *   Recreate a turn report of a given turn. Send it to the player
 *   that requested it.
 * BUGS
 *   Does not send XML nor machine reports.
 * SOURCE
 */

int CMD_report( int argc, char **argv ) {
    int result;
    char *logName;

    logName = createString( "%s/log/orders_processed.txt", galaxynghome );
    openLog( logName, "a" );
    free( logName );

    plogtime( LBRIEF );
    result = EXIT_FAILURE;
    if ( argc >= 2 ) {
        char* returnAddress;
		char* raceName;
		char* password;
		char* final_orders;
        int resNumber, theTurnNumber;
        game* aGame;
        FILE* report;
        char* reportName;

        reportName = createString( "%s/temp_report_copy", tempdir );
        if ( ( report = GOS_fopen( reportName, "w" ) ) ) {
            envelope *anEnvelope;

            anEnvelope = createEnvelope(  );
            returnAddress = getReturnAddress( stdin );
            setHeader( anEnvelope, MAILHEADER_TO, "%s", returnAddress );
	    setHeader(anEnvelope, MAILHEADER_REPLYTO,
		      aGame->serverOptions.ReplyTo);
            plog( LBRIEF, "Report request from %s.\n", returnAddress );
            theTurnNumber = getTurnNumber( stdin );
            raceName = NULL;
            password = NULL;
			final_orders = NULL;
            aGame = NULL;
            resNumber =
                areValidOrders( stdin, &aGame, &raceName, &password,
                                &final_orders, &theTurnNumber );
            if ( ( resNumber == RES_TURNRAN ) ||
                 ( ( resNumber == RES_OK ) &&
				   ( theTurnNumber == LG_CURRENT_TURN ) ) ) {
                game *aGame2;

                if ( theTurnNumber > 0 ) {
                    aGame2 = loadgame( aGame->name, theTurnNumber - 1 );
                }
				else if ( theTurnNumber == LG_CURRENT_TURN ) {
                    theTurnNumber = aGame->turn;
                    aGame2 = loadgame( aGame->name, theTurnNumber - 1 );
                }
				else {
                    aGame2 = loadgame( aGame->name, 0 );
                }
				
                if ( aGame2 ) {
                    player *aPlayer;
                    int index;

                    loadNGConfig( aGame2 );
                    setHeader( anEnvelope, MAILHEADER_SUBJECT,
                               "[GNG] Copy of turn %d report",
                               theTurnNumber );
                    if ( theTurnNumber > 0 ) {  /* Rerun the turn */
                        char *ordersName;

                        ordersName =
                            createString( "%s/orders/%s/%d.all",
                                          galaxynghome, aGame2->name,
                                          theTurnNumber );
                        runTurn( aGame2, ordersName );
                        free( ordersName );
                    }
                    /* Translate the current race name into the name used
		       during the turn that is requested
		    */
                    aPlayer =
                        findElement( player, aGame->players, raceName );

                    index = ptonum( aGame->players, aPlayer );
                    aPlayer = numtop( aGame2->players, index );

                    if ( theTurnNumber == 0 )
                        aPlayer->pswdstate = 1;
                    highScoreList( aGame2 );
                    createTurnReport( aGame2, aPlayer, report, 0 );
                }
				else {
                    setHeader( anEnvelope, MAILHEADER_SUBJECT,
                               "[GNG] Copy of turn report request." );
                    fprintf( report,
                             "\n\nThe turn you requested is no longer available...\n" );
                }
            }
			else if ( resNumber == RES_OK ) {
                setHeader( anEnvelope, MAILHEADER_SUBJECT,
                           "[GNG] Major Trouble" );
                fprintf( report,
                         "You can not request a report for the next turn\n" );
                fprintf( report,
                         "or any following turns,"
                         " I can not see into the future!\n" );
            }
			else {
                setHeader( anEnvelope, MAILHEADER_SUBJECT,
                           "[GNG] Major Trouble" );
                generateErrorMessage( resNumber, aGame, raceName,
                                      theTurnNumber, report );
            }
			
            fclose( report );
            result = eMail( aGame, anEnvelope, reportName );
            destroyEnvelope( anEnvelope );
            result |= ssystem( "rm %s", reportName );
            result = ( result ) ? EXIT_FAILURE : EXIT_SUCCESS;
            if ( raceName )
                free( raceName );
            if ( password )
                free( password );
        }
		else {
            fprintf( stderr, "Can't open \"%s\"\n", reportName );
        }
        free( reportName );
    }
	else {
        usage(  );
    }
    closeLog(  );
	
    return result;
}
