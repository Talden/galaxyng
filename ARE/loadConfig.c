/* This is simple demonstration of how to use expat. This program
reads an XML document from standard input and writes a line with the
name of each element to standard output indenting child elements by
one tab stop more than their parent element. */

#include <stdio.h>
#include "xmlparse.h"
#include "list.h"
#include "are.h"

void startElement(void *userData, const char *name, const char **atts)
{
  int i;
  serverOpts* so = (serverOpts*)userData;
  puts(name);
}

void endElement(void *userData, const char *name)
{
  return;
}

int 
loadConfig(serverOpts* so, const char* galaxynghome)
{
  FILE* areFP;
  char arename[BUFSIZ];
  char buf[BUFSIZ];
  XML_Parser parser = XML_ParserCreate(NULL);
  int done;
  int depth = 0;
  gameopts* go;

  XML_SetUserData(parser, &so);
  XML_SetElementHandler(parser, startElement, endElement);

  so->from = NULL;
  so->subject = NULL;
  so->replyto = NULL;
  so->cc = NULL;
  so->go = NULL;

  sprintf(arename, "%s/.arerc", galaxynghome);
  if ((areFP = fopen(arename, "r")) == NULL) {
    plog(LPART, "Could not open \"%s\" for input.\n", arename);
    return EXIT_FAILURE;
  }

  do {
    size_t len = fread(buf, 1, sizeof(buf), areFP);
    done = len < sizeof(buf);
    if (!XML_Parse(parser, buf, len, done)) {
      fprintf(stderr,
	      "%s at line %d\n",
	      XML_ErrorString(XML_GetErrorCode(parser)),
	      XML_GetCurrentLineNumber(parser));
      return 1;
    }
  } while (!done);
  XML_ParserFree(parser);
  return 0;
}
