#
# $Id$
#

CFLAGS = -Wall -pedantic -I../include $(ADDTL_CFLAGS)
LIBS = -lexpat -lm -L../lib -lgalaxyng $(ADDTL_LIBS)
CC = gcc

SOURCES=are.c loadConfig.c
OBJECTS=$(SOURCES:.c=.o)
ARE=are

all : $(ARE)

are: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) $(LIBS) -o $(ARE)

clean:
	rm -f $(ARE) $(OBJECTS) *~
