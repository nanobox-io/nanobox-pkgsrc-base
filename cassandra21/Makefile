# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=		2.1.16
DISTNAME=		apache-cassandra-${VERSION}-bin
PKGNAME=		cassandra-${VERSION}
CATEGORIES=		pagoda
MASTER_SITES=		http://www.apache.org/dyn/closer.lua/cassandra/${VERSION}/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://cassandra.apache.org/
COMMENT=	Highly scalable, distributed structured key-value store
LICENSE=	apache-2.0

NO_BUILD=	yes
USE_LANGUAGES=	# none
USE_JAVA=	run
USE_JAVA2=	6
USE_TOOLS+=	bash:run pax

DEPENDS+=	snappy-java10>=1.0.5:../../base/snappy-java10

BINFILES=	cassandra cassandra-cli cassandra.in.sh cqlsh debug-cql		\
		nodetool sstablekeys sstableloader sstablescrub sstableupgrade	\
		stop-server
DOCFILES=	CHANGES LICENSE NEWS NOTICE
EGFILES=	cassandra-env.sh cassandra-rackdc.properties			\
		cassandra-topology.properties cassandra.yaml			\
		commitlog_archiving.properties cqlshrc.sample			\
		logback-tools.xml logback.xml cassandra-topology.yaml		\
		metrics-reporter-config-sample.yaml

.include "../../mk/bsd.prefs.mk"

CASSANDRA_HOME=		${PREFIX}/share/cassandra
EGDIR=			${PREFIX}/share/examples/cassandra
DOCDIR=			${PREFIX}/share/doc/cassandra

FILES_SUBST+=		JAVA_HOME=${PKG_JAVA_HOME}		\
			CASSANDRA_HOME=${CASSANDRA_HOME}	\
			CASSANDRA_USER=${CASSANDRA_USER}	\
			CASSANDRA_GROUP=${CASSANDRA_GROUP}

SUBST_CLASSES+=		path
SUBST_STAGE.path=	pre-install
SUBST_MESSAGE.path=	Fixing default paths
SUBST_FILES.path=	bin/cassandra.in.sh bin/cassandra
SUBST_VARS.path=	VARBASE

INSTALLATION_DIRS+=	${CASSANDRA_HOME} ${EGDIR} ${DOCDIR}
INSTALLATION_DIRS+=	${CASSANDRA_HOME} ${CASSANDRA_HOME}/bin ${EGDIR} ${DOCDIR}

CHECK_INTERPRETER_SKIP+=share/cassandra/interface/cassandra.thrift
CHECK_INTERPRETER_SKIP+=share/cassandra/pylib/setup.py
CHECK_INTERPRETER_SKIP+=share/cassandra/tools/bin/token-generator

post-extract:
	${RM} -f ${WRKSRC}/lib/snappy-java-*.jar

do-install:
.for d in ${WORK_DIRS}
		${RM} -rf ${WRKSRC}/${d}
.endfor
.for f in ${BINFILES}
		${INSTALL_SCRIPT} ${WRKSRC}/bin/${f} ${DESTDIR}${CASSANDRA_HOME}/bin/${f}
.endfor
.for f in ${DOCFILES}
		${INSTALL_DATA} ${WRKSRC}/${f}.txt ${DESTDIR}${DOCDIR}/${f}
		${RM} -f ${WRKSRC}/${f}.txt
.endfor
.for f in ${EGFILES}
		${INSTALL_DATA} ${WRKSRC}/conf/${f} ${DESTDIR}${EGDIR}/${f}
.endfor
	${FIND} ${WRKSRC} -name \*.exe -type f -print | ${XARGS} ${RM} -f
	${FIND} ${WRKSRC} -name \*.bat -type f -print | ${XARGS} ${RM} -f
	cd ${WRKSRC} && \
	  ${PAX} -rw -pm interface javadoc lib pylib tools \
	  ${DESTDIR}${CASSANDRA_HOME}
	${FIND} ${DESTDIR}${CASSANDRA_HOME} -type d -print |	\
		${XARGS} ${CHMOD} ${PKGDIRMODE}
	${FIND} ${DESTDIR}${CASSANDRA_HOME} -type f -print |	\
		${XARGS} ${CHMOD} ${SHAREMODE}
	${FIND} ${DESTDIR}${CASSANDRA_HOME}/bin -type f -print |	\
		${XARGS} ${CHMOD} ${BINMODE}
	${FIND} ${DESTDIR}${CASSANDRA_HOME} -type f -name \*.sh -print |	\
		${XARGS} ${CHMOD} ${BINMODE}

post-install:
	${LN} -sf ${PREFIX}/lib/java/snappy-java/snappy-java-1.0.5.jar \
		${DESTDIR}${PREFIX}/share/cassandra/lib/snappy-java.jar

.include "../../lang/python/application.mk"
.include "../../base/java/java-vm.mk"
.include "../../mk/bsd.pkg.mk"
