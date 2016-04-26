# $NetBSD: Makefile,v 1.2 2012/10/08 13:04:27 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		session
CATEGORIES+=		www
COMMENT=		PHP extension for session support

CONFLICTS=		php-session-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}

.include "../../base/php/ext.mk"
.if ${_PHP_VERSION} == "53" || ${_PHP_VERSION} == "54"
PKGREVISION=		1
.endif

INSTALLATION_DIRS+=	include/php/ext/session
INSTALLATION_DIRS+=	var/php/sessions

SESSION_INCLUDES=	mod_files.h mod_user.h php_session.h
PLIST_SRC+=		${.CURDIR}/../../base/php-session/PLIST.session

post-install:
.for inc in ${SESSION_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/session/${inc}
.endfor

.include "../../mk/bsd.pkg.mk"