# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

PKGNAME=		${APACHE_PKG_PREFIX}-${PHP_PKG_PREFIX}-${PHP_BASE_VERS}
PKGBASE=		${APACHE_PKG_PREFIX}-${PHP_PKG_PREFIX}
VERSION=		${PHP_BASE_VERS}
COMMENT=		Apache (${PKG_APACHE}) module for ${PKG_PHP}
PKGREVISION=		1

CONFLICTS=		ap-php-[0-9]*

USE_TOOLS+=		lex
USE_LIBTOOL=		YES

APACHE_MODULE=		YES

.include "../../base/php/phpversion.mk"
.include "${PHPPKGSRCDIR}/Makefile.php"

MESSAGE_SUBST+=		PKG_PHP_MAJOR_VERS=${PKG_PHP_MAJOR_VERS}

# Ensure we export symbols in the linked shared object.
CONFIGURE_ENV+=		EXTRA_LDFLAGS=${EXPORT_SYMBOLS_LDFLAGS:M*:Q}

INSTALLATION_DIRS=	lib/httpd

do-install:
	if [ -f ${WRKSRC}/.libs/libphp${PKG_PHP_MAJOR_VERS}.so ]; then	\
		${INSTALL_DATA} ${WRKSRC}/.libs/libphp${PKG_PHP_MAJOR_VERS}.so \
			${DESTDIR}${PREFIX}/lib/httpd/mod_php${PKG_PHP_MAJOR_VERS}.so;   \
	elif [ -f ${WRKSRC}/libs/libphp${PKG_PHP_MAJOR_VERS}.so ]; then	\
		${INSTALL_DATA} ${WRKSRC}/libs/libphp${PKG_PHP_MAJOR_VERS}.so  \
			${DESTDIR}${PREFIX}/lib/httpd/mod_php${PKG_PHP_MAJOR_VERS}.so;   \
	fi

.include "${PHPPKGSRCDIR}/buildlink3.mk"
.include "../../base/apache/apache.mk"
.include "../../mk/bsd.pkg.mk"
