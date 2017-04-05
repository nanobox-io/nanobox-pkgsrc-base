PKGDIR= ${.CURDIR}/../../lang/python35

post-install:
	ln -s 2to3-3.5 ${DESTDIR}${PREFIX}/bin/2to3
	ln -s pydoc3.5 ${DESTDIR}${PREFIX}/bin/pydoc3
	ln -s python3.5 ${DESTDIR}${PREFIX}/bin/python
	ln -s python3.5 ${DESTDIR}${PREFIX}/bin/python3

.include "../../lang/python35/Makefile"

PLIST_SRC+=	../../base/python35/PLIST.extra
