# $NetBSD: Makefile,v 1.97 2015/03/02 03:53:26 tnn Exp $

JDK_MICRO=      112
DISTNAME=       openjdk8-1.8.${JDK_MICRO}
PKGNAME=        openjdk8-1.8.${JDK_MICRO}
CATEGORIES=     lang

MAINTAINER=     pkgsrc-users@NetBSD.org
HOMEPAGE=       http://openjdk.java.net/
COMMENT=        Open-source implementation of the Java Platform, Standard Edition
LICENSE=        gnu-gpl-v2

JAVA_NAME=      openjdk8
JAVA_HOME=      ${PREFIX}/java/${JAVA_NAME}
JAVA_WRAPPERS=  jar java javac javadoc javah javap keytool orbd \
                policytool rmid rmiregistry servertool tnameserv

NO_CONFIGURE=           yes
BUILD_DIRS=		#empty

USE_TOOLS+=     pax

WRKSRC=		${WRKDIR}/openjdk8

do-install:
	${INSTALL_DATA_DIR} ${DESTDIR}${JAVA_HOME}
	cd ${WRKSRC} && pax -rwp ma . ${DESTDIR}${JAVA_HOME}	

.include "../../audio/alsa-lib/buildlink3.mk"
.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../fonts/fontconfig/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libXi/buildlink3.mk"
.include "../../x11/libXtst/buildlink3.mk"
.include "../../base/java/java-env.mk"
.include "../../mk/bsd.pkg.mk"
