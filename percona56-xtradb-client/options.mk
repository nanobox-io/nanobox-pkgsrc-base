# $NetBSD: options.mk,v 1.3 2014/03/25 13:56:38 jperkin Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.mysql5

# ndb-cluster does not configure with cmake
PKG_SUPPORTED_OPTIONS+=	dtrace embedded-server ndb-cluster memcached ssl
PKG_SUGGESTED_OPTIONS+=	ssl

.include "../../mk/bsd.options.mk"

# Enable OpenSSL support
.if !empty(PKG_OPTIONS:Mssl)
.	include "../../security/openssl/buildlink3.mk"
CMAKE_ARGS+=		-DWITH_SSL=system
.else
CMAKE_ARGS+=		-DWITH_SSL=no
.endif

# Enable DTrace support
.if !empty(PKG_OPTIONS:Mdtrace)
CMAKE_ARGS+=		-DENABLE_DTRACE=ON
.endif

# Enable InnoDB Memcached support
PLIST_VARS+=		memcached
.if !empty(PKG_OPTIONS:Mmemcached)
PLIST.memcached=	yes
CMAKE_ARGS+=		-DWITH_INNODB_MEMCACHED=ON
CMAKE_ARGS+=		-DWITH_BUNDLED_MEMCACHED=ON
.include "../../devel/libevent/buildlink3.mk"
.else
CMAKE_ARGS+=		-DWITH_INNODB_MEMCACHED=OFF
.endif
