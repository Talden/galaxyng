#include <stdio.h>
#include "xmlparse.h"
#include "list.h"
#include "are.h"
#include "storage.h"

enum element_context {
	unknown, start, are, server, server_data, game, homeworlds, growth, stuff,
	asteroids, player
};

static enum element_context stack[64] = {start};
static int top = 0;
static int line_number = 1;

static char** curElement;
static serverOpts* so = NULL;
static gameOpts* go = NULL;
static playerOpts* po = NULL;

void startElement (void *userData, const char *name, const char **atts) {
	
	enum ELEMENT_VALS element;

	if (*name == '\n') {
		line_number++;
		return;
	}
	
	if ((element = lookupElement(name)) == UnknownElement) {
		fprintf(stderr, "Unexpected element \"%s\", exiting.\n", name);
		exit(EXIT_FAILURE);
	}

	switch(stack[top]) {
		case unknown:			/* this should never happen */
			fprintf(stderr, "TRC: unbalanced stack, line %d\n", line_number);
			exit(EXIT_FAILURE);
			break;
			
		case start:
			if (element != areElement) {
				fprintf(stderr, "Expected <are> at line %d\n", line_number);
				exit(EXIT_FAILURE);
			}

			if (strcmp(atts[1], "1.0") != 0) {
				fprintf(stderr, "unrecognized ARE version, continuing\n");
			}
			stack[++top] = are;
			break;

		case are:
			switch(element) {
				case serverElement:
					stack[++top] = server_data;
					break;

				case gameElement:
					stack[++top] = game_data;
					go = allocStruct(gameOpts);
					assert(go != NULL);
					go->next = NULL;
					go->from = NULL;
					go->succeed_subject = NULL;
					go->fail_subject = NULL;
					go->replyto = NULL;
					go->cc = NULL;
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
					go->initial_weapons = 1.0;
					go->initial_shields = 1.0;
					go->initial_cargo = 1.0;
					go->game_options = 0;
					setName(go,atts[1]);
					break;

				default:
					fprintf(stderr, "Expecting <server> or <game> at line\n",
							line_number);
					break;
			}
			break;

		case server_data:
			switch(element) {
				case fromElement:
					curElement = &so->from;
					break;

				case subjectElement:
					if (noCaseStrcmp(atts[1], "success") == 0)
						curElement = &so->succeed_subject;
					else
						curElement = &so->fail_subject;
					break;

				case replytoElement:
					curElement = &so->replyto;
					break;

				case ccElement:
					curElement = &so->cc;
					break;

				default:
					fprintf(stderr, "Unexpected element \"%s\" at line %d\n",
							name, line_number);
					break;
			}
			break;

		case game_data:
			switch(element) {
				case fromElement:
					curElement = &go->from;
					break;

				case subjectElement:
					if (noCaseStrcmp(atts[1], "success") == 0)
						curElement = &go->succeed_subject;
					else
						curElement = &go->fail_subject;
					break;
					
				case repltytoElement:
					curElement = &go->replyto;
					break;

				case ccElement:
					curElement = &go->cc;
					break;
			}
			break;
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
	else if (noCaseStrcmp(name, "delay_hours") == 0) {
		curElement = (char**)&go->delay_hours;
	}
	else if (noCaseStrcmp(name, "nation_spacing") == 0) {
		curElement = (char**)&go->nation_spacing;
	}
	else if (noCaseStrcmp(name, "planet") == 0) {
		if (context == core_context) {
			core_idx = atoi(atts[1]) - 1;
			curElement = (char**)&go->core_sizes;
		}
	}
	else if (noCaseStrcmp(name, "growth_planets") == 0) {
		context = growth_context;
	}
	else if (noCaseStrcmp(name, "count") == 0) {
		if (context == growth_context) 
			curElement = (char**)&go->growth_planets_count;
	}
	else if (noCaseStrcmp(name, "radius") == 0) {
		if (context == growth_context)
			curElement = (char**)&go->growth_planets_radius;
	}
	else if (noCaseStrcmp(name, "stuff_planets") == 0) {
		curElement = (char**)&go->stuff_planets;
	}
	else if (noCaseStrcmp(name, "paxgalactica") == 0) {
		curElement = (char**)&go->pax_galactica;
	}
	else if (noCaseStrcmp(name, "initial_tech_levels") == 0) {
		context = tech_context;
	}
	else if (noCaseStrcmp(name, "drive") == 0) {
		if (context == tech_context)
			curElement = (char**)&go->initial_drive;
	}
	else if (noCaseStrcmp(name, "weapons") == 0) {
		if (context == tech_context)
			curElement = (char**)&go->initial_weapons;
	}
	else if (noCaseStrcmp(name, "shields") == 0) {
		if (context == tech_context)
			curElement = (char**)&go->initial_shields;
	}
	else if (noCaseStrcmp(name, "cargo") == 0) {
		if (context == tech_context)
			curElement = (char**)&go->initial_cargo;
	}
	else if (noCaseStrcmp(name, "full_bombing") == 0) {
		go->game_options |= GAME_NONGBOMBING;
	}
	else if (noCaseStrcmp(name, "keep_production") == 0) {
		go->game_options |= GAME_KEEPPRODUCTION;
	}
	else if (noCaseStrcmp(name, "dont_drop_dead") == 0) {
		go->game_options |= GAME_NODROP;
	}
	else if (noCaseStrcmp(name, "save_report_copy") == 0) {
		go->game_options |= GAME_SAVECOPY;
	}
	else if (noCaseStrcmp(name, "spherical_galaxy") == 0) {
		go->game_options |= GAME_SPHERICALGALAXY;
	}
	else if (noCaseStrcmp(name, "players") == 0) {
		tagContext = 0;
		context = player_context;
		po = allocStruct(playerOpts);
		assert(po != NULL);
		po->next = NULL;
		po->email = NULL;
		po->password = NULL;
		po->real_name = NULL;
		po->x = 0.0;
		po->y = 0.0;
		po->size = 0.0;
		po->planets = allocStruct(planet);
		po->options = 0;
	}
	else if (noCaseStrcmp(name, "player") == 0) {
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
    int errors = 0;
    if (go->from == NULL) {
      if (so->from == NULL) {
	fprintf(stderr, "**ERROR** Either the server or a game section "
		"must specify a <from> element.\n");
	errors++;
      }
      else {
	go->from = strdup(so->from);
      }
    }
    if (go->succeed_subject == NULL) {
      if (so->succeed_subject == NULL) {
	fprintf(stderr, "**ERROR** Either the server or a game section "
		"must specify a <subject type=\"succeed\"> element\n");
	errors++;
      }
      else {
	go->succeed_subject = strdup(so->succeed_subject);
      }
    }
    if (go->fail_subject == NULL) {
      if (so->fail_subject == NULL) {
	fprintf(stderr, "**ERROR** Either the server or a game section "
		"must specify a <subject type=\"fail\"> element\n");
	errors++;
      }
      else {
	go->fail_subject = strdup(so->fail_subject);
      }
    }

    if (errors) {
      fprintf(stderr, "Please fix %s problem%s and try again.\n",
	      errors == 1 ? "this" : "these", &"s"[errors == 1]);
      exit(EXIT_FAILURE);
    }

    addList(&so->go, go);
    context = server_context;
    go = NULL;
  }
  else if (noCaseStrcmp(name, "core_sizes") == 0) {
    context = game_context;
  }
  else if (noCaseStrcmp(name, "growth_planets") == 0) {
    context = game_context;
  }
  else if (noCaseStrcmp(name, "initial_tech") == 0) {
    context = game_context;
  }
  else if (noCaseStrcmp(name, "players") == 0) {
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
    else if (curElement == &go->succeed_subject) {
      if (*curElement == NULL)
	*curElement = strdup(ltext);
      else {
	int newlen = strlen(*curElement) + len + 1;
	*curElement = (char*)realloc(*curElement, newlen);
	strcat(*curElement, ltext);
      }
    }
    else if (curElement == &go->fail_subject) {
      if (*curElement == NULL)
	*curElement = strdup(ltext);
      else {
	int newlen = strlen(*curElement) + len + 1;
	*curElement = (char*)realloc(*curElement, newlen);
	strcat(*curElement, ltext);
      }
    }
    else if (curElement == &go->replyto) {
      if (*curElement == NULL)
	*curElement = strdup(ltext);
      else {
	int newlen = strlen(*curElement) + len + 1;
	*curElement = (char*)realloc(*curElement, newlen);
	strcat(*curElement, ltext);
      }
    }
    else if (curElement == &go->cc) {
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
      go->galaxy_size = atof(ltext);
    }
    else if (curElement == (char**)&go->delay_hours) {
      go->delay_hours = atol(ltext);
    }
    else if (curElement == (char**)&go->nation_spacing) {
      go->nation_spacing = atof(ltext);
    }
    else if (curElement == (char**)&go->core_sizes) {
      go->core_sizes[core_idx] = atof(ltext);
    }
    else if (curElement == (char**)&go->growth_planets_count) {
      go->growth_planets_count = atoi(ltext);
    }
    else if (curElement == (char**)&go->growth_planets_radius) {
      go->growth_planets_radius = atof(ltext);
    }
    else if (curElement == (char**)&go->stuff_planets) {
      go->stuff_planets = atoi(ltext);
    }
    else if (curElement == (char**)&go->pax_galactica) {
      go->pax_galactica = atoi(ltext);
    }
    else if (curElement == (char**)&go->initial_drive) {
      if ((go->initial_drive = atof(ltext)) < 1.0)
	go->initial_drive = 1.0;
    }
    else if (curElement == (char**)&go->initial_shields) {
      if ((go->initial_shields = atof(ltext)) < 1.0)
	go->initial_shields = 1.0;
    }
    else if (curElement == (char**)&go->initial_weapons) {
      if ((go->initial_weapons = atof(ltext)) < 1.0)
	go->initial_weapons = 1.0;
    }
    else if (curElement == (char**)&go->initial_cargo) {
      if ((go->initial_cargo = atof(ltext)) < 1.0)
	go->initial_cargo = 1.0;
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
  fprintf(stderr, "  %d growth planets within %f\n",
	  go->growth_planets_count, go->growth_planets_radius);
  fprintf(stderr, "  Pax Galactica: %d\n", go->pax_galactica);
  fprintf(stderr, "  initial tech: %.2f %.2f %.2f %.2f\n",
	  go->initial_drive, go->initial_weapons, go->initial_cargo,
	  go->initial_cargo);
}

serverOpts* loadConfig (const char *galaxynghome) {
    FILE *areFP;
    char arename[BUFSIZ];
    char buf[BUFSIZ];
    XML_Parser parser = XML_ParserCreate (NULL);
    int done;
    so = (serverOpts*)malloc(sizeof(serverOpts));

	initElementLookup();
	
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
