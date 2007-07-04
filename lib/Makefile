#
# $Id$
#
#
# NOTE:
#   If you use this makefile for regular development
#   run a 
#     make depend
#   to create a set of dependencies.
#

CFLAGS = -Wall -pedantic -I../include $(ADDTL_CFLAGS)
# For a cross compile.
MINGW_CC=/usr/local/bin/i386-mingw32-gcc
MINGW_AR=/usr/local/bin/i386-mingw32-ar

CC = gcc
AR = ar

SOURCES=strutl.c logging.c list.c globals.c mail.c util.c loadNGConfig.c \
		lockFile.c randomize.c
OBJECTS=$(SOURCES:.c=.o)
DEPENDENCIES = $(OBJECTS:.o=.d)

all : libgalaxyng.a

libgalaxyng.a: $(OBJECTS)
	$(AR) cr libgalaxyng.a $(OBJECTS)

clean:
	rm -f libgalaxyng.a $(OBJECTS) *~ $(DEPENDENCIES)

xcompile:
	$(MAKE) -f Makefile CC=$(MINGW_CC) AR=$(MINGW_AR) libgalaxyng.a

# Make a copy of the master configuration
# file.
.indent.pro : ../Source/.indent.pro
	cp ../Source/.indent.pro .indent.pro

# Indent all source code.
# It's good to have an uniform look.
# The  master configuration file is 
# in ../Source
indent: .indent.pro
	indent *.c

-include $(DEPENDENCIES)

# Use gcc to create the dependencies for us.
# This makes a set of .d files.
depend:
	$(CC) -MMD -E -I../include $(SOURCES) > /dev/null

