#include "galaxyng.h"

/****f* CLI/CMD_test
 * NAME
 *   CMD_test -- check the integrity of a game.
 * FUNCTION
 *   Check if a GAME is OK by running checkIntegrity() on it.
 ******
 */

int CMD_test( int argc, char **argv ) {
    game *aGame;
    int result;
    int turn;

    printf( "Loading game...\n" );
    turn = LG_CURRENT_TURN;

    if ( ( aGame = loadgame( argv[2], LG_CURRENT_TURN ) ) ) {
        checkIntegrity( aGame );
        dumpPlanets( aGame->planets );
        dumpPlayers( aGame->players );
        printf( "Game is OK\n" );
        result = EXIT_SUCCESS;
    }
	else {
        printf( "Game is NOT OK\n" );   /* This is wrong! the game did not
										 * load.. it still might be ok! */
        result = EXIT_FAILURE;
    }
	
    return result;
}
