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
# if you want to have a .png map generated when a turn is processed
# then you'll need to have libgd (http://www.boutell.com/gd/)
# installed with png, jpeg, and freetype support enabled.
#
# you will also need to uncomment the following lines
#
#CFLAGS = -Wall -pedantic -g -DDRAW_INFLUENCE_MAP -I.
#LIBS = -lgd -lpng -lz -ljpeg -lfreetype -lm
#ADDTL_SRCS = influence.c
#ADDTL_OBJS = influence.o
#

#
# and comment these lines
#
CFLAGS = -Wall -pedantic -g
LIBS = -lm
ADDTL_SRCS=




CC=gcc


SOURCES=loadgame.c savegame.c create.c phase.c battle.c process.c \
        report.c util.c list.c selftest.c report_xml.c mail.c \
        report_m.c galaxyng.c wopr.c globals.c avl.c $(ADDTL_SOURCES)

OBJECTS=loadgame.o savegame.o create.o phase.o battle.o process.o \
        report.o util.o list.o selftest.o report_xml.o mail.o \
        report_m.o globals.o avl.o  $(ADDTL_OBJS)

GALAXYNG=galaxyng
WOPR=wopr

all: $(GALAXYNG) $(WOPR)

loadgame.o: loadgame.c
	$(CC) $(CFLAGS) -c loadgame.c -o loadgame.o

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
	rm -f $(REFS) 
	rm -f galaxyng.xrefs
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

#
#
#

TYPES= -T batstat -T mapdimensions -T list -T strlist -T player \
-T fleetname -T shiptype -T planet -T group -T alliance \
-T participant -T shot -T bprotocol -T battle -T bombing \
-T planet_claim -T option -T orderinfo -T fielddef -T game \
-T envelope -T newplayer -T gamespecification 
INOPT= -orig -i2 -br -nce -nbc -ncdb -bad -bap

indent:
	indent $(INOPT) $(TYPES) process.c
	expand process.c > /tmp/tt
	cp     /tmp/tt process.c
	indent $(INOPT) $(TYPES) process.h
	expand process.h > /tmp/tt
	cp     /tmp/tt process.h
	indent $(INOPT) $(TYPES) battle.c	
	expand battle.c > /tmp/tt
	cp     /tmp/tt battle.c
	indent $(INOPT) $(TYPES) battle.h	
	expand battle.h > /tmp/tt
	cp     /tmp/tt battle.h
	indent $(INOPT) $(TYPES) report.c
	expand report.c > /tmp/tt	
	cp /tmp/tt report.c 
	indent $(INOPT) $(TYPES) report.h
	expand report.h > /tmp/tt
	cp /tmp/tt report.h 
	indent $(INOPT) $(TYPES) loadgame.c
	expand loadgame.c > /tmp/tt
	cp /tmp/tt loadgame.c
	indent $(INOPT) $(TYPES) loadgame.h
	expand loadgame.h > /tmp/tt
	cp /tmp/tt loadgame.h
	indent $(INOPT) $(TYPES) phase.c
	expand phase.c > /tmp/tt
	cp /tmp/tt phase.c
	indent $(INOPT) $(TYPES) phase.h
	expand phase.h > /tmp/tt
	cp /tmp/tt phase.h
	indent $(INOPT) $(TYPES) create.c
	expand create.c > /tmp/tt
	cp /tmp/tt create.c
	indent $(INOPT) $(TYPES) create.h
	expand create.h > /tmp/tt
	cp /tmp/tt create.h
	indent $(INOPT) $(TYPES) util.c
	expand util.c > /tmp/tt
	cp /tmp/tt util.c
	indent $(INOPT) $(TYPES) util.h
	expand util.h > /tmp/tt
	cp /tmp/tt util.h
	indent $(INOPT) $(TYPES) galaxyng.c
	expand galaxyng.c > /tmp/tt
	cp /tmp/tt galaxyng.c
	indent $(INOPT) $(TYPES) galaxy.h
	expand galaxy.h > /tmp/tt
	cp /tmp/tt galaxy.h
	indent $(INOPT) $(TYPES) savegame.c
	expand savegame.c > /tmp/tt
	cp /tmp/tt savegame.c
	indent $(INOPT) $(TYPES) savegame.h
	expand savegame.h > /tmp/tt
	cp /tmp/tt savegame.h
	indent $(INOPT) $(TYPES) report_m.c
	expand report_m.c > /tmp/tt
	cp /tmp/tt report_m.c

#
# Documentation extracted from the source code.
#

DOCS=battle.c.html battle.h.html create.c.html create.h.html galaxy.h.html \
  galaxyng.c.html list.c.html list.h.html loadgame.c.html \
  loadgame.h.html mail.c.html mail.h.html phase.c.html phase.h.html \
  process.c.html process.h.html report.c.html report.h.html \
  report_m.c.html report_m.h.html report_xml.c.html report_xml.h.html \
  savegame.c.html savegame.h.html selftest.c.html selftest.h.html \
  util.c.html util.h.html \

REFS=battle.c.xref battle.h.xref create.c.xref create.h.xref galaxy.h.xref \
  galaxyng.c.xref list.c.xref list.h.xref loadgame.c.xref \
  loadgame.h.xref mail.c.xref mail.h.xref phase.c.xref phase.h.xref \
  process.c.xref process.h.xref report.c.xref report.h.xref \
  report_m.c.xref report_m.h.xref report_xml.c.xref report_xml.h.xref \
  savegame.c.xref savegame.h.xref selftest.c.xref selftest.h.xref \
  util.c.xref util.h.xref \

doc: galaxyng.xrefs $(DOCS) masterindex.html 
refs: $(REFS)

ROBODOC=robodoc

battle.c.xref : battle.c
	$(ROBODOC) battle.c battle.c.html -g battle.c.xref SORT INTERNAL
battle.h.xref : battle.h
	$(ROBODOC) battle.h battle.h.html -g battle.h.xref SORT INTERNAL
create.c.xref : create.c
	$(ROBODOC) create.c create.c.html -g create.c.xref SORT INTERNAL
create.h.xref : create.h
	$(ROBODOC) create.h create.h.html -g create.h.xref SORT INTERNAL
galaxy.h.xref : galaxy.h
	$(ROBODOC) galaxy.h galaxy.h.html -g galaxy.h.xref SORT INTERNAL
galaxyng.c.xref : galaxyng.c
	$(ROBODOC) galaxyng.c galaxyng.c.html -g galaxyng.c.xref SORT INTERNAL
list.c.xref : list.c
	$(ROBODOC) list.c list.c.html -g list.c.xref SORT INTERNAL
list.h.xref : list.h
	$(ROBODOC) list.h list.h.html -g list.h.xref SORT INTERNAL
loadgame.c.xref : loadgame.c
	$(ROBODOC) loadgame.c loadgame.c.html -g loadgame.c.xref SORT INTERNAL
loadgame.h.xref : loadgame.h
	$(ROBODOC) loadgame.h loadgame.h.html -g loadgame.h.xref SORT INTERNAL
mail.c.xref : mail.c
	$(ROBODOC) mail.c mail.c.html -g mail.c.xref SORT INTERNAL
mail.h.xref : mail.h
	$(ROBODOC) mail.h mail.h.html -g mail.h.xref SORT INTERNAL
phase.c.xref : phase.c
	$(ROBODOC) phase.c phase.c.html -g phase.c.xref SORT INTERNAL
phase.h.xref : phase.h
	$(ROBODOC) phase.h phase.h.html -g phase.h.xref SORT INTERNAL
process.c.xref : process.c
	$(ROBODOC) process.c process.c.html -g process.c.xref SORT INTERNAL
process.h.xref : process.h
	$(ROBODOC) process.h process.h.html -g process.h.xref SORT INTERNAL
report.c.xref : report.c
	$(ROBODOC) report.c report.c.html -g report.c.xref SORT INTERNAL
report.h.xref : report.h
	$(ROBODOC) report.h report.h.html -g report.h.xref SORT INTERNAL
report_m.c.xref : report_m.c
	$(ROBODOC) report_m.c report_m.c.html -g report_m.c.xref SORT INTERNAL
report_m.h.xref : report_m.h
	$(ROBODOC) report_m.h report_m.h.html -g report_m.h.xref SORT INTERNAL
report_xml.c.xref : report_xml.c
	$(ROBODOC) report_xml.c report_xml.c.html -g report_xml.c.xref SORT INTERNAL
report_xml.h.xref : report_xml.h
	$(ROBODOC) report_xml.h report_xml.h.html -g report_xml.h.xref SORT INTERNAL
savegame.c.xref : savegame.c
	$(ROBODOC) savegame.c savegame.c.html -g savegame.c.xref SORT INTERNAL
savegame.h.xref : savegame.h
	$(ROBODOC) savegame.h savegame.h.html -g savegame.h.xref SORT INTERNAL
selftest.c.xref : selftest.c
	$(ROBODOC) selftest.c selftest.c.html -g selftest.c.xref SORT INTERNAL
selftest.h.xref : selftest.h
	$(ROBODOC) selftest.h selftest.h.html -g selftest.h.xref SORT INTERNAL
util.c.xref : util.c
	$(ROBODOC) util.c util.c.html -g util.c.xref SORT INTERNAL
util.h.xref : util.h
	$(ROBODOC) util.h util.h.html -g util.h.xref SORT INTERNAL


galaxyng.xrefs: $(REFS)
	/bin/ls *.xref > $@


ROBOFLAGS=HTML C SORT -x galaxyng.xrefs INTERNAL

battle.c.html : battle.c
	$(ROBODOC) battle.c battle.c.html $(ROBOFLAGS)
battle.h.html : battle.h
	$(ROBODOC) battle.h battle.h.html $(ROBOFLAGS)
create.c.html : create.c
	$(ROBODOC) create.c create.c.html $(ROBOFLAGS)
create.h.html : create.h
	$(ROBODOC) create.h create.h.html $(ROBOFLAGS)
galaxy.h.html : galaxy.h
	$(ROBODOC) galaxy.h galaxy.h.html $(ROBOFLAGS)
galaxyng.c.html : galaxyng.c
	$(ROBODOC) galaxyng.c galaxyng.c.html $(ROBOFLAGS)
list.c.html : list.c
	$(ROBODOC) list.c list.c.html $(ROBOFLAGS)
list.h.html : list.h
	$(ROBODOC) list.h list.h.html $(ROBOFLAGS)
loadgame.c.html : loadgame.c
	$(ROBODOC) loadgame.c loadgame.c.html $(ROBOFLAGS)
loadgame.h.html : loadgame.h
	$(ROBODOC) loadgame.h loadgame.h.html $(ROBOFLAGS)
mail.c.html : mail.c
	$(ROBODOC) mail.c mail.c.html $(ROBOFLAGS)
mail.h.html : mail.h
	$(ROBODOC) mail.h mail.h.html $(ROBOFLAGS)
phase.c.html : phase.c
	$(ROBODOC) phase.c phase.c.html $(ROBOFLAGS)
phase.h.html : phase.h
	$(ROBODOC) phase.h phase.h.html $(ROBOFLAGS)
process.c.html : process.c
	$(ROBODOC) process.c process.c.html $(ROBOFLAGS)
process.h.html : process.h
	$(ROBODOC) process.h process.h.html $(ROBOFLAGS)
report.c.html : report.c
	$(ROBODOC) report.c report.c.html $(ROBOFLAGS)
report.h.html : report.h
	$(ROBODOC) report.h report.h.html $(ROBOFLAGS)
report_m.c.html : report_m.c
	$(ROBODOC) report_m.c report_m.c.html $(ROBOFLAGS)
report_m.h.html : report_m.h
	$(ROBODOC) report_m.h report_m.h.html $(ROBOFLAGS)
report_xml.c.html : report_xml.c
	$(ROBODOC) report_xml.c report_xml.c.html $(ROBOFLAGS)
report_xml.h.html : report_xml.h
	$(ROBODOC) report_xml.h report_xml.h.html $(ROBOFLAGS)
savegame.c.html : savegame.c
	$(ROBODOC) savegame.c savegame.c.html $(ROBOFLAGS)
savegame.h.html : savegame.h
	$(ROBODOC) savegame.h savegame.h.html $(ROBOFLAGS)
selftest.c.html : selftest.c
	$(ROBODOC) selftest.c selftest.c.html $(ROBOFLAGS)
selftest.h.html : selftest.h
	$(ROBODOC) selftest.h selftest.h.html $(ROBOFLAGS)
util.c.html : util.c
	$(ROBODOC) util.c util.c.html $(ROBOFLAGS)
util.h.html : util.h
	$(ROBODOC) util.h util.h.html $(ROBOFLAGS)

masterindex.html: galaxyng.xrefs
	$(ROBODOC) galaxyng.xrefs masterindex.html INDEX




# DO NOT DELETE

loadgame.o: loadgame.h galaxy.h list.h util.h
savegame.o: savegame.h galaxy.h list.h util.h
create.o: create.h galaxy.h list.h util.h report.h loadgame.h mail.h
create.o: report_m.h report_xml.h savegame.h process.h phase.h battle.h
create.o: selftest.h
phase.o: galaxy.h list.h util.h phase.h loadgame.h savegame.h
battle.o: battle.h galaxy.h list.h util.h
process.o: process.h galaxy.h list.h util.h savegame.h loadgame.h phase.h
process.o: battle.h report.h mail.h report_m.h report_xml.h selftest.h
report.o: report.h galaxy.h loadgame.h list.h util.h mail.h report_m.h
report.o: report_xml.h
util.o: util.h galaxy.h list.h loadgame.h
list.o: list.h util.h galaxy.h
selftest.o: selftest.h galaxy.h util.h list.h create.h process.h savegame.h
selftest.o: loadgame.h phase.h battle.h report.h mail.h report_m.h
selftest.o: report_xml.h
report_xml.o: report_xml.h galaxy.h report.h loadgame.h list.h util.h mail.h
report_xml.o: report_m.h
mail.o: mail.h galaxy.h util.h list.h
report_m.o: report_m.h galaxy.h list.h util.h report.h loadgame.h mail.h
report_m.o: report_xml.h
galaxyng.o: galaxy.h util.h list.h process.h savegame.h loadgame.h phase.h
galaxyng.o: battle.h report.h mail.h report_m.h report_xml.h selftest.h
galaxyng.o: create.h
wopr.o: galaxy.h util.h list.h process.h savegame.h loadgame.h phase.h
wopr.o: battle.h report.h mail.h report_m.h report_xml.h selftest.h create.h
wopr.o: wopr.h
globals.o: galaxy.h
