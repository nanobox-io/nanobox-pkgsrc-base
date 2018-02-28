# $NetBSD: Makefile,v 1.87 2013/12/04 21:02:23 richard Exp $

DISTFILES=	setup_agent.sh
VERSION=	5.21.0
PKGNAME=        datadog-agent-${VERSION}
DIST_SUBDIR=	datadog-${VERSION}
CATEGORIES=     sysutil
MASTER_SITES=   https://raw.githubusercontent.com/DataDog/dd-agent/master/packaging/datadog-agent/source/

MAINTAINER=     pkgsrc-users@NetBSD.org
HOMEPAGE=       www.datadoghq.com
COMMENT=        The Datadog Agent faithfully collects events and metrics
LICENSE=        bsd

USE_TOOLS+=	gsed

EXTRACT_OPTS=	-f none

NO_BUILD=	yes

do-install:
	mkdir -p ${DESTDIR}${PREFIX}/datadog
	cd ${WRKDIR}; DD_HOME=${DESTDIR}${PREFIX}/datadog DD_START_AGENT=0 /bin/sh setup_agent.sh


DEPENDS+=	sysstat>=11.7.0:../../base/sysstat

.include "../../lang/python27/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
