#
# $Id$
#

PAGES=players.html tiger3ships.html tiger3effind.html
M4=m4

%.html : %.m4
	$(M4) -P -I../.. $< > $@

all: $(PAGES)

clean:
	rm -f *~ 
	rm -f $(PAGES)

