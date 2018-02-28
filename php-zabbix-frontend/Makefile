# $NetBSD: Makefile,v 1.4 2017/07/26 08:24:06 adam Exp $

.include "../../base/zabbix/Makefile.common"

PKGNAME=	${PHP_PKG_PREFIX}-${DISTNAME:S/-/-frontend-/}
COMMENT=	Zabbix PHP frontend

USE_TOOLS+=		pax
NO_BUILD=		yes

do-configure:
	${DO_NADA}

REPLACE_SH+=	${WRKSRC}/frontends/php/locale/*.sh

.include "../../mk/bsd.prefs.mk"

#BUILD_DEFS+=		APACHE_GROUP APACHE_USER
#PKG_GROUPS_VARS+=	${APACHE_GROUP}
#PKG_USERS_VARS=		${APACHE_USER}

DEPENDS+=	${PHP_PKG_PREFIX}-bcmath>=${PHP_BASE_VERS}:../../base/php-bcmath
DEPENDS+=	${PHP_PKG_PREFIX}-gd>=${PHP_BASE_VERS}:../../base/php-gd
DEPENDS+=	${PHP_PKG_PREFIX}-gettext>=${PHP_BASE_VERS}:../../base/php-gettext
DEPENDS+=	${PHP_PKG_PREFIX}-json>=${PHP_BASE_VERS}:../../base/php-json
DEPENDS+=	${PHP_PKG_PREFIX}-ldap>=${PHP_BASE_VERS}:../../base/php-ldap
DEPENDS+=	${PHP_PKG_PREFIX}-mbstring>=${PHP_BASE_VERS}:../../base/php-mbstring
DEPENDS+=	${PHP_PKG_PREFIX}-mysqli>=${PHP_BASE_VERS}:../../base/php-mysqli
DEPENDS+=	${PHP_PKG_PREFIX}-pgsql>=${PHP_BASE_VERS}:../../base/php-pgsql
DEPENDS+=	${PHP_PKG_PREFIX}-sockets>=${PHP_BASE_VERS}:../../base/php-sockets
DEPENDS+=	${PHP_PKG_PREFIX}-sysvsem>=${PHP_BASE_VERS}:../../base/php-sysvsem

INSTALLATION_DIRS+=	share/zabbix/frontend

do-install:
	rm -f ${WRKSRC}/frontends/php/locale/*.orig
	cd ${WRKSRC}/frontends; ${PAX} -rw php ${DESTDIR}${PREFIX}/share/zabbix/

.include "../../base/php/phpversion.mk"
.include "../../mk/bsd.pkg.mk"
