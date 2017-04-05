PKGDIR= ${.CURDIR}/../../lang/python36

post-install:
	ln -s 2to3-3.6 ${DESTDIR}${PREFIX}/bin/2to3
	ln -s pydoc3.6 ${DESTDIR}${PREFIX}/bin/pydoc3
	ln -s python3.6 ${DESTDIR}${PREFIX}/bin/python
	ln -s python3.6 ${DESTDIR}${PREFIX}/bin/python3

.include "../../lang/python36/Makefile"

PLIST_SRC+=	../../base/python36/PLIST.extra
