#include <ctype.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#include "process.h"

static void fakeGame( game **aGame );

/****h* GalaxyNG/Process
 * FUNCTION
 *   This module contains functions to process orders
 *   and run a turn.
 ******
 */

#define vprocess "$Id$"

void forecast_xml( game *aGame, player *aPlayer, FILE *forecast );

/****v* Process/phase1orders
 * NAME
 *   phase1orders -- map of all phase 1 orders.
 * FUNCTION
 *   A map that maps an order name to the corresponding function
 *   that executes the order.  
 * SOURCE
 */

orderinfo phase1orders[] = {
    {"@", &at_order},           /* send message */
    {"=", &eq_order},           /* FS 1999/12 set real name */
    {"a", &a_order},            /* alliance */
    {"b", &b_order},            /* break off ships */
    {"d", &d_order},            /* design ship */
    {"e", &e_order},            /* eliminate ship type */
    {"f", &f_order},            /* get Race's email address */
    {"h", &h_order},            /* CB-19980923, to recall (halt) a group */
    {"i", &i_order},            /* intercept */
    {"j", &j_order},            /* group join fleet */
    {"l", &l_order},            /* load cargo */
    {"m", &m_order},            /* change map area */
    {"o", &o_order},            /* set options */
    {"p", &p_order},            /* set production */
    {"q", &q_order},            /* quit */
    {"r", &r_order},            /* set route */
    {"s", &s_order},            /* send group/fleet to planet */
    {"u", &u_order},            /* unload cargo */
    {"v", &v_order},            /* claim victory */
    {"w", &w_order},            /* cancel alliance */
    {"x", &x_order},            /* scrap group */
    {"y", &y_order},            /* change password */
    {"z", &z_order},            /* change email */
    {NULL, NULL}
};

/**********/

/****v* Process/phase2orders
 * NAME
 *   phase2orders -- map of all phase 2 orders.
 * FUNCTION
 *   A map that maps an order name to the corresponding function
 *   that executes the order.  
 * SOURCE
 */

orderinfo phase2orders[] = {
    {"g", &g_order},            /* upgrade ships */
    {"n", &n_order},            /* rename planet */
    {"t", &t_order},            /* change ship/fleet name */
    {NULL, NULL}
};

/*********/

/****v* Process/phase3orders
 * NAME
 *   phase3orders -- map of all phase 3 orders.
 * FUNCTION
 *   A map that maps an order name to the corresponding function
 *   that executes the order.  
 * SOURCE
 */

orderinfo phase3orders[] = {
    {"c", &c_order},            /* change race name */
    {NULL, NULL}
};

/*********/


/* WIN32 */

/****f* Process/mistake
 * NAME
 *   mistake -- generate an error message about an order.
 * FUNCTION
 *   Dynamically generate an error message and add it to
 *   the list of mistakes of a player.
 * SOURCE
 */

void
mistake( player *P, enum error_type elevel, strlist *s, char *format, ... )
{
    int n;                      /* return value */
    va_list ap;                 /* argument list */
    char *lformat;              /* local copy of format */

    va_start( ap, format );

    lformat = ( char * ) malloc( strlen( format ) + 4 );

    switch ( elevel ) {
    case INFO:
        sprintf( lformat, "+I %s", format );
        break;

    case WARNING:
        sprintf( lformat, "+W %s", format );
        break;

    case ERROR:
        sprintf( lformat, "+E %s", format );
        break;
    }

    n = vsnprintf( lineBuffer, LINE_BUFFER_SIZE, lformat, ap );
    assert( n != -1 );

    free( lformat );

    va_end( ap );

    insertList( &P->orders, s, makestrlist( lineBuffer ) );
}

/********/







/****f* Process/runTurn
 * NAME
 *   runTurn -- run a turn.
 * SYNOPSIS
 *   int runTurn(game *, char *)
 *   result = runTurn(aGame, ordersFileName)
 * FUNCTION
 *   Move one turn forward in time. All orders sent in by the races
 *   are executed and the different phases are executed.  
 *   Races that did not sent in orders for a number of consecutive
 *   turns are removed from the game.
 *   Although we can assume all the orders are correct, since they
 *   have been processed by checkorders(), we stil do some sanity
 *   checks.
 * INPUTS
 *   aGame --
 *   ordersFileName -- name of the file that contains the orders
 *                     of _all_ the races.
 * RESULTS
 *   aGame->turn is increased by one.
 *   aGame       contains the new situation, including battles,
 *               bombings and messages.
 *   result 
 *     FALSE -- Error occured during turn processing
 *     TRUE  -- All OK
 * NOTE
 *   The turn is not saved and no reports are generated, this is handled
 *   by seperate functions.  This function should be split in parts.
 * SOURCE
 */

int
runTurn( game *aGame, char *ordersFileName )
{
    player *P;
    char *oGameName;
    char *raceName;
    char *password;
    FILE *ordersFile;

    char *rm_notify;

    rm_notify = createString( "/bin/rm -f %s/orders/%s/*.notify",
                              galaxynghome, aGame->name );
    /*printf("executing \"%s\"\n", rm_notify); */
    ssystem( rm_notify );
    free( rm_notify );

    plog( LPART, "Reading orders from file %s\n", ordersFileName );

    ordersFile = Fopen( ordersFileName, "r" );

    getLine( ordersFile );
    for ( ; !feof( ordersFile ); ) {
        char *ptr;
        if ( ( ptr = strchr( lineBuffer, '#' ) ) == NULL )
            ptr = lineBuffer;
        if ( noCaseStrncmp( "#GALAXY", ptr, 7 ) == 0 ) {
            player *aPlayer;

            getstr( ptr );
            oGameName = strdup( getstr( NULL ) );
            raceName = strdup( getstr( NULL ) );
            password = strdup( getstr( NULL ) );
            if ( noCaseStrcmp( oGameName, aGame->name ) == 0 ) {
                aPlayer = findElement( player, aGame->players, raceName );

                if ( aPlayer ) {
                    aPlayer->lastorders = aGame->turn + 1;
                    if ( noCaseStrcmp( aPlayer->pswd, password ) == 0 ) {
                        aPlayer->orders = NULL;
                        getLine( ordersFile );
                        if ( ( ptr = strchr( lineBuffer, '#' ) ) == NULL )
                            ptr = lineBuffer;
                        for ( ; !feof( ordersFile ) &&
                              noCaseStrncmp( "#GALAXY", ptr, 7 ) &&
                              noCaseStrncmp( "#END", ptr, 4 ); ) {
                            strlist *s;

                            if ( ( s = makestrlist( lineBuffer ) ) != NULL )
                                addList( &( aPlayer->orders ), s );
                            getLine( ordersFile );
                            if ( ( ptr = strchr( lineBuffer, '#' ) ) == NULL )
                                ptr = lineBuffer;

                        }
                    } else {
                        plog( LPART, "Password Incorrect.\n" );
                    }
                } else {
                    plog( LPART, "Unrecognized player %s.\n", raceName );
                }
            } else {
                plog( LPART, "Orders are not for game %s.\n", aGame->name );
            }
            free( oGameName );
            free( raceName );
            free( password );
        }
        getLine( ordersFile );
    }
    fclose( ordersFile );

    ( aGame->turn )++;

    if ( !checkIntegrity( aGame ) )
        return FALSE;

    plog( LPART, "Orders read, processing...\n" );
    plog( LFULL, "# Phase 1 Orders\n" );
    for ( P = aGame->players; P; P = P->next ) {
        doOrders( aGame, P, phase1orders, 1 );
    }

    if ( !checkIntegrity( aGame ) )
        return FALSE;

    plog( LFULL, "# Phase 2 Orders\n" );
    for ( P = aGame->players; P; P = P->next ) {
        doOrders( aGame, P, phase2orders, 2 );
    }

    if ( !checkIntegrity( aGame ) )
        return FALSE;

    plog( LFULL, "# Phase 3 Orders\n" );
    for ( P = aGame->players; P; P = P->next ) {
        doOrders( aGame, P, phase3orders, 3 );
    }

    if ( !checkIntegrity( aGame ) )
        return FALSE;

    plog( LFULL, "# joinphase I\n" );
    joinphase( aGame );
    preComputeGroupData( aGame );
    plog( LFULL, "# fightphase I\n" );
    fightphase( aGame, GF_INBATTLE1 );
    plog( LFULL, "# bombphase I\n" );
    bombphase( aGame );
    plog( LFULL, "# loadphase\n" );
    loadphase( aGame );
    plog( LFULL, "# fleetphase I \n" );
    fleetphase( aGame );
    if ( !checkIntegrity( aGame ) )
        return FALSE;
    plog( LFULL, "# interceptphase\n" );
    interceptphase( aGame );
    plog( LFULL, "# movephase\n" );
    movephase( aGame );
    plog( LFULL, "# joinphase II\n" );
    joinphase( aGame );
    preComputeGroupData( aGame );
    plog( LFULL, "# fightphase II\n" );
    fightphase( aGame, GF_INBATTLE2 );
    plog( LFULL, "# bombphase II\n" );
    bombphase( aGame );
    plog( LFULL, "# producephase\n" );
    producephase( aGame );
    plog( LFULL, "# unloadphase\n" );
    unloadphase( aGame );
    plog( LFULL, "# joinphase III\n" );
    joinphase( aGame );
    plog( LFULL, "# fleetphase II\n" );
    fleetphase( aGame );
    if ( !checkIntegrity( aGame ) )
        return FALSE;
    preComputeGroupData( aGame );
    sortphase( aGame );

    if ( !( aGame->gameOptions.gameOptions & GAME_NODROP ) )
        removeDeadPlayer( aGame );
    raceStatus( aGame );

    return TRUE;
}

/****************/


/****f* Process/checkOrders
 * NAME
 *   checkOrders --  check orders
 * SYNOPSIS
 *   int checkOrders(char *ordersFileName)
 *   resNumber = checkOrders(ordersFileName)
 * FUNCTION
 *   Checks a file with orders and prints a report with a forecast and 
 *   any errors found in the orders to stdout.
 *   It is checked that the orders contain a valid game name, race
 *   name and password.
 *   A copy of the orders is stored in the directory orders/<gameName>. 
 *
 *   If the orders start with #REPORT instead of #GALAXY a copy
 *   of the previous turn report is send to stdout.
 * INPUTS
 *   ordersFileName - name of the file with the orders.
 * RESULT
 *   resNumber -- return code:
 *      RES_NO_ORDERS - no line containing "#GALAXY" or #REPORT was found.
 *      RES_PASSWORD  - password was incorrect.
 *      RES_PLAYER    - no such player (Race) exists.
 *      RES_NO_GAME   - no such game exists.
 *      RES_TURNRAN   - orders are for a turn that already ran.
 *      RES_OK        - everything was OK.
 * BUGS
 *   Does not handle machine reports or xml reports.
 * SEE ALSO
 *   areValidOrders(), copyOrders() 
 * SOURCE
 */

#if FS_NEW_FORECAST
void
checkOrders( game *aGame, char *raceName )
{
    player *aPlayer;

    pdebug( DFULL, "check orders\n" );
    aPlayer = findElement( player, aGame->players, raceName );

    tagVisiblePlanets( aGame->planets, aPlayer );

    checkIntegrity( aGame );

    doOrders( aGame, aPlayer, phase1orders, 1 );
    doOrders( aGame, aPlayer, phase2orders, 2 );

    joinphase( aGame );
    loadphase( aGame );
    fleetphase( aGame );
    checkIntegrity( aGame );
    interceptphase( aGame );
    movephase( aGame );
    joinphase( aGame );
    producephase( aGame );
    unloadphase( aGame );
    joinphase( aGame );
    fleetphase( aGame );

    preComputeGroupData( aGame );
    sortphase( aGame );
    checkIntegrity( aGame );
}
#else
void
checkOrders( game *aGame, char *raceName, FILE *forecast, int kind )
{
    player *aPlayer;
    struct fielddef fields;

    /* blatant attempt to avoid doing orders more than once if more than 
       one report type is being generated */
    static int orders_done = 0;

    pdebug( DFULL, "check orders\n" );
    aPlayer = findElement( player, aGame->players, raceName );

    fields.destination = forecast;
    tagVisiblePlanets( aGame->planets, aPlayer );

    checkIntegrity( aGame );

    if ( orders_done == 0 ) {
        doOrders( aGame, aPlayer, phase1orders, 1 );
        doOrders( aGame, aPlayer, phase2orders, 2 );

        joinphase( aGame );
        loadphase( aGame );
        fleetphase( aGame );
        checkIntegrity( aGame );
        interceptphase( aGame );
        movephase( aGame );
        joinphase( aGame );
        producephase( aGame );
        unloadphase( aGame );
        joinphase( aGame );
        fleetphase( aGame );

        preComputeGroupData( aGame );
        sortphase( aGame );
        checkIntegrity( aGame );
    }

    ( aGame->turn )++;
    if ( kind == F_XMLREPORT ) {
        report_xml( aGame, aPlayer, forecast, Forecast );
    } else {
        raceStatus( aGame );
        reportGlobalMessages( aGame->messages, &fields );
        reportMessages( aPlayer, &fields );
        reportOrders( aPlayer, &fields );
        reportMistakes( aPlayer, &fields );
        yourStatusForecast( aGame->planets, aPlayer, &fields );
        if ( aPlayer->flags & F_SHIPTYPEFORECAST ) {
            reportYourShipTypes( aPlayer, &fields );
        }
        if ( aPlayer->flags & F_PLANETFORECAST ) {
            yourPlanetsForecast( aGame->planets, aPlayer, &fields );
            reportProdTable( aGame->planets, aPlayer, &fields );
        }
        if ( aPlayer->flags & F_ROUTESFORECAST ) {
            reportRoutes( aGame->planets, aPlayer, &fields );
        }
        if ( aPlayer->flags & F_GROUPFORECAST ) {
            reportYourGroups( aGame->planets, aPlayer, &fields );
            reportFleets( aPlayer, &fields );
        }
    }

    if ( orders_done == 0 ) {
        orders_done = 1;
        doOrders( aGame, aPlayer, phase3orders, 3 );
    }

    ( aGame->turn )--;
}
#endif

/*************/


/****f* Process/copyOrders
 * NAME
 *   copyOrders -- copy incoming orders to file.
 * SYNOPSIS
 * void copyOrders(game *aGame, FILE *orders, char *raceName, 
 *                 char *password, int theTurnNumber)
 * FUNCTION
 *   Copy the orders to a file called 
 *     GAMEHOME/orders/<game name>/<race name>.<turn number>
 *   If and #END line is missing one is generated.
 * INPUTS
 *   orderFile      - should point to the line after the #GALAXY line.
 *   aGame 
 *   raceName
 *   password
 *   theTurnNumber
 * SOURCE
 */

void
copyOrders( game *aGame, FILE *orders, char *raceName, char *password,
            char *final_orders, int theTurnNumber )
{
    strlist *s;
    char *copyFileName;
    FILE *copyFile;
    player *aPlayer;

    aPlayer = findElement( player, aGame->players, raceName );

    aPlayer->orders = NULL;
    copyFileName = alloc( strlen( aGame->name ) + strlen( aPlayer->name ) +
                          strlen( galaxynghome ) + strlen( "/orders//" ) +
                          20 );
    if ( final_orders ) {
        sprintf( copyFileName, "%s/orders/%s/%s.%d", galaxynghome,
                 aGame->name, aPlayer->name, theTurnNumber );
        unlink( copyFileName );
        sprintf( copyFileName, "%s/orders/%s/%s_final.%d", galaxynghome,
                 aGame->name, aPlayer->name, theTurnNumber );
    } else {
        sprintf( copyFileName, "%s/orders/%s/%s_final.%d", galaxynghome,
                 aGame->name, aPlayer->name, theTurnNumber );
        unlink( copyFileName );
        sprintf( copyFileName, "%s/orders/%s/%s.%d", galaxynghome,
                 aGame->name, aPlayer->name, theTurnNumber );
    }

    copyFile = Fopen( copyFileName, "w" );
    savefprintf( copyFile, "#GALAXY %s %s %s",
                 aGame->name, raceName, password );
    if ( final_orders )
        savefprintf( copyFile, " FinalOrders" );
    savefprintf( copyFile, "\n" );

    getLine( orders );
    for ( ; !feof( orders ) && noCaseStrncmp( "#END", lineBuffer, 4 ); ) {
        savefprintf( copyFile, "%s", lineBuffer );
        s = makestrlist( lineBuffer );
        addList( &( aPlayer->orders ), s );
        getLine( orders );
    }
    if ( feof( orders ) )
        savefprintf( copyFile, "#END\n" );
    else
        savefprintf( copyFile, "%s\n", lineBuffer );

    free( copyFileName );
}

/*****************/


/****f* Process/areValidOrders
 * NAME
 *   areValidOrders -- check if orders are valid and load game.
 * SYNOPSIS
 *   int areValidOrders(FILE *ordersFile, 
 *                      char **command, game **game, 
 *                      char **raceName, char** final_orders,
 *                      char **password)
 * FUNCTION
 *   Scans through a file with orders until a line that starts
 *   with "#" is found.  The the rest of the line is then
 *   used to determine the name of the game, the race the orders
 *   are for, and the password for the race.
 *   The given game is loaded.  It is checked that the given
 *   player exists in this game, and that the given password
 *   is equal to the stored password.
 * INPUTS
 *   ordersFile     - pointer to a opened file with orders.
 *   theTurnNumber  - turn number the orders are supposed to be for.
 * RESULT
 *   result      - return code:
 *      RES_NO_ORDERS - no line containing "#GALAXY" was found.
 *      RES_PASSWORD  - password was incorrect.
 *      RES_PLAYER    - no such player (Race) exists.
 *      RES_NO_GAME   - no such game exists.
 *      RES_TURNRAN   - orders are for a turn that already ran.
 *      RES_OK        - everything was OK.
 *   aGame       - game Structure loaded from disk
 *   raceName  - name of the race the orders are for.
 *   password    - given password of the race.
 *
 *   ordersFile  - points to the line after the #GALAXY line.
 *   
 *   If the result is RES_OK then the game and its configuration
 *   file are loaded from disk.
 * SEE ALSO
 *   CMD_report(), CMD_check(), CMD_relay()
 * SOURCE
 */

enum
{ GALAXY, GAMENAME, RACENAME, PASSWORD, TURNNBR, FINALORDERS, NBRITEMS };

int
areValidOrders( FILE *ordersFile, game **aGame, char **raceName,
                char **password, char **final_orders, int *theTurnNumber )
{
    player *aPlayer;

    char *galaxyItems[NBRITEMS];
    char *gameName;
    char *isRead;
    char *ptr;

    int resNumber = RES_OK;
    int foundOrders;
    int giIdx = 0;

    *aGame = NULL;
    *raceName = NULL;
    *password = NULL;
    *final_orders = NULL;

    gameName = NULL;

    foundOrders = FALSE;
    for ( isRead = fgets( lineBuffer, LINE_BUFFER_SIZE, ordersFile );
          isRead;
          isRead = fgets( lineBuffer, LINE_BUFFER_SIZE, ordersFile ) ) {
        if ( ( ptr = strchr( lineBuffer, '#' ) ) != NULL ) {
            if ( noCaseStrncmp( "#GALAXY", ptr, 7 ) == 0 ) {
                foundOrders = TRUE;
                break;
            }
        }
    }

    if ( !foundOrders ) {
        fakeGame( aGame );
        return RES_NO_ORDERS;
    }

    for ( giIdx = 0; giIdx < NBRITEMS; giIdx++ ) {
        galaxyItems[giIdx] = NULL;
    }

    ptr = strtok( lineBuffer, " " );
    giIdx = 0;

    do {
        galaxyItems[giIdx++] = strdup( ptr );
        plog( LBRIEF, "%d: \"%s\"\n", giIdx - 1, ptr );
    } while ( ( ptr = strtok( NULL, " " ) ) != NULL );


    for ( giIdx = 0; giIdx < NBRITEMS; giIdx++ ) {
        switch ( giIdx ) {
        case GALAXY:           /* #galaxy */
            if ( noCaseStrcmp( galaxyItems[GALAXY], "#galaxy" ) != 0 ) {
                plog( LBRIEF, "areValidOrders(%d): invalid #galaxy line\n",
                      __LINE__ );
                fakeGame( aGame );
                return RES_NO_GAME;
            }
            break;

        case GAMENAME:
            if ( galaxyItems[GAMENAME] == NULL ) {
                fakeGame( aGame );
                return RES_NO_GAME;
            }
            gameName = galaxyItems[GAMENAME];
            break;

        case RACENAME:
            if ( galaxyItems[RACENAME] == NULL ) {
                fakeGame( aGame );
                return RES_NO_GAME;
            }
            *raceName = galaxyItems[RACENAME];
            break;

        case PASSWORD:
            if ( galaxyItems[PASSWORD] == NULL ) {
                fakeGame( aGame );
                return RES_NO_GAME;
            }
            *password = galaxyItems[PASSWORD];
            break;

        case TURNNBR:
            if ( galaxyItems[TURNNBR] == NULL ) {
                *theTurnNumber = LG_CURRENT_TURN;
                resNumber = RES_NO_TURN_NBR;
            } else {
                *theTurnNumber = atoi( galaxyItems[TURNNBR] );
                free( galaxyItems[TURNNBR] );
            }
            break;

        case FINALORDERS:
            if ( galaxyItems[FINALORDERS] != NULL ) {
                *final_orders = galaxyItems[FINALORDERS];
            }
            break;
        }
    }

    if ( ( *aGame = loadgame( gameName, LG_CURRENT_TURN ) ) == NULL ) {
        fakeGame( aGame );
        return RES_NO_GAME;
    }


    loadNGConfig( *aGame );

    if ( noCaseStrcmp( "GM", *raceName ) == 0 ) {
        if ( strcmp( ( *aGame )->serverOptions.GMpassword, *password ) != 0 ) {
            return RES_PASSWORD;
        }
    }

    aPlayer = findElement( player, ( *aGame )->players, *raceName );

    if ( aPlayer == NULL ) {
        return RES_PLAYER;
    }

    if ( noCaseStrcmp( aPlayer->pswd, *password ) != 0 ) {
        return RES_PASSWORD;
    }

    if ( *theTurnNumber <= ( *aGame )->turn ) {
        return RES_TURNRAN;
    }

    if ( *theTurnNumber > ( *aGame )->turn ) {
        return RES_TURNFUTURE;
    }

    return resNumber;
}


static void
fakeGame( game **aGame )
{
    *aGame = allocStruct( game );

    setName( *aGame, "UnknownGame" );
    loadNGConfig( *aGame );
}

/*********/


/****f* Process/getTurnNumber
 * NAME
 *   getTurnNumber -- get the turn number
 * FUNCTION
 *   Scans an incomming email for the From: line.
 *   If it is found it looks for the word "order" or "report"
 *   It then looks if there is a number after this word.
 *   If there is this number is returned.
 *   If no From: line was found the program aborts.
 * RESULTS
 *   >= 0             -- the turn number
 *   LG_CURRENT_TURN  -- no turn number was specified
 ****/

int
getTurnNumber( FILE *orders )
{
    int theTurnNumber;
    char *isRead;

    theTurnNumber = LG_CURRENT_TURN;
    for ( isRead = fgets( lineBuffer, LINE_BUFFER_SIZE, orders );
          isRead; isRead = fgets( lineBuffer, LINE_BUFFER_SIZE, orders ) ) {
        /* WIN32 */
        if ( noCaseStrncmp( string_mail_subject, lineBuffer, 8 ) == 0 ) {
            int temp, nrRead;
            char *c;

            for ( c = lineBuffer; *c; c++ )
                *c = ( char ) tolower( *c );
            c = strstr( lineBuffer, "order" );
            if ( c == NULL ) {
                c = strstr( lineBuffer, "report" );
            }
            if ( c == NULL ) {
                c = strstr( lineBuffer, "shutdown" );
            }
            if ( c != NULL ) {
                nrRead = sscanf( c, "%*s%d", &temp );
                if ( nrRead == 1 )
                    theTurnNumber = temp;
            } else {
                assert( 0 );
            }
            break;
        }
    }
    assert( isRead != NULL );

    return theTurnNumber;
}


/****f* Process/getDestination
 * NAME
 *   getDestination -- get Destination for the message
 * FUNCTION
 *   Extract the destination of a relay message from a players
 *   email.
 * NOTE
 *   The message should contain the line
 *      Subject:   relay <race name>
 ******
 */

char *
getDestination( char *subject )
{
    int theTurnNumber;
    char *destination;
    char *c;

    theTurnNumber = LG_CURRENT_TURN;

    /*plog(LBRIEF, ">getDestination(%s)\n", subject); */

    c = strlwr( strdup( subject ) );

    if ( ( destination = strstr( c, "relay" ) ) == NULL ) {
        plog( LBRIEF, "  subject does not have \"relay\" in it\n" );
        return NULL;            /* can't be a relay subject */
    } else
        destination += 5;

    while ( isspace( *destination ) )
        destination++;

    destination = strdup( destination );
    free( c );

    /*plog(LBRIEF, "<getDestination(%s)\n", destination); */

    return destination;
}





/****f* Process/doOrders
 * NAME
 *   doOrders -- carry out all orders.
 * SYNOPSIS
 *   void doOrders(game *aGame, player *aPlayer, 
 *                 orderinfo *orderInfo, int phase)
 * FUNCTION
 *   Carry out all orders for one player. 
 * SOURCE
 */

void
doOrders( game *aGame, player *aPlayer, orderinfo *orderInfo, int phase )
{
    strlist *s;
    orderinfo *op;

    plog( LFULL, "doOrders: Phase %d Race %s\n", phase, aPlayer->name );

    pdebug( DFULL, "doOrders\n" );
    pdebug( DFULL2, "  Phase %d Race %s\n", phase, aPlayer->name );
    for ( s = aPlayer->orders; s; ) {
        char *order;

        pdebug( DFULL2, "  Order %s\n", s->str );
        for ( order = getstr( s->str );
              ( s ) && ( phase != 1 ) && ( *order eq '@' ); ) {
            plog( LFULL, "order: %s phase:%d\n", order, phase );
            for ( s = s->next; s; s = s->next ) {
                order = getstr( s->str );
                if ( *order eq '@' )
                    break;
            }
            if ( s ) {
                s = s->next;
                if ( s )
                    order = getstr( s->str );
            }
        }

        if ( s ) {
            order = getstr( s->str );
            for ( op = orderInfo; op->name != 0; op++ ) {
                if ( noCaseStrncmp( op->name, order, ORDER_SIZE ) == 0 ) {
                    ( *( op->func ) ) ( aGame, aPlayer, &s );
                    break;
                }
            }
        }
        if ( s )
            s = s->next;
    }
}

/***************/

/****f* Process/removeDeadPlayer 
 * NAME
 *   removeDeadPlayer -- Removes idle players 
 * FUNCTION
 *   Check if a player last sent-in orders, and if this was too
 *   long ago the player is removed from the game. 
 * SOURCE
 */

void
removeDeadPlayer( game *aGame )
{
    player *P;
    player *P3;
    int allowedOrderGap;
    int nbrPlanets;

    pdebug( DFULL, "removeDeadPlayer\n" );
    allowedOrderGap = ( aGame->turn < ENDPHASE1TURN ) ? ORDERGAP1 : ORDERGAP2;
    for ( P = aGame->players; P; P = P3 ) {
        P3 = P->next;
        if ( P->addr[0] ) {
            int idleTurns;

            idleTurns = ( P->lastorders ) ? aGame->turn - P->lastorders :
                allowedOrderGap + 1;
            plog( LFULL, "Player %s idle turns %d\n", P->name, idleTurns );
            if ( idleTurns != 0 ) {
                if ( idleTurns < allowedOrderGap ) {
                    int gap = allowedOrderGap - idleTurns;
                    sprintf( lineBuffer, "\n\
*** NOTE: You didn't send orders this turn.  You have %d more turn%s to\n\
*** remain idle before you forfeit your position.", gap, &"s"[gap == 1] );

                    addList( &P->messages, makestrlist( lineBuffer ) );
                } else if ( idleTurns == allowedOrderGap ) {
                    addList( &P->messages, makestrlist( "\n\
*** WARNING: If you do not send orders for this next turn then you will\n\
*** forfeit your position in the game!  Please send orders next turn if you\n\
*** wish to continue playing." ) );
                } else if ( idleTurns > allowedOrderGap ) {
                    planet *p;

                    P->flags |= F_DEAD;

/*                    if ( aGame->turn < ENDPHASE1TURN ) {*/
                    P->groups = NULL;
                    nbrPlanets = 0;
                    for ( p = aGame->planets; p; p = p->next ) {
                        if ( p->owner eq P ) {
                            nbrPlanets++;
                            plog( LPART, "Resetting planet %s\n", p->name );
                            p->col = 0;
                            p->producing = PR_CAP;
                            p->producingshiptype = 0;
                            p->inprogress = 0;
                            memset( p->routes, 0, sizeof( p->routes ) );
                            p->pop = 0;
                            p->ind = 0;
                            p->cap = 0;
                            p->mat = 0;
                            p->owner = NULL;
                        }
                    }
                    if ( nbrPlanets ) {
                        plog( LPART, "Discontinuing reports for %s\n",
                              P->name );
                        sprintf( lineBuffer,
                                 "\n-*-*-*-\n%s had an unfortunate accident and was "
                                 "obliterated.\n-*-*-*-\n", P->name );
                        addList( &( aGame->messages ),
                                 makestrlist( lineBuffer ) );
                    }
/*                    }*/
                }
            }
        }
    }
}


void
cleanDeadPlayers( game *aGame )
{
    player *P;
    player *P3;
    int allowedOrderGap;

    pdebug( DFULL, "removeDeadPlayer\n" );
    allowedOrderGap = ( aGame->turn < ENDPHASE1TURN ) ? ORDERGAP1 : ORDERGAP2;
    for ( P = aGame->players; P; P = P3 ) {
        P3 = P->next;
        if ( P->addr[0] ) {
            int idleTurns;

            idleTurns = ( P->lastorders ) ? aGame->turn - P->lastorders :
                allowedOrderGap + 1;
            plog( LFULL, "Player %s idle turns %d\n", P->name, idleTurns );
            if ( idleTurns != 0 ) {
                if ( idleTurns < allowedOrderGap ) {
                    int gap = allowedOrderGap - idleTurns;
                    sprintf( lineBuffer, "\n\
*** NOTE: You didn't send orders this turn.  You have %d more turn%s to\n\
*** remain idle before you forfeit your position.", gap, &"s"[gap == 1] );

                    addList( &P->messages, makestrlist( lineBuffer ) );
                } else if ( idleTurns == allowedOrderGap ) {
                    addList( &P->messages, makestrlist( "\n\
*** WARNING: If you do not send orders for this next turn then you will\n\
*** forfeit your position in the game!  Please send orders next turn if you\n\
*** wish to continue playing." ) );
                } else if ( idleTurns > allowedOrderGap ) {
                    planet *p;

                    plog( LPART, "Discontinuing reports for %s\n", P->name );
                    P->flags |= F_DEAD;

/*                    if ( aGame->turn < ENDPHASE1TURN ) {*/
                    P->groups = NULL;
                    sprintf( lineBuffer,
                             "\n-*-*-*-\n%s had an unfortunate accident and was "
                             "obliterated.\n-*-*-*-\n", P->name );
                    addList( &( aGame->messages ),
                             makestrlist( lineBuffer ) );

                    for ( p = aGame->planets; p; p = p->next ) {
                        if ( p->owner eq P ) {
                            plog( LPART, "Resetting planet %s\n", p->name );
                            p->col = 0;
                            p->producing = PR_CAP;
                            p->producingshiptype = 0;
                            p->inprogress = 0;
                            memset( p->routes, 0, sizeof( p->routes ) );
                            p->pop = 0;
                            p->ind = 0;
                            p->cap = 0;
                            p->mat = 0;
                            p->owner = NULL;
                        }
                    }
/*                    }*/
                }
            }
        }
    }
}

/***********/


/****f* Process/preComputeGroupData
 * NAME
 *   preComputeGroupData -- precompute some frequently used values.
 * FUNCTION
 *   This is a very nasty function that precomputes some properties of
 *   groups.  This speeds up turn processing but also creates some
 *   serious problems when the function is not called at the right
 *   time.  A very nice case of premature optimization.
 * SOURCE
 */

void
preComputeGroupData( game *aGame )
{
    player *aPlayer;
    group *aGroup;

    for ( aPlayer = aGame->players; aPlayer; aPlayer = aPlayer->next ) {
        for ( aGroup = aPlayer->groups; aGroup; aGroup = aGroup->next ) {
            aGroup->attack = groupAttack( aGroup );
            aGroup->defense = groupDefense( aGroup );
            aGroup->location = groupLocation( aGame, aGroup );
        }
    }
}

/**********/


/****f* Process/generateErrorMessage 
 * NAME
 *   generateErrorMessage -- create error message for faulty orders.
 * FUNCTION
 *   
 * INPUTS
 *    resNumber -- The kind of error.
 *    forecast  -- file to write the message to.
 * SOURCE
 */

void
generateErrorMessage( int resNumber, game *aGame,
                      char *raceName, int theTurnNumber, FILE *forecast )
{
    switch ( resNumber ) {
    case RES_NO_ORDERS:
        fprintf( forecast, "O Wise Leader, your mail did not contain any "
                 "orders.\nRemember orders start with\n\n"
                 "#GALAXY GameName RaceName Password TurnNumber "
                 "[FinalOrders]\n\nand end with\n\n#END\n" );
        break;

    case RES_ERR_GALAXY:
        fprintf( forecast, "O Wise Leader, you must supply your race name "
                 "and galaxy name.\n Remember orders start with,\n\n"
                 "#GALAXY GameName RaceName Password TurnNumber "
                 "[FinalOrders]\n\nand end with\n\n#END\n" );
        break;

    case RES_NO_GAME:
        fprintf( forecast, "O Wise Leader, there is no galaxy called %s.\n"
                 "This probably means that you mispelled the galaxy name "
                 "in your orders\n", aGame->name );
        break;

    case RES_PASSWORD:
        fprintf( forecast, "O Wise Leader, the password you gave is "
                 "incorrect.\n" );
        break;

    case RES_PLAYER:
        fprintf( forecast, "O Wise Leader there is no race called %s.\n"
                 "This probably means that you mispelled your "
                 "race name.\n", raceName );
        break;

    case RES_TURNRAN:
        fprintf( forecast, "O Wise Leader, you sent in orders for turn %d "
                 "but that turn already ran.\nThe next turn is %d.",
                 theTurnNumber, aGame->turn + 1 );
        break;

    case RES_DESTINATION:
        fprintf( forecast, "O Wise Leader, the recipient of the message "
                 "you sent does not exist.\n" );
        break;

    case RES_NODESTINATION:
        fprintf( forecast, "O Wise Leader, you failed to give a "
                 "destination for your message.\n" );
        break;

    case RES_NO_TURN_NBR:
        fprintf( forecast, "O Wise Leader, you didn't specify a turn "
                 "number.\nRemember that orders start with\n\n"
                 "#GALAXY GameName RaceName Password TurnNumber "
                 "[FinalOrders]\n\n" "and end with\n\n#END\n" );
        break;
    }
    fprintf( forecast,
             "\nYour orders have been discarded!\n"
             "Please correct the mistake and retransmit your orders.\n" );
}

/***********/
