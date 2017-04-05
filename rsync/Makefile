# $NetBSD: Makefile,v 1.103 2015/12/23 19:53:24 ryoon Exp $

DISTNAME=	rsync-${VERSION}
VERSION=	3.1.2
PKGREVISION=	1
CATEGORIES=	net
MASTER_SITES=	http://rsync.samba.org/ftp/rsync/ \
		http://rsync.samba.org/ftp/rsync/old-versions/  \
		ftp://ftp.fu-berlin.de/unix/network/rsync/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://rsync.samba.org/
COMMENT=	Network file distribution/synchronisation utility
LICENSE=	gnu-gpl-v3

DISTFILES=	${DEFAULT_DISTFILES}
DISTFILES+=	rsync-patches-${VERSION}${EXTRACT_SUFX}

INSTALLATION_DIRS=	bin ${PKGMANDIR}/man1 ${PKGMANDIR}/man5 share/doc/rsync

USE_TOOLS+=perl

GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--with-included-popt
CONFIGURE_ARGS+=	--with-rsyncd-conf=${PKG_SYSCONFDIR}/rsyncd.conf
TEST_TARGET=		test

PKG_SYSCONFSUBDIR=	rsync

RCD_SCRIPTS=		rsyncd
RCD_SCRIPT_SRC.rsyncd=	files/rsyncd.sh
SMF_NAME=		rsyncd

SUBST_CLASSES+=		paths
SUBST_MESSAGE.paths=	Fixing hardcoded paths.
SUBST_STAGE.paths=	post-patch
SUBST_FILES.paths=	rsync.1 rsyncd.conf.5
SUBST_SED.paths=	-e 's|/etc/rsyncd|${PKG_SYSCONFDIR}/rsyncd|g'
SUBST_SED.paths+=	-e 's|/usr/bin/rsync|${PREFIX}/bin/rsync|g'

post-patch:
	cd ${WRKSRC}; patch -p1 <patches/ignore-case.diff

post-install:
	${INSTALL_DATA} ${WRKSRC}/README ${WRKSRC}/tech_report.tex \
		${DESTDIR}${PREFIX}/share/doc/rsync

.include "../../converters/libiconv/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
