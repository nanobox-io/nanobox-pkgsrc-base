# $NetBSD: Makefile,v 1.2 2015/11/10 11:35:30 jperkin Exp $

# Note: This must be kept in sync with the oracle-jre9 package
# Note: make sure you include sums for both the x86_64 and the x86_32
# in distinfo (make makesum will eat one of them)

DISTNAME=	jdk-9.0.${UPDATE_NUMBER}_${DIST_OS}-${DIST_ARCH}_bin
PKGNAME=	oracle-jdk9-9.0.${UPDATE_NUMBER}
MASTER_SITES=	# empty

LICENSE=	oracle-binary-code-license

DOWNLOAD_NAME=	Java Development Kit (JDK) 9u${UPDATE_NUMBER}

DEPENDS+=	${PKGNAME_NOREV:S/jdk/jre/}*:../../base/oracle-jre9

WRKSRC=		${WRKDIR}/jdk-9.0.${UPDATE_NUMBER}
JAVA_WRAPPERS=	appletviewer apt extcheck idlj jar jarsigner \
		javac javadoc javah javap jdb rmic serialver jps

MAKE_JOBS_SAFE=	no

.include "../../base/oracle-jre9/Makefile.common"

.if !empty(MACHINE_PLATFORM:MLinux-*-x86_64)
CHECK_SHLIBS_SUPPORTED=	no
.endif

PLIST_SRC=	PLIST.${DIST_OS}-${EMUL_ARCH}
PLIST_SUBST+=	JAVA_ARCH="${JAVA_ARCH}"

# Simplify distinfo generation
.if make(distinfo)
#DISTFILES=	jdk-9u${UPDATE_NUMBER}-linux-i586.tar.gz
DISTFILES+=	jdk-9.0.${UPDATE_NUMBER}_linux-x64_bin.tar.gz
#DISTFILES+=	jdk-9u${UPDATE_NUMBER}-solaris-x64.tar.gz
FETCH_MESSAGE=	"You must fetch the following files to generate distinfo:"
FETCH_MESSAGE+=	""
.for file in ${DISTFILES}
FETCH_MESSAGE+=	"	${file}"
.endfor
FETCH_MESSAGE+=	""
FETCH_MESSAGE+=	"from:"
FETCH_MESSAGE+=	"	${DOWNLOAD}"
FETCH_MESSAGE+=	"	or ${ARCHIVE}"
.endif

# Remove parts that are in common with the JRE
#
post-extract:
	${MKDIR} ${WRKSRC}/lib/
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

.include "../../mk/bsd.pkg.mk"
