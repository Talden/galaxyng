/* This is simple demonstration of how to use expat. This program
reads an XML document from standard input and writes a line with the
name of each element to standard output indenting child elements by
one tab stop more than their parent element. */

#include <stdio.h>
#include "xmlparse.h"
#include "list.h"
#include "are.h"

static char** curElement;
static gameopts* go = NULL;
static int tagContext = 0;
static serverOpts* so = NULL;

#define email 0
#define game  1

void
startElement (void *userData, const char *name, const char **atts)
{
    int i;
    const char *ptr;
    static int context;


    if (noCaseStrcmp (name, "are") == 0) {
	if (strcmp(atts[1], "1.0") != 0)
	    fprintf(stderr, "unrecognized ARE version, continuing\n");
    }
    else if (noCaseStrcmp(name, "email") == 0) {
	context = email;
    }
    else if (noCaseStrcmp(name, "from") == 0) {
    	tagContext = 1;
	if (context == email)
	    curElement = &so->from;
	else if (context == game)
	    curElement = &go->from;
    }
    else if (noCaseStrcmp(name, "subject") == 0) {
    	tagContext = 1;
	curElement = &so->subject;
    }
    else if (noCaseStrcmp(name, "replyto") == 0) {
    	tagContext = 1;
	curElement = &so->replyto;
    }
    else if (noCaseStrcmp(name, "cc") == 0) {
    	tagContext = 1;
	curElement = &so->cc;
    }
    else if (noCaseStrcmp(name, "game") == 0) {
	go = allocStruct(gameopts);
	assert(go != NULL);
	go->from = NULL;
	go->next = NULL;
	go->playerlimit = 0;
	go->maxplanetsize = 0.0;
	go->totalplanetsize = 0.0;
	go->maxplanets = 0;
	setName(go,atts[1]);
	context = game;
    }
    else if (noCaseStrcmp(name, "playerlimit") == 0) {
    	tagContext = 1;
	curElement = (char**)&go->playerlimit;
    }
    else if (noCaseStrcmp(name, "totalplanetsize") == 0) {
    	tagContext = 1;
	curElement = (char**)&go->totalplanetsize;
    }
    else if (noCaseStrcmp(name, "maxplanetsize") == 0) {
    	tagContext = 1;
	curElement = (char**)&go->maxplanetsize;
    }
    else if (noCaseStrcmp(name, "maxplanets") == 0) {
    	tagContext = 1;
	curElement = (char**)&go->maxplanets;
    }
    else
	printf("unrecognized element %s\n", name);
    
}

void
endElement (void *userData, const char *name)
{
    if (noCaseStrcmp(name, "game") == 0) {
	addList(&so->go, go);
	go = NULL;
    }

    tagContext = 0;
    return;
}

void
contentData(void* userData, const char* text, int len)
{
    char ltext[1024];

    if (!tagContext)
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
	else if (curElement == (char**)&go->playerlimit) {
	    go->playerlimit = atoi(ltext);
	}
	else if (curElement == (char**)&go->totalplanetsize) {
	    go->totalplanetsize = atof(ltext);
	}
	else if (curElement == (char**)&go->maxplanetsize) {
	    go->maxplanetsize = atof(ltext);
	}
	else if (curElement == (char**)&go->maxplanets) {
	    go->maxplanets = atoi(ltext);
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
    gameopts* go = (gameopts*)data;

    fprintf(stderr, "  from: %s\n", go->from);
    fprintf(stderr, "  playerlimit: %d\n", go->playerlimit);
    fprintf(stderr, "  totalplanetsize: %f\n", go->totalplanetsize);
    fprintf(stderr, "  maxplanetsize: %f\n", go->maxplanetsize);
    fprintf(stderr, "  maxplanets: %d\n", go->maxplanets);
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
    gameopts *go;
    so = (serverOpts*)malloc(sizeof(serverOpts));

    XML_SetUserData (parser, NULL);
    XML_SetElementHandler (parser, startElement, endElement);
    XML_SetCharacterDataHandler(parser, contentData);

    so->from = NULL;
    so->subject = NULL;
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

    printf("so->from: \"%s\"\n", so->from);
    printf("so->subject: \"%s\"\n", so->subject);
    printf("so->replyto: \"%s\"\n", so->replyto);
    printf("so->cc: \"%s\"\n", so->cc);

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
