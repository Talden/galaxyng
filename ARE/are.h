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

typedef struct _gameopts {
  /* basic list structure */
  struct _gameopts* next;
  long              cookie;
  char*             name;
  /* end basic list */
  char* from;
  int   playerlimit;
  float totalplanetsize;
  float maxplanetsize;
  int   maxnbrplanets;
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
char* getstr(char *s);
int   noCaseStrncmp(char *s, char *t, int n);
void  badPlanetMessage(char *planets);
int   loadConfig(serverOpts* so, const char* gamename);

#endif
