# $NetBSD: Makefile,v 1.17 2014/06/05 02:41:09 obache Exp $
#

DISTNAME=			libdwarf-20150507
# PKGREVISION=		1
CATEGORIES=			devel
MASTER_SITES=		http://www.prevanders.net/

MAINTAINER=			pkgsrc-users@NetBSD.org
HOMEPAGE=			http://www.prevanders.net/dwarf.html
COMMENT=			DWARF
LICENSE=			gnu-lgpl-v2

USE_LANGUAGES+=		c c++
GNU_CONFIGURE=		yes

CONFIGURE_ARGS+=	--enable-shared

WRKSRC=				${WRKDIR}/${DISTNAME:S/lib//}/libdwarf

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/lib/
	cp ${WRKSRC}/libdwarf.so ${DESTDIR}${PREFIX}/lib/libdwarf.so
	cp ${WRKSRC}/libdwarf.a ${DESTDIR}${PREFIX}/lib/libdwarf.a
	mkdir -p ${DESTDIR}${PREFIX}/include/
	cp ${WRKSRC}/libdwarf.h ${DESTDIR}${PREFIX}/include/libdwarf.h
	chmod 644 ${DESTDIR}${PREFIX}/include/libdwarf.h
	cp ${WRKSRC}/dwarf.h ${DESTDIR}${PREFIX}/include/dwarf.h
	chmod 644 ${DESTDIR}${PREFIX}/include/dwarf.h

.include "../../devel/libelf/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
