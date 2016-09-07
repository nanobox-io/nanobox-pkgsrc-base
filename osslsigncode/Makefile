# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		osslsigncode-1.7.1
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=osslsigncode/}

MAINTAINER=		braxton@pagodabox.com
HOMEPAGE=		http://signcode.sourceforge.net/
COMMENT=		Platform-independent tool for Authenticode signing of PE(EXE/SYS/DLL/etc)
LICENSE=		GPL-3

USE_TOOLS+=		gmake pax
USE_LANGUAGES=		c99
GNU_CONFIGURE=		yes

.include "../../mk/bsd.prefs.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
