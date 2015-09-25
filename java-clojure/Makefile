# $NetBSD: Makefile,v 1.3 2013/06/11 19:51:27 asau Exp $

VERSION=	1.7.0
DISTNAME=	clojure-${VERSION}
CATEGORIES=	lang
MASTER_SITES=	http://repo1.maven.org/maven2/org/clojure/clojure/$(PKGVERSION_NOREV)/
EXTRACT_SUFX=	.zip
PKGNAME=	${PKG_JVM:S/-//:S/.//}-clojure-${VERSION}

MAINTAINER=	ryoon@NetBSD.org
HOMEPAGE=	http://clojure.org/
COMMENT=	Dynamic programming language that targets the Java VM
LICENSE=	epl-v1.0

NO_BUILD=	yes
USE_JAVA=	run
USE_JAVA2=	1.5
USE_LANGUAGES=	# none
USE_TOOLS+=	pax

INSTALLATION_DIRS=	bin \
			share/doc/clojure-${VERSION} \
			lib/java/clojure \
			share/examples/clojure-${VERSION}

CLOJURE_DOCS=	changes.md epl-v10.html readme.txt \
		doc/clojure/pprint/CommonLispFormat.markdown \
		doc/clojure/pprint/PrettyPrinting.markdown

SUBST_CLASSES+=		java
SUBST_STAGE.java=	pre-install
SUBST_MESSAGE.java=	Set Java
SUBST_FILES.java=	clj.sh
SUBST_SED.java=		-e 's,@JAVA_HOME@,${PKG_JAVA_HOME},g'
SUBST_SED.java+=	-e 's,@SH@,${SH},'

pre-patch:
	${INSTALL_DATA} ${FILESDIR}/clj.sh ${WRKSRC}

do-install:
	${INSTALL_DATA} ${WRKSRC}/clojure-${VERSION}.jar \
		${DESTDIR}${PREFIX}/lib/java/clojure/clojure.jar

	cd ${WRKSRC}/test/clojure && pax -rw -pmp test_clojure \
		${DESTDIR}${PREFIX}/share/examples/clojure-${VERSION}/
	${INSTALL_DATA} ${WRKSRC}/test/clojure/test_helper.clj \
		${DESTDIR}${PREFIX}/share/examples/clojure-${VERSION}

.for f in ${CLOJURE_DOCS}
	${INSTALL_DATA} ${WRKSRC}/${f} \
		${DESTDIR}${PREFIX}/share/doc/clojure-${VERSION}
.endfor

	${INSTALL_SCRIPT} ${WRKSRC}/clj.sh ${DESTDIR}${PREFIX}/bin/clj

.include "../../base/java/java-env.mk"
.include "../../base/java/java-vm.mk"
.include "../../mk/bsd.pkg.mk"
