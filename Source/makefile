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
# freetype support enabled.
#
# you will also need to uncomment the following lines
#
ADDTL_CFLAGS = -DDRAW_INFLUENCE_MAP -I.
ADDTL_LIBS = -lgd -lpng -lz -ljpeg -lfreetype
ADDTL_SRCS = influence.c
ADDTL_OBJS = influence.o

CFLAGS = -Wall -pedantic -g $(ADDTL_CFLAGS)
#CFLAGS = -Wall -pedantic -g -DFS_NEW_FORECAST $(ADDTL_CFLAGS)
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
	makedepend -Y"" $(SOURCES)

# DO NOT DELETE

loadgame.o: loadgame.h galaxy.h list.h util.h
savegame.o: savegame.h galaxy.h list.h util.h
create.o: create.h galaxy.h avl.h list.h util.h report.h loadgame.h mail.h
create.o: report_m.h report_xml.h savegame.h process.h phase.h battle.h
create.o: selftest.h
phase.o: galaxy.h list.h util.h phase.h loadgame.h savegame.h
battle.o: battle.h galaxy.h list.h util.h
process.o: process.h galaxy.h list.h util.h savegame.h loadgame.h phase.h
process.o: battle.h report.h mail.h report_m.h report_xml.h selftest.h
report.o: report.h galaxy.h loadgame.h list.h util.h mail.h report_m.h
report.o: report_xml.h create.h avl.h
util.o: util.h galaxy.h list.h create.h avl.h loadgame.h
list.o: list.h util.h galaxy.h
selftest.o: selftest.h galaxy.h util.h list.h create.h avl.h process.h
selftest.o: savegame.h loadgame.h phase.h battle.h report.h mail.h report_m.h
selftest.o: report_xml.h
report_xml.o: create.h galaxy.h avl.h report_xml.h report.h loadgame.h list.h
report_xml.o: util.h mail.h report_m.h
mail.o: mail.h galaxy.h util.h list.h
report_m.o: create.h galaxy.h avl.h report_m.h list.h util.h report.h
report_m.o: loadgame.h mail.h report_xml.h
galaxyng.o: galaxy.h util.h list.h process.h savegame.h loadgame.h phase.h
galaxyng.o: battle.h report.h mail.h report_m.h report_xml.h selftest.h
galaxyng.o: create.h avl.h
wopr.o: galaxy.h util.h list.h process.h savegame.h loadgame.h phase.h
wopr.o: battle.h report.h mail.h report_m.h report_xml.h selftest.h create.h
wopr.o: avl.h wopr.h
globals.o: galaxy.h
avl.o: avl.h
usage.o: galaxy.h
