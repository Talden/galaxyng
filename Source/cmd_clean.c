#include "galaxyng.h"

int
CMD_clean( int argc, char **argv )
{
    int result;

    game *aGame;
    int turn;

    result = EXIT_FAILURE;
    openLog( "w", "%s/log/%s", galaxynghome, argv[2] );

    plogtime( LPART, "CMD_clean" );
    plog( LPART, "Trying to clean Game \"%s\".\n", argv[2] );

    aGame = NULL;
    turn = LG_CURRENT_TURN;

    if ( ( aGame = loadgame( argv[2], turn ) ) ) {
        loadNGConfig( aGame );
        cleanDeadPlayers( aGame );
        aGame->turn--;          /* hack to force it to save to the current game file */
        savegame( aGame );
    }

    return EXIT_SUCCESS;
}
