# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

VERSION=		3.7.20
DISTNAME=		glusterfs-${VERSION}
CATEGORIES=		pagoda
MASTER_SITES=	http://download.gluster.org/pub/gluster/glusterfs/3.7/${VERSION}/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.gluster.org/
COMMENT=	Cluster filesystem
LICENSE=	gnu-gpl-v3

GNU_CONFIGURE=		yes
USE_LIBTOOL=		yes
USE_TOOLS+=		flex bison pkg-config bash

INSTALL_UNSTRIPPED=	yes

REPLACE_PYTHON+=	contrib/ipaddr-py/ipaddr.py
REPLACE_PYTHON+=	extras/ganesha/scripts/generate-epoch.py
REPLACE_PYTHON+=	extras/geo-rep/schedule_georep.py
REPLACE_PYTHON+=	extras/snap_scheduler/gcron.py
REPLACE_PYTHON+=	extras/snap_scheduler/snap_scheduler.py
REPLACE_PYTHON+=	geo-replication/src/peer_mountbroker.in
REPLACE_PYTHON+=	geo-replication/syncdaemon/changelogagent.py
REPLACE_PYTHON+=	geo-replication/syncdaemon/gsyncd.py
REPLACE_PYTHON+=	geo-replication/syncdaemon/gsyncdstatus.py
REPLACE_PYTHON+=	tools/gfind_missing_files/gfid_to_path.py
REPLACE_PYTHON+=	tools/glusterfind/S57glusterfind-delete-post.py
REPLACE_PYTHON+=	tools/glusterfind/glusterfind.in
REPLACE_PYTHON+=	tools/glusterfind/src/__init__.py
REPLACE_PYTHON+=	tools/glusterfind/src/brickfind.py
REPLACE_PYTHON+=	tools/glusterfind/src/changelog.py
REPLACE_PYTHON+=	tools/glusterfind/src/changelogdata.py
REPLACE_PYTHON+=	tools/glusterfind/src/conf.py
REPLACE_PYTHON+=	tools/glusterfind/src/libgfchangelog.py
REPLACE_PYTHON+=	tools/glusterfind/src/main.py
REPLACE_PYTHON+=	tools/glusterfind/src/nodeagent.py
REPLACE_PYTHON+=	tools/glusterfind/src/utils.py

REPLACE_BASH+=		extras/ganesha/ocf/ganesha_grace
REPLACE_BASH+=		extras/ganesha/ocf/ganesha_mon
REPLACE_BASH+=		extras/ganesha/ocf/ganesha_nfsd
REPLACE_BASH+=		extras/ganesha/scripts/ganesha-ha.sh
REPLACE_BASH+=		extras/geo-rep/generate-gfid-file.sh
REPLACE_BASH+=		extras/geo-rep/get-gfid.sh
REPLACE_BASH+=		extras/geo-rep/gsync-upgrade.sh
REPLACE_BASH+=		extras/geo-rep/slave-upgrade.sh
REPLACE_BASH+=		extras/peer_add_secret_pub.in
REPLACE_BASH+=		extras/peer_add_secret_pub.in
REPLACE_BASH+=		extras/post-upgrade-script-for-quota.sh
REPLACE_BASH+=		extras/pre-upgrade-script-for-quota.sh
REPLACE_BASH+=		geo-replication/src/gverify.sh
REPLACE_BASH+=		geo-replication/src/peer_gsec_create.in
REPLACE_BASH+=		geo-replication/src/set_geo_rep_pem_keys.sh

PLIST_SUBST+=		PYSITELIB=${PYSITELIB:Q}

post-install:
	${INSTALL_SCRIPT} ${DESTDIR}/sbin/mount.glusterfs \
	    ${DESTDIR}/${PREFIX}/sbin/mount.glusterfs

.include "../../mk/bsd.prefs.mk"

.include "../../base/libacl/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../databases/sqlite3/buildlink3.mk"
.include "../../devel/userspace-rcu/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../lang/python/extension.mk"
.include "../../mk/bsd.pkg.mk"
