# $NetBSD$
#

VERSION=	1.7.23
# PKGREVISION=	1
DISTNAME=	jruby-bin-${VERSION}
PKGNAME=	${DISTNAME:S/-bin//}
CATEGORIES=	lang
MASTER_SITES=	http://jruby.org.s3.amazonaws.com/downloads/${VERSION}/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://jruby.org/
COMMENT=	Implementation of the Ruby programming language atop the JVM
LICENSE=	cpl-1.0 OR gnu-gpl-v2 OR gnu-lgpl-v2.1

WRKSRC=	${WRKDIR}/${PKGNAME_NOREV}

NO_BUILD=	yes
USE_JAVA=	run
USE_JAVA2=	1.5
USE_LANGUAGES=	# none
USE_TOOLS+=	pax bash:run

INSTALLATION_DIRS=	bin

JRUBYDOMMANDS1=	ast gem irb jgem jirb jirb_swing jruby jruby.sh jrubyc \
		rake rdoc ri testrb
JRUBYDOMMANDS2=	jgem jirb jirb_swing jruby jruby.sh jrubyc

SUBST_CLASSES+=		jruby
SUBST_STAGE.jruby=	post-patch
SUBST_MESSAGE.jruby=	Set jruby
SUBST_FILES.jruby=	bin/*
SUBST_SED.jruby=	-e 's,/usr/bin/env jruby,${PREFIX}/bin/jruby,'
SUBST_SED.jruby+=	-e 's,@JRUBY_HOME@,${PREFIX}/share/${PKGNAME_NOREV},'

REPLACE_BASH+=	bin/*

do-install:
.for f in ${JRUBYDOMMANDS1}
	${INSTALL_SCRIPT} ${WRKSRC}/bin/${f} \
		${DESTDIR}${PREFIX}/bin/${f}
.endfor
.for f in ${JRUBYDOMMANDS2}
	${INSTALL_SCRIPT} ${WRKSRC}/bin/${f} \
		${DESTDIR}${PREFIX}/bin/
.endfor

	ln -s jruby ${DESTDIR}${PREFIX}/bin/ruby

	cd ${WRKSRC}/docs && pax -rw -pmp * \
		${DESTDIR}${PREFIX}/share/doc/${PKGNAME_NOREV}

	cd ${WRKSRC} && pax -rw -pmp lib \
		${DESTDIR}${PREFIX}/share/${PKGNAME_NOREV}

	cd ${WRKSRC}/samples && pax -rw -pmp * \
		${DESTDIR}${PREFIX}/share/examples/${PKGNAME_NOREV}

	cd ${WRKSRC} && pax -rw -pmp tool \
		${DESTDIR}${PREFIX}/share/${PKGNAME_NOREV}

.include "../../mk/bsd.pkg.mk"
