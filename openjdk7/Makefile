# $NetBSD: Makefile,v 1.97 2015/03/02 03:53:26 tnn Exp $

JDK_MICRO=	80
DISTNAME=	openjdk-1.7.${JDK_MICRO}-20150609
PKGNAME=	openjdk7-1.7.${JDK_MICRO}
PKGREVISION=	2
CATEGORIES=	lang
MASTER_SITES=	${MASTER_SITE_LOCAL:=openjdk7/}
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://openjdk.java.net/
COMMENT=	Open-source implementation of the Java Platform, Standard Edition
LICENSE=	gnu-gpl-v2

DISTFILES=	${DEFAULT_DISTFILES}
EXTRACT_ONLY=	${DISTNAME}${EXTRACT_SUFX}

DIST_SUBDIR=	openjdk7

JAVA_NAME=	openjdk7
JAVA_HOME=	${PREFIX}/java/${JAVA_NAME}
JAVA_WRAPPERS=	jar java javac javadoc javah javap keytool orbd \
		policytool rmid rmiregistry servertool tnameserv


MAKE_ENV+=		PKGSRC_ZIPEXE=${TOOLS_PATH.zip}
MAKE_ENV+=		PKGSRC_UNZIP=${TOOLS_PATH.unzip}
MAKE_ENV+=		PKGSRC_UNZIPSFX=${TOOLS_PATH.unzip}sfx

BUILD_DEPENDS+=		mozilla-rootcerts>=1.0.20140820nb2:../../security/mozilla-rootcerts

NO_CONFIGURE=		yes
USE_LANGUAGES=		c c++
USE_TOOLS+=		gmake pax unzip:run zip:run gawk# patch
UNLIMIT_RESOURCES=	datasize stacksize
WRKSRC=			${WRKDIR}/openjdk
PLIST_SRC+=		${PLIST_SRC_DFLT}

BUILDLINK_PASSTHRU_DIRS+=	${ALT_BOOTDIR}
PREPEND_PATH+=			${ALT_BOOTDIR}/bin

MAKE_ENV+=	ALT_BOOTDIR=${ALT_BOOTDIR}
MAKE_ENV+=	ALT_DROPS_DIR=${DISTDIR}/${DIST_SUBDIR}
MAKE_ENV+=	ALT_FREETYPE_LIB_PATH=${BUILDLINK_PREFIX.freetype2}/lib
MAKE_ENV+=	ALT_FREETYPE_HEADERS_PATH=${BUILDLINK_PREFIX.freetype2}/include
MAKE_ENV+=	ALT_CUPS_HEADERS_PATH=${BUILDLINK_PREFIX.cups}/include
MAKE_ENV+=	ALT_COMPILER_PATH=${WRAPPER_DIR}/bin
MAKE_ENV+=	ALT_PACKAGE_PATH=${PREFIX}
MAKE_ENV+=	RHINO_JAR=${WRKDIR}/${RHINO}/js.jar
MAKE_ENV+=	ALSA_HEADERS_PATH=${PREFIX}/include
MAKE_ENV+=	ALSA_LIB_PATH=${PREFIX}/lib
MAKE_ENV+=	OPENWIN_HOME=${PREFIX}

MAKE_ENV+=	ALT_PARALLEL_COMPILE_JOBS=${MAKE_JOBS:U1}
MAKE_ENV+=	HOTSPOT_BUILD_JOBS=${MAKE_JOBS}

MAKE_ENV+=	HOTSPOT_BUILD_USER=pkgsrc
MAKE_ENV+=	NO_DOCS=true
MAKE_ENV+=	SKIP_COMPARE_IMAGES=true

# Avoid build errors when JAVA_HOME and CLASSPATH are defined by user.
MAKE_ENV+=	JAVA_HOME=
MAKE_ENV+=	CLASSPATH=

BUILD_OPSYS=	${OPSYS:C/.*BSD/bsd/:S/DragonFly/bsd/:S/SunOS/solaris/:S/Linux/linux/}
BUILD_ARCH=	${MACHINE_ARCH:S/i386/i586/:S/x86_64/amd64/:S/sparc64/sparcv9/:C/^e?arm.*$/arm/}
LIBDIR_ARCH=	${MACHINE_ARCH:S/x86_64/amd64/:S/sparc64/sparcv9/:C/^e?arm.*$/arm/}
BUILDDIR=	${WRKSRC}/build/${BUILD_OPSYS}-${BUILD_ARCH}
LD_LIBRARY_PATH=	${WRKDIR}/bootstrap/jre/lib/${LIBDIR_ARCH}:${WRKDIR}/bootstrap/jre/lib/${LIBDIR_ARCH}/jli:${WRKDIR}/bootstrap/jre/lib/${LIBDIR_ARCH}/server
MAKE_ENV+=	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}
BUILDLINK_PASSTHRU_RPATHDIRS+=	${PREFIX}/java/openjdk7/jre/lib/${LIBDIR_ARCH}
BUILDLINK_PASSTHRU_RPATHDIRS+=	${PREFIX}/java/openjdk7/jre/lib/${LIBDIR_ARCH}/jli

JAVA_LD_LIBRARY_PATH= ${JAVA_HOME}/lib/${BUILD_ARCH}/jli

PLIST_SUBST+=	ARCH=${LIBDIR_ARCH}
PLIST_SUBST+=	LOWER_OPSYS=${LOWER_OPSYS}

.include "../../mk/compiler.mk"

.if ${OPSYS} == "SunOS" && !empty(PKGSRC_COMPILER:Mgcc)
MAKE_ENV+=	USE_GCC=1
MAKE_ENV+=	ARCH_DATA_MODEL=${ABI:Q}
.endif

SUBST_CLASSES+=		libpath
SUBST_STAGE.libpath=	pre-build
SUBST_FILES.libpath+=	hotspot/src/os/bsd/vm/os_bsd.cpp
SUBST_VARS.libpath=	PREFIX

# SmartOS has ccs tools in /usr/bin
.if ${OS_VARIANT} == "SmartOS"
SUBST_CLASSES+=		ccspath
SUBST_STAGE.ccspath=	pre-build
SUBST_FILES.ccspath=	jdk/make/common/shared/Defs-utils.gmk
SUBST_FILES.ccspath+=	hotspot/make/solaris/makefiles/build_vm_def.sh
SUBST_SED.ccspath=	-e 's/UNIXCCS_PATH/UNIXCOMMAND_PATH/g'
SUBST_SED.ccspath+=	-e 's,/usr/ccs/bin,/usr/bin,g'
.endif

.if ${OPSYS} == "SunOS"
SUBST_CLASSES+=		mapfix
SUBST_STAGE.mapfix=	pre-build
SUBST_FILES.mapfix=	jdk/make/com/sun/java/pack/mapfile-vers
SUBST_FILES.mapfix+=	jdk/make/java/main/java/mapfile-amd64
SUBST_FILES.mapfix+=	jdk/make/java/main/java/mapfile-i586
SUBST_SED.mapfix=	-e '/__fsr_init_value/d'
SUBST_SED.mapfix+=	-e '/__progname/d'

# environ should only be removed from this file (added by patches)
SUBST_CLASSES+=		mapfix2
SUBST_STAGE.mapfix2=	pre-build
SUBST_FILES.mapfix2=	jdk/make/com/sun/java/pack/mapfile-vers
SUBST_SED.mapfix2=	-e '/environ/d'
.endif

CFLAGS+=	-D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
CFLAGS+=	-Wl,-R${JAVA_LD_LIBRARY_PATH}
CXXFLAGS+=	-D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
CXXFLAGS+=	-Wl,-R${JAVA_LD_LIBRARY_PATH}

.if !empty(PKGSRC_COMPILER:Mclang)
_WRAP_EXTRA_ARGS.CXX+=	-Wno-parentheses -Wno-sign-conversion \
			-Wno-shorten-64-to-32 -Wno-conversion \
			-Wno-unused-value -Wno-switch-enum -Wno-switch \
			-Wno-tautological-compare \
			-Wno-delete-non-virtual-dtor \
			-Wno-return-type -Wno-unused-parameter \
			-Wno-parentheses-equality -Wno-empty-body
CWRAPPERS_APPEND.cxx+=	-Wno-parentheses -Wno-sign-conversion \
			-Wno-shorten-64-to-32 -Wno-conversion \
			-Wno-unused-value -Wno-switch-enum -Wno-switch \
			-Wno-tautological-compare \
			-Wno-delete-non-virtual-dtor \
			-Wno-return-type -Wno-unused-parameter \
			-Wno-parentheses-equality -Wno-empty-body
.if ${OPSYS} != "FreeBSD"
_WRAP_EXTRA_ARGS.CXX+=	-Wno-new-returns-null
CWRAPPERS_APPEND.cxx+=	-Wno-new-returns-null
.endif
BUILDLINK_TRANSFORM+=	rm:-fcheck-new
BUILDLINK_TRANSFORM+=	rm:-fpch-deps
.  if ${MACHINE_ARCH} == "x86_64"
_WRAP_EXTRA_ARGS.CXX+=	-mstackrealign
CWRAPPERS_APPEND.cxx+=	-mstackrealign
.  endif
.endif
.include "bootstrap.mk"
.include "icedtea-extras.mk"

.include "options.mk"

SUBST_CLASSES+=			add-rpaths
SUBST_STAGE.add-rpaths=		pre-build
SUBST_MESSAGE.add-rpaths=	adding X11 run path flags to Makefiles
SUBST_FILES.add-rpaths=		jdk/make/sun/awt/Makefile		\
				jdk/make/sun/awt/mawt.gmk		\
				jdk/make/sun/jawt/Makefile		\
				jdk/make/sun/jdga/Makefile		\
				jdk/make/sun/splashscreen/Makefile	\
				jdk/make/sun/xawt/Makefile
SUBST_SED.add-rpaths=		-e 's|-L$$(OPENWIN_LIB)|-L$$(OPENWIN_LIB) -Wl,-R$$(OPENWIN_LIB)|g'

SUBST_CLASSES+=			fontpaths
SUBST_STAGE.fontpaths=		pre-build
SUBST_MESSAGE.fontpaths=	fixing font paths
SUBST_FILES.fontpaths=		jdk/src/solaris/classes/sun/awt/fontconfigs/bsd.fontconfig.properties
SUBST_FILES.fontpaths+=		jdk/src/solaris/native/sun/awt/fontpath.c
SUBST_SED.fontpaths=		-e 's|@PREFIX@|${PREFIX}|g'
SUBST_SED.fontpaths+=		-e 's|@BUILDLINK_PREFIX.fontconfig@|${BUILDLINK_PREFIX.fontconfig}|g'

SUBST_CLASSES+=				alsapaths
SUBST_STAGE.alsapaths+=		post-patch
SUBST_MESSAGE.alsapaths+=	fixing alsa paths
SUBST_FILES.alsapaths+=		jdk/make/common/shared/Sanity.gmk
# SUBST_FILES.alsapaths+=		jdk/make/javax/sound/jsoundalsa/Makefile
SUBST_SED.alsapaths+=		-e 's|@PREFIX@|${PREFIX}|g'

SUBST_CLASSES+=				awtpaths
SUBST_STAGE.awtpaths+=		post-patch
SUBST_MESSAGE.awtpaths+=	fixing awt paths
SUBST_FILES.awtpaths+=		jdk/make/sun/awt/mawt.gmk
SUBST_SED.awtpaths+=		-e 's|@PREFIX@|${PREFIX}|g'

SUBST_CLASSES+=				gawkpaths
SUBST_STAGE.gawkpaths+=		post-patch
SUBST_MESSAGE.gawkpaths+=	fixing gawk paths
SUBST_FILES.gawkpaths+=		corba/make/common/shared/Defs-utils.gmk
SUBST_FILES.gawkpaths+=		jdk/make/common/shared/Defs-utils.gmk
SUBST_FILES.gawkpaths+=		make/scripts/vsvars.sh
SUBST_SED.gawkpaths+=		-e 's|@PREFIX@|${PREFIX}|g'

PLIST_VARS+=	i386
.if ${MACHINE_ARCH} == "i386"
PLIST.i386=	yes
.endif

PLIST_VARS+=	sctp alsa
.if ${OPSYS} == "FreeBSD"
PLIST.sctp=	yes
PLIST.alsa=	yes
.include "../../audio/alsa-lib/buildlink3.mk"
.endif

post-extract:
	chmod +x ${ANT_BIN}/ant
	${LN} -s mapfile-i586 ${WRKSRC}/jdk/make/java/main/java/mapfile-arm
# These libs are bundled w/ the netbsd-7 bootstrap to facilitate building with
# MKLLVM=yes / MKGCC=no. Nuke them from bootstrap if they are present in base.
.if exists(/lib/libgcc_s.so.1)
	${RM} -f ${ALT_BOOTDIR}/jre/lib/${LIBDIR_ARCH}/libgcc_s.so*
.endif
.if exists(/usr/lib/libstdc++.so.7)
	${RM} -f ${ALT_BOOTDIR}/jre/lib/${LIBDIR_ARCH}/libstdc++.so*
.endif

do-build: ${WRKDIR}/stage3-done

# stage 1 builds a native JDK using the bootstrap binaries
${WRKDIR}/stage1-done:
	${_ULIMIT_CMD} cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE_PROGRAM} ${JDK_MAKE_TARGET}
	rm -rf ${ALT_BOOTDIR}
	cd ${BUILDDIR} && mv j2sdk-image ${ALT_BOOTDIR}
	mv ${BUILDDIR} ${BUILDDIR}-stage1
	touch ${.TARGET}

# stage 2 rebuilds the JDK using native tools
${WRKDIR}/stage2-done: ${WRKDIR}/stage1-done
	${_ULIMIT_CMD} cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE_PROGRAM} ${JDK_MAKE_TARGET}
	touch ${BUILDDIR}/j2sdk-image/jre/lib/applet/.keep
	touch ${.TARGET}

# stage 3 builds third party add-ons
${WRKDIR}/stage3-done: ${WRKDIR}/stage2-done ${WRKDIR}/cacerts.out
	touch ${.TARGET}

${WRKDIR}/cacerts.out:
	mkdir ${WRKDIR}/cacerts && cd ${WRKDIR}/cacerts && 		\
		${PREFIX}/sbin/mozilla-rootcerts extract
	for cert in ${WRKDIR}/cacerts/*.pem; do				\
		${INFO_MSG} "Importing $$cert" &&			\
		 ${SETENV} LD_LIBRARY_PATH=${LD_LIBRARY_PATH} LC_ALL=C	\
		  ${BUILDDIR}/bin/keytool				\
		  -noprompt						\
		  -importcert						\
		  -keystore ${.TARGET}					\
		  -alias `${ECHO} $$cert | sed 's,.*/\\([^/]*\\)\\.pem,\\1,'` \
		  -file $$cert						\
		  -storepass changeit;					\
	done

do-install:
	${INSTALL_DATA_DIR} ${DESTDIR}${JAVA_HOME}
	cd ${BUILDDIR}/j2sdk-image && pax -rwpp .			\
	  ${DESTDIR}${JAVA_HOME}/.
	${INSTALL_DATA} ${WRKDIR}/cacerts.out				\
	  ${DESTDIR}${JAVA_HOME}/jre/lib/security/cacerts
	rm -f ${DESTDIR}${JAVA_HOME}/include/jni_md.h
	ln -s ${LOWER_OPSYS}/jni_md.h					\
	  ${DESTDIR}${JAVA_HOME}/include/jni_md.h

.if ${OPSYS} == "NetBSD"
TOOLS_PLATFORM.unzip=
.endif

# Include binutils for objcopy and GNU strip on SmartOS
.if ${OS_VARIANT} == "SmartOS"
.include "../../devel/binutils/buildlink3.mk"
BUILDLINK_DEPMETHOD.binutils?=	build
MAKE_ENV+=	ALT_OBJCOPY=${PREFIX}/bin/gobjcopy
MAKE_ENV+=	STRIP=${PREFIX}/bin/gstrip
.endif

BUILDLINK_DEPMETHOD.gawk?=	build
BUILDLINK_TREE+=	gawk

.if !defined(GAWK_BUILDLINK3_MK)
GAWK_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.gawk+=	gawk>=4.1
BUILDLINK_PKGSRCDIR.gawk?=		../../lang/gawk

.endif	# GAWK_BUILDLINK3_MK

BUILDLINK_TREE+=	-gawk


.include "../../converters/libiconv/buildlink3.mk"
.include "../../fonts/fontconfig/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
BUILDLINK_DEPMETHOD.cups?=	build
.include "../../print/cups/buildlink3.mk"
.include "../../audio/alsa-lib/buildlink3.mk"
.include "../../base/java/java-env.mk"
.include "../../mk/bsd.pkg.mk"
