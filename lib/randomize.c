#include "galaxy.h"
#include "list.h"

char *vrandomize = "$Id$";

/*
 * this is a routine to randomize the players list so that the lowest
 * number doesn't always get the advantage.
 */

player *
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

  return randList;
}
