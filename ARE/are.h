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
 *   playeropts -- options for players, replaces passing many parameters
 * SOURCE
 */

typedef struct _playerOpts {
  char* planets;
  char* address;
  char  racename[NAMESIZE];
  char  xmlreports;
  char  txtreports;
} playerOpts;

typedef struct gameopts {
  /* basic list structure */
  struct gameopts*  next;
  long              cookie;
  char*             name;
  /* end basic list */
  char* from;
  char* subject;
  char* replyto;
  int   playerlimit;
  float totalplanetsize;
  float maxplanetsize;
  int   maxplanets;
} gameopts;
  
typedef struct _serverOpts {
  char* from;
  char* subject;
  char* replyto;
  char* cc;
  gameopts* go;
} serverOpts;

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
