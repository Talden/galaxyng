#ifndef GNG_SAVEGAME_H
#define GNG_SAVEGAME_H

#include "galaxy.h"
#include "list.h"
#include "util.h"

#if defined(DRAW_MAP)
/* this is to enable the current map to be created as an image */
#include <gd.h>
#include <avl.h>
#endif

void            writeString(char *s);
void            writeFloat(double f);
void            writeInt(int i);
void            writeLong(long l);
void            savegame(game *aGame);

#endif                          /* GNG_SAVEGAME_H */
