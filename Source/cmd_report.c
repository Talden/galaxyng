#include "galaxyng.h"

/****f* CLI/CMD_report
 * NAME 
 *   CMD_report -- create a copy of a turn report.
 * SYNOPSIS
 *   ./galaxyng -report <gamename> <player> <turnnumber>
 *   int CMD_report(int argc, char **argv) 
 * FUNCTION
 *   Recreate a turn report of a given turn. 
 *   Report is send to stdout.
 * BUGS
 *   Does not send XML nor machine reports.
 * SOURCE
 */

int
CMD_report( int argc, char **argv )
{
    char *logName = createString( "%s/log/orders_processed.txt", galaxynghome );

    openLog( logName, "a" );
    free( logName );

    plogtime( LBRIEF );

    if ( argc != 5 ) {
        /* Not enough parameters */
        return EXIT_FAILURE;
    } else {
        game*   aGame   = NULL;
        char *gameName = argv[ 2 ];
        char *raceName = argv[ 3 ];
        int theTurnNumber = atoi( argv[ 4 ] );

        if ( ( aGame = loadgame( gameName, LG_CURRENT_TURN ) ) == NULL ) {
            /* Can't load game */
            return EXIT_FAILURE;
        } else {
            player* aPlayer = findElement( player, ( aGame )->players, raceName );
            if ( aPlayer == NULL  ) {
                /* Can't find player */
                return EXIT_FAILURE;
            } else {
                /* Game loaded, player found, ready to check orders. */
                game *aGame2;

                if ( theTurnNumber > 0 ) {
                    aGame2 = loadgame( aGame->name, theTurnNumber - 1 );
                } else {
                    aGame2 = loadgame( aGame->name, 0 );
                }

                if ( aGame2 == NULL ) {
                    /* Turn does not load */
                    return EXIT_FAILURE;
                } else {
                    player *aPlayer;
                    int index;

                    loadNGConfig( aGame2 );

                    if ( theTurnNumber > 0 ) {      /* Rerun the turn */
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
                    aPlayer = findElement( player, aGame->players, raceName );

                    index = ptonum( aGame->players, aPlayer );
                    aPlayer = numtop( aGame2->players, index );

                    if ( theTurnNumber == 0 ) {
                        aPlayer->pswdstate = 1;
                    }
                    highScoreList( aGame2 );
                    createTurnReport( aGame2, aPlayer, stdout, 0 );

                    freegame( aGame2 );
                }
            }
            freegame( aGame );
        }
    }
    closeLog(  );
    return EXIT_SUCCESS;
}


