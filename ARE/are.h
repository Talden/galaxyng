#if !defined(ARE_H_)
#define ARE_H_

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "expat.h"
#include "galaxy.h"
#include "mail.h"

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
 *   2) delay_hours is the number of hours to wait until generating
 *   the game. this is only used if minimum_players <
 *   maximum_players. set to 0 to allow the GM to start the game
 *   manually. if minimum_players == maximum_players then this value
 *   is ignored.
 *
 *   3) minumum_planets is the minimum number of planets that the
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
  char*  succeed_subject;	/* subject for successful registration */
  char*  fail_subject;		/* subject for failed registration */
  char*  replyto;
  int    minplayers;		/* at least this many players must
				   sign up */
  int    maxplayers;		/* no more than this number can sign
				   up */
  int    delay_hours;		/* wait this long after minimum number
				   of players signed up to start game */
  float  totalplanetsize;	/* total size of planets GM allows
				    player to specify */
  float  maxplanetsize;		/* largest possible planet */
  int    minplanets;		/* minimum number of planets a player
				   can define */
  int    maxplanets;		/* maximum number of planets a player
				   can define */
  float  galaxy_size;		/* size of the galaxy */
  float  nation_spacing;	/* how far apart nations must be */
  float* core_sizes;		/* list of initial planet sizes, can
				   be overridden by registering player
				   input*/
  int    growth_planets_count;	/* number of growth planets */
  float  growth_planets_radius;	/* located within this radius */
  int    stuff_planets;		/* number of filler planets */
  int    pax_galactica;		/* number of turns of enforced peace */
  float  initial_drive;		/* initial tech levels, must be at
				   least 1.0 */
  float  initial_weapons;
  float  initial_shields;
  float  initial_cargo;
  long   game_options;		/* game option flags */
  playerOpts* po;		/* players signed up for the game */
} gameOpts;
  

/****v* ARE/serverOpts
 * NAME
 *   serverOpts -- options GM sets for a server, read from
 *   $GALACYNGHOME/.arerc file in XML format, includes list of games
 * SOURCE
 */

typedef struct _serverOpts {
  char* from;			/* default email information, can be
				   overridden in each game */
  char*  succeed_subject;	/* subject for successful registration */
  char*  fail_subject;		/* subject for failed registration */
  char* replyto;
  char* cc;
  gameOpts* go;			/* list of games registration is being
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
serverOpts* loadConfig(const char* gamename);

#endif
