# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=	mongodb-src-r3.2.15
PKGNAME=	${DISTNAME:S/src-r/server-/:S/-rc/rc/}
CATEGORIES=	databases
MASTER_SITES=	http://downloads.mongodb.org/src/

MAINTAINER=	bartosz.kuzma@gmail.com
HOMEPAGE=	http://mongodb.org/
COMMENT=	NOSQL distributed document-oriented database
LICENSE=	gnu-agpl-v3 # Client and tools licensed under apache-2.0

NO_CONFIGURE=	yes
USE_LANGUAGES=	c c++
USE_CWRAPPERS=	no

DEPENDS+=	mongodb32-tools>=3.2.0:../../base/mongodb32-tools
BUILD_DEPENDS+=	scons-[0-9]*:../../devel/scons

BUILDLINK_TREE+=	valgrind

.if !defined(VALGRIND_BUILDLINK3_MK)
VALGRIND_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.valgrind+=	valgrind>=3.10.1
BUILDLINK_PKGSRCDIR.valgrind?=	../../devel/valgrind
.endif # VALGRIND_BUILDLINK3_MK

BUILDLINK_TREE+=	-valgrind

SCONS_BIN=	${PREFIX}/bin/scons
SCONS_ARGS=	${_MAKE_JOBS}
# SCONS_ARGS+=	--cc=${WRAPPER_BINDIR}/${CC:Q}
# SCONS_ARGS+=	--cxx=${WRAPPER_BINDIR}/${CXX:Q}
# CXX=${WRAPPER_BINDIR}/g++
# CC=${WRAPPER_BINDIR}/gcc
SCONS_ARGS+=	--use-system-boost
SCONS_ARGS+=	--use-system-pcre
SCONS_ARGS+=	--use-system-snappy
SCONS_ARGS+=	--use-system-tcmalloc
SCONS_ARGS+=	--use-system-yaml
SCONS_ARGS+=	--use-system-zlib
SCONS_ARGS+=	--release

.include "../../mk/bsd.fast.prefs.mk"

.if defined(MAKE_JOBS)
MAKE_JOBS=	8
.endif

CPPFLAGS+=	-fno-jump-tables

CXXFLAGS+=	-Wno-maybe-uninitialized
CXXFLAGS+=	-Wno-unused-variable
CXXFLAGS+=	-Wno-error=maybe-uninitialized
CFLAGS+=	-Wno-unused-variable
CFLAGS+=	-Wno-error=maybe-uninitialized

.include "options.mk"

SMF_METHODS+=		mongodb

BUILD_DEFS+=		VARBASE
BUILD_DEFS+=		MONGODB_USER MONGODB_GROUP MONGODB_DBPATH
BUILD_DEFS+=		MONGODB_LOGPATH

MONGODB_USER?=		mongodb
MONGODB_GROUP?=		mongodb
MONGODB_DBPATH?=	${VARBASE}/mongodb
MONGODB_LOGPATH?=	${VARBASE}/log/mongodb

#PKG_USERS_VARS+=	MONGODB_USER
#PKG_GROUPS_VARS+=	MONGODB_GROUP

#PKG_GROUPS=		${MONGODB_GROUP}
#PKG_USERS=		${MONGODB_USER}:${MONGODB_GROUP}

#PKG_GECOS.${MONGODB_USER}=	MongoDB database administrator
#PKG_HOME.${MONGODB_USER}=	${MONGODB_DBPATH}
#PKG_SHELL.${MONGODB_USER}=	${SH}

#OWN_DIRS_PERMS+=	${MONGODB_DBPATH} ${MONGODB_USER} ${MONGODB_GROUP} 0755
#OWN_DIRS_PERMS+=	${MONGODB_DBPATH}/journal ${MONGODB_USER} ${MONGODB_GROUP} 0755
#OWN_DIRS_PERMS+=	${MONGODB_LOGPATH} ${MONGODB_USER} ${MONGODB_GROUP} 0755

FILES_SUBST+=		MONGODB_USER=${MONGODB_USER}
FILES_SUBST+=		MONGODB_GROUP=${MONGODB_GROUP}
FILES_SUBST+=		MONGODB_DBPATH=${MONGODB_DBPATH}
FILES_SUBST+=		MONGODB_LOGPATH=${MONGODB_LOGPATH}

# XXX No better idea how to pass CXXFLAGS and LDFLAGS to scons
SUBST_CLASSES+=		scons
SUBST_STAGE.scons=	pre-build
SUBST_FILES.scons=	SConstruct
SUBST_VARS.scons=	PREFIX CXXFLAGS LDFLAGS

SUBST_CLASSES+=		path
SUBST_STAGE.path=	pre-build
SUBST_FILES.path=	src/mongo/db/flushtest.cpp debian/mongod.conf
SUBST_FILES.path+=	debian/mongod.1 debian/mongo.1 src/mongo/shell/dbshell.cpp
SUBST_SED.path=		-e 's|/data/db|${MONGODB_DBPATH}|g'
SUBST_SED.path+=	-e 's|/etc|${PKG_SYSCONFDIR}|'
SUBST_VARS.path=	MONGODB_DBPATH MONGODB_LOGPATH

MONGODB_MAN_FILES=	bsondump.1 mongo.1 mongod.1 mongodump.1 mongoexport.1	\
			mongofiles.1 mongoimport.1 mongooplog.1 mongoperf.1	\
			mongorestore.1 mongos.1 mongosniff.1 mongostat.1 mongotop.1

#RCD_SCRIPTS=		mongodb

INSTALLATION_DIRS=	share/doc/mongodb share/examples/mongodb ${PKGMANDIR}/man1

CONF_FILES+=		share/examples/mongodb/mongod.conf \
			${PKG_SYSCONFDIR}/mongod.conf

REAL_CXX=${WRAPPER_BINDIR}/${CXX:Q}
REAL_CC=${WRAPPER_BINDIR}/${CC:Q}

post-extract:
	chmod -R g-w ${WRKSRC}
	cp -r ${WRKSRC}/src/third_party/mozjs-38/platform/x86_64/freebsd \
		${WRKSRC}/src/third_party/mozjs-38/platform/x86_64/dragonfly
	cp -r ${WRKSRC}/src/third_party/mozjs-38/platform/x86_64/openbsd \
		${WRKSRC}/src/third_party/mozjs-38/platform/x86_64/netbsd

do-build:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV:S/${CC}/${REAL_CC}/:S/${CXX}/${REAL_CXX}/} ${SCONS_BIN} ${SCONS_ARGS} all CXX=${REAL_CXX} CC=${REAL_CC}

do-install:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV:S/${CC}/${REAL_CC}/:S/${CXX}/${REAL_CXX}/} ${SCONS_BIN} ${SCONS_ARGS} \
		--prefix=${DESTDIR}${PREFIX} install CXX=${REAL_CXX} CC=${REAL_CC}

do-test:
	cd ${WRKSRC} && ./test

post-install:
	${INSTALL_DATA} ${WRKSRC}/README ${DESTDIR}${PREFIX}/share/doc/mongodb
.for file in ${MONGODB_MAN_FILES}
	${INSTALL_MAN} ${WRKSRC}/debian/${file} \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man1
.endfor
	${INSTALL_DATA} ${WRKSRC}/debian/mongod.conf \
		${DESTDIR}${PREFIX}/share/examples/mongodb
	for i in ${DESTDIR}${PREFIX}/bin/*; do \
		strip $$i; \
	done

.include "../../devel/boost-headers/buildlink3.mk"
.include "../../devel/boost-libs/buildlink3.mk"
.include "../../devel/py-boost/buildlink3.mk"
.if exists(../../devel/libexecinfo/buildlink3.mk)
.include "../../devel/libexecinfo/buildlink3.mk"
.endif
.include "../../base/gperftools/buildlink3.mk"
.include "../../devel/pcre/buildlink3.mk"
.include "../../devel/snappy/buildlink3.mk"
.include "../../net/libpcap/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../textproc/yaml-cpp/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
