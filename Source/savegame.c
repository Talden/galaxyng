#include <assert.h>
#include <string.h>

#include "savegame.h"

/****h* GalaxyNG/SaveGame
 * NAME
 *   SaveGame -- a number of functions to save a turn to file.
 * FUNCTION
 *   The whole game structure is written to file in a structured way.
 *   All data is written in ASCII format. Each value is written
 *   on a seperate line. And empty line indicates a zero value.
 *   Pointers are converted to index number. This is possible because
 *   all pointers that are used in the game structure are pointers
 *   to elements in a list.
 *
 ****
 * ADDED
 *   The option to write out a .png file of the current map
 *****
 */

char           *vsavegame =
    "$Id$";

#if defined(DRAW_MAP)
struct map_avl {
  struct avl      avl;
  long            key;          /* key is x * 1000 + y */

  /* two are used here, one for current value, one for next value - we'll
   * use modulus to keep track of which one is which and eliminate the
   * need for copying. */
  int             color[2];     /* color of this region */
  int             weight[2];    /* how important */
};

int
cmplong(void *a, void *b)
{
  return ((struct map_avl *) a)->key - ((struct map_avl *) b)->key;
}

struct avl_tree influence;
struct avl_tree holding;

struct map_avl *mnode;

/* nxtIdx will always be (curIdx+1)%2 */
int             curIdx = 0;
int             nxtIdx = 1;

static void
listree(struct avl *a, int m)
{
  int             n = m;
  struct map_avl *ma = (struct map_avl *) a;

  if (a == 0)
    return;
  if (a->right)
    listree(a->right, m + 1);
  while (n--)
    printf("   ");
  printf("%ld/%d/%d (%d)\n", ma->key, ma->color[curIdx],
         ma->weight[curIdx], a->balance);
  if (a->left)
    listree(a->left, m + 1);
}

#endif


/****i* SaveGame/writeString
 * NAME
 *   writeString -- write a string to file.
 *****
 */

void
writeString(char *s)
{
  fprintf(turnFile, "%s\n", s);
}

/****i* SaveGame/writeFloat
 * NAME
 *   writeFloat -- write a float to file.
 *****
 */

void
writeFloat(double d)
{
  if (d != 0)
    fprintf(turnFile, "%g\n", d);
  else
    fprintf(turnFile, "\n");
}

/****i* SaveGame/writeInt
 * NAME
 *   writeInt
 *****
 */

void
writeInt(int i)
{
  if (i)
    fprintf(turnFile, "%d\n", i);
  else
    fprintf(turnFile, "\n");
}

/****i* SaveGame/writeLong
 * NAME
 *   writeLong
 *****
 */

void
writeLong(long l)
{
  if (l)
    fprintf(turnFile, "%ld\n", l);
  else
    fprintf(turnFile, "\n");
}


/****i* SaveGame/savegame
 * NAME
 *   savegame -- save a turn to file.
 * RESULTS
 *   A file with the name <turn number>.new
 *   (optional) a file with the name <turn number>.png
 * NOTES
 *   The extension .new is there cause of historical reasons.
 * BUGS
 *   Uses Fopen().
 * SOURCE
 */

void
savegame(game *aGame)
{
  player         *P;
  planet         *p;

#if defined(DRAW_MAP)
  FILE           *mapfile;      /* output for map */
  char           *err;


  gdImagePtr      map;          /* image */
  int             white;        /* colour indices */

  double          scale;
  double          max_resource = 0.0;

  int             brect[8];
  int             i;
  char           *font = "cranberr";
  int             nation_colors[42][4] = {
    {0, 0, 0, 0},               /* black */
    {255, 255, 255, 0},         /* white */
    {0, 255, 127, 0},           /* spring green */
    {205, 92, 92, 0},           /* indian red */
    {132, 112, 255, 0},         /* light slate blue */
    {193, 255, 193, 0},         /* DarkSeaGreen1 */
    {238, 154, 73, 0},          /* tan2 */
    {100, 149, 237, 0},         /* cornflower blue */
    {85, 107, 47, 0},           /* dark olive green */
    {255, 250, 205, 0},         /* lemon chiffon */
    {235, 245, 230, 0},         /* mint cream */
    {240, 255, 255, 0},         /* azure */
    {230, 230, 250, 0},         /* lavender */
    {255, 228, 225, 0},         /* misty rose */
    {135, 206, 250, 0},         /* light sky blue */
     /**/ {176, 224, 230, 0},   /* powder blue */
    {0, 206, 209, 0},           /* dark turquoise */
    {0, 255, 255, 0},           /* cyan */
    {102, 205, 170, 0},         /* medium aquamarine */
    {46, 139, 87, 0},           /* sea green */
    {152, 251, 152, 0},         /* pale green */
    {173, 255, 47, 0},          /* green yellow */
    {107, 142, 35, 0},          /* olive drab */
     /**/ {238, 232, 170, 0},   /* pale goldenrod */
    {255, 215, 0, 0},           /* gold */
    {222, 184, 135, 0},         /* burlywood */
    {178, 34, 34, 0},           /* firebrick */
    {255, 160, 122, 0},         /* light salmon */
    {255, 140, 0, 0},           /* dark orange */
    {240, 128, 128, 0},         /* light coral */
    {255, 99, 71, 0},           /* tomato */
    {255, 105, 180, 0},         /* hot pink */
     /**/ {219, 112, 147, 0},   /* pale violet red */
    {176, 48, 96, 0},           /* maroon */
    {186, 85, 211, 0},          /* medium orchid */
    {148, 0, 211, 0},           /* dark violet */
    {255, 250, 250, 0},         /* snow1 */
    {255, 246, 143, 0},         /* khaki1 */
    {238, 220, 130, 0},         /* LightGoldenrod2 */
    {205, 155, 155, 0},         /* RosyBrown3 */
    {139, 95, 101, 0},          /* LightPink4 */
    {205, 150, 205, 0},         /* plum3 */
  };

  influence.compar = cmplong;
  holding.compar = cmplong;
  influence.root = 0;
  holding.root = 0;

  sprintf(buf, "%s/data/%s/%d_planet.png",
          galaxynghome, aGame->name, aGame->turn);
  mapfile = GOS_fopen(buf, "wb");

  map = gdImageCreateTrueColor(1024, 768);

  for (i = 0; i < 42; i++) {
    fprintf(stderr, "%d\n", i);
    nation_colors[i][3] = gdImageColorAllocate(map, nation_colors[i][0],
                                               nation_colors[i][1],
                                               nation_colors[i][2]);
  }

  white = nation_colors[1][3];

  gdImageRectangle(map, 0, 0, 1023, 767, white);
  gdImageLine(map, 767, 0, 767, 767, white);
  gdImageLine(map, 767, 745, 1023, 745, white);
  gdImageLine(map, 767, 723, 1023, 723, white);
  sprintf(buf, "%s   Turn: %d", aGame->name, aGame->turn);
  err = gdImageStringFT((gdImagePtr) NULL, &brect[0], white, font,
                        12., 0., 0, 0, buf);
  if (err)
    fprintf(stderr, "%s\n", err);
  gdImageStringFT(map, NULL, white, font, 12., 0., 896 - (brect[4] / 2),
                  762, buf);

  strcpy(buf, "Planetary Influence Map");
  err = gdImageStringFT((gdImagePtr) NULL, &brect[0], white, font,
                        12., 0., 0, 0, buf);
  if (err)
    fprintf(stderr, "%s\n", err);
  gdImageStringFT(map, NULL, white, font, 12., 0., 896 - (brect[4] / 2),
                  740, buf);

#endif

  sprintf(buf, "%s/data/%s/next_turn", galaxynghome, aGame->name);
  turnFile = GOS_fopen(buf, "w");
  assert(turnFile != NULL);
  fprintf(turnFile, "%d", aGame->turn + 1);
  fclose(turnFile);

  sprintf(buf, "%s/data/%s/%d.new", galaxynghome, aGame->name,
          aGame->turn);
  turnFile = GOS_fopen(buf, "w");
  assert(turnFile != NULL);
  printf("Saving game %s turn %d...\n", aGame->name, aGame->turn);

  writeString(vcid);            /* Galaxy version */
  writeInt(aGame->turn);
  writeFloat(aGame->galaxysize);

#if defined(DRAW_MAP)
  scale = 765.0 / aGame->galaxysize;
#endif

  writeString("@GameOptions");  /* CB-20010407 */
  writeFloat(aGame->gameOptions.gameOptions);
  writeFloat(aGame->gameOptions.initial_drive);
  writeFloat(aGame->gameOptions.initial_weapons);
  writeFloat(aGame->gameOptions.initial_shields);
  writeFloat(aGame->gameOptions.initial_cargo);
  writeString("@EGameOptions");

  writeString("@Players");
#if defined(DRAW_MAP)
  i = 2;                        /* nations off by 2 due to black/white */
#endif
  for (P = aGame->players; P; P = P->next) {
    shiptype       *aShipType;
    fleetname      *aFleetName;

#if defined(DRAW_MAP)
    err = gdImageStringFT(map, NULL, nation_colors[i][3], font, 10., 0.,
                          770, 3 + ((i - 1) * 15), P->name);
    if (err)
      fprintf(stderr, "%s\n", err);
    i++;
#endif
    writeString(P->name);
    writeString(P->addr);
    writeString(P->pswd);
    writeFloat(P->drive);
    writeFloat(P->weapons);
    writeFloat(P->shields);
    writeFloat(P->cargo);
    writeFloat(P->mx);
    writeFloat(P->my);
    writeFloat(P->msize);

    writeString(P->realName);
    writeInt(P->team);
    writeInt(P->unused3);
    writeInt(P->unused4);
    writeInt(P->unused5);
    writeFloat(P->masslost);
    writeFloat(P->massproduced);
    writeInt(P->lastorders);
    writeLong(P->flags);

    writeString("@ShipTypes");
    for (aShipType = P->shiptypes; aShipType; aShipType = aShipType->next) {
      writeString(aShipType->name);
      writeFloat(aShipType->drive);
      writeInt(aShipType->attacks);
      writeFloat(aShipType->weapons);
      writeFloat(aShipType->shields);
      writeFloat(aShipType->cargo);
    }
    writeString("@EShipTypes");

    writeString("@Fleets");
    for (aFleetName = P->fleetnames;
         aFleetName; aFleetName = aFleetName->next) {
      writeString(aFleetName->name);
    }
    writeString("@EFleets");
  }
  writeString("@EPlayers");

  for (P = aGame->players; P; P = P->next) {
    alliance       *anAlliance;

    writeString("@Allies");
    for (anAlliance = P->allies; anAlliance; anAlliance = anAlliance->next) {
      writeInt(ptonum(aGame->players, anAlliance->who));
    }
    writeString("@EAllies");
  }

  writeString("@Planets");
#if defined(DRAW_MAP)
  {
    double          this_res;

    for (p = aGame->planets; p; p = p->next) {
      if ((this_res = p->size * p->resources) > max_resource)
        max_resource = this_res;
    }
  }
#endif

  for (p = aGame->planets; p; p = p->next) {
    player         *owner;

    writeString(p->name);
    if ((owner = p->owner)) {
      writeInt(ptonum(aGame->players, owner));
#if defined(DRAW_MAP)
      {
        /* add all the elements of colour into the map */
        int             rel_size, weight, x, y, xo, yo, pcolor;

        weight = (int) (p->size * p->resources);
        rel_size = (int) (10 * (weight / max_resource));
        pcolor = ptonum(aGame->players, owner) + 1;
        x = (int) ((scale * p->x) + 1);
        y = (int) ((scale * p->y) + 1);

        for (xo = x - rel_size / 2; xo < x + rel_size / 2; xo++) {
          for (yo = y - rel_size / 2; yo < y + rel_size / 2; yo++) {
            mnode = (struct map_avl *) malloc(sizeof(struct map_avl));
            mnode->key = xo * 1000 + yo;
            mnode->color[curIdx] = pcolor;
            mnode->weight[curIdx] = weight;
            avl_insert(&influence, (struct avl *) mnode);
            fprintf(stderr, "%ld: %d %d\n", mnode->key,
                    mnode->color[curIdx], mnode->weight[curIdx]);
          }
        }
      }
#endif
    }
    else {
      writeInt(0);
    }
    writeFloat(p->x);
    writeFloat(p->y);
    writeFloat(p->size);
    writeFloat(p->resources);
    writeFloat(p->pop);
    writeFloat(p->ind);
    writeInt(p->producing);
    if (p->producingshiptype) {
      assert(owner != NULL);
      writeInt(ptonum(owner->shiptypes, p->producingshiptype));
    }
    else {
      writeInt(0);
    }
    writeFloat(p->cap);
    writeFloat(p->mat);
    writeFloat(p->col);
    writeFloat(p->inprogress);
    writeFloat(p->spent);       /* Should be removed */
  }
  writeString("@EPlanets");

  writeString("@Routes");
  for (p = aGame->planets; p; p = p->next) {
    int             routeIndex;

    for (routeIndex = 0; routeIndex < MAXCARGO; routeIndex++) {
      if (p->routes[routeIndex])
        writeInt(ptonum(aGame->planets, p->routes[routeIndex]));
      else
        writeInt(0);
    }
  }
  writeString("@ERoutes");

  for (P = aGame->players; P; P = P->next) {
    group          *aGroup;

    writeString("@PGroups");
    for (aGroup = P->groups; aGroup; aGroup = aGroup->next) {
      writeInt(ptonum(P->shiptypes, aGroup->type));
      writeInt(aGroup->number);
      writeFloat(aGroup->drive);
      writeFloat(aGroup->weapons);
      writeFloat(aGroup->shields);
      writeFloat(aGroup->cargo);
      writeInt(aGroup->loadtype);
      writeFloat(aGroup->load);
      if (aGroup->from)
        writeInt(ptonum(aGame->planets, aGroup->from));
      else
        writeInt(0);
      if (aGroup->where)
        writeInt(ptonum(aGame->planets, aGroup->where));
      else
        writeInt(0);
      writeFloat(aGroup->dist);
      writeInt(aGroup->ships);
      if (aGroup->thefleet)
        writeInt(ptonum(P->fleetnames, aGroup->thefleet));
      else
        writeInt(0);
    }
    writeString("@EPGroups");
  }
  saveRanTab(turnFile);
  fclose(turnFile);
#if 0
#if defined(DRAW_MAP)
  {
    int             i, j, k, reps, tfact;
    int             io, jo;
    int             most_seen_color, highest_color_count;
    int             colors_seen[42];

    int             offsets[2][8] = {
      {-1, 0, 1, -1, 1, -1, 0, 1},
      {-1, -1, -1, 0, 0, 1, 1, 1}
    };
    int             steady_state = 0;

    for (reps = 0; reps < 50 && !steady_state; reps++) {
      fprintf(stderr,
              "******************************\nRep: %d\n******************************\n",
              reps);

      /* first, add uncharted nodes around each node that has a value */

      addEmpty(influence.root);

      /* now, go through each node in the list, compute its weight by
       * adding up all the neighbors and dividing by number of neighbors
       * 
       * 
       */

      memset(colors_seen, 0, sizeof(int) * 42);

      colors_seen[colormap[i][j]] = weightmap[i][j];

      tfact = 8;

      for (k = 0; k < 8; k++) {
        io = i + offsets[0][k];
        jo = j + offsets[1][k];

        if (io < 0 || io > 767 || jo < 0 || jo > 767) {
          tfact--;
        }
      }

      for (k = 0; k < 8; k++) {
        io = offsets[0][k];
        jo = offsets[1][k];

        if (i + io < 0 || i + io > 767)
          continue;
        if (j + jo < 0 || j + jo > 767)
          continue;

        if ((colormap[i][j] != colormap[i + io][j + jo]) &&
            (colormap[i + io][j + jo] != 0)) {
          tmpmap[i][j] -= weightmap[i + io][j + jo];
        }
        else {
          tmpmap[i][j] += weightmap[i + io][j + jo];
        }

        colors_seen[colormap[i + io][j + jo]] += weightmap[i][j];
      }

      if (tmpmap[i][j] < 0) {
        tmpmap[i][j] *= -1;
      }

      for (k = 0; k < 8; k++) {
        io = i + offsets[0][k];
        jo = j + offsets[1][k];

        if (io < 0 || io > 767 || jo < 0 || jo > 767) {
          tfact--;
        }
      }

      highest_color_count = most_seen_color = 0;
      for (k = 1; k < 42; k++) {
        if (colors_seen[k] > highest_color_count) {
          highest_color_count = colors_seen[k];
          most_seen_color = k;
        }
      }

      tmpcolormap[i][j] = most_seen_color;

      tmpmap[i][j] /= tfact;
    }
  }
#endif
  /* 
   * { int y, z; for (y = 0; y < 767; y++) { for (z = 0; z < 767; z++) {
   * fprintf(stderr, "%5d/%5d/%2d ", weightmap[y][z], tmpmap[y][z],
   * tmpcolormap[y][z]); } fprintf(stderr, "\n"); } } */
  if (memcmp(weightmap, tmpmap, sizeof(weightmap)) == 0) {
    steady_state = 1;
  }
  else {
    memcpy(weightmap, tmpmap, sizeof(weightmap));
    memcpy(colormap, tmpcolormap, sizeof(colormap));
  }
}

for (i = 1; i < 767; i++) {
  for (j = 1; j < 767; j++) {
    gdImageSetPixel(map, i, j, nation_colors[colormap[i][j]][3]);
  }
}
}

gdImagePng(map, mapfile);
fclose(mapfile);
gdImageDestroy(map);
#endif
}

/****/
