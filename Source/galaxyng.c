/****h* Galaxy/GalaxyNG
*  NAME  
*    galaxyng -- Server for the play-by-email game GalaxyNG
*  SYNOPSIS
*    galaxyng [command [options]]
*  FUNCTION
*    Checks incoming orders, runs the turn, and sends out the turn
*    reports. 
*
*    The code is divided into a number of modules:
*     List     -- (list.c list.h) functions for manipulating lists.
*     Util     -- (util.c util.h) frequently used functions.
*     Phase    -- (phase.c phase.h) code for the various phases in the game.
*     Process  -- (process.c process.h ) code for order checking, 
*                 order processing, and running a turn.
*     Report   -- (report.c report.h) 
*                 Code to generate the turn reports.
*     Battle   -- (battle.c battle.h) code that performs the battles.
*     Loadgame -- saves a turn to disk
*     Savegame -- load a turn from disk
*     GalaxyNG -- glues it all together.
*  AUTHOR
*    Created by:  
*    o Frans Slothouber
*    o Christophe  Barbier 
*    o Jacco van Weert 
*    o Tommy Lindqvist       
*    o Rogerio Fung
*    o Ken Weinert
*
*    This code contains parts of the the orginal Galaxy code which was
*    created by Russell Wallace (RWALLACE@vax1.tcd.ie), and updated by the
*    Galaxy PBeM Development Group which include 
*    o Russell Wallace (RWALLACE@vax1.tcd.ie) 
*    o Tim Myers (tmyers@unlinfo.unl.edu), 
*    o Robert Stone (stone@athena.cs.uga.edu), 
*    o Mayan Moudgill (moudgill@cs.cornell.edu), 
*    o Graeme Griffiths (graeme@abekrd.co.uk), 
*    o K Pankhurst (k.pankhurst@ic.ac.uk).
*  CREATION DATE
*    4-Jan-1997
*  COPYRIGHT
*    GPL  see ../COPYING
*  NOTES
*    This is not the most pretty code around. It is a product of many
*    years and many people. The code hosts a lot of global variables
*    and many not very descriptively named function. The code is
*    pretty stable however.
*  BUGS
*    See the sourceforge page at
*       http://sourceforge.net/projects/galaxyng/
**********
*/

#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include "galaxy.h"
#include "util.h"
#include "process.h"
#include "create.h"
#include "loadgame.h"
#include "savegame.h"
#include "report.h"
#include "selftest.h"
#include "mail.h"

char *galaxyng = "$Id$";

char vcid[128];

/* Should be in galaxy.h */

#define CMD_RUN_REAL    1       /* -run will mail turn reports */
#define CMD_RUN_DUMMY   2       /* -run will save turn reports to disk */
#define CMD_CHECK_REAL  1
#define CMD_CHECK_DUMMY 2

enum
{
    CMD_DUMP_MAP = 1, CMD_DUMP_LASTORDERS, CMD_DUMP_PLAYERS,
    CMD_DUMP_PSCORE, CMD_DUMP_HALL, CMD_DUMP_MAILHEADER,
    CMD_DUMP_TEAM_INFO, CMD_DUMP_TEAM_REPORT_NAMES, CMD_DUMP_MAP_GNUPLOT
};

int CMD_create( int argc, char **argv );
int CMD_mail0( int argc, char **argv, int kind );
int CMD_run( int argc, char **argv, int kind );
int CMD_check( int argc, char **argv, int kind );
#if 0
int CMD_checkFile( int argc, char **argv, int kind );
#endif
int CMD_report( int argc, char **argv );
int CMD_score( int argc, char **argv );
int CMD_graph( int argc, char **argv );
int CMD_dump( int argc, char **argv, int kind );
int CMD_test( int argc, char **argv );
int CMD_relay( int argc, char **argv );
int CMD_template( int argc, char **argv );
int CMD_selftest(  );
int CMD_battletest( int argc, char **argv );
#if defined(DRAW_INFLUENCE_MAP)
int CMD_influence( int argc, char **argv );
#endif
int checkTime( game *aGame );
int relayMessage( game *aGame, char *nationName, player *to );


/****h* GalaxyNG/CLI
 * FUNCTION
 *   Function for the command line interface of GalaxyNG.
 *****
 * This stuff will move to a seperate file later on.
 */

/****f* CLI/main
 * NAME
 *   main -- the start of it all.
 * RESULT
 *   Reports any errors that occur back to the environment.
 * SOURCE
 */

#ifndef ROBOTESTER
int
main( int argc, char **argv )
{
    char *value;
    int result;

    /* Some initializations */
    resetErnie( 197162622 );

    logLevel = LBRIEF;

    sprintf( vcid, "GalaxyNG release-%d-%d, %s.",
             GNG_MAJOR, GNG_MINOR, GNG_DATE );

    /* This should be a function */
    if ( ( value = getenv( "GALAXYNGHOME" ) ) ) {
        galaxynghome = strdup( value );
    } else if ( ( value = getenv( "HOME" ) ) ) {
        sprintf( lineBuffer, "%s/Games", value );
        galaxynghome = strdup( lineBuffer );
    } else {
        galaxynghome =
            strdup( "/please/set/your/HOME/or/GALAXYNGHOME/variable" );
    }

#ifdef WIN32
    /* This should be a function */
    if ( ( value = getenv( "TEMP" ) ) ) {
        tempdir = strdup( value );
    } else if ( ( value = getenv( "TMP" ) ) ) {
        tempdir = strdup( value );
    } else {
        tempdir = strdup( "c:/temp" );
    }
#else
    tempdir = strdup( "/tmp" );
#endif

    if ( ( value = getenv( "GNG_LOG_LEVEL" ) ) ) {
        if ( strcasecmp( value, "full" ) == 0 )
            logLevel = LFULL;
        else if ( strcasecmp( value, "part" ) == 0 )
            logLevel = LPART;
        else if ( strcasecmp( value, "brief" ) == 0 )
            logLevel = LBRIEF;
        else if ( strcasecmp( value, "none" ) == 0 )
            logLevel = LNONE;
        else
            logLevel = LBRIEF;
    }

    if ( argc <= 1 ) {
        usage(  );
    } else if ( strstr( argv[1], "create" ) ) {
        result = CMD_create( argc, argv );
    } else if ( strstr( argv[1], "dummymail0" ) ) {
        result = CMD_mail0( argc, argv, CMD_CHECK_DUMMY );
    } else if ( strstr( argv[1], "mail0" ) ) {
        result = CMD_mail0( argc, argv, CMD_CHECK_REAL );
    }
#if 0
    else if ( strstr( argv[1], "filecheck" ) ) {
        result = CMD_checkFile( argc, argv, CMD_CHECK_DUMMY );
    }
#endif
    else if ( strstr( argv[1], "dummycheck" ) ) {
        result = CMD_check( argc, argv, CMD_CHECK_DUMMY );
    } else if ( strstr( argv[1], "check" ) ) {
        result = CMD_check( argc, argv, CMD_CHECK_REAL );
    } else if ( strstr( argv[1], "dummyrun" ) ) {
        result = CMD_run( argc, argv, CMD_RUN_DUMMY );
    } else if ( strstr( argv[1], "run" ) ) {
        result = CMD_run( argc, argv, CMD_RUN_REAL );
    } else if ( strstr( argv[1], "selftest" ) ) {       /* experimental */
        result = CMD_selftest(  );
    } else if ( strstr( argv[1], "battletest" ) ) {     /* experimental */
        result = CMD_battletest( argc, argv );
    } else if ( strstr( argv[1], "test" ) ) {   /* experimental */
        result = CMD_test( argc, argv );
    } else if ( strstr( argv[1], "report" ) ) {
        result = CMD_report( argc, argv );
    } else if ( strstr( argv[1], "relay" ) ) {
        result = CMD_relay( argc, argv );
    } else if ( strstr( argv[1], "pscore" ) ) { /* experimental */
        result = CMD_dump( argc, argv, CMD_DUMP_PSCORE );
    } else if ( strstr( argv[1], "score" ) ) {
        result = CMD_score( argc, argv );
    } else if ( strstr( argv[1], "graph" ) ) {  /* experimental */
        result = CMD_graph( argc, argv );
    } else if ( strstr( argv[1], "template" ) ) {
        result = CMD_template( argc, argv );
    }
#if defined(DRAW_INFLUENCE_MAP)
    else if ( strstr( argv[1], "influence" ) ) {
        result = CMD_influence( argc, argv );
    }
#endif
    else if ( strstr( argv[1], "map" ) ) {
        result = CMD_dump( argc, argv, CMD_DUMP_MAP );
    } else if ( strstr( argv[1], "hall" ) ) {
        result = CMD_dump( argc, argv, CMD_DUMP_HALL );
    } else if ( strstr( argv[1], "lastorders" ) ) {
        result = CMD_dump( argc, argv, CMD_DUMP_LASTORDERS );
    } else if ( strstr( argv[1], "players" ) ) {
        result = CMD_dump( argc, argv, CMD_DUMP_PLAYERS );
    } else if ( strstr( argv[1], "toall" ) ) {
        result = CMD_dump( argc, argv, CMD_DUMP_MAILHEADER );
    } else if ( strstr( argv[1], "teaminfo" ) ) {
        result = CMD_dump( argc, argv, CMD_DUMP_TEAM_INFO );
    } else if ( strstr( argv[1], "teamdump" ) ) {
        result = CMD_dump( argc, argv, CMD_DUMP_TEAM_REPORT_NAMES );
    } else {
        usage(  );
    }
    return result;
}
#endif

/******/


/****f* CLI/CMD_template
 * NAME
 *   CMD_template -- Create a template .glx file that the GM can edit.
 * SYNOPSIS
 *   ./galaxyng <name> <number of players>
 * FUNCTION
 *   Creates a template .glx file.
 *   All parameters are given some sensible default values.
 *
 *   The number of players is used to determine the size of the galaxy,
 *   using the following formule
 *      42 * ceil (sqrt(number of players))
 *   For games with very few players this size is sometimes too small.
 * SOURCE
 */

int
CMD_template( int argc, char **argv )
{
    int result = EXIT_FAILURE;

    if ( argc == 4 ) {
        FILE *glxfile;
        char *glxname;
        int numberOfPlayers;

        glxname = createString( "%s.glx", argv[2] );
        numberOfPlayers = atoi( argv[3] );
        if ( ( glxfile = GOS_fopen( glxname, "w" ) ) ) {
            int i;
            int gsize;

            fprintf( glxfile, "\n\nname %s\n\n", argv[2] );
            gsize =
                ( int ) ( 42.0 * ceil( sqrt( ( double ) numberOfPlayers ) ) );
            gsize /= 10;
            gsize *= 10;
            fprintf( glxfile,
                     "; The following size is only approximately right.\n"
                     "; You probably want to experiment with different sizes to get a galaxy\n"
                     "; that looks right. It should not be too crowded nor too sparse.\n\n" );
            fprintf( glxfile, "size %d\n", gsize );
            fprintf( glxfile,
                     "\n"
                     "; The engine will make sure that distance between any of primary home\n"
                     "; planets is atleast 30.0 light years.\n"
                     "\n" "nation_spacing 30.0\n" "\n" );
            fprintf( glxfile,
                     "; The sizes of the core home planets for each nation.\n"
                     "; The following would give each nation 3 homeplanets of sizes\n"
                     "; 1000 250 350. The first one is the primary home planet.\n"
                     "; You have to define these before any of the player definitions.\n"
                     "\n" "core_sizes 1000 250 350\n" "\n" );
            fprintf( glxfile,
                     "; Within a radius [2,r] from the primary home world the engine allocates\n"
                     "; a number of empty planets for the nation to colonize.\n"
                     "; The following two parameters define how many there are per nation,\n"
                     "; and in within what radius. A number between 4 and 10 and\n"
                     "; a radius of  nation_spacing/2.0  is a good guess.\n"
                     "\n" );
            fprintf( glxfile,
                     "empty_planets 6\n"
                     "empty_radius 15\n"
                     "\n"
                     "; It is possible to add a number of 'stuff' planets. These are useless\n"
                     "; planets, all of size 50 or less, that are use to fill up the empty\n"
                     "; space between the home worlds. They make it possible for a players to\n"
                     "; approach (attack) other players by different routes. The following\n"
                     "; parameter specifies how many there are per nation.\n"
                     "\n" );
            fprintf( glxfile,
                     "stuff_planets 8\n"
                     ";\n"
                     "; The list of the players, you can add here the mail address\n"
                     "; of each player that enrolled in your game.\n" ";\n"
                     "\n" );
            for ( i = 1; i <= numberOfPlayers; i++ ) {
                fprintf( glxfile, "player  player%d@itsaddress.somewhere\n",
                         i );
            }
            fprintf( glxfile,
                     ";\n"
                     "; You can override the core size for a player by adding the sizes.\n"
                     "; For instance the following player will get one home planet\n"
                     "; of size 1600.0\n"
                     "\n"
                     "; player player3@itsaddress.somewhere 1600.0\n"
                     "\n"
                     "; While the following player gets 3 home planets of sizes\n"
                     "; 500.0, 100.0, and 1000.0\n"
                     "\n"
                     "; player player4@itsaddress.somewhere 500.0 100.0 1000.0\n\n" );
            fprintf( glxfile,
                     "\n"
                     "; You can specify several other options :\n"
                     ";\n"
                     "; Initial tech levels\n"
                     "; In order : Drive Weapons Shields Cargo\n"
                     "; They can't be lower than 1 (don't ask why, I don't know\n"
                     "; myself why I did this).\n"
                     "; In the case below, drive will be forced to 1 by the server.\n"
                     ";\n" );
            fprintf( glxfile,
                     "; Uncomment if you want this option.\n"
                     "\n"
                     "; InitialTechLevels 0.42 1 3.21 1.24\n"
                     ";\n"
                     "; Full bombing, when bombed planets are completely bombed.\n"
                     "; All population, industry, capital, colonists, and materials are gone.\n"
                     "; Normally the population and industry is reduced to 25%% of its\n"
                     "; original value.\n" ";\n" );
            fprintf( glxfile,
                     "; Uncomment if you want this option.\n"
                     "\n"
                     "; FullBombing\n"
                     "\n"
                     "; If keepproduction is set, the production points spent\n"
                     "; on the previous product are preserved, otherwise all points are lost\n"
                     ";\n" "; Uncomment if you want this option.\n" "\n" );
            fprintf( glxfile,
                     "; KeepProduction\n"
                     "\n"
                     ";\n"
                     "; Don't remove idle nations from a game.\n"
                     "; Normally if players do not send in orders for a couple of turns\n"
                     "; their nation self destructs.\n"
                     ";\n" "; Uncomment if you want this option.\n" "\n" );
            fprintf( glxfile,
                     "; DontDropDead\n"
                     "\n"
                     ";\n"
                     "; Sometimes, if you have enough disk space, it is nice to get a copy\n"
                     "; of turn reports that are send out to the players.\n"
                     "; If you uncomment the following parameter, a copy of each turn report\n"
                     "; that is send out is stored in reports/<game name>/\n"
                     ";\n" "; Uncomment if you want this option.\n" "\n" );
            fprintf( glxfile,
                     "; SaveReportCopy\n"
                     "; The galaxy can be (roughly) mapped on a sphere\n"
                     "; This way, the gap between x (or y) coordinates of two\n"
                     "; planets is computed with borders lines crossing, and reappearing\n"
                     "; on the other side.\n"
                     ";\n"
                     "; Uncomment if you want this option.\n"
                     "\n" "; sphericalgalaxy\n" "\n" );
            fclose( glxfile );
        } else {
            fprintf( stderr, "Can't open \"%s\".\n", glxname );
        }
        printf( "Created the file \"%s\".\n", glxname );
        free( glxname );
    } else {
        usage(  );
    }
    return result;
}

/************/


/****f* CLI/CMD_run
 * NAME
 *   CMD_run -- run turn and send turn reports
 * SYNOPSIS
 *   ./galaxyng -run <game name> <file with all orders>
 * FUNCTION
 *   Run an turn, Compute the highscore list, and send the turn reports 
 *   to all players. The GM is send a status report. If the option
 *   SaveReportCopy is specified in the .galaxyngrc file, a copy of each
 *   turn report is also saved in reports/
 *
 *   This function is also run for: 
 *     ./galaxyng -dummyrun <game name> <file with all orders>
 *   In this case the run is a dummy run, and the turn reports are stored 
 *   in reports/. Nothing is mailed. This is used to debug the server code.
 * 
 * OUTPUT
 *   Turn reports are send out to the players and the turn is saved
 *   to disk. The GM is sent a status report. A log can be found in
 *   log/<game name>.
 * DIAGNOSTICS
 *   Message to stderr in case of an error.
 *   (Game does not exist, not the right time to run the game,
 *    game structure is corrupted).
 * RESULT
 *   EXIT_FAILURE  or  EXIT_SUCCESS
 * SOURCE
 */

int
CMD_run( int argc, char **argv, int kind )
{
    int result;

    result = EXIT_FAILURE;
    if ( argc >= 4 ) {
        game *aGame;
        int turn;
        char *logName;

        logName = createString( "%s/log/%s", galaxynghome, argv[2] );
        openLog( logName, "w" );
        free( logName );

        plogtime( LPART );
        plog( LPART, "Trying to run Game \"%s\".\n", argv[2] );

        aGame = NULL;
        turn = ( argc == 4 ) ? LG_CURRENT_TURN : atoi( argv[4] ) - 1;

        if ( ( aGame = loadgame( argv[2], turn ) ) ) {
            player *aPlayer;

            loadConfig( aGame );
            if ( checkTime( aGame ) || ( kind == CMD_RUN_DUMMY ) ) {
                checkIntegrity( aGame );

                if ( runTurn( aGame, argv[3] ) ) {
                    highScoreList( aGame );
                    result = 0;
                    for ( aPlayer = aGame->players; aPlayer;
                          aPlayer = aPlayer->next ) {
                        if ( aPlayer->flags & F_TXTREPORT ) {
                            if ( kind == CMD_RUN_REAL ) {
                                result |=
                                    mailTurnReport( aGame, aPlayer,
                                                    F_TXTREPORT );
                                if ( aGame->gameOptions.
                                     gameOptions & GAME_SAVECOPY ) {
                                    saveTurnReport( aGame, aPlayer,
                                                    F_TXTREPORT );
                                }
                            } else {
                                saveTurnReport( aGame, aPlayer, F_TXTREPORT );
                            }
                        }

                        if ( aPlayer->flags & F_XMLREPORT ) {
                            if ( kind == CMD_RUN_REAL ) {
                                result |=
                                    mailTurnReport( aGame, aPlayer,
                                                    F_XMLREPORT );
                                if ( aGame->gameOptions.
                                     gameOptions & GAME_SAVECOPY ) {
                                    saveTurnReport( aGame, aPlayer,
                                                    F_XMLREPORT );
                                } else {
                                    saveTurnReport( aGame, aPlayer,
                                                    F_XMLREPORT );
                                }
                            }
                        }

                        if ( aPlayer->flags & F_MACHINEREPORT ) {
                            if ( kind == CMD_RUN_REAL ) {
                                result |=
                                    mailTurnReport( aGame, aPlayer,
                                                    F_MACHINEREPORT );
                                if ( aGame->gameOptions.
                                     gameOptions & GAME_SAVECOPY ) {
                                    saveTurnReport( aGame, aPlayer,
                                                    F_MACHINEREPORT );
                                } else {
                                    saveTurnReport( aGame, aPlayer,
                                                    F_MACHINEREPORT );
                                }
                            }
                        }
                    }
                    savegame( aGame );
                } else {
                    fprintf( stderr,
                             "The server has detected an error in the game data structure. The run\n"
                             "of the turn has been aborted. No turn reports have been sent. Please\n"
                             "contact Ken Weinert at mc@quarter-flash.com for a solution to this\n"
                             "problem.\n" );
                    result = 1;
                }
                plogtime( LPART );
                plog( LPART, "Run is completed.\n" );
                result = ( result ) ? EXIT_FAILURE : EXIT_SUCCESS;
            } else {
                plog( LBRIEF, "Error, attempt to run the game \"%s\" at the"
                      " wrong time.\n"
                      "You specified a start time of %s in your .galaxyngrc file.\n",
                      argv[2], aGame->starttime );
                fprintf( stderr,
                         "Error, attempt to run the game \"%s\" at the wrong time.\n"
                         "You specified a start time of %s in your .galaxyngrc file.\n",
                         argv[2], aGame->starttime );
            }
            closeLog(  );
            if ( kind == CMD_RUN_REAL ) {
                mailGMReport( aGame, argv[2] );
            }
            freegame( aGame );
        }

        else {
            plog( LBRIEF, "Game \"%s\" does not exist.\n", argv[2] );
            fprintf( stderr, "Game \"%s\" does not exist.\n", argv[2] );
        }
    } else {
        usage(  );
    }
    closeLog(  );
    return result;
}

/*********/


/****f* CLI/checkTime
 * NAME
 *   checkTime -- check if it is really time to run a turn.
 * SYNOPSIS
 *   int checkTime(game *aGame)
 * FUNCTION
 *   Does a sanity check to see if a turn really has to be run.  On
 *   some systems, after a reboot, crontab goes bezerk and executes a
 *   whole bunch of entries in your crontab file for no good reason.
 *   This will cause turns to be run prematurely.
 *
 *   This function checks if the current time is equal to the time a
 *   game is supposed to be run.  The GM has to put this time in a
 *   game specific .galaxyngrc file, using the starttime key.
 *
 * EXAMPLE
 *   You want to make sure a game runs at 13:00. Add the entry
 *
 *     starttime 13:00 
 *
 *   to the .galaxyngrc file. The a turn will then only run, if and
 *   only if, it is started by between 13:00 and 13:09.  Add starttime
 *   13:10, and it will only run if started between 13:10 and 13:19.
 * RESULT
 *   TRUE  -- the game is allowed to run.
 *   FALSE -- the game is not allowed to run.
 * SOURCE
 */

int
checkTime( game *aGame )
{
    int runGame;

    assert( aGame != NULL );

    runGame = FALSE;
    if ( aGame->starttime ) {
        char timeBuffer[255];
        time_t ttp;

        time( &ttp );
        strftime( timeBuffer, 255, "%H:%M", localtime( &ttp ) );
        if ( strncmp( timeBuffer, aGame->starttime, 4 ) == 0 ) {
            runGame = TRUE;
        }
    } else {
        runGame = TRUE;
    }
    return runGame;
}

/**********/


/****f* CLI/CMD_check
 * NAME
 *   CMD_check -- check incoming orders.
 * FUNCTION
 *   Check incoming orders and create a forecast of the
 *   situation at the next turn.
 * INPUTS
 *   Orders come in via stdin. The forecast is mailed directy to the player.
 *   Orders are assumed to have a proper mailheader, that is start with:
 *      To: <player>@theaddress
 *      Subject:  orders [turn number]
 *   This header can be produced with formail (see .procmailrc file).
 * RESULTS
 *   Orders are stored in
 *   $GALAXYNGHOME/orders/<game name>/<nation name>.<turn number>
 *   Forecast is mailed to the player.
 *   A log is kept of all order processing in log/orders_processed.txt
 * SOURCE
 */

#if FS_NEW_FORECAST
int mail_XML_Forecast( game* aGame, player *aPlayer, envelope *anEnvelope,
       char* nationName, int kind )
{
    int result = FALSE;
    FILE *forecast;
    char* forecastName = 
        createString( "%s/NG_XML_%d_forecast", tempdir, getpid(  ) );

    if ( ( forecast = GOS_fopen( forecastName, "w" ) ) == NULL ) {
        plog( LBRIEF, "Could not open %s for forecasting\n", forecastName );
        fprintf( stderr, "Could not open %s for forecasting\n", forecastName );
        return EXIT_FAILURE;
    }

    setHeader( anEnvelope, MAILHEADER_SUBJECT,
            "Galaxy HQ, %s turn %d XML forecast for %s",
            aGame->name, ( aGame->turn ) + 1, nationName );

    ( aGame->turn )++;
    fprintf( stderr, "Creating XML report, %s:%d\n", nationName, kind );
    report_xml( aGame, aPlayer, forecast, Forecast );
    ( aGame->turn )--;
    fclose( forecast );

    if ( kind == CMD_CHECK_REAL ) {
        plog( LBRIEF, "mailing XML report %s to %s\n", forecastName, anEnvelope->to );
        fprintf( stderr, "mailing XML report %s to %s\n", forecastName, anEnvelope->to );
        result |= eMail( aGame, anEnvelope, forecastName );
    } else {
        /* TODO Create a file copy */
    }
    result |= GOS_delete( forecastName );
    free( forecastName );
    return result;
}



int mail_TXT_Forecast( game* aGame, player *aPlayer, envelope *anEnvelope,
       char* nationName, int kind )
{
    int result = FALSE;
    FILE *forecast;
    char* forecastName = 
        createString( "%s/NG_TXT_%d_forecast", tempdir, getpid(  ) );

    if ( ( forecast = GOS_fopen( forecastName, "w" ) ) == NULL ) {
        plog( LBRIEF, "Could not open %s for forecasting\n", forecastName );
        fprintf( stderr, "Could not open %s for forecasting\n", forecastName );
        return EXIT_FAILURE;
    }

    setHeader( anEnvelope, MAILHEADER_SUBJECT,
            "Galaxy HQ, %s turn %d TXT forecast for %s",
            aGame->name, ( aGame->turn ) + 1, nationName );

    ( aGame->turn )++;
    fprintf( stderr, "Creating TXT report, %s:%d\n", nationName, kind );
    reportForecast( aGame, nationName, forecast );
    ( aGame->turn )--;
    fclose( forecast );

    if ( kind == CMD_CHECK_REAL ) {
        plog( LBRIEF, "mailing TXT report %s to %s\n", forecastName, anEnvelope->to );
        fprintf( stderr, "mailing TXT report %s to %s\n", forecastName, anEnvelope->to );
        result |= eMail( aGame, anEnvelope, forecastName );
    } else {
        /* TODO Create a file copy */
    }
    result |= GOS_delete( forecastName );
    free( forecastName );
    return result;
}

int mail_TXT_Error( game* aGame, envelope *anEnvelope, char* nationName, int kind,
       int resNumber, int theTurnNumber )
{
    int result = FALSE;

    char *forecastName = createString( "%s/NG_TXT_%d_errors",
            tempdir, getpid(  ) );
    FILE* forecast = GOS_fopen( forecastName, "w" );

    setHeader( anEnvelope, MAILHEADER_SUBJECT,
            "Galaxy HQ, major trouble" );
    plog( LBRIEF, "major trouble %d\n", resNumber );

    generateErrorMessage( resNumber, aGame, nationName,
            theTurnNumber, forecast );
    fclose( forecast );

    if ( kind == CMD_CHECK_REAL ) {
        plog( LBRIEF, "mailing error report %s to %s\n", forecastName,
                anEnvelope->to );
        result |= eMail( aGame, anEnvelope, forecastName );
    } else {
        /* TODO */
    }
    result |= GOS_delete( forecastName );
    free( forecastName );
    return result;
}

int
CMD_check( int argc, char **argv, int kind )
{
    char *logName;
    int result = EXIT_FAILURE;

    logName = createString( "%s/log/orders_processed.txt", galaxynghome );
    openLog( logName, "a" );
    free( logName );

    plogtime( LBRIEF );
    if ( argc >= 2 ) {
        envelope *anEnvelope = createEnvelope(  );
        char *returnAddress = getReturnAddress( stdin );
        int   theTurnNumber = getTurnNumber( stdin );
        char *nationName = NULL;
        char *password = NULL;
        game *aGame = NULL;
        int resNumber = areValidOrders( stdin, &aGame, &nationName,
                                    &password, theTurnNumber );
        plog( LBRIEF, "game %s\n", aGame->name );

        setHeader( anEnvelope, MAILHEADER_TO, "%s", returnAddress );

        if ( resNumber == RES_OK ) {
            player *aPlayer = findElement( player, aGame->players, nationName );

            assert( aPlayer);
            aPlayer->orders = NULL;
            plog( LBRIEF, "Orders from %s\n", returnAddress );

            if ( ( theTurnNumber == LG_CURRENT_TURN ) ||
                 ( theTurnNumber == ( aGame->turn ) + 1 ) ) {

                copyOrders( aGame, stdin, nationName, password,
                        aGame->turn + 1 );
                checkOrders( aGame, nationName );

                if ( aPlayer->flags & F_XMLREPORT ) {
                     result = mail_XML_Forecast( aGame, aPlayer, anEnvelope, nationName, kind );
                }
                if ( aPlayer->flags & F_TXTREPORT ) {
                     result = mail_TXT_Forecast( aGame, aPlayer, anEnvelope, nationName, kind );
                }
            } else {
                /* They are advance orders */
            }
        } else {
            /* Some major error */
            result |= mail_TXT_Error( aGame, anEnvelope, 
                    nationName, kind, resNumber, theTurnNumber );
        }
    }

    return result;
}

#else
int
CMD_check( int argc, char **argv, int kind )
{
    int result;
    char *logName;
    envelope *anEnvelope;
    char *forecastName;
    char *returnAddress;
    char *nationName;
    char *password;
    game *aGame;
    FILE *forecast;
    player *aPlayer;

    int resNumber, theTurnNumber;

    result = FALSE;

    logName = createString( "%s/log/orders_processed.txt", galaxynghome );
    openLog( logName, "a" );
    free( logName );

    plogtime( LBRIEF );
    if ( argc >= 2 ) {
        anEnvelope = createEnvelope(  );
        returnAddress = getReturnAddress( stdin );
        theTurnNumber = getTurnNumber( stdin );
        nationName = NULL;
        password = NULL;
        aGame = NULL;
        resNumber = areValidOrders( stdin, &aGame, &nationName,
                                    &password, theTurnNumber );
        plog( LBRIEF, "game %s\n", aGame->name );

        setHeader( anEnvelope, MAILHEADER_TO, "%s", returnAddress );

        if ( resNumber == RES_OK ) {
            aPlayer = findElement( player, aGame->players, nationName );
            aPlayer->orders = NULL;

            plog( LBRIEF, "Orders from %s\n", returnAddress );

            /* produce an XML forecast */
            if ( aPlayer->flags & F_XMLREPORT ) {
                if ( ( theTurnNumber == LG_CURRENT_TURN ) ||
                     ( theTurnNumber == ( aGame->turn ) + 1 ) ) {
                    forecastName = createString( "%s/NG_XML_%d_forecast",
                                                 tempdir, getpid(  ) );
                    copyOrders( aGame, stdin, nationName, password,
                                aGame->turn + 1 );
                    if ( ( forecast =
                           GOS_fopen( forecastName, "w" ) ) == NULL ) {
                        plog( LBRIEF, "Could not open %s for forecasting\n",
                              forecastName );
                        fprintf( stderr,
                                 "Could not open %s for forecasting\n",
                                 forecastName );
                        return EXIT_FAILURE;
                    }

                    setHeader( anEnvelope, MAILHEADER_SUBJECT,
                               "Galaxy HQ, %s turn %d XML forecast for %s",
                               aGame->name, ( aGame->turn ) + 1, nationName );

                    checkOrders( aGame, nationName, forecast, F_XMLREPORT );

                    fclose( forecast );
                    if ( kind == CMD_CHECK_REAL ) {
                        plog( LBRIEF, "mailing XML report %s to %s\n",
                              forecastName, anEnvelope->to );
                        fprintf( stderr, "mailing XML report %s to %s\n",
                                 forecastName, anEnvelope->to );
                        result |= eMail( aGame, anEnvelope, forecastName );
                    } else {
                        char *forecastFile;
                        forecastFile =
                            createString( "%s/forecasts/%s/%s_XML",
                                          galaxynghome, argv[2],
                                          returnAddress );
                        GOS_copy( forecastName, forecastFile );
                    }
                    result |= GOS_delete( forecastName );
                    free( forecastName );
                }
            }

            /* produce a text forecast */
            if ( aPlayer->flags & F_TXTREPORT ) {
                if ( ( theTurnNumber == LG_CURRENT_TURN ) ||
                     ( theTurnNumber == ( aGame->turn ) + 1 ) ) {
                    forecastName = createString( "%s/NG_TXT_%d_forecast",
                                                 tempdir, getpid(  ) );
                    if ( ( forecast =
                           GOS_fopen( forecastName, "w" ) ) == NULL ) {
                        plog( LBRIEF, "Could not open %s for forecasting\n",
                              forecastName );
                        return EXIT_FAILURE;
                    }

                    if ( aPlayer->orders == NULL )
                        copyOrders( aGame, stdin, nationName, password,
                                    aGame->turn + 1 );

                    setHeader( anEnvelope, MAILHEADER_SUBJECT,
                               "Galaxy HQ, %s turn %d TXT forecast for %s",
                               aGame->name, ( aGame->turn ) + 1, nationName );

                    checkOrders( aGame, nationName, forecast, F_TXTREPORT );

                    fclose( forecast );

                    if ( kind == CMD_CHECK_REAL ) {
                        plog( LBRIEF, "mailing TXT report %s to %s\n",
                              forecastName, anEnvelope->to );
                        fprintf( stderr, "mailing TXT report %s to %s\n",
                                 forecastName, anEnvelope->to );

                        result |= eMail( aGame, anEnvelope, forecastName );
                    } else {
                        char *forecastFile;
                        forecastFile =
                            createString( "%s/forecasts/%s/%s_TXT",
                                          galaxynghome, argv[2],
                                          returnAddress );
                        GOS_copy( forecastName, forecastFile );
                    }
                    result |= GOS_delete( forecastName );
                    free( forecastName );
                }
            }

        } else {
            forecastName = createString( "%s/NG_TXT_%d_errors",
                                         tempdir, getpid(  ) );
            forecast = GOS_fopen( forecastName, "w" );
            setHeader( anEnvelope, MAILHEADER_SUBJECT,
                       "Galaxy HQ, major trouble" );
            plog( LBRIEF, "major trouble %d\n", resNumber );

            generateErrorMessage( resNumber, aGame, nationName,
                                  theTurnNumber, forecast );
            fclose( forecast );

            if ( kind == CMD_CHECK_REAL ) {
                plog( LBRIEF, "mailing error report %s to %s\n", forecastName,
                      anEnvelope->to );

                result |= eMail( aGame, anEnvelope, forecastName );
            } else {
                char *forecastFile;
                forecastFile =
                    createString( "%s/forecasts/%s/%s_ERR",
                                  galaxynghome, argv[2], returnAddress );
                GOS_copy( forecastName, forecastFile );
            }
            result |= GOS_delete( forecastName );
            free( forecastName );
        }

        /* code here for advanced orders, we need to see how to determine this */
        if ( !( ( theTurnNumber == LG_CURRENT_TURN ) ||
                ( theTurnNumber == ( aGame->turn ) + 1 ) ) ) {

            if ( aPlayer->orders == NULL )
                copyOrders( aGame, stdin, nationName, password,
                            theTurnNumber );

            setHeader( anEnvelope, MAILHEADER_SUBJECT,
                       "Galaxy HQ, %s advance orders received for %s.",
                       aGame->name, nationName );
            plog( LBRIEF, "%s advance orders received for %s.\n",
                  aGame->name, nationName );
            if ( aPlayer->flags & F_XMLREPORT ) {
                forecastName = createString( "%s/NG_XML_forecast", tempdir );
                forecast = GOS_fopen( forecastName, "w" );

                fprintf( forecast,
                         "<galaxy>\n  <variant>GalaxyNG</variant>\n" );
                fprintf( forecast, "  <version>%d.%d.%d</version>\n",
                         GNG_MAJOR, GNG_MINOR, GNG_RELEASE );
                fprintf( forecast, "  <game name=\"%s\">\n", aGame->name );
                fprintf( forecast, "    <turn num=\"%d\">\n", theTurnNumber );
                fprintf( forecast, "      <race name=\"%s\">\n", nationName );
                fprintf( forecast, "        <message>\n" );
                fprintf( forecast, "          <line num=\"1\">"
                         "O wise leader, your orders for turn %d</line>",
                         theTurnNumber );
                fprintf( forecast, "          <line num=\"2\">"
                         "have been received and stored.</line>" );
                fprintf( forecast, "        </message>\n" );
                fprintf( forecast, "      </race>\n" );
                fprintf( forecast, "    </turn>\n" );
                fprintf( forecast, "  </game>\n" );
                fprintf( forecast, "</galaxy>\n" );
                fclose( forecast );
                if ( kind == CMD_CHECK_REAL ) {
                    result |= eMail( aGame, anEnvelope, forecastName );
                } else {
                    char *forecastFile;

                    forecastFile =
                        createString( "%s/forecasts/%s/%s_XML",
                                      galaxynghome, argv[2], returnAddress );
                    GOS_copy( forecastName, forecastFile );
                }
                result |= GOS_delete( forecastName );
                free( forecastName );
            }

            if ( aPlayer->flags & F_TXTREPORT ) {
                if ( aPlayer->orders == NULL )
                    copyOrders( aGame, stdin, nationName, password,
                                theTurnNumber );
                forecastName = createString( "%s/NG_TXT_forecast", tempdir );
                forecast = GOS_fopen( forecastName, "w" );
                fprintf( forecast, "O wise leader your orders for turn %d "
                         "have been received and stored.\n", theTurnNumber );
                fclose( forecast );
                if ( kind == CMD_CHECK_REAL ) {
                    result |= eMail( aGame, anEnvelope, forecastName );
                } else {
                    char *forecastFile;

                    forecastFile =
                        createString( "%s/forecasts/%s/%s_TXT",
                                      galaxynghome, argv[2], returnAddress );
                    GOS_copy( forecastName, forecastFile );
                }

                result |= GOS_delete( forecastName );
                free( forecastName );
            }
        }
    }

    if ( nationName )
        free( nationName );
    if ( password )
        free( password );
    destroyEnvelope( anEnvelope );
    result = ( result ) ? EXIT_FAILURE : EXIT_SUCCESS;

    return result;
}
#endif

/***********/


/****f* CLI/CMD_checkFile
 * NAME
 *   CMD_checkFile --
 * NOTE
 *   This should be merged with CMD_check(). 
 ****/
#if 0
int
CMD_checkFile( int argc, char **argv, int kind )
{
    int result;
    char *logName;
    FILE *stream;

    result = EXIT_FAILURE;

    logName = createString( "%s/log/orders_processed.txt", galaxynghome );
    openLog( logName, "a" );
    free( logName );

    plogtime( LBRIEF );
    if ( argc >= 2 ) {
        char *forecastName, *returnAddress, *nationName, *password;
        int resNumber, theTurnNumber;
        game *aGame;
        FILE *forecast;

        forecastName = createString( "%s/NGforecast", tempdir );
        if ( ( ( forecast = GOS_fopen( forecastName, "w" ) ) != 0 ) &
             ( ( stream = GOS_fopen( argv[2], "r" ) ) != NULL ) ) {
            envelope *anEnvelope;

            anEnvelope = createEnvelope(  );

            returnAddress = getReturnAddress( stream );
            theTurnNumber = getTurnNumber( stream );
            nationName = NULL;
            password = NULL;
            aGame = NULL;
            resNumber = areValidOrders( stream, &aGame, &nationName,
                                        &password, theTurnNumber );
            plog( LBRIEF, "game %s\n", aGame->name );
            setHeader( anEnvelope, MAILHEADER_TO, "%s", returnAddress );
            plog( LBRIEF, "Orders from %s\n", returnAddress );
            if ( resNumber == RES_OK ) {
                if ( ( theTurnNumber == LG_CURRENT_TURN ) ||
                     ( theTurnNumber == ( aGame->turn ) + 1 ) ) {
                    copyOrders( aGame, stream, nationName, password,
                                ( aGame->turn ) + 1 );
                    setHeader( anEnvelope, MAILHEADER_SUBJECT,
                               "Galaxy HQ, %s turn %d forecast for %s",
                               aGame->name, ( aGame->turn ) + 1, nationName );
                    plog( LBRIEF, "%s turn %d orders checked for %s.\n",
                          aGame->name, ( aGame->turn ) + 1, nationName );
                    checkOrders( aGame, nationName, forecast, F_TXTREPORT );
                } else {
                    copyOrders( aGame, stream, nationName, password,
                                theTurnNumber );
                    setHeader( anEnvelope, MAILHEADER_SUBJECT,
                               "Galaxy HQ, %s advance orders received for %s.",
                               aGame->name, nationName );
                    plog( LBRIEF, "%s advance orders received for %s.\n",
                          aGame->name, nationName );
                    fprintf( forecast,
                             "O wise leader your orders for turn %d "
                             "have been received and stored.\n",
                             theTurnNumber );
                }
            } else {
                setHeader( anEnvelope, MAILHEADER_SUBJECT,
                           "Galaxy HQ, major trouble" );
                plog( LBRIEF, "major trouble %d\n", resNumber );
                generateErrorMessage( resNumber, aGame, nationName,
                                      theTurnNumber, forecast );
            }
            fprintf( forecast, "\n\n%s\n", vcid );
            fclose( forecast );
            result = 0;
            if ( kind == CMD_CHECK_REAL ) {
                result |= eMail( aGame, anEnvelope, forecastName );
            } else {
                char *forecastFile;

                forecastFile = createString( "%s\\forecasts\\%s",
                                             galaxynghome, returnAddress );
                GOS_copy( forecastName, forecastFile );
            }
            if ( nationName )
                free( nationName );
            if ( password )
                free( password );
            destroyEnvelope( anEnvelope );
            result |= GOS_delete( forecastName );
            result = ( result ) ? EXIT_FAILURE : EXIT_SUCCESS;
        } else {
            fprintf( stderr, "Can't open \"%s\".\n", forecastName );
        }
        fclose( stream );
        free( forecastName );
    } else {
        usage(  );
    }
    closeLog(  );
    return result;
}
#endif
/***********/



/****i* CLI/CMD_relay
 * NAME 
 *   CMD_relay -- relay a message from one nation to another.
 * FUNCTION
 ******
 */

int
CMD_relay( int argc, char **argv )
{
    int result;
    char *logName;

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
            player *aPlayer;
            char *destination, *returnAddress, *nationName, *password;
            int theTurnNumber = LG_CURRENT_TURN;
            envelope *anEnvelope;

            anEnvelope = createEnvelope(  );
            returnAddress = getReturnAddress( stdin );
            setHeader( anEnvelope, MAILHEADER_TO, "%s", returnAddress );
            destination = getDestination( stdin );
            nationName = NULL;
            password = NULL;
            aGame = NULL;
            resNumber =
                areValidOrders( stdin, &aGame, &nationName,
                                &password, theTurnNumber );
            if ( destination == NULL ) {
                resNumber = RES_NODESTINATION;
            }
            if ( resNumber == RES_OK ) {
                aPlayer = findElement( player, aGame->players, destination );

                if ( aPlayer == NULL ) {
                    resNumber = RES_DESTINATION;
                }
            }
            plog( LBRIEF, "Message from %s\n", returnAddress );
            result = 0;
            if ( resNumber == RES_OK ) {
                result |= relayMessage( aGame, nationName, aPlayer );
                if ( result == 0 ) {
                    setHeader( anEnvelope, MAILHEADER_SUBJECT,
                               "Galaxy HQ, message sent" );
                    fprintf( confirm, "Message has been sent to %s.\n",
                             aPlayer->name );
                } else {
                    setHeader( anEnvelope, MAILHEADER_SUBJECT,
                               "Galaxy HQ, message not sent" );
                    fprintf( confirm,
                             "Due to a server error the message was not send!\n"
                             "Please contact your Game Master.\n" );
                }
            } else {
                setHeader( anEnvelope, MAILHEADER_SUBJECT,
                           "Galaxy HQ, major trouble." );
                generateErrorMessage( resNumber, aGame, nationName,
                                      theTurnNumber, confirm );
            }
            fprintf( confirm, "\n\n%s\n", vcid );
            fclose( confirm );
            result |= eMail( aGame, anEnvelope, confirmName );
            if ( destination )
                free( destination );
            if ( nationName )
                free( nationName );
            if ( password )
                free( password );
            destroyEnvelope( anEnvelope );
            result |= ssystem( "rm %s", confirmName );
            result = ( result ) ? EXIT_FAILURE : EXIT_SUCCESS;
        } else {
            fprintf( stderr, "Can't open \"%s\".\n", confirmName );
        }
        free( confirmName );
    } else {
        usage(  );
    }
    closeLog(  );
    return result;
}


/****i* CLI/relayMessage
 * NAME
 *   relayMessage --
 ******
 */

int
relayMessage( game *aGame, char *nationName, player *to )
{
    char *messageName;
    FILE *message;
    envelope *anEnvelope;
    int result;

    result = 1;
    messageName = createString( "%s/NGmessage", tempdir );
    if ( to->addr ) {
        if ( ( message = GOS_fopen( messageName, "w" ) ) ) {
            char *isRead;

            anEnvelope = createEnvelope(  );

            setHeader( anEnvelope, MAILHEADER_TO, "%s", to->addr );
            setHeader( anEnvelope, MAILHEADER_SUBJECT,
                       "Galaxy HQ, message relay %s", nationName );
            plog( LBRIEF, "Message relay, destination %s.\n", to->addr );
            fprintf( message, "#GALAXY %s %s %s\n",
                     aGame->name, to->name, to->pswd );
            fprintf( message, "\n-*- Message follows -*-\n\n" );
            for ( isRead = fgets( lineBuffer, LINE_BUFFER_SIZE, stdin );
                  isRead;
                  isRead = fgets( lineBuffer, LINE_BUFFER_SIZE, stdin ) ) {
                fputs( lineBuffer, message );
            }
            fclose( message );
            result = eMail( aGame, anEnvelope, messageName );
            destroyEnvelope( anEnvelope );
            result |= ssystem( "rm %s", messageName );
            free( messageName );
        } else {
            fprintf( stderr, "Can't open \"%s\".\n", messageName );
        }
    }
    return result;
}


/****f* CLI/CMD_create
 * NAME
 *   CMD_create -- create a new galaxy and game.
 * SYNOPSIS
 *   galaxyng -create <game specification file>
 * FUNCTION
 *   Creates a new game based on the specification found in
 *   the specification file.
 * INPUTS
 *   specificationfile -- file with the dimensions of the galaxy
 *     and the addresses of all the players. (.glx file).
 * SEE 
 *   CMD_mail0(), CMD_template()  
 * SOURCE
 */

int
CMD_create( int argc, char **argv )
{
    gamespecification *gspec;
    game *aGame;
    int result;
    FILE *specfile;

    result = EXIT_FAILURE;
    if ( argc == 3 ) {
        if ( ( specfile = GOS_fopen( argv[2], "r" ) ) ) {
            gspec = readGameSpec( specfile );
            fclose( specfile );
            printGameSpecs( gspec );
            if ( ( aGame = creategame( gspec ) ) ) {
                struct fielddef fields;

                fields.destination = stdout;
                loadConfig( aGame );
                checkIntegrity( aGame );
                savegame( aGame );
                reportMap( aGame, aGame->players, &fields );
                printf( "Number of planets: %d\n",
                        numberOfElements( aGame->planets ) );
                result = EXIT_SUCCESS;
            } else {
                fprintf( stderr, "Can't create the game\n" );
            }
        } else {
            fprintf( stderr, "Can't open specification file \"%s\"\n",
                     argv[2] );
        }
    } else {
        usage(  );
    }
    return result;
}

/********/


/****f* CLI/CMD_mail0
 * NAME
 *   CMD_mail0 -- mail the turn 0 reports.
 * SYNOPSIS
 *   ./galaxyng -mail0 <Game Name>
 *   int CMD_mail0(int argc, char **argv) 
 * FUNCTION
 *   Mail the turn 0 reports to the players. 
 *   To be run after a new game is created.
 * SOURCE
 */

int
CMD_mail0( int argc, char **argv, int kind )
{
    game *aGame;
    int result;

    result = EXIT_FAILURE;
    if ( argc == 3 ) {
        if ( ( aGame = loadgame( argv[2], LG_CURRENT_TURN ) ) ) {
            player *aPlayer;

            loadConfig( aGame );
            checkIntegrity( aGame );
            for ( aPlayer = aGame->players; aPlayer; aPlayer = aPlayer->next ) {
                aPlayer->pswdstate = 1;

                if ( ( aGame->gameOptions.gameOptions & GAME_SAVECOPY ) |
                     ( kind == CMD_CHECK_DUMMY ) ) {
                    if ( aPlayer->flags & F_TXTREPORT )
                        saveTurnReport( aGame, aPlayer, F_TXTREPORT );
                    if ( aPlayer->flags & F_XMLREPORT )
                        saveTurnReport( aGame, aPlayer, F_XMLREPORT );
                }

                if ( aPlayer->flags & F_TXTREPORT ) {
                    if ( kind == CMD_CHECK_DUMMY ) {
                        saveTurnReport( aGame, aPlayer, F_TXTREPORT );
                    } else {
                        mailTurnReport( aGame, aPlayer, F_TXTREPORT );
                    }

                }

                if ( aPlayer->flags & F_XMLREPORT ) {
                    if ( kind == CMD_CHECK_DUMMY ) {
                        saveTurnReport( aGame, aPlayer, F_XMLREPORT );
                    } else {
                        mailTurnReport( aGame, aPlayer, F_XMLREPORT );
                    }
                }

                if ( aPlayer->flags & F_MACHINEREPORT ) {
                    if ( kind == CMD_CHECK_DUMMY ) {
                        saveTurnReport( aGame, aPlayer, F_MACHINEREPORT );
                    } else {
                        mailTurnReport( aGame, aPlayer, F_MACHINEREPORT );
                    }
                }
            }
            result = EXIT_SUCCESS;
        } else {
            fprintf( stderr, "Could not load game \"%s\"\n", argv[2] );
        }
    } else {
        usage(  );
    }
    return result;
}

/**********/


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
    int result;
    char *logName;

    logName = createString( "%s/log/orders_processed.txt", galaxynghome );
    openLog( logName, "a" );
    free( logName );

    plogtime( LBRIEF );
    result = EXIT_FAILURE;
    if ( argc >= 2 ) {
        char *returnAddress, *nationName, *password;
        int resNumber, theTurnNumber;
        game *aGame;
        FILE *report;
        char *reportName;

        reportName = createString( "%s/temp_report_copy", tempdir );
        if ( ( report = GOS_fopen( reportName, "w" ) ) ) {
            envelope *anEnvelope;

            anEnvelope = createEnvelope(  );
            returnAddress = getReturnAddress( stdin );
            setHeader( anEnvelope, MAILHEADER_TO, "%s", returnAddress );
            plog( LBRIEF, "Report request from %s.\n", returnAddress );
            theTurnNumber = getTurnNumber( stdin );
            nationName = NULL;
            password = NULL;
            aGame = NULL;
            resNumber =
                areValidOrders( stdin, &aGame, &nationName, &password,
                                theTurnNumber );
            if ( ( resNumber == RES_TURNRAN )
                 || ( ( resNumber == RES_OK )
                      && ( theTurnNumber == LG_CURRENT_TURN ) ) ) {
                game *aGame2;

                if ( theTurnNumber > 0 ) {
                    aGame2 = loadgame( aGame->name, theTurnNumber - 1 );
                } else if ( theTurnNumber == LG_CURRENT_TURN ) {
                    theTurnNumber = aGame->turn;
                    aGame2 = loadgame( aGame->name, theTurnNumber - 1 );
                } else {
                    aGame2 = loadgame( aGame->name, 0 );
                }
                if ( aGame2 ) {
                    player *aPlayer;
                    int index;

                    loadConfig( aGame2 );
                    setHeader( anEnvelope, MAILHEADER_SUBJECT,
                               "Galaxy HQ, Copy of turn %d report",
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
                    /* Translate the current nation name into the name used during
                     * the * turn * * * * that is requested */
                    aPlayer =
                        findElement( player, aGame->players, nationName );

                    index = ptonum( aGame->players, aPlayer );
                    aPlayer = numtop( aGame2->players, index );

                    if ( theTurnNumber == 0 )
                        aPlayer->pswdstate = 1;
                    highScoreList( aGame2 );
                    createTurnReport( aGame2, aPlayer, report, 0 );
                } else {
                    setHeader( anEnvelope, MAILHEADER_SUBJECT,
                               "Galaxy HQ, Copy of turn report request." );
                    fprintf( report,
                             "\n\nThe turn you requested is no longer available...\n" );
                }
            } else if ( resNumber == RES_OK ) {
                setHeader( anEnvelope, MAILHEADER_SUBJECT,
                           "Galaxy HQ, Major Trouble" );
                fprintf( report,
                         "You can not request a report for the next turn\n" );
                fprintf( report,
                         "or any following turns,"
                         " I can not see into the future!\n" );
            } else {
                setHeader( anEnvelope, MAILHEADER_SUBJECT,
                           "Galaxy HQ, Major Trouble" );
                generateErrorMessage( resNumber, aGame, nationName,
                                      theTurnNumber, report );
            }
            fclose( report );
            result = eMail( aGame, anEnvelope, reportName );
            destroyEnvelope( anEnvelope );
            result |= ssystem( "rm %s", reportName );
            result = ( result ) ? EXIT_FAILURE : EXIT_SUCCESS;
            if ( nationName )
                free( nationName );
            if ( password )
                free( password );
        } else {
            fprintf( stderr, "Can't open \"%s\"\n", reportName );
        }
        free( reportName );
    } else {
        usage(  );
    }
    closeLog(  );
    return result;
}

/**********/


/****f* CLI/CMD_score
 * NAME
 *   CMD_score -- Show highscore list.
 * FUNCTION
 *   Write a HTML-ized version of the highscore list to stdout.
 * SOURCE
 */

int
CMD_score( int argc, char **argv )
{
    int result;
    game *aGameThisTurn;
    game *aGamePrevTurn;

    result = EXIT_FAILURE;
    if ( argc == 3 ) {
        if ( ( aGameThisTurn = loadgame( argv[2], LG_CURRENT_TURN ) ) ) {
            if ( ( aGamePrevTurn =
                   loadgame( aGameThisTurn->name,
                             aGameThisTurn->turn - 1 ) ) ) {
                score( aGamePrevTurn, aGameThisTurn, TRUE, stdout );
                result = EXIT_SUCCESS;
            } else {
                fprintf( stderr, "Could not load game \"%s\"\n", argv[2] );
            }
        } else {
            fprintf( stderr, "Could not load game \"%s\" turn %d\n", argv[2],
                     aGameThisTurn->turn - 1 );
        }
    } else {
        usage(  );
    }
    return result;
}

/*********/


/****f* CLI/CMD_graph
 * NAME
 *   CMD_graph -- create a data dump for a graph of a game.
 * NOTES 
 *   Experimental. See Tools/graphscore.tcl
 * SOURCE
 */

int
CMD_graph( int argc, char **argv )
{
    game *aGame;
    int result;

    result = EXIT_FAILURE;
    if ( argc == 4 ) {
        if ( ( aGame = loadgame( argv[2], atoi( argv[3] ) ) ) ) {
            player *aPlayer;
            int number;

            nationStatus( aGame );
            for ( number = 0, aPlayer = aGame->players;
                  aPlayer; aPlayer = aPlayer->next, number++ ) {
                printf( "%d %d %s %f\n", aGame->turn, number, aPlayer->name,
                        effectiveIndustry( aPlayer->totPop,
                                           aPlayer->totInd ) );
            }
        } else {
            fprintf( stderr, "Could not load game \"%s\" turn %s\n",
                     argv[2], argv[3] );
        }
    } else {
        usage(  );
    }
    return result;
}

/******/


/****f* CLI/CMD_dump
 *  NAME
 *    CMD_dump -- dump game data.
 *  SYNOPSIS
 *     ./galaxyng -players     <game> [turn]
 *     ./galaxyng -lastorders  <game> [turn]
 *     ./galaxyng -map         <game> [turn]
 *
 *     CMD_dump(int argc, char **argv, int kind) 
 *  FUNCTION
 *    Dump game information.
 *  SWITCHES
 *    kind:
 *      CMD_DUMP_LASTORDERS
 *         show turn when players last send in orders.
 *      CMD_DUMP_MAP
 *         show a map of the galaxy
 *      CMD_DUMP_PLAYERS
 *         show password and address of players
 *      CMD_DUMP_HALL
 *         show information for use in the hall of fame.
 *      CMD_DUMP_TEAM_INFO
 *         show info on all members of a team
 *         (used in Tiger games).
 * SOURCE
 */

int
CMD_dump( int argc, char **argv, int kind )
{
    game *aGame;
    int result;
    int turn;
    int team;

    result = EXIT_FAILURE;
    if ( argc >= 3 ) {
        if ( argc == 3 ) {
            turn = LG_CURRENT_TURN;
        } else {
            turn = atoi( argv[3] );
        }
        if ( ( aGame = loadgame( argv[2], turn ) ) ) {
            player *aDummyPlayer;
            struct fielddef fields;

            fields.destination = stdout;

            loadConfig( aGame );
            switch ( kind ) {
            case CMD_DUMP_MAP:{
                    aDummyPlayer = allocStruct( player );

                    setName( aDummyPlayer, "DummyDummy" );
                    aDummyPlayer->msize = aGame->galaxysize;
                    reportMap( aGame, aDummyPlayer, &fields );
                    break;
                }
            case CMD_DUMP_MAP_GNUPLOT:{
                    aDummyPlayer = allocStruct( player );

                    setName( aDummyPlayer, "DummyDummy" );
                    aDummyPlayer->msize = aGame->galaxysize;
                    reportMap_gnuplot( aGame, aDummyPlayer, &fields );
                    break;
                }
            case CMD_DUMP_LASTORDERS:{
                    reportLastOrders( aGame->players, &fields );
                    break;
                }
            case CMD_DUMP_PLAYERS:{
                    reportPlayers( aGame->players, &fields );
                    break;
                }
            case CMD_DUMP_PSCORE:{
                    scorePercent( aGame, &fields );
                    break;
                }
            case CMD_DUMP_HALL:{
                    reportHall( aGame, &fields );
                    break;
                }
            case CMD_DUMP_MAILHEADER:{
                    createMailToAllHeader( aGame );
                    break;
                }
            case CMD_DUMP_TEAM_INFO:{
                    if ( argc == 5 ) {
                        team = atoi( argv[4] );
                        reportTeam( aGame, &fields, team );
                    } else {
                        fprintf( stderr,
                                 "You have to specify a team number.\n" );
                    }
                    break;
                }
            case CMD_DUMP_TEAM_REPORT_NAMES:{
                    if ( argc == 5 ) {
                        player *aPlayer;

                        team = atoi( argv[4] );
                        for ( aPlayer = aGame->players;
                              aPlayer; aPlayer = aPlayer->next ) {
                            if ( aPlayer->team == team ) {
                                printf( "reports/%s/%s_%d.txt\n", aGame->name,
                                        aPlayer->name, aGame->turn );
                            }
                        }
                    } else {
                        fprintf( stderr,
                                 "You have to specify a team number.\n" );
                    }
                    break;
                }
            }
            result = EXIT_SUCCESS;
            freegame( aGame );
        } else {
            fprintf( stderr, "Could not load game \"%s\".\n", argv[2] );
        }
    } else {
        usage(  );
    }
    return result;
}

/**********/


/****f* CLI/CMD_test
 * NAME
 *   CMD_test -- check the integrity of a game.
 * FUNCTION
 *   Check if a GAME is OK by running checkIntegrity() on it.
 ******
 */

int
CMD_test( int argc, char **argv )
{
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
    } else {
        printf( "Game is NOT OK\n" );   /* This is wrong! the game did not * * * *
                                           * * load.. * it still might be * ok! */
        result = EXIT_FAILURE;
    }
    return result;
}



/****f* CLI/CMD_selftest
 * NAME
 *   CMD_selftest -- run a series of selftests
 * FUNCTION
 *   Run a series of selftest.  Used for debug purposes.
 *****
 */

int
CMD_selftest(  )
{
    getstrTest(  );
    frandTest(  );
    frand2Test(  );
    frand3Test(  );
    return 0;
}


int
CMD_battletest( int argc, char **argv )
{
    game *aGame;

    aGame = bat_createGame(  );
    if ( ( aGame ) ) {
        player *aPlayer;

        /* srand((int) time(NULL)); */
        /* printf("%d", atoi(argv[2])); */
        resetErnie( atoi( argv[2] ) );
        switch ( atoi( argv[3] ) ) {
        case 1:
            bat_scenario_1( aGame );
            break;
        case 2:
            bat_scenario_2( aGame );
            break;
        case 3:
            bat_scenario_3( aGame );
            break;
        case 4:
            bat_scenario_4( aGame );
            break;
        case 5:
            bat_scenario_5( aGame );
            break;
        case 6:
            bat_scenario_6( aGame );
            break;
        case 7:
            bat_scenario_7( aGame );
            break;
        case 8:
            bat_scenario_8( aGame );
            break;
        case 9:
            bat_scenario_9( aGame );
            break;
        case 10:
            bat_scenario_10( aGame );
            break;
        case 11:
            bat_scenario_11( aGame );
            break;
        case 12:
            bat_scenario_12( aGame );
            break;
        case 13:
            bat_scenario_13( aGame );
            break;
        case 14:
            bat_scenario_14( aGame );
            break;
        }
        preComputeGroupData( aGame );
        fightphase( aGame, GF_INBATTLE2 );
        joinphase( aGame );

        for ( aPlayer = aGame->players; aPlayer; aPlayer = aPlayer->next ) {
            aPlayer->pswdstate = 1;
            printf( "%s %d  ", aPlayer->name,
                    numberOfElements( aPlayer->groups ) );
            /* saveTurnReport(aGame, aPlayer, 0); */
        }

        printf( "\n" );
    }
    return 0;
}
