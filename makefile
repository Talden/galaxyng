#
# $Id$
#

all : 
	make -C Source galaxyng
	make -C ARE

install: Source/galaxyng
	./install.sh

clean:
	cd Source ; make clean ; cd ..
	cd Util   ; make clean ; cd ..
	cd ARE    ; make clean ; cd ..
	rm -f *~ *.bak
