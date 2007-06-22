#include "galaxyng.h"

/****f* CLI/CMD_check
 * NAME
 *   CMD_check -- check incoming orders.
 * FUNCTION
 *   Check incoming orders and create a forecast of the
 *   situation at the next turn.
 * INPUTS
 *   Orders come in via stdin.
 * RESULTS
 *   Forecast is is send to stdout.
 *   A log is kept of all order processing in log/orders_processed.txt
 * SOURCE
 */

int
CMD_check( int argc, char **argv )
{
    int result;
    char *logName;

    result = FALSE;

    logName = createString( "%s/log/orders_processed.txt", galaxynghome );
    openLog( logName, "a" );
    free( logName );

    plogtime( LBRIEF );
    if ( argc != 4 ) {
        /* Not enough parameters */
        return EXIT_FAILURE;
    } else {
        game*   aGame   = NULL;
        char *gameName = argv[ 2 ];
        char *raceName = argv[ 3 ];

        if ( ( aGame = loadgame( gameName, LG_CURRENT_TURN ) ) == NULL ) {
            /* Can't load game */
            return EXIT_FAILURE;
        } else {
            player* aPlayer = findElement( player, ( aGame )->players, raceName );
            if ( aPlayer == NULL  ) {
                /* Can't find player */
                return EXIT_FAILURE;
            } else {
                strlist *s;
                loadNGConfig( aGame );
                /* Game loaded, player found, ready to check orders. */

                getLine( stdin );
                for ( ; !feof( stdin ); ) {
                    s = makestrlist( lineBuffer );
                    addList( &( aPlayer->orders ), s );
                    getLine( stdin );
                }

                checkOrders( aGame, raceName, stdout, F_TXTREPORT );
            }
            freegame( aGame );
        }
    }
    return EXIT_SUCCESS;
}

