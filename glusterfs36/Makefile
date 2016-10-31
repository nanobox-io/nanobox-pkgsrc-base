# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=		3.6.9
DISTNAME=		glusterfs-${VERSION}
CATEGORIES=		pagoda
MASTER_SITES=	http://download.gluster.org/pub/gluster/glusterfs/3.6/${VERSION}/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.gluster.org/
COMMENT=	Cluster filesystem
LICENSE=	gnu-gpl-v3

GNU_CONFIGURE=	yes

USE_LIBTOOL=		yes
USE_TOOLS+=		flex bison pkg-config bash

INSTALL_UNSTRIPPED=	yes

REPLACE_PYTHON+=	geo-replication/syncdaemon/changelogagent.py
REPLACE_PYTHON+=	geo-replication/syncdaemon/gsyncd.py
REPLACE_PYTHON+=	contrib/ipaddr-py/ipaddr.py

REPLACE_BASH+=		extras/geo-rep/generate-gfid-file.sh
REPLACE_BASH+=		extras/geo-rep/get-gfid.sh
REPLACE_BASH+=		extras/post-upgrade-script-for-quota.sh
REPLACE_BASH+=		extras/pre-upgrade-script-for-quota.sh
REPLACE_BASH+=		extras/geo-rep/slave-upgrade.sh
REPLACE_BASH+=		extras/geo-rep/gsync-upgrade.sh
REPLACE_BASH+=		geo-replication/src/gverify.sh
REPLACE_BASH+=		geo-replication/src/peer_add_secret_pub.in
REPLACE_BASH+=		geo-replication/src/peer_gsec_create.in
REPLACE_BASH+=		geo-replication/src/set_geo_rep_pem_keys.sh

PLIST_SUBST+=		PYSITELIB=${PYSITELIB:Q}

post-install:
	${INSTALL_SCRIPT} ${DESTDIR}/sbin/mount.glusterfs \
	    ${DESTDIR}/${PREFIX}/sbin/mount.glusterfs

.include "../../security/openssl/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
#.include "../../databases/sqlite3/buildlink3.mk"
#.include "../../devel/userspace-rcu/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../lang/python/extension.mk"

.include "../../mk/bsd.pkg.mk"
