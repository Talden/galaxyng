#include "galaxy.h"
#include "list.h"

char *vrandomize = "$Id$";

/*
 * this is a routine to randomize the players list so that the lowest
 * number doesn't always get the advantage.
 */

void
randomizePlayers(game *aGame)
{
  player  *randList = NULL;
  player  *curPlayer;
  player  *randPlayer = NULL;

  int      unlinkedPlayers;
  int      nbrPlayers;

  int      usedPlayers[1024];

  memset((void*)usedPlayers, 0, sizeof(int)*1024);

  curPlayer = aGame->players;

  unlinkedPlayers = nbrPlayers = numberOfElements(aGame->players);;

  while(curPlayer != NULL) {
    curPlayer->randNext = NULL;
    curPlayer = curPlayer->next;
  }

  while (unlinkedPlayers > 0) {
    int idx = frand3(nbrPlayers);

    if (usedPlayers[idx] != 0)
      continue;


    usedPlayers[idx] = 1;

    curPlayer = aGame->players;
    while (idx--) {
      curPlayer = curPlayer->next;
    }

    /* first one chosen must be the root */
    if (randPlayer == NULL) {
      randList = randPlayer = curPlayer;
      unlinkedPlayers--;
    }
    else {
      randPlayer->randNext = curPlayer;
      randPlayer = randPlayer->randNext;
      unlinkedPlayers--;
    }
  }

  plog(LFULL, "Randomized players: ");
  for (randPlayer = randList; randPlayer; randPlayer = randPlayer->randNext)
    plog(LFULL, "%s / ", randPlayer->name);
  plog(LFULL, "\n");

  aGame->randPlayers = randList;

  return;
}


/*
 * this is a routine to randomize the planets list so that the lowest
 * number doesn't always get the advantage.
 */

planet *
randomizePlanets(game *aGame)
{
  planet  *randList = NULL;
  planet  *curPlanet;
  planet  *randPlanet = NULL;

  int      unlinkedPlanets;
  int      nbrPlanets;

  int     *usedPlanets = NULL;

  nbrPlanets = numberOfElements(aGame->planets);
  if (usedPlanets == 0) {
    usedPlanets = (int*)malloc(sizeof(int) * nbrPlanets);
  }

  memset((void*)usedPlanets, 0, sizeof(int)*nbrPlanets);

  curPlanet = aGame->planets;

  unlinkedPlanets = nbrPlanets;

  while(curPlanet != NULL) {
    curPlanet->randNext = NULL;
    curPlanet = curPlanet->next;
  }

  while (unlinkedPlanets > 0) {
    int idx = frand3(nbrPlanets);

    if (usedPlanets[idx] != 0)
      continue;

    usedPlanets[idx] = 1;

    curPlanet = aGame->planets;
    while (idx--) {
      curPlanet = curPlanet->next;
    }

    /* first one chosen must be the root */
    if (randPlanet == NULL) {
      randList = randPlanet = curPlanet;
      unlinkedPlanets--;
    }
    else {
      randPlanet->randNext = curPlanet;
      randPlanet = randPlanet->randNext;
      unlinkedPlanets--;
    }
  }

  return randList;
}
