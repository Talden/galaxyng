#
# $Id$
#

Source/galaxyng:
	cd Source ; make ; cd .. 

install: Source/galaxyng
	./install.sh

clean:
	cd Source ; make clean ; cd ..
	cd Util   ; make clean ; cd ..
	cd Doc    ; make clean ; cd ..
	cd ARE    ; make clean ; cd ..
	rm -f *~ index.html *.bak

wwwdocs:
	cd Doc ; make wwwbase      ; cd ..
	cd Doc ; make distribution ; cd ..

distribution:
	cd Doc ; make relbase      ; cd ..
	cd Doc ; make distribution ; cd ..

