#
# $Id$
#

M4=m4

DOCS=FAQ.html index.html server.html ManGalaxyNG.html RefManual.html

%.html : %.m4
	$(M4) -P -I ../../WWW/ $< > $@

clean:
	rm -f *~ *.html base.m4
	rm -f toc.m4 stoc.m4

wwwbase:  
	cp ../../WWW/wwwbase.m4 base.m4

relbase:
	cp relbase.m4 base.m4

distribution: $(DOCS)
	mv index.html ..	

#
# Server Manual with auto generated table of contents.
#


server.html: server.m4 stoc.html
	$(M4) -P -I ../../WWW/ $< > $@	

stoc.html: stoc.m4 tocgen.m4
	$(M4) -P $< > $@

stoc.m4: server.m4
	echo  "m4_include(tocgen.m4)m4_dnl" > $@
	egrep "(www).*(ection)" $< >> $@

#
# Manual with auto generated table of contents.
#

ManGalaxyNG.html: ManGalaxyNG.m4 toc.html
	$(M4) -P -I ../../WWW/ $< > $@	


toc.html: toc.m4 tocgen.m4
	$(M4) -P $< > $@


toc.m4: ManGalaxyNG.m4
	echo  "m4_include(tocgen.m4)m4_dnl" > $@
	egrep "(www).*(ection)" $< >> $@

