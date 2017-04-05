PKGDIR= ${.CURDIR}/../../lang/python34

post-install:
	ln -s 2to3-3.4 ${DESTDIR}${PREFIX}/bin/2to3
	ln -s pydoc3.4 ${DESTDIR}${PREFIX}/bin/pydoc3
	ln -s python3.4 ${DESTDIR}${PREFIX}/bin/python
	ln -s python3.4 ${DESTDIR}${PREFIX}/bin/python3

.include "../../lang/python34/Makefile"

PLIST_SRC+=	../../base/python34/PLIST.extra
