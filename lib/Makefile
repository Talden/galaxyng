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

strutl.o: ../include/strutl.h /usr/include/stdio.h /usr/include/features.h
strutl.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
strutl.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
strutl.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
strutl.o: /usr/include/bits/typesizes.h /usr/include/libio.h
strutl.o: /usr/include/_G_config.h /usr/include/wchar.h
strutl.o: /usr/include/bits/wchar.h /usr/include/gconv.h
strutl.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
strutl.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
strutl.o: /usr/include/string.h /usr/include/ctype.h /usr/include/endian.h
strutl.o: /usr/include/bits/endian.h /usr/include/malloc.h
strutl.o: /usr/include/assert.h ../include/cookies.h ../include/logging.h
