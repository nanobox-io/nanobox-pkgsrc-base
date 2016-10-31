# $NetBSD: Makefile,v 1.5 2015/10/20 12:13:33 fhajny Exp $

DISTNAME=	snappy-java-${SNAPPYVER}
PKGNAME=	${DISTNAME:S/java/java10/}
PKGREVISION=	1
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=xerial/}

MAINTAINER=	ryoon@NetBSD.org
HOMEPAGE=	http://github.com/xerial/snappy-java/
COMMENT=	Snappy compressor/decompressor for Java
LICENSE=	apache-2.0

GITHUB_PROJECT=	snappy-java
SNAPPYVER=	1.0.5

DIST_SUBDIR=	${PKGBASE}
DISTFILES=	${DEFAULT_DISTFILES}
DISTFILES+=	snappy-java-${SNAPPYVER}-deps.tar.gz
DISTFILES+=	snappy-${SNAPPYVER}.tar.gz
SITES.snappy-${SNAPPYVER}.tar.gz=		https://snappy.googlecode.com/files/
SITES.snappy-java-${SNAPPYVER}-deps.tar.gz=	ftp://ftp.NetBSD.org/pub/NetBSD/misc/fhajny/
EXTRACT_DIR.snappy-${SNAPPYVER}.tar.gz=		${WRKSRC}/target

TOOL_DEPENDS+=	${PKG_JVM:S/-//:S/.//}-maven33:../../base/java-maven33

USE_LANGUAGES=	c++
USE_TOOLS+=	gmake
USE_JAVA=	yes
USE_JAVA2=	6

CXXFLAGS+=	-I${WRKSRC}/target/snappy-${SNAPPYVER}
CXXFLAGS+=	-fPIC

MAVEN_FLAGS+=	-Duser.home=${FAKEHOMEDIR}
MAVEN_FLAGS+=	-Dmaven.repo.local=${WRKDIR}/deps
#MAVEN_FLAGS+=	--offline

MAKE_FLAGS+=	JAVA_HOME=${PKG_JAVA_HOME}
MAKE_FLAGS+=	MVN="mvn ${MAVEN_FLAGS}"
MAKE_FLAGS+=	CXXFLAGS=${CXXFLAGS:Q}
MAKE_JOBS_SAFE=	no

INSTALLATION_DIRS+=	lib/java/snappy-java

post-extract:
	${TOUCH} ${WRKSRC}/target/snappy-extracted.log

do-install:
	${INSTALL_DATA} ${WRKSRC}/target/snappy-java-${SNAPPYVER}.jar \
		${DESTDIR}${PREFIX}/lib/java/snappy-java

.include "../../base/java/java-env.mk"
.include "../../base/java/java-vm.mk"
.include "../../mk/bsd.pkg.mk"
