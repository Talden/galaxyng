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

GNG_SRCS=galaxyng.c loadgame.c savegame.c create.c phase.c battle.c \
	process.c report.c selftest.c report_xml.c cmd_template.c cmd_run.c \
	report_m.c avl.c usage.c cmd_immediate.c influence.c checkTime.c \
	cmd_check.c cmd_relay.c cmd_relaymessage.c cmd_create.c cmd_mail0.c \
	cmd_clean.c cmd_report.c cmd_score.c cmd_graph.c cmd_dump.c \
	cmd_test.c cmd_selftest.c cmd_battletest.c cmd_ordersdue.c \
	$(ADDTL_SOURCES)

GNG_OBJS=$(GNG_SRCS:.c=.o)

WOPR_SRCS=wopr.c 
WOPR_OBJS=$(WOPR_SRCS:.c=.o)

GALAXYNG=galaxyng
WOPR=wopr

all: $(GALAXYNG)

loadgame.o: loadgame.c
	$(CC) $(CFLAGS) -c loadgame.c -o loadgame.o

cmd_template.o: cmd_template.c
	$(CC) $(CFLAGS) -c cmd_template.c -o cmd_template.o

cmd_relay.o: cmd_relay.c
	$(CC) $(CFLAGS) -c cmd_relay.c -o cmd_relay.o

cmd_relaymessage.o: cmd_relaymessage.c
	$(CC) $(CFLAGS) -c cmd_relaymessage.c -o cmd_relaymessage.o

cmd_create.o: cmd_create.c
	$(CC) $(CFLAGS) -c cmd_create.c -o cmd_create.o

cmd_mail0.o: cmd_mail0.c
	$(CC) $(CFLAGS) -c cmd_mail0.c -o cmd_mail0.o

cmd_immediate.o: cmd_immediate.c
	$(CC) $(CFLAGS) -c cmd_immediate.c -o cmd_immediate.o

cmd_run.o: cmd_run.c
	$(CC) $(CFLAGS) -c cmd_run.c -o cmd_run.o

cmd_clean.o: cmd_clean.c
	$(CC) $(CFLAGS) -c cmd_clean.c -o cmd_clean.o

cmd_report.o: cmd_report.c
	$(CC) $(CFLAGS) -c cmd_report.c -o cmd_report.o

cmd_score.o: cmd_score.c
	$(CC) $(CFLAGS) -c cmd_score.c -o cmd_score.o

cmd_graph.o: cmd_graph.c
	$(CC) $(CFLAGS) -c cmd_graph.c -o cmd_graph.o

cmd_dump.o: cmd_dump.c
	$(CC) $(CFLAGS) -c cmd_dump.c -o cmd_dump.o

cmd_test.o: cmd_test.c
	$(CC) $(CFLAGS) -c cmd_test.c -o cmd_test.o

cmd_selftest.o: cmd_selftest.c
	$(CC) $(CFLAGS) -c cmd_selftest.c -o cmd_selftest.o

cmd_battletest.o: cmd_battletest.c
	$(CC) $(CFLAGS) -c cmd_battletest.c -o cmd_battletest.o

cmd_ordersdue.o: cmd_ordersdue.c
	$(CC) $(CFLAGS) -c cmd_ordersdue.c -o cmd_ordersdue.o

usage.o: usage.c
	$(CC) $(CFLAGS) -c usage.c -o usage.o

savegame.o: savegame.c
	$(CC) $(CFLAGS) -c savegame.c -o savegame.o

mail0.o: mail0.c
	$(CC) $(CFLAGS) -c mail0.c -o mail0.o

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

ordersdue.o: ordersdue.c
	$(CC) $(CFLAGS) -c ordersdue.c -o ordersdue.o

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


$(GALAXYNG): $(GNG_OBJS)
	$(CC) $(GNG_OBJS) -o $(GALAXYNG) $(LIBS)

$(WOPR): $(WOPR_OBJS)
	$(CC) $(WOPR_OBJS) -o $(WOPR) $(LIBS)

clean:
	rm -f $(GNG_OBJS) $(WOPR_OBJS)
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
mail0.o: ../include/create.h ../include/galaxy.h ../include/strutl.h
mail0.o: ../include/cookies.h
mail0.o: ../include/logging.h 
mail0.o: ../include/avl.h
mail0.o: ../include/list.h ../include/util.h
mail0.o: ../include/report.h ../include/loadgame.h ../include/mail.h
mail0.o: ../include/report_m.h ../include/report_xml.h ../include/savegame.h
mail0.o: ../include/process.h ../include/phase.h ../include/battle.h
mail0.o: ../include/selftest.h
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
battletest.o: ../include/selftest.h ../include/galaxy.h ../include/strutl.h
battletest.o: ../include/cookies.h ../include/logging.h
battletest.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
battletest.o: ../include/util.h /usr/include/limits.h
battletest.o: ../include/list.h ../include/create.h ../include/avl.h
battletest.o: ../include/process.h
battletest.o: ../include/savegame.h ../include/loadgame.h ../include/phase.h
battletest.o: ../include/battle.h ../include/report.h ../include/mail.h
battletest.o: ../include/report_m.h ../include/report_xml.h
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
