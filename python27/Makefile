PKGDIR= ${.CURDIR}/../../lang/python27

post-install:
	ln -s 2to3-2.7 ${DESTDIR}${PREFIX}/bin/2to3
	ln -s pydoc2.7 ${DESTDIR}${PREFIX}/bin/pydoc
	ln -s python2.7 ${DESTDIR}${PREFIX}/bin/python
	ln -s python2.7 ${DESTDIR}${PREFIX}/bin/python2
	ln -s smtpd2.7.py ${DESTDIR}${PREFIX}/bin/smtpd.py

.include "../../lang/python27/Makefile"

PLIST_SRC+=     ../../base/python27/PLIST.extra
