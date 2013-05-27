all: src test qtsrc Makefile

.PHONY:src test qtsrc clean

src:
	make -C src
qtsrc:
	make -C qtsrc
	cp qtsrc/qtsrc bin/androidmanage
clean:
	make -C src clean
	make -C qtsrc clean
	rm ./etc/tmp/*
	rm ./etc/vusr/*
#qtinstall:
#	./build/qtinstall.sh
help:
	@echo "Usage: make xxx"
	@echo "  make qtinstall must be run at the first time you compile!"
	@echo "  Other support target for make is: src/test/qtsrc/clean"
	@echo "  The lib and obj files will be placed at ./libs"
	
