#
# $Id$(MAKE)file,v 1.7 1998/12/07 05:06:56 gumpu Exp $
#

PAGES=intro.html index.html index2.html download.html hosting.html games.html join.html \
links.html mailing.html example.html ng.html start.html news.html


M4=m4

%.html : %.m4
	$(M4) -P $< > $@

all: $(PAGES) general.m4 navigator.m4 Tools/all
	touch all

Tools/all:
	$(MAKE) -C Tools all
	$(MAKE) -C PTiger all
	$(MAKE) -C HQ all
	$(MAKE) -C Hall all

clean:
	rm -f $(PAGES) *~ all
	$(MAKE) -C Tools clean
	$(MAKE) -C Download clean
	$(MAKE) -C NonM4 clean
	$(MAKE) -C Hall clean
	$(MAKE) -C PTiger clean
	$(MAKE) -C Examples clean
	$(MAKE) -C HQ clean

