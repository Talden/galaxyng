#
# 	$Id$	
#
# This are the setting for a Sun Sparc Station and Linux Box
#
# !! Warning !!
# DO NOT USE -O2 OR ANY OTHER FORM OF OPTIMIZATION
# IT WILL BREAK THE CODE
#
# This makefile is much bigger than necessary. With a few implicit
# rules it could be a fraction of the size. However not all versions
# of make support this. This makefile will hopefully work with even
# all versions of make.
#

#
# Influence mapping:
# if you want to have a .png map generated when the -influence 
# command is used, then you'll need to have libgd 
# (http://www.boutell.com/gd/) installed with png, jpeg, and 
# freetype support enabled and uncomment the following lines:
#ADDTL_CFLAGS = -DDRAW_INFLUENCE_MAP -I.
#ADDTL_LIBS = -lgd -lpng -lz -ljpeg -lfreetype
#ADDTL_SRCS = influence.c
#ADDTL_OBJS = influence.o

CFLAGS = -Wall -pedantic $(ADDTL_CFLAGS)
#CFLAGS = -Wall -pedantic -DFS_NEW_FORECAST $(ADDTL_CFLAGS)
LIBS = -lm $(ADDTL_LIBS)


CC=gcc

SOURCES=loadgame.c savegame.c create.c phase.c battle.c process.c \
        report.c util.c list.c selftest.c report_xml.c mail.c \
        report_m.c galaxyng.c wopr.c globals.c avl.c usage.c $(ADDTL_SOURCES)

OBJECTS=loadgame.o savegame.o create.o phase.o battle.o process.o \
        report.o util.o list.o selftest.o report_xml.o mail.o \
        report_m.o globals.o avl.o  usage.o $(ADDTL_OBJS)

GALAXYNG=galaxyng
WOPR=wopr

all: $(GALAXYNG) $(WOPR)

loadgame.o: loadgame.c
	$(CC) $(CFLAGS) -c loadgame.c -o loadgame.o

usage.o: usage.c
	$(CC) $(CFLAGS) -c usage.c -o usage.o

savegame.o: savegame.c
	$(CC) $(CFLAGS) -c savegame.c -o savegame.o

create.o: create.c
	$(CC) $(CFLAGS) -c create.c -o create.o

phase.o: phase.c
	$(CC) $(CFLAGS) -c phase.c -o phase.o

globals.o: globals.c
	$(CC) $(CFLAGS) -c globals.c -o globals.o

battle.o: battle.c
	$(CC) $(CFLAGS) -c battle.c -o battle.o

process.o: process.c
	$(CC) $(CFLAGS) -c process.c -o process.o

report.o: report.c
	$(CC) $(CFLAGS) -c report.c -o report.o

util.o: util.c
	$(CC) $(CFLAGS) -c util.c -o util.o

list.o: list.c
	$(CC) $(CFLAGS) -c list.c -o list.o

selftest.o: selftest.c
	$(CC) $(CFLAGS) -c selftest.c -o selftest.o

report_xml.o: report_xml.c
	$(CC) $(CFLAGS) -c report_xml.c -o report_xml.o

mail.o: mail.c
	$(CC) $(CFLAGS) -c mail.c -o mail.o

report_m.o: report_m.c
	$(CC) $(CFLAGS) -c report_m.c -o report_m.o

avl.o: avl.c
	$(CC) $(CFLAGS) -c avl.c -o avl.o

influence.o: influence.c
	$(CC) $(CFLAGS) -c influence.c -o influence.o

galaxyng.o: galaxyng.c
	$(CC) $(CFLAGS) -c galaxyng.c -o galaxyng.o

wopr.o: wopr.c
	$(CC) $(CFLAGS) -c wopr.c -o wopr.o


$(GALAXYNG): $(OBJECTS) galaxyng.o
	$(CC) galaxyng.o $(OBJECTS) -o $(GALAXYNG) $(LIBS)

$(WOPR): $(OBJECTS) wopr.o
	$(CC) wopr.o $(OBJECTS) -o $(WOPR) $(LIBS)

clean:
	rm -f $(OBJECTS)
	rm -f $(GALAXYNG)
	rm -f $(GALAXYNG).o
	rm -f $(WOPR)
	rm -f $(WOPR).o
	rm -f core
	rm -f *.*~
	rm -f *~
	rm -f tags
	rm -f $(DOCS)
	rm -f masterindex.html

#=========================================================
#                For development 
#=========================================================

test: galaxyng
	cp galaxyng $(HOME)/Games/galaxyng

count:
	egrep -v -G "^ \*" *.c *.h | egrep -v -G "/\*"  | wc

TAGS: $(SOURCES)
	etags $(SOURCES)

depend:
	makedepend -- $(CFLAGS) -- $(SOURCES) galaxyng.c wopr.c

# DO NOT DELETE THIS LINE -- make depend depends on it.

