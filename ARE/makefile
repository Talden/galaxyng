#
# $Id$
#


CFLAGS = -Wall -pedantic -I../include $(ADDTL_CFLAGS)
LIBS = -lm $(ADDTL_LIBS)
CC = gcc

SOURCES=are.c
OBJECTS=$(SOURCES:.c=.o)

all : are

are: $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) $(LIBS) -o are

clean:
	rm -f are $(OBJECTS) *~

