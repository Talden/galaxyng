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
#ADDTL_CFLAGS = -DDRAW_INFLUENCE_MAP
#ADDTL_LIBS = -lgd -lpng -lz -ljpeg -lfreetype
#ADDTL_SRCS = influence.c
#ADDTL_OBJS = influence.o

CFLAGS = -Wall -pedantic -I../include $(ADDTL_CFLAGS)
#CFLAGS = -Wall -pedantic -DFS_NEW_FORECAST $(ADDTL_CFLAGS)
LIBS = -L../lib -lgalaxyng -lm $(ADDTL_LIBS)


CC=gcc

SOURCES=loadgame.c savegame.c create.c phase.c battle.c process.c \
        report.c util.c selftest.c report_xml.c mail.c \
        report_m.c galaxyng.c wopr.c globals.c avl.c usage.c $(ADDTL_SOURCES)

OBJECTS=loadgame.o savegame.o create.o phase.o battle.o process.o \
        report.o util.o selftest.o report_xml.o mail.o \
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

loadgame.o: /usr/include/assert.h /usr/include/features.h
loadgame.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
loadgame.o: ../include/loadgame.h ../include/galaxy.h ../include/strutl.h
loadgame.o: /usr/include/stdio.h
loadgame.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
loadgame.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
loadgame.o: /usr/include/bits/typesizes.h /usr/include/libio.h
loadgame.o: /usr/include/_G_config.h /usr/include/wchar.h
loadgame.o: /usr/include/bits/wchar.h /usr/include/gconv.h
loadgame.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
loadgame.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
loadgame.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
loadgame.o: /usr/include/endian.h /usr/include/bits/endian.h
loadgame.o: /usr/include/malloc.h ../include/cookies.h ../include/logging.h
loadgame.o: /usr/include/time.h /usr/include/bits/time.h ../include/list.h
loadgame.o: ../include/util.h /usr/include/limits.h
loadgame.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
savegame.o: /usr/include/assert.h /usr/include/features.h
savegame.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
savegame.o: /usr/include/string.h
savegame.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
savegame.o: ../include/savegame.h ../include/galaxy.h ../include/strutl.h
savegame.o: /usr/include/stdio.h /usr/include/bits/types.h
savegame.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
savegame.o: /usr/include/libio.h /usr/include/_G_config.h
savegame.o: /usr/include/wchar.h /usr/include/bits/wchar.h
savegame.o: /usr/include/gconv.h
savegame.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
savegame.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
savegame.o: /usr/include/stdlib.h /usr/include/ctype.h /usr/include/endian.h
savegame.o: /usr/include/bits/endian.h /usr/include/malloc.h
savegame.o: ../include/cookies.h ../include/logging.h /usr/include/time.h
savegame.o: /usr/include/bits/time.h ../include/list.h ../include/util.h
savegame.o: /usr/include/limits.h
savegame.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
create.o: ../include/create.h ../include/galaxy.h ../include/strutl.h
create.o: /usr/include/stdio.h /usr/include/features.h
create.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
create.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
create.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
create.o: /usr/include/bits/typesizes.h /usr/include/libio.h
create.o: /usr/include/_G_config.h /usr/include/wchar.h
create.o: /usr/include/bits/wchar.h /usr/include/gconv.h
create.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
create.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
create.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
create.o: /usr/include/endian.h /usr/include/bits/endian.h
create.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
create.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
create.o: ../include/avl.h /usr/include/fcntl.h /usr/include/bits/fcntl.h
create.o: /usr/include/sys/types.h /usr/include/math.h
create.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
create.o: /usr/include/bits/mathcalls.h ../include/list.h ../include/util.h
create.o: /usr/include/limits.h
create.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
create.o: ../include/report.h ../include/loadgame.h ../include/mail.h
create.o: ../include/report_m.h ../include/report_xml.h ../include/savegame.h
create.o: ../include/process.h ../include/phase.h ../include/battle.h
create.o: ../include/selftest.h
phase.o: /usr/include/math.h /usr/include/features.h /usr/include/sys/cdefs.h
phase.o: /usr/include/gnu/stubs.h /usr/include/bits/huge_val.h
phase.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
phase.o: /usr/include/assert.h /usr/include/stdlib.h
phase.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
phase.o: /usr/include/string.h ../include/galaxy.h ../include/strutl.h
phase.o: /usr/include/stdio.h /usr/include/bits/types.h
phase.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
phase.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
phase.o: /usr/include/bits/wchar.h /usr/include/gconv.h
phase.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
phase.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
phase.o: /usr/include/ctype.h /usr/include/endian.h
phase.o: /usr/include/bits/endian.h /usr/include/malloc.h
phase.o: ../include/cookies.h ../include/logging.h /usr/include/time.h
phase.o: /usr/include/bits/time.h ../include/list.h ../include/util.h
phase.o: /usr/include/limits.h
phase.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
phase.o: ../include/phase.h ../include/loadgame.h ../include/savegame.h
battle.o: ../include/battle.h ../include/galaxy.h ../include/strutl.h
battle.o: /usr/include/stdio.h /usr/include/features.h
battle.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
battle.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
battle.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
battle.o: /usr/include/bits/typesizes.h /usr/include/libio.h
battle.o: /usr/include/_G_config.h /usr/include/wchar.h
battle.o: /usr/include/bits/wchar.h /usr/include/gconv.h
battle.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
battle.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
battle.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
battle.o: /usr/include/endian.h /usr/include/bits/endian.h
battle.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
battle.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
battle.o: /usr/include/math.h /usr/include/bits/huge_val.h
battle.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
battle.o: ../include/list.h ../include/util.h /usr/include/limits.h
battle.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
process.o: /usr/include/ctype.h /usr/include/features.h
process.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
process.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
process.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
process.o: /usr/include/bits/typesizes.h /usr/include/endian.h
process.o: /usr/include/bits/endian.h /usr/include/assert.h
process.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
process.o: /usr/include/stdlib.h /usr/include/math.h
process.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
process.o: /usr/include/bits/mathcalls.h /usr/include/string.h
process.o: ../include/process.h ../include/galaxy.h ../include/strutl.h
process.o: /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h
process.o: /usr/include/wchar.h /usr/include/bits/wchar.h
process.o: /usr/include/gconv.h /usr/include/bits/stdio_lim.h
process.o: /usr/include/bits/sys_errlist.h /usr/include/malloc.h
process.o: ../include/cookies.h ../include/logging.h /usr/include/time.h
process.o: /usr/include/bits/time.h ../include/list.h ../include/util.h
process.o: /usr/include/limits.h
process.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
process.o: ../include/savegame.h ../include/loadgame.h ../include/phase.h
process.o: ../include/battle.h ../include/report.h ../include/mail.h
process.o: ../include/report_m.h ../include/report_xml.h
process.o: ../include/selftest.h
report.o: ../include/report.h ../include/galaxy.h ../include/strutl.h
report.o: /usr/include/stdio.h /usr/include/features.h
report.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
report.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
report.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
report.o: /usr/include/bits/typesizes.h /usr/include/libio.h
report.o: /usr/include/_G_config.h /usr/include/wchar.h
report.o: /usr/include/bits/wchar.h /usr/include/gconv.h
report.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
report.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
report.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
report.o: /usr/include/endian.h /usr/include/bits/endian.h
report.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
report.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
report.o: ../include/loadgame.h ../include/list.h ../include/util.h
report.o: /usr/include/limits.h
report.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
report.o: ../include/mail.h ../include/report_m.h ../include/report_xml.h
report.o: ../include/create.h ../include/avl.h /usr/include/fcntl.h
report.o: /usr/include/bits/fcntl.h /usr/include/sys/types.h
report.o: /usr/include/math.h /usr/include/bits/huge_val.h
report.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
util.o: ../include/util.h ../include/galaxy.h ../include/strutl.h
util.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
util.o: /usr/include/gnu/stubs.h
util.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
util.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
util.o: /usr/include/bits/typesizes.h /usr/include/libio.h
util.o: /usr/include/_G_config.h /usr/include/wchar.h
util.o: /usr/include/bits/wchar.h /usr/include/gconv.h
util.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
util.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
util.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
util.o: /usr/include/endian.h /usr/include/bits/endian.h
util.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
util.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
util.o: /usr/include/limits.h
util.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
util.o: ../include/list.h /usr/include/math.h /usr/include/bits/huge_val.h
util.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
util.o: /usr/include/sys/stat.h /usr/include/bits/stat.h
util.o: /usr/include/sys/types.h /usr/include/fcntl.h
util.o: /usr/include/bits/fcntl.h /usr/include/unistd.h
util.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
util.o: ../include/create.h ../include/avl.h ../include/loadgame.h
selftest.o: ../include/selftest.h ../include/galaxy.h ../include/strutl.h
selftest.o: /usr/include/stdio.h /usr/include/features.h
selftest.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
selftest.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
selftest.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
selftest.o: /usr/include/bits/typesizes.h /usr/include/libio.h
selftest.o: /usr/include/_G_config.h /usr/include/wchar.h
selftest.o: /usr/include/bits/wchar.h /usr/include/gconv.h
selftest.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
selftest.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
selftest.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
selftest.o: /usr/include/endian.h /usr/include/bits/endian.h
selftest.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
selftest.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
selftest.o: /usr/include/math.h /usr/include/bits/huge_val.h
selftest.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
selftest.o: ../include/util.h /usr/include/limits.h
selftest.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
selftest.o: ../include/list.h ../include/create.h ../include/avl.h
selftest.o: /usr/include/fcntl.h /usr/include/bits/fcntl.h
selftest.o: /usr/include/sys/types.h ../include/process.h
selftest.o: ../include/savegame.h ../include/loadgame.h ../include/phase.h
selftest.o: ../include/battle.h ../include/report.h ../include/mail.h
selftest.o: ../include/report_m.h ../include/report_xml.h
report_xml.o: /usr/include/time.h /usr/include/features.h
report_xml.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
report_xml.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
report_xml.o: /usr/include/bits/time.h /usr/include/bits/types.h
report_xml.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
report_xml.o: ../include/create.h ../include/galaxy.h ../include/strutl.h
report_xml.o: /usr/include/stdio.h /usr/include/libio.h
report_xml.o: /usr/include/_G_config.h /usr/include/wchar.h
report_xml.o: /usr/include/bits/wchar.h /usr/include/gconv.h
report_xml.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
report_xml.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
report_xml.o: /usr/include/stdlib.h /usr/include/string.h
report_xml.o: /usr/include/ctype.h /usr/include/endian.h
report_xml.o: /usr/include/bits/endian.h /usr/include/malloc.h
report_xml.o: /usr/include/assert.h ../include/cookies.h ../include/logging.h
report_xml.o: ../include/avl.h /usr/include/fcntl.h /usr/include/bits/fcntl.h
report_xml.o: /usr/include/sys/types.h ../include/report_xml.h
report_xml.o: ../include/report.h ../include/loadgame.h ../include/list.h
report_xml.o: ../include/util.h /usr/include/limits.h
report_xml.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
report_xml.o: ../include/mail.h ../include/report_m.h
mail.o: ../include/mail.h ../include/galaxy.h ../include/strutl.h
mail.o: /usr/include/stdio.h /usr/include/features.h /usr/include/sys/cdefs.h
mail.o: /usr/include/gnu/stubs.h
mail.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
mail.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
mail.o: /usr/include/bits/typesizes.h /usr/include/libio.h
mail.o: /usr/include/_G_config.h /usr/include/wchar.h
mail.o: /usr/include/bits/wchar.h /usr/include/gconv.h
mail.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
mail.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
mail.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
mail.o: /usr/include/endian.h /usr/include/bits/endian.h
mail.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
mail.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
mail.o: ../include/util.h /usr/include/limits.h
mail.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
mail.o: ../include/list.h
report_m.o: ../include/create.h ../include/galaxy.h ../include/strutl.h
report_m.o: /usr/include/stdio.h /usr/include/features.h
report_m.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
report_m.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
report_m.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
report_m.o: /usr/include/bits/typesizes.h /usr/include/libio.h
report_m.o: /usr/include/_G_config.h /usr/include/wchar.h
report_m.o: /usr/include/bits/wchar.h /usr/include/gconv.h
report_m.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
report_m.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
report_m.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
report_m.o: /usr/include/endian.h /usr/include/bits/endian.h
report_m.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
report_m.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
report_m.o: ../include/avl.h /usr/include/fcntl.h /usr/include/bits/fcntl.h
report_m.o: /usr/include/sys/types.h ../include/report_m.h ../include/list.h
report_m.o: ../include/util.h /usr/include/limits.h
report_m.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
report_m.o: ../include/report.h ../include/loadgame.h ../include/mail.h
report_m.o: ../include/report_xml.h
galaxyng.o: /usr/include/math.h /usr/include/features.h
galaxyng.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
galaxyng.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
galaxyng.o: /usr/include/bits/mathcalls.h /usr/include/stdlib.h
galaxyng.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
galaxyng.o: /usr/include/assert.h /usr/include/string.h /usr/include/time.h
galaxyng.o: /usr/include/bits/time.h /usr/include/bits/types.h
galaxyng.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
galaxyng.o: /usr/include/sys/types.h /usr/include/unistd.h
galaxyng.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
galaxyng.o: ../include/galaxy.h ../include/strutl.h /usr/include/stdio.h
galaxyng.o: /usr/include/libio.h /usr/include/_G_config.h
galaxyng.o: /usr/include/wchar.h /usr/include/bits/wchar.h
galaxyng.o: /usr/include/gconv.h
galaxyng.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
galaxyng.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
galaxyng.o: /usr/include/ctype.h /usr/include/endian.h
galaxyng.o: /usr/include/bits/endian.h /usr/include/malloc.h
galaxyng.o: ../include/cookies.h ../include/logging.h ../include/util.h
galaxyng.o: /usr/include/limits.h
galaxyng.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
galaxyng.o: ../include/list.h ../include/process.h ../include/savegame.h
galaxyng.o: ../include/loadgame.h ../include/phase.h ../include/battle.h
galaxyng.o: ../include/report.h ../include/mail.h ../include/report_m.h
galaxyng.o: ../include/report_xml.h ../include/selftest.h ../include/create.h
galaxyng.o: ../include/avl.h /usr/include/fcntl.h /usr/include/bits/fcntl.h
galaxyng.o: ../include/galaxyng.h
wopr.o: ../include/galaxy.h ../include/strutl.h /usr/include/stdio.h
wopr.o: /usr/include/features.h /usr/include/sys/cdefs.h
wopr.o: /usr/include/gnu/stubs.h
wopr.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
wopr.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
wopr.o: /usr/include/bits/typesizes.h /usr/include/libio.h
wopr.o: /usr/include/_G_config.h /usr/include/wchar.h
wopr.o: /usr/include/bits/wchar.h /usr/include/gconv.h
wopr.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
wopr.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
wopr.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
wopr.o: /usr/include/endian.h /usr/include/bits/endian.h
wopr.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
wopr.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
wopr.o: /usr/include/math.h /usr/include/bits/huge_val.h
wopr.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
wopr.o: ../include/util.h /usr/include/limits.h
wopr.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
wopr.o: ../include/list.h ../include/process.h ../include/savegame.h
wopr.o: ../include/loadgame.h ../include/phase.h ../include/battle.h
wopr.o: ../include/report.h ../include/mail.h ../include/report_m.h
wopr.o: ../include/report_xml.h ../include/selftest.h ../include/create.h
wopr.o: ../include/avl.h /usr/include/fcntl.h /usr/include/bits/fcntl.h
wopr.o: /usr/include/sys/types.h ../include/wopr.h
globals.o: ../include/galaxy.h ../include/strutl.h /usr/include/stdio.h
globals.o: /usr/include/features.h /usr/include/sys/cdefs.h
globals.o: /usr/include/gnu/stubs.h
globals.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
globals.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
globals.o: /usr/include/bits/typesizes.h /usr/include/libio.h
globals.o: /usr/include/_G_config.h /usr/include/wchar.h
globals.o: /usr/include/bits/wchar.h /usr/include/gconv.h
globals.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
globals.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
globals.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
globals.o: /usr/include/endian.h /usr/include/bits/endian.h
globals.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
globals.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
avl.o: ../include/avl.h /usr/include/stdio.h /usr/include/features.h
avl.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
avl.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
avl.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
avl.o: /usr/include/bits/typesizes.h /usr/include/libio.h
avl.o: /usr/include/_G_config.h /usr/include/wchar.h
avl.o: /usr/include/bits/wchar.h /usr/include/gconv.h
avl.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
avl.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
usage.o: ../include/galaxy.h ../include/strutl.h /usr/include/stdio.h
usage.o: /usr/include/features.h /usr/include/sys/cdefs.h
usage.o: /usr/include/gnu/stubs.h
usage.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
usage.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
usage.o: /usr/include/bits/typesizes.h /usr/include/libio.h
usage.o: /usr/include/_G_config.h /usr/include/wchar.h
usage.o: /usr/include/bits/wchar.h /usr/include/gconv.h
usage.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
usage.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
usage.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
usage.o: /usr/include/endian.h /usr/include/bits/endian.h
usage.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
usage.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
galaxyng.o: /usr/include/math.h /usr/include/features.h
galaxyng.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
galaxyng.o: /usr/include/bits/huge_val.h /usr/include/bits/mathdef.h
galaxyng.o: /usr/include/bits/mathcalls.h /usr/include/stdlib.h
galaxyng.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
galaxyng.o: /usr/include/assert.h /usr/include/string.h /usr/include/time.h
galaxyng.o: /usr/include/bits/time.h /usr/include/bits/types.h
galaxyng.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
galaxyng.o: /usr/include/sys/types.h /usr/include/unistd.h
galaxyng.o: /usr/include/bits/posix_opt.h /usr/include/bits/confname.h
galaxyng.o: ../include/galaxy.h ../include/strutl.h /usr/include/stdio.h
galaxyng.o: /usr/include/libio.h /usr/include/_G_config.h
galaxyng.o: /usr/include/wchar.h /usr/include/bits/wchar.h
galaxyng.o: /usr/include/gconv.h
galaxyng.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
galaxyng.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
galaxyng.o: /usr/include/ctype.h /usr/include/endian.h
galaxyng.o: /usr/include/bits/endian.h /usr/include/malloc.h
galaxyng.o: ../include/cookies.h ../include/logging.h ../include/util.h
galaxyng.o: /usr/include/limits.h
galaxyng.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
galaxyng.o: ../include/list.h ../include/process.h ../include/savegame.h
galaxyng.o: ../include/loadgame.h ../include/phase.h ../include/battle.h
galaxyng.o: ../include/report.h ../include/mail.h ../include/report_m.h
galaxyng.o: ../include/report_xml.h ../include/selftest.h ../include/create.h
galaxyng.o: ../include/avl.h /usr/include/fcntl.h /usr/include/bits/fcntl.h
galaxyng.o: ../include/galaxyng.h
wopr.o: ../include/galaxy.h ../include/strutl.h /usr/include/stdio.h
wopr.o: /usr/include/features.h /usr/include/sys/cdefs.h
wopr.o: /usr/include/gnu/stubs.h
wopr.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
wopr.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
wopr.o: /usr/include/bits/typesizes.h /usr/include/libio.h
wopr.o: /usr/include/_G_config.h /usr/include/wchar.h
wopr.o: /usr/include/bits/wchar.h /usr/include/gconv.h
wopr.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
wopr.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
wopr.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
wopr.o: /usr/include/endian.h /usr/include/bits/endian.h
wopr.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
wopr.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
wopr.o: /usr/include/math.h /usr/include/bits/huge_val.h
wopr.o: /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h
wopr.o: ../include/util.h /usr/include/limits.h
wopr.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
wopr.o: ../include/list.h ../include/process.h ../include/savegame.h
wopr.o: ../include/loadgame.h ../include/phase.h ../include/battle.h
wopr.o: ../include/report.h ../include/mail.h ../include/report_m.h
wopr.o: ../include/report_xml.h ../include/selftest.h ../include/create.h
wopr.o: ../include/avl.h /usr/include/fcntl.h /usr/include/bits/fcntl.h
wopr.o: /usr/include/sys/types.h ../include/wopr.h
