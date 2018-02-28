# $NetBSD: Makefile,v 1.8 2018/01/01 21:18:53 adam Exp $

PKGREVISION= 3
PKGNAME=        ${DISTNAME:S/-/-agentd-/}
.include "../../base/zabbix/Makefile.common"

COMMENT=	Enterprise-class Monitoring Solution for Everyone

DEPENDS+=	fping-[0-9]*:../../net/fping

USE_TOOLS+=		pax pkg-config
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--enable-agent
CONFIGURE_ARGS+=	--sysconfdir=${PKG_SYSCONFDIR}
CONFIGURE_ARGS+=	--with-iconv=${BUILDLINK_PREFIX.iconv}
CONFIGURE_ARGS+=	--with-jabber
CONFIGURE_ARGS+=	--with-ldap=${BUILDLINK_PREFIX.openldap-client}
CONFIGURE_ARGS+=	--with-libcurl
CONFIGURE_ARGS+=	--with-libxml2
CONFIGURE_ARGS+=	--with-openssl=${BUILDLINK_PREFIX.openssl}
CONFIGURE_ARGS+=	--with-libevent=${BUILDLINK_PREFIX.libevent}
CONFIGURE_ARGS+=	--with-libpcre=${BUILDLINK_PREFIX.pcre}

EGDIR=		share/examples/zabbix
CONF_FILES+=	${EGDIR}/zabbix_agentd.conf ${PKG_SYSCONFDIR}/zabbix_agentd.conf

#RCD_SCRIPTS=	zabbix_agentd zabbix_proxy zabbix_server

INSTALLATION_DIRS+=	${EGDIR} share/zabbix

SUBST_CLASSES+=		fix-paths
SUBST_STAGE.fix-paths=	pre-configure
SUBST_MESSAGE.fix-paths=Fixing absolute paths.
SUBST_FILES.fix-paths=	conf/*.conf
SUBST_FILES.fix-paths+=	man/*.man
SUBST_SED.fix-paths=	-e 's,/usr/local/etc,${PKG_SYSCONFDIR},g'

.include "../../mk/bsd.prefs.mk"

#ZABBIX_GROUP?=		zabbix
#ZABBIX_USER?=		zabbix
#PKG_GROUPS+=		${ZABBIX_GROUP}
#PKG_USERS+=		${ZABBIX_USER}:${ZABBIX_GROUP}
#PKG_GECOS.${ZABBIX_USER}=Zabbix user

.include "options.mk"

.include "../../converters/libiconv/buildlink3.mk"
.include "../../databases/openldap-client/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../textproc/iksemel/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../devel/libevent/buildlink3.mk"
.include "../../devel/pcre/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
