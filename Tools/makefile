#
#
#

PAGES=tools.html wopr.html report.html dist.html planets.html shipyard.html

M4=m4

%.html : %.m4
	$(M4) -P -I.. $< > $@

all: $(PAGES) ../general.m4 toolnavigator.m4
	touch all

clean:
	rm -f $(PAGES) *~ all
