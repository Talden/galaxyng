#
#
#

PAGES=index.html

M4=m4

%.html : %.m4
	$(M4) -P -I.. $< > $@

all: $(PAGES) ../general.m4 hallnavigator.m4
	$(MAKE) -C Tiger all
	touch all

clean:
	rm -f $(PAGES) *~ all
	rm -f galaxybase HallOfFame.c hall.html players.html games.html
	$(MAKE) -C Tiger clean
