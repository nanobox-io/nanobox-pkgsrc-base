# $NetBSD: Makefile,v 1.3 2013/06/11 19:51:27 asau Exp $

VERSION=	0.13.15
# PKGREVISION=	2
DISTNAME=	sbt-${VERSION}
CATEGORIES=	devel
MASTER_SITES=	https://dl.bintray.com/sbt/native-packages/sbt/${VERSION}/
EXTRACT_SUFX=	.tgz
PKGNAME=	${PKG_JVM:S/-//:S/.//}-sbt-${VERSION}

MAINTAINER=	braxton@pagodabox.com
HOMEPAGE=	http://www.scala-sbt.org/
COMMENT=	The interactive build tool
# LICENSE=	

NO_BUILD=	yes
USE_JAVA=	run
USE_JAVA2=	1.5
USE_LANGUAGES=	# none
USE_TOOLS+=	pax

INSTALLATION_DIRS=	bin \
			lib/java/sbt 

SUBST_CLASSES+=		java
SUBST_STAGE.java=	pre-install
SUBST_MESSAGE.java=	Set Java
SUBST_FILES.java=	sbt.sh
SUBST_SED.java=		-e 's,@JAVA_HOME@,${PKG_JAVA_HOME},g'
SUBST_SED.java+=	-e 's,@SH@,${SH},'

WRKSRC=${WRKDIR}/sbt

PHONY: build-all

pre-patch:
	${INSTALL_DATA} ${FILESDIR}/sbt.sh ${WRKSRC}

do-install:
	${INSTALL_DATA} ${WRKSRC}/bin/sbt-launch.jar \
		${DESTDIR}${PREFIX}/lib/java/sbt/sbt-launch.jar

	${INSTALL_SCRIPT} ${WRKSRC}/sbt.sh ${DESTDIR}${PREFIX}/bin/sbt

build-all:
	for i in sun-jdk6 sun-jdk7 sun-jdk8 openjdk7 openjdk8; do bmake clean PKG_JVM_DEFAULT=$${i}; bmake package PKG_JVM_DEFAULT=$${i}; done

.include "../../base/java/java-vm.mk"
.include "../../mk/bsd.pkg.mk"
