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

int
CMD_report( int argc, char **argv )
{
    int result;                 /* return value of the function */
    char *returnAddress;        /* where the mail will be returned to
                                   if it fails  */
    char *raceName;             /*  */
    char *password;
    char *final_orders;         /* flag if finalorders was set */
    int resNumber;              /* return value of the function */
    int theTurnNumber;
    game *aGame;
    game *aGame2;
    FILE *report;
    char *reportName;
    envelope *anEnvelope;
    player *aPlayer;
    int index;


    DBUG_ENTER( "CMD_report" );

    /* append to the log for tracking what happens */
    openLog( "a", "%s/log/report.txt", galaxynghome );

    plogtime( LBRIEF, NULL );
    result = EXIT_FAILURE;

    /* check to ensure that we were called correctly */
    if ( argc < 2 ) {
        usage(  );
        plog( LBRIEF, "incorrect argument count\n" );
        return EXIT_FAILURE;
    }

    /* are the orders valid? */
    resNumber = areValidOrders( stdin, &aGame, &raceName, &password,
                                &final_orders, &theTurnNumber );

    switch ( resNumber ) {
    case RES_OK:
    case RES_TURNRAN:
        reportName = createString( "%s/%s_report_copy", tempdir, raceName );
        if ( ( report = fopen( reportName, "w" ) ) == NULL ) {
            plog( LBRIEF, "Could not open \"%s\" for report copy\n",
                  reportName );
            free( reportName );
            return EXIT_FAILURE;
        }
        break;

    case RES_TURNFUTURE:
        setHeader( anEnvelope, MAILHEADER_SUBJECT, "[GNG] Major Trouble" );
        fprintf( report, "You can not request a report for the next turn\n" );
        fprintf( report,
                 "or any following turns,"
                 " I can not see into the future!\n" );
        return EXIT_FAILURE;

    default:
        plog( LBRIEF, "invalid request (%d)\n", resNumber );
        setHeader( anEnvelope, MAILHEADER_SUBJECT, "[GNG] Major Trouble" );
        generateErrorMessage( resNumber, aGame, raceName, theTurnNumber,
                              report );
        return EXIT_FAILURE;
    }

    anEnvelope = createEnvelope(  );

    setHeader( anEnvelope, MAILHEADER_TO, "%s", returnAddress );
    plog( LBRIEF, "Report request from %s.\n", returnAddress );


    theTurnNumber = theTurnNumber < 0 ? 0 : theTurnNumber - 1;
    aGame2 = loadgame( aGame->name, theTurnNumber );

    if ( aGame2 == NULL ) {
        setHeader( anEnvelope, MAILHEADER_SUBJECT,
                   "[GNG] Copy of turn report request." );
        fprintf( report,
                 "\n\nThe turn you requested is no longer available...\n" );
        fclose( report );
        result = eMail( aGame, anEnvelope, reportName );
        destroyEnvelope( anEnvelope );
        result |= ssystem( "rm %s", reportName );
        return result ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    loadNGConfig( aGame2 );
    setHeader( anEnvelope, MAILHEADER_SUBJECT,
               "[GNG] Copy of turn %d report", theTurnNumber );

    if ( theTurnNumber > 0 ) {  /* Rerun the turn */
        char *ordersName;

        ordersName =
            createString( "%s/orders/%s/%d.all",
                          galaxynghome, aGame2->name, theTurnNumber );
        runTurn( aGame2, ordersName );
        free( ordersName );
    }

    /* Translate the current race name into the name used during
     * the turn that is requested */
    aPlayer = findElement( player, aGame->players, raceName );

    index = ptonum( aGame->players, aPlayer );
    aPlayer = numtop( aGame2->players, index );

    if ( theTurnNumber == 0 )
        aPlayer->pswdstate = 1;
    highScoreList( aGame2 );
    createTurnReport( aGame2, aPlayer, report, 0 );


    fclose( report );
    result = eMail( aGame, anEnvelope, reportName );
    destroyEnvelope( anEnvelope );
    result |= ssystem( "rm %s", reportName );
    result = ( result ) ? EXIT_FAILURE : EXIT_SUCCESS;
    if ( raceName )
        free( raceName );
    if ( password )
        free( password );
    free( reportName );

    closeLog(  );

    return result;
}
