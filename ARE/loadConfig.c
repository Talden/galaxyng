/* This is simple demonstration of how to use expat. This program
reads an XML document from standard input and writes a line with the
name of each element to standard output indenting child elements by
one tab stop more than their parent element. */

#include <stdio.h>
#include "xmlparse.h"
#include "list.h"
#include "are.h"

enum element_context {server_context, game_context, core_context};

static char** curElement;
static gameOpts* go = NULL;
static int tagContext = 0;
static serverOpts* so = NULL;
static enum element_context context = server_context;
static int core_idx = 0;


void
startElement (void *userData, const char *name, const char **atts)
{
  tagContext = 1;

  if (noCaseStrcmp (name, "are") == 0) {
    if (strcmp(atts[1], "1.0") != 0)
      fprintf(stderr, "unrecognized ARE version, continuing\n");
    tagContext = 0;
  }
  else if (noCaseStrcmp(name, "server") == 0) {
    context = server_context;
    tagContext = 0;
  }
  else if (noCaseStrcmp(name, "from") == 0) {
    switch(context) {
    case server_context:
      curElement = &so->from;
      break;
    case game_context:
      curElement = &go->from;
      break;
    case core_context:
      break;
    }
  }
  else if (noCaseStrcmp(name, "subject") == 0) {
    switch(context) {
    case server_context:
      if (noCaseStrcmp(atts[1], "success") == 0)
	curElement = &so->succeed_subject;
      else
	curElement = &so->fail_subject;
      break;
    case game_context:
      if (noCaseStrcmp(atts[1], "success") == 0)
	curElement = &go->succeed_subject;
      else
	curElement = &go->fail_subject;
      break;
    case core_context:
      break;
    }
  }
  else if (noCaseStrcmp(name, "replyto") == 0) {
    switch(context) {
    case server_context:
      curElement = &so->replyto;
      break;
    case game_context:
      curElement = &go->replyto;
      break;
    case core_context:
      break;
    }
  }
  else if (noCaseStrcmp(name, "cc") == 0) {
    curElement = &so->cc;
  }
  else if (noCaseStrcmp(name, "game") == 0) {
    tagContext = 0;
    go = allocStruct(gameOpts);
    assert(go != NULL);
    go->next = NULL;
    go->from = NULL;
    go->succeed_subject = NULL;
    go->fail_subject = NULL;
    go->minplayers = 0;
    go->maxplayers = 0;
    go->delay_hours = 0;
    go->totalplanetsize = 0.0;
    go->maxplanetsize = 0.0;
    go->minplanets = 0;
    go->maxplanets = 0;
    go->galaxy_size = 0.0;
    go->nation_spacing = 0.0;
    go->core_sizes = (float*)malloc(sizeof(float));
    go->core_sizes[0] = -1;
    go->growth_planets_count = 0;
    go->growth_planets_radius = 0.0;
    go->stuff_planets = 0;
    go->pax_galactica = 0;
    go->initial_drive = 1.0;
    go->initial_shields = 1.0;
    go->initial_shields = 1.0;
    go->initial_cargo = 1.0;
    go->game_options = 0;
    setName(go,atts[1]);
    context = game_context;
  }
  else if (noCaseStrcmp(name, "core_sizes") == 0) {
    int nbr_core = atoi(atts[1]);
    free(go->core_sizes);
    go->core_sizes = (float*)malloc(sizeof(float)*(nbr_core+1));
    go->core_sizes[nbr_core] = -1;
    context = core_context;
  }
  else if (noCaseStrcmp(name, "minplayers") == 0) {
    curElement = (char**)&go->minplayers;
  }
  else if (noCaseStrcmp(name, "maxplayers") == 0) {
    curElement = (char**)&go->maxplayers;
  }
  else if (noCaseStrcmp(name, "totalplanetsize") == 0) {
    curElement = (char**)&go->totalplanetsize;
  }
  else if (noCaseStrcmp(name, "maxplanetsize") == 0) {
    curElement = (char**)&go->maxplanetsize;
  }
  else if (noCaseStrcmp(name, "minplanets") == 0) {
    curElement = (char**)&go->minplanets;
  }
  else if (noCaseStrcmp(name, "maxplanets") == 0) {
    curElement = (char**)&go->maxplanets;
  }
  else if (noCaseStrcmp(name, "galaxy_size") == 0) {
    curElement = (char**)&go->galaxy_size;
  }
  else if (noCaseStrcmp(name, "planet") == 0) {
    if (context == core_context) {
      core_idx = atoi(atts[1]) - 1;
      curElement = (char**)&go->core_sizes;
    }
  }
  else {
    tagContext = 0;
    printf("unrecognized element %s\n", name);
  }
}

void
endElement (void *userData, const char *name)
{
  if (noCaseStrcmp(name, "game") == 0) {
    addList(&so->go, go);
    context = server_context;
    go = NULL;
  }
  else if (noCaseStrcmp(name, "core_sizes") == 0) {
    context = game_context;
  }
  
  tagContext = 0;
  curElement = NULL;
  return;
}

void
contentData(void* userData, const char* text, int len)
{
  char ltext[1024];

  if (!tagContext || curElement == NULL)
    return;
  
  sprintf(ltext, "%*.*s", len, len, text);
  
  if (go) {
    if (curElement == &go->from) {
      if (*curElement == NULL)
	*curElement = strdup(ltext);
      else {
	int newlen = strlen(*curElement) + len + 1;
	*curElement = (char*)realloc(*curElement, newlen);
	strcat(*curElement, ltext);
      }
    }
    else if (curElement == (char**)&go->minplayers) {
      go->minplayers = atoi(ltext);
    }
    else if (curElement == (char**)&go->maxplayers) {
      go->maxplayers = atoi(ltext);
    }
    else if (curElement == (char**)&go->totalplanetsize) {
      go->totalplanetsize = atof(ltext);
    }
    else if (curElement == (char**)&go->maxplanetsize) {
      go->maxplanetsize = atof(ltext);
    }
    else if (curElement == (char**)&go->minplanets) {
      go->minplanets = atoi(ltext);
    }
    else if (curElement == (char**)&go->maxplanets) {
      go->maxplanets = atoi(ltext);
    }
    else if (curElement == (char**)&go->galaxy_size) {
      go->galaxy_size - atof(ltext);
    }
    else if (curElement == (char**)&go->core_sizes) {
      go->core_sizes[core_idx] = atof(ltext);
    }
    else {
      if (*curElement == NULL)
	*curElement = strdup(ltext);
      else {
	int newlen = strlen(*curElement) + len + 1;
	*curElement = (char*)realloc(*curElement, newlen);
	strcat(*curElement, ltext);
      }
    }
  }
  else {
    if (*curElement == NULL)
      *curElement = strdup(ltext);
    else {
      int newlen = strlen(*curElement) + len + 1;
      *curElement = (char*)realloc(*curElement, newlen);
      strcat(*curElement, ltext);
    }
  }
}

void
dumpGameOptData(void* data)
{
    gameOpts* go = (gameOpts*)data;
    int i;

    fprintf(stderr, "  from: %s\n", go->from);

    if (go->succeed_subject)
      fprintf(stderr, "  subject (succeed): %s\n", go->succeed_subject);
    if (go->fail_subject)
      fprintf(stderr, "  subject (failed): %s\n", go->fail_subject);
    if (go->replyto)
      fprintf(stderr, "  replyto: %s\n", go->replyto);

    fprintf(stderr, "  playerlimit: %d to %d\n", go->minplayers,
	    go->maxplayers);
    fprintf(stderr, "  delay_hours: %d\n", go->delay_hours);

    fprintf(stderr, "  totalplanetsize: %f\n", go->totalplanetsize);
    fprintf(stderr, "  maxplanetsize: %f\n", go->maxplanetsize);
    fprintf(stderr, "  planets: %d to %d\n", go->minplanets, go->maxplanets);
    fprintf(stderr, "  galaxy_size: %f\n", go->galaxy_size);
    fprintf(stderr, "  nation_spacing: %f\n", go->nation_spacing);
    fprintf(stderr, "  core planets: ");
    for (i = 0; go->core_sizes[i] != -1; i++)
      fprintf(stderr, " %f ", go->core_sizes[i]);
    fprintf(stderr, "\n");
    fprintf(stderr, "%d growth planets within %f\n",
	    go->growth_planets_count, go->growth_planets_radius);
    fprintf(stderr, "Pax Galactica: %d\n", go->pax_galactica);
    fprintf(stderr, "initial tech: %.2f %.2f %.2f %.2f\n",
	    go->initial_drive, go->initial_weapons, go->initial_cargo,
	    go->initial_cargo);
}

serverOpts*
loadConfig (const char *galaxynghome)
{
    FILE *areFP;
    char arename[BUFSIZ];
    char buf[BUFSIZ];
    XML_Parser parser = XML_ParserCreate (NULL);
    int done;
    int depth = 0;
    gameOpts *go;
    so = (serverOpts*)malloc(sizeof(serverOpts));

    XML_SetUserData (parser, NULL);
    XML_SetElementHandler (parser, startElement, endElement);
    XML_SetCharacterDataHandler(parser, contentData);

    so->from = NULL;
    so->succeed_subject = NULL;
    so->fail_subject = NULL;
    so->replyto = NULL;
    so->cc = NULL;
    so->go = NULL;

    sprintf (arename, "%s/.arerc", galaxynghome);
    if ((areFP = fopen (arename, "r")) == NULL) {
	plog (LPART, "Could not open \"%s\" for input.\n", arename);
	return NULL;
    }

    do {
	size_t len = fread (buf, 1, sizeof (buf), areFP);
	done = len < sizeof (buf);
	if (!XML_Parse (parser, buf, len, done)) {
	    fprintf (stderr, "%s at line %d\n",
			XML_ErrorString (XML_GetErrorCode (parser)),
			XML_GetCurrentLineNumber (parser));
	    return NULL;
	}
    } while (!done);

    fprintf(stderr, "so->from: \"%s\"\n", so->from);
    fprintf(stderr, "so->succeed_subject: \"%s\"\n", so->succeed_subject);
    fprintf(stderr, "so->fail_subject: \"%s\"\n", so->fail_subject);
    fprintf(stderr, "so->replyto: \"%s\"\n", so->replyto);
    fprintf(stderr, "so->cc: \"%s\"\n", so->cc);

    dumpList("games", (list*)so->go, dumpGameOptData);

    XML_ParserFree (parser);
    return so;
}

#if defined(LoadConfigMainNeeded)

int
main (int argc, char *argv[])
{
  serverOpts *so;

  so = loadConfig ("/home/kenw/Games");
}

#endif
