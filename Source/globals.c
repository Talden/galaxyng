#include "galaxy.h"

char            map[MAPWIDTH][MAPHEIGHT];
char            buf[LINE_BUFFER_SIZE];

/****v* GalaxyNG/lineBuffer
 * NAME
 *   lineBuffer -- global line buffer.
 * NOTES
 *   2 is there to prevent buffer overflows.
 * SOURCE
 */

char            lineBuffer[2 * LINE_BUFFER_SIZE];

/******/


/****v* GalaxyNG/productname
 * NAME
 *   productname -- things a planet can produce.
 * SOURCE
 */

char           *productname[] = {
  "CAP", "MAT", 0, "Drive", "Weapons", "Shields", "Cargo",
};

/******/

int             nbrProducts = sizeof(productname) / sizeof(char *);

FILE           *turnFile = NULL;


/****v* GalaxyNG/logFile
 * NAME
 *   logFile -- 
 * SOURCE
 */

FILE           *logFile = NULL;

/******/


/****v* GalaxyNG/logLevel
 * NAME
 *   logLevel -- specifies the level of detail in log files.
 * SOURCE
 */

int             logLevel = LFULL;

/******/

int             debugLevel = DERR;      /* DFULL2; */

/****v* GalaxyNG/galaxynghome
 * NAME
 *   galaxynghome -- path to all data files
 * SOURCE
 */

char           *galaxynghome = NULL;

/*****/

/****v* GalaxyNG/tempdir
 * NAME
 *   tempdir -- path to the directory used to store temporary files.
 * SOURCE
 */

char           *tempdir = NULL;

/*****/


/****v* GalaxyNG/options
 * NAME 
 *   options -- options available to players. 
 * FUNCTION
 *   Associative array to look-up option flag by option names. 
 * SOURCE
 */

struct option   options[] = {
  {"Anonymous", F_ANONYMOUS},
  {"AutoUnload", F_AUTOUNLOAD},
  {"ProdTable", F_PRODTABLE},
  {"SortGroups", F_SORTGROUPS},
  {"GroupForeCast", F_GROUPFORECAST},
  {"PlanetForeCast", F_PLANETFORECAST},
  {"ShipTypeForecast", F_SHIPTYPEFORECAST},
  {"RoutesForecast", F_ROUTESFORECAST},
  {"Compress", F_COMPRESS},
  {"Gplus", F_GPLUS},
  {"MachineReport", F_MACHINEREPORT},   /* CB 1998 - Experimental */
  {"BattleProtocol", F_BATTLEPROTOCOL},
  {"XMLReport", F_XMLREPORT},   /* KDW 1999 - experimental */
  {NULL, 0}
};

/**********/
