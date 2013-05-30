ifeq ($(__QT__),)
all:
	qmake -project
	echo "QT  += webkit" >> qtsrc.pro
	echo "QT  +=network" >> qtsrc.pro
#	echo "QT += sql" >> qtsrc.pro
	qmake -o makefile-tmp
	sed -e 's/\(^INCPATH.*\)\=/\1+=/' -e 's/\(^LIBS.*\)\=/\1+=/' < makefile-tmp >makefile-qt
	rm -f makefile-tmp
	make __QT__=1
clean:
	rm -f moc_*.cpp qrc_*.cpp ui_*.h *.o *~ core *.core
else

LIBS		:= -L../libs -landroidmanage  -L/usr/local/Trolltech/Qt-4.8.4/lib
INCPATH		:= -I../inc -I/usr/local/Trolltech/Qt-4.8.4/include
include makefile-qt

endif
