#include <assert.h>
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
  FILE*      mapfile;		/* output for map */
  char*      err;

  gdImagePtr map;		/* image */
  int        white;		/* colour indices */

  double     scale;
  double     max_resource = 0.0;

  int        brect[8];
  int        i;
  char*      font = "cranberr";
  int        nation_colors[41][4] = {
    {255,  255,  255, 0}, /* white */
    {255,  250,  205, 0}, /* lemon chiffon */
    {235,  245,  230, 0}, /* mint cream */
    {240,  255,  255, 0}, /* azure */
    {230,  230,  250, 0}, /* lavender */
    {255,  228,  225, 0}, /* misty rose */
    {100,  149,  237, 0}, /* cornflower blue */
    {132,  112,  255, 0}, /* light slate blue */
    {135,  206,  250, 0}, /* light sky blue */
/**/{176,  224,  230, 0}, /* powder blue */
    {  0,  206,  209, 0}, /* dark turquoise */
    {  0,  255,  255, 0}, /* cyan */
    {102,  205,  170, 0}, /* medium aquamarine */
    { 85,  107,   47, 0}, /* dark olive green */
    { 46,  139,   87, 0}, /* sea green */
    {152,  251,  152, 0}, /* pale green */
    {  0,  255,  127, 0}, /* spring green */
    {173,  255,   47, 0}, /* green yellow */
    {107,  142,   35, 0}, /* olive drab */
/**/{238,  232,  170, 0}, /* pale goldenrod */
    {255,  215,    0, 0}, /* gold */
    {205,   92,   92, 0}, /* indian red */
    {222,  184,  135, 0}, /* burlywood */
    {178,   34,   34, 0}, /* firebrick */
    {255,  160,  122, 0}, /* light salmon */
    {255,  140,    0, 0}, /* dark orange */
    {240,  128,  128, 0}, /* light coral */
    {255,   99,   71, 0}, /* tomato */
    {255,  105,  180, 0}, /* hot pink */
/**/{219,  112,  147, 0}, /* pale violet red */
    {176,   48,   96, 0}, /* maroon */
    {186,   85,  211, 0}, /* medium orchid */
    {148,    0,  211, 0}, /* dark violet */
    {255,  250,  250, 0}, /* snow1 */
    {193,  255,  193, 0}, /* DarkSeaGreen1 */
    {255,  246,  143, 0}, /* khaki1 */
    {238,  220,  130, 0}, /* LightGoldenrod2 */
    {205,  155,  155, 0}, /* RosyBrown3 */
    {238,  154,   73, 0}, /* tan2 */
    {139,   95,  101, 0}, /* LightPink4 */
    {205,  150,  205, 0}, /* plum3 */
  };

  sprintf(buf, "%s/data/%s/%d.png", galaxynghome, aGame->name, aGame->turn);
  mapfile = GOS_fopen(buf, "wb");

  map = gdImageCreateTrueColor(1024, 768);
  white = gdImageColorAllocate(map, 255, 255, 255);
  for (i = 0; i <= 40; i++) {
    nation_colors[i][3] = gdImageColorAllocate(map, nation_colors[i][0],
					       nation_colors[i][1],
					       nation_colors[i][2]);
  }
  gdImageRectangle(map, 0, 0, 1023, 767, white);
  gdImageLine(map, 767, 0, 767, 767, white);
  gdImageLine(map, 767, 745, 1023, 745, white);
  sprintf(buf, "%s   Turn: %d", aGame->name, aGame->turn);
  err = gdImageStringFT((gdImagePtr)NULL, &brect[0], white, font,
			12., 0., 0, 0, buf);
  if (err)
    fprintf(stderr, "%s\n", err);
  gdImageStringFT(map, NULL, white, font, 12., 0., 896-(brect[4]/2), 762, buf);

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

  writeString(vcid); /* Galaxy version*/
  writeInt(aGame->turn);
  writeFloat(aGame->galaxysize);

#if defined(DRAW_MAP)
  scale = 765.0 / aGame->galaxysize;
#endif

  writeString("@GameOptions"); /* CB-20010407*/
  writeFloat(aGame->gameOptions.gameOptions);
  writeFloat(aGame->gameOptions.initial_drive);
  writeFloat(aGame->gameOptions.initial_weapons);
  writeFloat(aGame->gameOptions.initial_shields);
  writeFloat(aGame->gameOptions.initial_cargo);
  writeString("@EGameOptions");

  writeString("@Players");
#if defined(DRAW_MAP)
  i = 1;
#endif
  for (P = aGame->players; P; P = P->next) {
    shiptype       *aShipType;
    fleetname      *aFleetName;

#if defined(DRAW_MAP)
    err = gdImageStringFT(map, NULL, nation_colors[i][3], font, 10., 0.,
			  770, 3+(i*15), P->name);
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
    double this_res;
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
      { int rel_size;
      rel_size = (int)(10 * (((p->size*p->resources)/max_resource))+ 0.5);
      fprintf(stderr, "%s %d (%d)\n", p->name, ptonum(aGame->players, owner),
	      rel_size);
      gdImageFilledArc(map, (int)((scale*p->x)+1), (int)((scale*p->y)+1),
		       (int)rel_size, (int)rel_size, 0, 360,
		       nation_colors[ptonum(aGame->players, owner)][3],
		       gdArc);
      }
#endif
    }
    else {
      writeInt(0);
#if defined(DRAW_MAP)
      { int rel_size;
      rel_size = (int)(10 * (((p->size*p->resources)/max_resource))+ 0.5);
      rel_size = rel_size < 1 ? 1 : rel_size;
      fprintf(stderr, "%s %d (%d)\n", p->name, 0, rel_size);
      if (rel_size == 1)
	gdImageSetPixel(map, (int)((scale*p->x)+1), (int)((scale*p->y)+1),
			nation_colors[0][3]);
      else
	gdImageFilledArc(map, (int)((scale*p->x)+1), (int)((scale*p->y)+1),
			 (int)rel_size, (int)rel_size, 0, 360,
			 nation_colors[0][3], gdArc);
      }
#endif
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
#if defined(DRAW_MAP)
  gdImagePng(map, mapfile);
  fclose(mapfile);
  gdImageDestroy(map);
#endif
}

/****/
