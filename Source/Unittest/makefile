#****h* GalaxyNG/Unittest
# FUNCTION
#   Unittest for WOPR and GalaxyNG
#*****

RBT_DIR     = /home/galaxyng/robotester-0.0.3/Source
NG_DIR      = /home/galaxyng/NG/Source
ROBORUN     = $(RBT_DIR)/roborun.pl

CC     = gcc
LIBS   = -lm
CFLAGS = -g -Wall -pedantic -I$(RBT_DIR) -I$(NG_DIR) -DROBOTESTER


#****v* Unittest/RBT_SOURCES
# FUNCTION
#   These are the source files for the robotester C framework.
#   We always need these.
# SOURCE
#
RBT_SOURCES = $(RBT_DIR)/rbt_assert.c \
              $(RBT_DIR)/robotester.c \
              $(RBT_DIR)/testcase.c \
              $(RBT_DIR)/testsuite.c

RBT_OBJECTS = ${RBT_SOURCES:.c=.o}

#*****

#****v* Unittest/TEST_SOURCES
# FUNCTION
#   These are the source files of the unittest.
# SOURCE
#

TEST_SOURCES = create_suites.c
TEST_OBJECTS = ${TEST_SOURCES:.c=.o}

#******

#****v* Unittest/REAL_SOURCES
# FUNCTION
#   These are the common sources between wopr and galaxyng
# SOURCE
#
REAL_SOURCES = $(NG_DIR)/loadgame.c $(NG_DIR)/savegame.c $(NG_DIR)/create.c $(NG_DIR)/phase.c \
               $(NG_DIR)/battle.c $(NG_DIR)/process.c \
               $(NG_DIR)/report.c $(NG_DIR)/util.c $(NG_DIR)/list.c $(NG_DIR)/selftest.c \
               $(NG_DIR)/report_xml.c $(NG_DIR)/mail.c \
               $(NG_DIR)/report_m.c $(NG_DIR)/globals.c \
               $(NG_DIR)/avl.c $(NG_DIR)/usage.c 
REAL_OBJECTS = ${REAL_SOURCES:.c=.o}

#******

WOPR_SOURCES = $(NG_DIR)/wopr.c
WOPR_OBJECTS = ${WOPR_SOURCES:.c=.o}

#****v* Unittest/OBJECTS
# FUNCTION
#   All the objects needed for the tester application.
# SOURCE
#

OBJECTS = $(RBT_OBJECTS) $(TEST_OBJECTS) $(REAL_OBJECTS)

#******

#****e* Example/robotester
# FUNCTION
#   This builds the test application that can run the individual
#   testcases in the unittest for WOPR.
# SOURCE
#

woprtester : $(OBJECTS) $(WOPR_OBJECTS)
	$(CC) $(OBJECTS) $(WOPR_OBJECTS) -o woprtester $(LIBS)

#*****

# TODO  target for ngtester

#****e* Example/test
# FUNCTION
#    This runs the testcases and collects all the results.
# SOURCE

test: woprtester
	perl $(ROBORUN)

#****

clean:
	-rm -f $(OBJECTS)
	-rm -f woprtester

