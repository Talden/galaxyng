#
# $Id$
#

PAGES=index.html

M4=m4

%.html : %.m4
	$(M4) -P -I.. $< > $@

all: $(PAGES) ../general.m4 hqnavigator.m4
	touch all

clean:
	rm -f *.html *~ all
