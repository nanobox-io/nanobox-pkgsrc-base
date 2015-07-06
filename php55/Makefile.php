# $NetBSD: Makefile.php,v 1.4 2012/07/27 00:21:03 obache Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet
# used by pagoda/php55/Makefile
# used by www/ap-php/Makefile

.include "../../base/php55/Makefile.common"

DISTINFO_FILE=	${.CURDIR}/../../base/php55/distinfo
PATCHDIR=	${.CURDIR}/../../base/php55/patches

USE_LIBTOOL=		YES
USE_LANGUAGES=		c c++
GNU_CONFIGURE=		YES
BUILD_DEFS+=		VARBASE
PLIST_VARS+=		suhosin dtrace

CONFIGURE_ENV+=		EXTENSION_DIR="${PREFIX}/${PHP_EXTENSION_DIR}"

.include "../../mk/bsd.prefs.mk"
.include "../../textproc/libxml2/buildlink3.mk"

CONFIGURE_ARGS+=	--with-config-file-path=${PKG_SYSCONFDIR}/php
CONFIGURE_ARGS+=	--with-config-file-scan-dir=${PKG_SYSCONFDIR}/php.d
CONFIGURE_ARGS+=	--sysconfdir=${PKG_SYSCONFDIR}
CONFIGURE_ARGS+=	--localstatedir=${VARBASE}
CONFIGURE_ARGS+=	--with-libxml-dir=${BUILDLINK_PREFIX.libxml2}

.if ${OPSYS} != Linux
CONFIGURE_ARGS+=	--enable-dtrace
.endif

CONFIGURE_ARGS+=	--without-pear
CONFIGURE_ARGS+=	--without-sqlite3
CONFIGURE_ARGS+=	--without-iconv
CONFIGURE_ARGS+=	--without-pdo-sqlite
CONFIGURE_ARGS+=	--disable-ctype   
CONFIGURE_ARGS+=	--disable-dom          
CONFIGURE_ARGS+=	--disable-fileinfo     
CONFIGURE_ARGS+=	--disable-filter       
CONFIGURE_ARGS+=	--disable-hash         
CONFIGURE_ARGS+=	--disable-json         
CONFIGURE_ARGS+=	--disable-mbregex
CONFIGURE_ARGS+=	--disable-opcache        
CONFIGURE_ARGS+=	--disable-pdo         
CONFIGURE_ARGS+=	--disable-phar        
CONFIGURE_ARGS+=	--disable-posix       
CONFIGURE_ARGS+=	--disable-session     
CONFIGURE_ARGS+=	--disable-simplexml   
CONFIGURE_ARGS+=	--disable-tokenizer   
CONFIGURE_ARGS+=	--disable-xml         
CONFIGURE_ARGS+=	--disable-xmlreader   
CONFIGURE_ARGS+=	--disable-xmlwriter
CONFIGURE_ARGS+=	--enable-mysqlnd

# Note: This expression is the same as ${PKGBASE}, but the latter is
# not defined yet, so we cannot use it here.
PKG_OPTIONS_VAR=	PKG_OPTIONS.${PKGNAME:C/-[0-9].*//}
PKG_SUPPORTED_OPTIONS+=	inet6 ssl maintainer-zts readline # suhosin
PKG_SUGGESTED_OPTIONS+=	inet6 ssl

.if ${OPSYS} == "SunOS" || ${OPSYS} == "Darwin" || ${OPSYS} == "FreeBSD"
PKG_SUPPORTED_OPTIONS+=	dtrace
.endif

#SUBST_CLASSES+=		ini
#SUBST_STAGE.ini=	post-patch
#SUBST_FILES.ini=	php.ini-development
#SUBST_FILES.ini+=	php.ini-production
#SUBST_SED.ini=		-e "s|\\;include_path = \".:/php/includes\"|include_path = \".:${PREFIX}/lib/php\"|g"
#SUBST_MESSAGE.ini=	Fixing default ini files.

.include "../../mk/bsd.options.mk"

#.if !empty(PKG_OPTIONS:Msuhosin)
#SUHOSIN_PHPVER=		5.4.0
#.  if ${SUHOSIN_PHPVER} != ${PHP_BASE_VERS}
#PKG_FAIL_REASON+=	"The suhosin patch is currently not available for"
#PKG_FAIL_REASON+=	"this version of PHP.  You may have to wait until"
#PKG_FAIL_REASON+=	"an updated patch is released or temporarily"
#PKG_FAIL_REASON+=	"build this package without the suhosin option."
#.  else
#PATCH_SITES=		http://download.suhosin.org/
#PATCHFILES+=		suhosin-patch-${SUHOSIN_PHPVER}-0.9.10.patch.gz
#PATCH_DIST_STRIP=	-p1
#PLIST.suhosin=		yes
#MESSAGE_SRC=		${.CURDIR}/../../base/php54/MESSAGE
#MESSAGE_SRC+=		${.CURDIR}/../../base/php54/MESSAGE.suhosin
#.  endif
#.endif

.if !empty(PKG_OPTIONS:Minet6)
CONFIGURE_ARGS+=	--enable-ipv6
.else
CONFIGURE_ARGS+=	--disable-ipv6
.endif

.if !empty(PKG_OPTIONS:Mssl)
.  include "../../security/openssl/buildlink3.mk"
.  if ${OPSYS} == "SunOS"
CONFIGURE_ARGS+=	--with-openssl=${BUILDLINK_PREFIX.openssl}
LIBS.SunOS+=		-lcrypto
.  else
CONFIGURE_ARGS+=	--with-openssl=${BUILDLINK_PREFIX.openssl}
.  endif
.else
CONFIGURE_ARGS+=	--without-openssl
.endif

.if !empty(PKG_OPTIONS:Mmaintainer-zts)
CONFIGURE_ARGS+=	--enable-maintainer-zts
.endif

.if !empty(PKG_OPTIONS:Mreadline)
USE_GNU_READLINE=	yes
.include "../../devel/readline/buildlink3.mk"
CONFIGURE_ARGS+=	--with-readline=${BUILDLINK_PREFIX.readline}
.else
CONFIGURE_ARGS+=	--without-readline
.endif

.if !empty(PKG_OPTIONS:Mdtrace)
PLIST.dtrace=		yes
CONFIGURE_ARGS+=	--enable-dtrace

# See https://bugs.php.net/bug.php?id=61268
INSTALL_MAKE_FLAGS+=	-r
.endif

DL_AUTO_VARS=		yes
.include "../../mk/dlopen.buildlink3.mk"
