#
# $Id$
#

Source/galaxyng:
	cd Source ; make ; cd .. 
	
ARE/are:
	cd ARE ; make ; cd ..

install: Source/galaxyng
	./install.sh

clean:
	cd Source ; make clean ; cd ..
	cd Util   ; make clean ; cd ..
	cd ARE    ; make clean ; cd ..
	rm -f *~ *.bak
