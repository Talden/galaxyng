#
# $Id$
#

CFLAGS = -Wall -pedantic -I../include $(ADDTL_CFLAGS)
CC = gcc

SOURCES=strutl.c logging.c list.c
OBJECTS=$(SOURCES:.c=.o)

all : libgalaxyng.a

libgalaxyng.a: $(OBJECTS)
	ar cr libgalaxyng.a $(OBJECTS)

clean:
	rm -f libgalaxyng.a $(OBJECTS) *~

depend:
	makedepend -- $(CFLAGS) -- $(SOURCES)

# DO NOT DELETE THIS LINE -- make depend depends on it.

strutl.o: ../include/strutl.h ../include/cookies.h ../include/logging.h 
logging.o: ../include/logging.h 
list.o: ../include/list.h ../include/util.h ../include/galaxy.h
list.o: ../include/strutl.h ../include/cookies.h ../include/logging.h 
