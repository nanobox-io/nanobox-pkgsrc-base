# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		mongodb-src-r${VERSION}
VERSION=		2.4.14
PKGNAME=		${DISTNAME:S/-src-r/-server-/}
CATEGORIES=		databases
MASTER_SITES=		http://fastdl.mongodb.org/src/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://fastdl.mongodb.org/src/
COMMENT=		TODO: Short description of the package
#LICENSE=		# TODO: (see mk/license.mk)

USE_TOOLS+=		pkg-config
USE_LANGUAGES=		c c++

NO_CONFIGURE=        	yes
USE_LANGUAGES=        	c c++

PKGCONFIG_OVERRIDE+=	src/third_party/pcre-8.30/libpcrecpp.pc.in
PKGCONFIG_OVERRIDE+=	src/third_party/pcre-8.30/libpcreposix.pc.in
PKGCONFIG_OVERRIDE+=	src/third_party/pcre-8.30/libpcre16.pc.in
PKGCONFIG_OVERRIDE+=	src/third_party/pcre-8.30/libpcre.pc.in

BUILD_DEPENDS+=        scons-[0-9]*:../../devel/scons

# MAKE_JOBS=        	2
SCONS_BIN=		${PREFIX}/bin/scons
# SCONS_ARGS=        	${_MAKE_JOBS}
SCONS_ARGS+=        	--use-system-tcmalloc=USE-SYSTEM-TCMALLOC
SCONS_ARGS+=        	--use-system-pcre=USE-SYSTEM-PCRE
SCONS_ARGS+=        	--use-system-boost=USE-SYSTEM-BOOST
SCONS_ARGS+=        	--use-system-snappy=USE-SYSTEM-SNAPPY

SCONS_ARGS+=        	--cc=${WRAPPER_BINDIR}/${CC}
SCONS_ARGS+=        	--cxx=${WRAPPER_BINDIR}/${CXX}

.if ${MACHINE_ARCH} == "x86_64"
SCONS_ARGS+=        	--64
.else
SCONS_ARGS+=        	--32
.endif

BUILD_DEFS+=            VARBASE
BUILD_DEFS+=            MONGODB_USER MONGODB_GROUP MONGODB_DBPATH
BUILD_DEFS+=            MONGODB_LOGPATH

MONGODB_USER?=          mongodb
MONGODB_GROUP?=         mongodb
MONGODB_DBPATH?=        ${VARBASE}/mongodb
MONGODB_LOGPATH?=       ${VARBASE}/log/mongodb

PKG_USERS_VARS+=        MONGODB_USER
PKG_GROUPS_VARS+=       MONGODB_GROUP

PKG_GROUPS=             ${MONGODB_GROUP}
PKG_USERS=              ${MONGODB_USER}:${MONGODB_GROUP}

PKG_GECOS.${MONGODB_USER}=	MongoDB database administrator
PKG_HOME.${MONGODB_USER}=       ${MONGODB_DBPATH}
PKG_SHELL.${MONGODB_USER}=      ${SH}

OWN_DIRS_PERMS+=	${MONGODB_DBPATH} ${MONGODB_USER} ${MONGODB_GROUP} 0755
OWN_DIRS_PERMS+=        ${MONGODB_DBPATH}/journal ${MONGODB_USER} ${MONGODB_GROUP} 0755
OWN_DIRS_PERMS+=        ${MONGODB_LOGPATH} ${MONGODB_USER} ${MONGODB_GROUP} 0755

# XXX No better idea how to pass CXXFLAGS and LDFLAGS to scons
SUBST_CLASSES+=		scons
SUBST_STAGE.scons=      pre-build
SUBST_FILES.scons=      SConstruct
SUBST_VARS.scons=       PREFIX CXXFLAGS LDFLAGS

SUBST_CLASSES+=        path
SUBST_STAGE.path=      pre-build
SUBST_FILES.path=      src/mongo/db/db.cpp src/mongo/db/flushtest.cpp
SUBST_FILES.path+=     src/mongo/db/pdfile.cpp debian/mongodb.conf
SUBST_SED.path=        -e "s|/data/db|${MONGODB_DBPATH}|g"
SUBST_VARS.path=       MONGODB_DBPATH MONGODB_LOGPATH

MONGODB_MAN_FILES=     bsondump.1 mongo.1 mongod.1 mongodump.1 mongoexport.1 \
                       	mongofiles.1 mongoimport.1 mongorestore.1 mongos.1    \
                        mongosniff.1 mongostat.1

RCD_SCRIPTS=           mongodb

INSTALLATION_DIRS=     share/doc/mongodb share/examples/mongodb ${PKGMANDIR}/man1

CONF_FILES+=           share/examples/mongodb/mongodb.conf \
                        ${PKG_SYSCONFDIR}/mongodb.conf

post-extract:
	chmod -R g-w ${WRKSRC}

do-build:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${SCONS_BIN} ${SCONS_ARGS} all

do-install:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${SCONS_BIN} \
		${SCONS_ARGS} --full --prefix ${DESTDIR}${PREFIX} install

do-test:
	cd ${WRKSRC} && ./test

post-install:
	${INSTALL_DATA} ${WRKSRC}/README ${DESTDIR}${PREFIX}/share/doc/mongodb
.	for file in ${MONGODB_MAN_FILES}
	${INSTALL_MAN} ${WRKSRC}/debian/${file} \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man1
.	endfor
	${INSTALL_DATA} ${WRKSRC}/debian/mongodb.conf \
		${DESTDIR}${PREFIX}/share/examples/mongodb

.include "../../devel/boost-headers/buildlink3.mk"
.include "../../devel/boost-libs/buildlink3.mk"
.include "../../devel/boost-python/buildlink3.mk"
.if exists(../../devel/libexecinfo/buildlink3.mk)
.include "../../devel/libexecinfo/buildlink3.mk"
.endif
.include "../../devel/pcre/buildlink3.mk"
.include "../../devel/snappy/buildlink3.mk"
.include "../../net/libpcap/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
