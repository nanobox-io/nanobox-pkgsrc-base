# $NetBSD: Makefile,v 1.15 2014/03/02 09:53:41 obache Exp $

# Note: This must be kept in sync with the sun-jre8 package
# Note: make sure you include sums for both the x86_64 and the x86_32
# in distinfo (make makesum will eat one of them)

DISTNAME=	jdk-8u${UPDATE_NUMBER}-${DIST_OS}-${DIST_ARCH}
PKGNAME=	sun-jdk8-8.0.${UPDATE_NUMBER}
MASTER_SITES=	# empty
PKGREVISION=	1

LICENSE=	oracle-binary-code-license

DOWNLOAD_NAME=	Java Development Kit (JDK) 8u${UPDATE_NUMBER}

DEPENDS+=	${PKGNAME_NOREV:S/jdk/jre/}*:../../base/sun-jre8

WRKSRC=		${WRKDIR}/jdk1.8.0_${UPDATE_NUMBER}
JAVA_WRAPPERS=	appletviewer apt extcheck idlj jar jarsigner \
		javac javadoc javah javap jdb rmic serialver

MAKE_JOBS_SAFE=	no

.include "../../base/sun-jre8/Makefile.common"

.if !empty(MACHINE_PLATFORM:MLinux-*-x86_64)
CHECK_SHLIBS_SUPPORTED=	no
.endif

# The 64-bit Solaris downloads for some inexplicable reason only contain
# the additional 64-bit files, and you need the main 32-bit file too.
.if ${EMUL_OPSYS} == "solaris" && ${EMUL_ARCH} == "x86_64"
DISTFILES=	${DEFAULT_DISTFILES} ${DEFAULT_DISTFILES:S/x64/i586/}
.endif

PLIST_SRC=	PLIST.${DIST_OS}-${EMUL_ARCH}
PLIST_SUBST+=	JAVA_ARCH="${JAVA_ARCH}"

# Remove parts that are in common with the JRE
#
post-extract:
	${MKDIR} ${WRKSRC}/lib/${JAVA_ARCH}
	${MV} ${WRKSRC}/jre/lib/${JAVA_ARCH}/libattach.so ${WRKSRC}/lib/${JAVA_ARCH}
	${MV} ${WRKSRC}/jre/lib/${JAVA_ARCH}/libsaproc.so ${WRKSRC}/lib/${JAVA_ARCH}
	common=`${AWK} '/^#.*/ { next } /^$$/ { next } { print }' ${FILESDIR}/common`; \
	cd ${WRKSRC}; for i in $$common; do				\
		if [ -d $$i ]; then					\
			${RM} -rf $$i;					\
		else							\
			${RM} -f $$i;					\
		fi;							\
	done
	${LN} -sf . ${WRKSRC}/jre

pre-install:
	# These files are generated the *first* time the package is built
	${RM} -f ${WRKSRC}/register.html
	${RM} -f ${WRKSRC}/register_ja.html
	${RM} -f ${WRKSRC}/register_zh_CN.html
	${CHMOD} -x \
		${WRKSRC}/db/bin/NetworkServerControl.bat \
		${WRKSRC}/db/bin/dblook.bat \
		${WRKSRC}/db/bin/derby_common.bat \
		${WRKSRC}/db/bin/ij.bat \
		${WRKSRC}/db/bin/setEmbeddedCP.bat \
		${WRKSRC}/db/bin/setNetworkClientCP.bat \
		${WRKSRC}/db/bin/setNetworkServerCP.bat \
		${WRKSRC}/db/bin/startNetworkServer.bat \
		${WRKSRC}/db/bin/stopNetworkServer.bat \
		${WRKSRC}/db/bin/sysinfo.bat

post-install:
	${RM} -f ${DESTDIR}${JAVA_HOME}/bin/jjs
	${RM} -f ${DESTDIR}${JAVA_HOME}/lib/${JAVA_ARCH}/libjawt.so
	${RM} -f ${DESTDIR}${JAVA_HOME}/man/ja_JP.UTF-8/man1/jjs.1
	${RM} -f ${DESTDIR}${JAVA_HOME}/man/man1/jjs.1

.include "../../mk/bsd.pkg.mk"
