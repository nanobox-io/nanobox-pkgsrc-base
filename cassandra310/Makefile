# $NetBSD: Makefile.common,v 1.1 2015/10/21 12:53:27 fhajny Exp $
# used by databases/apache-cassandra/Makefile
# used by databases/apache-cassandra2/Makefile
#

# $NetBSD: Makefile,v 1.2 2017/01/09 22:13:19 fhajny Exp $
#

DISTNAME=	apache-cassandra-${CASSANDRA_VER}
CASSANDRA_VER=	3.10
PKGNAME=        cassandra-${CASSANDRA_VER}
CATEGORIES=	databases
DISTFILES=	${DISTNAME}-bin${EXTRACT_SUFX}
MASTER_SITES=	${MASTER_SITE_APACHE:=cassandra/${CASSANDRA_VER:C/-.*//}/}

MAINTAINER=	tonnerre@NetBSD.org
HOMEPAGE=	http://cassandra.apache.org/
COMMENT=	Highly scalable, distributed structured key-value store

LICENSE=	apache-2.0
NO_BUILD=	yes
USE_LANGUAGES=	# none
USE_JAVA=	run
USE_JAVA2=	8
USE_TOOLS+=	bash:run pax

.include "../../mk/bsd.prefs.mk"

CASSANDRA_HOME=		${PREFIX}/share/cassandra
EGDIR=			${PREFIX}/share/examples/cassandra
DOCDIR=			${PREFIX}/share/doc/cassandra

BINFILES=	cassandra cassandra.in.sh cqlsh debug-cql \
		nodetool sstableloader sstablescrub sstableupgrade sstableutil sstableverify \
		stop-server
DOCFILES=	CHANGES LICENSE NEWS NOTICE
EGFILES=	cassandra-env.sh cassandra-rackdc.properties cassandra-jaas.config		\
		cassandra-topology.properties cassandra.yaml			\
		commitlog_archiving.properties cqlshrc.sample hotspot_compiler jvm.options			\
		logback-tools.xml logback.xml		\
		metrics-reporter-config-sample.yaml

SUBST_CLASSES+=		path
SUBST_STAGE.path=	pre-install
SUBST_MESSAGE.path=	Fixing default paths
SUBST_FILES.path=	bin/cassandra.in.sh bin/cassandra
SUBST_VARS.path=	VARBASE

REPLACE_BASH+=		bin/cassandra

INSTALLATION_DIRS+=	${CASSANDRA_HOME} ${EGDIR} ${DOCDIR}
INSTALLATION_DIRS+=	${CASSANDRA_HOME} ${CASSANDRA_HOME}/bin ${EGDIR} ${DOCDIR}

CHECK_INTERPRETER_SKIP+=share/cassandra/interface/cassandra.thrift
CHECK_INTERPRETER_SKIP+=share/cassandra/pylib/setup.py
CHECK_INTERPRETER_SKIP+=share/cassandra/tools/bin/token-generator

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

.include "../../lang/python/application.mk"
.include "../../base/java/java-vm.mk"
.include "../../mk/bsd.pkg.mk"
