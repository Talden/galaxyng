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
ADDTL_CFLAGS = -DDRAW_INFLUENCE_MAP
ADDTL_LIBS = -lgd -lpng -lz -ljpeg -lfreetype
ADDTL_SRCS = influence.c
ADDTL_OBJS = influence.o

CFLAGS = -g -Wall -pedantic -I../include -I$(HOME)/include $(ADDTL_CFLAGS)
#CFLAGS = -Wall -pedantic -DFS_NEW_FORECAST $(ADDTL_CFLAGS)
LIBS = -L$(HOME)/lib -L../lib -lgalaxyng -lm $(ADDTL_LIBS)


CC=gcc

SOURCES=loadgame.c savegame.c create.c phase.c battle.c process.c \
        report.c selftest.c report_xml.c \
        report_m.c galaxyng.c wopr.c avl.c usage.c $(ADDTL_SOURCES)

OBJECTS=loadgame.o savegame.o create.o phase.o battle.o process.o \
        report.o selftest.o report_xml.o \
        report_m.o avl.o  usage.o $(ADDTL_OBJS)

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

battle.o: battle.c
	$(CC) $(CFLAGS) -c battle.c -o battle.o

process.o: process.c
	$(CC) $(CFLAGS) -c process.c -o process.o

report.o: report.c
	$(CC) $(CFLAGS) -c report.c -o report.o

list.o: list.c
	$(CC) $(CFLAGS) -c list.c -o list.o

selftest.o: selftest.c
	$(CC) $(CFLAGS) -c selftest.c -o selftest.o

report_xml.o: report_xml.c
	$(CC) $(CFLAGS) -c report_xml.c -o report_xml.o

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

loadgame.o: ../include/loadgame.h ../include/galaxy.h ../include/strutl.h
loadgame.o: ../include/cookies.h ../include/logging.h
loadgame.o: ../include/list.h
loadgame.o: ../include/util.h
savegame.o: ../include/savegame.h ../include/galaxy.h ../include/strutl.h
savegame.o: ../include/cookies.h ../include/logging.h /usr/include/time.h
savegame.o: ../include/list.h ../include/util.h
create.o: ../include/create.h ../include/galaxy.h ../include/strutl.h
create.o: ../include/cookies.h
create.o: ../include/logging.h 
create.o: ../include/avl.h
create.o: ../include/list.h ../include/util.h
create.o: ../include/report.h ../include/loadgame.h ../include/mail.h
create.o: ../include/report_m.h ../include/report_xml.h ../include/savegame.h
create.o: ../include/process.h ../include/phase.h ../include/battle.h
create.o: ../include/selftest.h
phase.o: ../include/galaxy.h ../include/strutl.h
phase.o: ../include/cookies.h ../include/logging.h
phase.o: ../include/list.h ../include/util.h
phase.o: ../include/phase.h ../include/loadgame.h ../include/savegame.h
battle.o: ../include/battle.h ../include/galaxy.h ../include/strutl.h
battle.o: ../include/logging.h 
battle.o: ../include/list.h ../include/util.h
process.o: ../include/process.h ../include/galaxy.h ../include/strutl.h
process.o: ../include/cookies.h ../include/logging.h
process.o: ../include/list.h ../include/util.h
process.o: ../include/savegame.h ../include/loadgame.h ../include/phase.h
process.o: ../include/battle.h ../include/report.h ../include/mail.h
process.o: ../include/report_m.h ../include/report_xml.h
process.o: ../include/selftest.h
report.o: ../include/report.h ../include/galaxy.h ../include/strutl.h
report.o: ../include/cookies.h ../include/logging.h
report.o: ../include/loadgame.h ../include/list.h ../include/util.h
report.o: ../include/mail.h ../include/report_m.h ../include/report_xml.h
report.o: ../include/create.h ../include/avl.h
selftest.o: ../include/selftest.h ../include/galaxy.h ../include/strutl.h
selftest.o: ../include/cookies.h ../include/logging.h
selftest.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
selftest.o: ../include/util.h /usr/include/limits.h
selftest.o: ../include/list.h ../include/create.h ../include/avl.h
selftest.o: ../include/process.h
selftest.o: ../include/savegame.h ../include/loadgame.h ../include/phase.h
selftest.o: ../include/battle.h ../include/report.h ../include/mail.h
selftest.o: ../include/report_m.h ../include/report_xml.h
report_xml.o: ../include/create.h ../include/galaxy.h ../include/strutl.h
report_xml.o: ../include/cookies.h ../include/logging.h ../include/avl.h
report_xml.o: ../include/report_xml.h
report_xml.o: ../include/report.h ../include/loadgame.h ../include/list.h
report_xml.o: ../include/util.h 
report_xml.o: ../include/mail.h ../include/report_m.h
report_m.o: ../include/create.h ../include/galaxy.h ../include/strutl.h
report_m.o: ../include/logging.h ../include/avl.h
report_m.o: ../include/report_m.h ../include/list.h ../include/util.h
report_m.o: ../include/report.h ../include/loadgame.h ../include/mail.h
report_m.o: ../include/report_xml.h
galaxyng.o: ../include/galaxy.h ../include/strutl.h
galaxyng.o: ../include/cookies.h ../include/logging.h ../include/util.h
galaxyng.o: ../include/list.h ../include/process.h ../include/savegame.h
galaxyng.o: ../include/loadgame.h ../include/phase.h ../include/battle.h
galaxyng.o: ../include/report.h ../include/mail.h ../include/report_m.h
galaxyng.o: ../include/report_xml.h ../include/selftest.h ../include/create.h
galaxyng.o: ../include/avl.h ../include/galaxyng.h
wopr.o: ../include/galaxy.h ../include/strutl.h
wopr.o: ../include/cookies.h ../include/logging.h ../include/util.h
wopr.o: ../include/list.h ../include/process.h ../include/savegame.h
wopr.o: ../include/loadgame.h ../include/phase.h ../include/battle.h
wopr.o: ../include/report.h ../include/mail.h ../include/report_m.h
wopr.o: ../include/report_xml.h ../include/selftest.h ../include/create.h
wopr.o: ../include/avl.h ../include/wopr.h
avl.o: ../include/avl.h
usage.o: ../include/galaxy.h ../include/strutl.h
usage.o: ../include/cookies.h ../include/logging.h
galaxyng.o: ../include/galaxy.h ../include/strutl.h
galaxyng.o: ../include/cookies.h ../include/logging.h ../include/util.h
galaxyng.o: ../include/list.h ../include/process.h ../include/savegame.h
galaxyng.o: ../include/loadgame.h ../include/phase.h ../include/battle.h
galaxyng.o: ../include/report.h ../include/mail.h ../include/report_m.h
galaxyng.o: ../include/report_xml.h ../include/selftest.h ../include/create.h
galaxyng.o: ../include/avl.h ../include/galaxyng.h
wopr.o: ../include/galaxy.h ../include/strutl.h ../include/cookies.h
wopr.o: ../include/logging.h ../include/util.h 
wopr.o: ../include/list.h ../include/process.h ../include/savegame.h
wopr.o: ../include/loadgame.h ../include/phase.h ../include/battle.h
wopr.o: ../include/report.h ../include/mail.h ../include/report_m.h
wopr.o: ../include/report_xml.h ../include/selftest.h ../include/create.h
wopr.o: ../include/avl.h /usr/include/fcntl.h ../include/wopr.h
