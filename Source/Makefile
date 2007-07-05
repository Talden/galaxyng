#
# 	$Id$	
#
# This are the setting for a Sun Sparc Station and Linux Box
#
# !! Warning !!
# DO NOT USE -O2 OR ANY OTHER FORM OF OPTIMIZATION
# IT WILL BREAK THE CODE
#
#
# NOTE
#
# This makefile is much bigger than necessary. With a few implicit
# rules it could be a fraction of the size. However not all versions
# of make support this. This makefile will hopefully work with even
# all versions of make.
#
# If you use this makefile for regular developement,
# use a
#   make depend
# to update the dependencies.
#
#
# Influence mapping:
# if you want to have a .png map generated when the -influence 
# command is used, then you'll need to have libgd 
# (http://www.boutell.com/gd/) installed with png, jpeg, and 
# freetype support enabled and uncomment the following lines:
# ADDTL_CFLAGS = -DDRAW_INFLUENCE_MAP
# ADDTL_LIBS = ../lib/libgd.a -lpng -lz -ljpeg -lfreetype
# ADDTL_SRCS = influence.c
# ADDTL_OBJS = influence.o
#
# NOTE: that influence mapping is now turned on by default and you'll
#       have to comment out the above lines to get rid of it
#

CFLAGS = -g -Wall -pedantic -I../include
CFLAGS += $(ADDTL_CFLAGS)
#CFLAGS += -fdelete-null-pointer-checks -std=gnu99 -D__USE_GNU 
#CFLAGS += -pipe -Wcast-qual -Wconversion -Wfloat-equal -Wformat=2
#CFLAGS += -Wmissing-declarations -Wmissing-format-attribute -Wnested-externs
#CFLAGS += -Wredundant-decls -Wstrict-prototypes -Wunreachable-code

LIBS = -L../lib -lgalaxyng -lm $(ADDTL_LIBS)

# For a cross compile.
MINGW_CC=/usr/local/bin/i386-mingw32-gcc

# Everybody has gcc
CC=gcc

GNG_SRCS=galaxyng.c loadgame.c savegame.c create.c phase.c battle.c \
	process.c report.c selftest.c report_xml.c cmd_template.c cmd_run.c \
	report_m.c avl.c usage.c checkTime.c \
	cmd_check.c cmd_create.c cmd_mail0.c \
	cmd_clean.c cmd_report.c cmd_score.c cmd_dump.c \
	cmd_test.c cmd_selftest.c \
	$(ADDTL_SOURCES)

GNG_OBJS=$(GNG_SRCS:.c=.o)

# Dependencies files.
# Automatically created with gcc
DEPS = $(GNG_OBJS:.o=.d)

WOPR_SRCS=wopr.c 
WOPR_OBJS=$(WOPR_SRCS:.c=.o)

GALAXYNG=galaxyng
WOPR=wopr

all: $(GALAXYNG)

loadgame.o: loadgame.c
	$(CC) $(CFLAGS) -c loadgame.c -o loadgame.o

cmd_template.o: cmd_template.c
	$(CC) $(CFLAGS) -c cmd_template.c -o cmd_template.o

cmd_create.o: cmd_create.c
	$(CC) $(CFLAGS) -c cmd_create.c -o cmd_create.o

cmd_mail0.o: cmd_mail0.c
	$(CC) $(CFLAGS) -c cmd_mail0.c -o cmd_mail0.o

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


$(GALAXYNG): $(GNG_OBJS) ../lib/libgalaxyng.a
	$(CC) $(GNG_OBJS) -o $(GALAXYNG)$(EXE) $(LIBS)

$(WOPR): $(WOPR_OBJS)
	$(CC) $(WOPR_OBJS) -o $(WOPR) $(LIBS)

clean:
	rm -f $(GNG_OBJS) $(WOPR_OBJS) $(DEPS)
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


# Cross compile for windows.
#
xcompile:
	$(MAKE) -f Makefile CC=$(MINGW_CC) EXE=.exe galaxyng


#=========================================================
#                For development 
#=========================================================

tags:
	ctags -R .

test: galaxyng
	cp galaxyng $(HOME)/Games/galaxyng

count:
	egrep -v -G "^ \*" *.c *.h | egrep -v -G "/\*"  | wc

#
# Indent all the .c files according to the settings
# in .indent.pro
# It is good to have a similar look for all sourcecode 
# See man indent for more information.
indent:
	indent *.c

-include $(DEPS)

depend:
	$(CC) -MD -E -I../include $(GNG_SRCS) > /dev/null

