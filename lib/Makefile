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
strutl.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/ctype.h
strutl.o: /usr/include/endian.h /usr/include/bits/endian.h
strutl.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
strutl.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
logging.o: ../include/logging.h /usr/include/stdio.h /usr/include/features.h
logging.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
logging.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
logging.o: /usr/include/bits/types.h /usr/include/bits/wordsize.h
logging.o: /usr/include/bits/typesizes.h /usr/include/libio.h
logging.o: /usr/include/_G_config.h /usr/include/wchar.h
logging.o: /usr/include/bits/wchar.h /usr/include/gconv.h
logging.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
logging.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
logging.o: /usr/include/time.h /usr/include/bits/time.h
list.o: ../include/list.h /usr/include/stdlib.h /usr/include/features.h
list.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
list.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stddef.h
list.o: /usr/include/string.h ../include/util.h ../include/galaxy.h
list.o: ../include/strutl.h /usr/include/stdio.h /usr/include/bits/types.h
list.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
list.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
list.o: /usr/include/bits/wchar.h /usr/include/gconv.h
list.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/stdarg.h
list.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
list.o: /usr/include/ctype.h /usr/include/endian.h /usr/include/bits/endian.h
list.o: /usr/include/malloc.h /usr/include/assert.h ../include/cookies.h
list.o: ../include/logging.h /usr/include/time.h /usr/include/bits/time.h
list.o: /usr/include/limits.h
list.o: /usr/lib/gcc-lib/i686-pc-linux-gnu/3.3.2/include/limits.h
