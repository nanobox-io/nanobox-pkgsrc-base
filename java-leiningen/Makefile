# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=		2.6.1
DISTNAME=		leiningen-${VERSION}
# PKGREVISION=		
CATEGORIES=		pagoda
MASTER_SITES=		https://github.com/technomancy/leiningen
PKGNAME=		${PKG_JVM:S/-//:S/.//}-leiningen-${VERSION}

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://github.com/technomancy/leiningen
COMMENT= 		Leiningen is for automating Clojure projects without setting your hair on fire.
LICENSE=		EPL

USE_JAVA=	run
USE_JAVA2=	6
NO_BUILD=	yes

GIT_REPOSITORIES=	leiningen
GIT_REPO.leiningen=	git@github.com:technomancy/leiningen.git
GIT_TAG=		${VERSION}

WRKSRC=			${WRKDIR}/leiningen


SUBST_CLASSES+=		leiningen
SUBST_FILES.leiningen=	bin/lein-pkg
SUBST_STAGE.leiningen=	pre-configure
# SUBST_SED.leiningen=	-e 's,/bin/bash,${PREFIX}/bin/bash,'
SUBST_SED.leiningen+=	-e 's,LEIN_JAR=.*,LEIN_JAR=${PREFIX}/lib/java/leiningen/leiningen.jar,'		

${DISTDIR}/leiningen-${VERSION}-standalone.zip:
	wget -O ${DISTDIR}/leiningen-${VERSION}-standalone.zip https://github.com/technomancy/leiningen/releases/download/${VERSION}/leiningen-${VERSION}-standalone.zip

do-install: ${DISTDIR}/leiningen-${VERSION}-standalone.zip
	${MKDIR} ${DESTDIR}${PREFIX}/bin
	${INSTALL_SCRIPT} ${WRKSRC}/bin/lein-pkg ${DESTDIR}${PREFIX}/bin/lein
	${MKDIR} ${DESTDIR}${PREFIX}/etc/bash_completion.d
	${INSTALL_DATA} ${WRKSRC}/bash_completion.bash ${DESTDIR}${PREFIX}/etc/bash_completion.d/_lein.bash
	${MKDIR} ${DESTDIR}${PREFIX}/share/zsh/site-functions
	${INSTALL_DATA} ${WRKSRC}/zsh_completion.zsh ${DESTDIR}${PREFIX}/share/zsh/site-functions/_lein
	${INSTALL_MAN} ${WRKSRC}/doc/lein.1 ${DESTDIR}${PKGMANDIR}/man/man1/
	${INSTALL_DATA} ${DISTDIR}/leiningen-${VERSION}-standalone.zip ${DESTDIR}${PREFIX}/lib/java/leiningen/leiningen.jar

.include "../../base/java/java-vm.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"