#
# $Id$
#
XMLINCLUDES = `xml2-config --cflags`
XMLLIBS = `xml2-config --libs`

CFLAGS = -g -Wall -pedantic -I../include $(XMLINCLUDES) $(ADDTL_CFLAGS)
LIBS = -lm -L../lib -lgalaxyng $(XMLLIBS) $(ADDTL_LIBS)
CC = gcc

SOURCES=are.c loadConfig.c storage.c
OBJECTS=$(SOURCES:.c=.o)
ARE=are

all : $(ARE) loadConfig

are: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) $(LIBS) -o $(ARE)

loadConfig: loadConfig.O storage.o
	gcc -g $(CFLAGS) loadConfig.O storage.o $(LIBS) -o loadConfig

loadConfig.O : loadConfig.c
	gcc -g -c $(CFLAGS) -DLoadConfigMainNeeded loadConfig.c -o loadConfig.O

clean:
	rm -f $(ARE) $(OBJECTS) *~

depend:
	makedepend -- $(CFLAGS) -- $(SOURCES)
# DO NOT DELETE

