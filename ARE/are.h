#if !defined(ARE_H_)
#define ARE_H_

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>

#include "list.h"
#include "galaxy.h"
#include "mail.h"

typedef struct _planetTemplate {
  /* basic list structure */
  struct _planetTemplate* next;
  long                    cookie;
  char*                   name;
  /* end basic list */
  float     size;
  float     res;
  float     pop;
  float     ind;
  float     cap;
  float     col;
  float     mat;
} planetTemplate;


/****v* ARE/planetSpec
 * NAME
 *   planetSpec -- the GM creates the specs for the planets to be
 *   created when the game is created. the player can do a limited
 *   override in regards to name and size (size within constraints)
 *
 *   $GALACYNGHOME/.arerc file in XML format, includes list of games
 * SOURCE
 */

typedef struct _planetSpec {
  float    res_min;
  float    res_max;
  float    radius;
  float    size_min;
  float    size_max;
  float    size_total;
  int      count_min;
  int      count_max;
  planetTemplate* pt;
} planetSpec; 


/****v* ARE/playerOpts
 * NAME
 *   playerOpts -- options for players, replaces passing many parameters
 * SOURCE
 */

typedef struct _playerOpts {
  /* basic list structure */
  struct _playerOpts*  next;
  long                 cookie;
  char*                name;	/* player's race name, for uniqueness */
  /* end basic list */
  char* email;			/* where to get reports at */
  char* password;		/* new password */

  char* real_name;		/* for the HoF */

  /* map options */
  float x;
  float y;
  float size;

  /* planets the player is specifying */
  planet* planets;
  long  options;
} playerOpts;

/****v* ARE/gameOpts
 * NAME
 *   gameOpts -- options GM sets for a game, read from
 *   $GALAXYNGHOME/.arerc file in XML format
 * NOTES
 *   this structure is meant to take the place of the .glx file. if
 *   the game is set up to use the ARE then game creation will come
 *   entirely from this structure, no .glx is needed (or will be
 *   looked at)
 *
 *   some usage notes:
 *   1) this structure allows for a range of players to sign up: set 
 *   minumum_players == maximum_players if you want exactly that
 *   number of players to join before starting.
 *
 *   2) minumum_planets is the minimum number of planets that the
 *   player *must* specify in their orders, maximum_planets is the
 *   number of planets that the player can't exceed. set
 *   minimum_planets == maximum planets to force the player to declare
 *   that number of planets. these numbers only matter if the player
 *   specifies *any* planets. if the player does not specify planets
 *   then the default sizes specified by the GM in the game
 *   configuration will be used.
 *
 * SOURCE
 */

typedef struct _gameOpts {
	/* basic list structure */
	struct _gameOpts*  next;
	long               cookie;
	char*              name;
	/* end basic list */
	char*  from;			/* email information for mail going
							   back to registering player. if
							   information is not found here, the
							   generic information from the server
							   will be used*/
	char*  sub_succeed;	/* subject for successful registration */
	char*  sub_fail;		/* subject for failed registration */
	char*  replyto;
	char*  cc;
	int    minplayers;		/* at least this many players must
							   sign up */
	int    maxplayers;		/* no more than this number can sign
							   up */
	int    galaxy_size;		/* size of the galaxy */
	float  nation_spacing;	/* how far apart nations must be */
	int    pax_galactica;		/* number of turns of enforced peace */
	float  initial_drive;		/* initial tech levels, must be at
								   least 1.0 */
	float  initial_weapons;
	float  initial_shields;
	float  initial_cargo;
	long   game_options;		/* game option flags */
	planetSpec home;
	planetSpec dev;
	planetSpec stuff;
	planetSpec asteroid;
	playerOpts* po;		/* players signed up for the game */
} gameOpts;
  

/****v* ARE/serverOpts
 * NAME
 *   serverOpts -- options GM sets for a server, read from
 *   $GALACYNGHOME/.arerc file in XML format, includes list of games
 * SOURCE
 */

typedef struct _serverOpts {
	char* from;					/* default email information, can be
								   overridden in each game */
	char*  sub_succeed;			/* subject for successful registration */
	char*  sub_fail;			/* subject for failed registration */
	char* replyto;
	char* cc;
	gameOpts* games;			/* list of games registration is being
								   accepted for*/
} serverOpts;


/* function prototypes, unique to ARE */
int   countPlayersRegistered(char* gameName);
int   registerPlayer(playerOpts* po, char* gameName, int type);
void  playerMessage(playerOpts* po, char* gameName);
void  standbyMessage(char* gameName);
int   getPlanetSizes(FILE *orders, char **planets, double totalPlanetSize,
		     int maxNumberOfPlanets, double maxPlanetSize);
char* getReturnAddress(FILE *orders);
void  badPlanetMessage(char *planets);
serverOpts* loadAREConfig(const char* gamename);

#endif
