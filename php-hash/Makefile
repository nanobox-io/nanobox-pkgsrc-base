# $NetBSD: Makefile,v 1.2 2012/10/08 13:04:27 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

MODNAME=		hash
CATEGORIES+=		devel
COMMENT=		PHP extension for hash conversion support

CONFLICTS=		php-hash-[0-9]*

CONFIGURE_ARGS+=	--enable-${MODNAME}

.include "../../base/php/ext.mk"

INSTALLATION_DIRS+=	include/php/ext/hash

.if ${PKG_PHP_VERSION} == 53
HASH_INCLUDES=		php_hash.h php_hash_adler32.h php_hash_crc32.h php_hash_gost.h php_hash_haval.h php_hash_md.h php_hash_ripemd.h php_hash_salsa.h php_hash_sha.h php_hash_snefru.h php_hash_tiger.h php_hash_types.h php_hash_whirlpool.h
.elif ${PKG_PHP_VERSION} == 54
HASH_INCLUDES=		php_hash.h php_hash_adler32.h php_hash_crc32.h php_hash_gost.h php_hash_haval.h php_hash_md.h php_hash_ripemd.h php_hash_sha.h php_hash_snefru.h php_hash_tiger.h php_hash_types.h php_hash_whirlpool.h
.elif ${PKG_PHP_VERSION} == 55
HASH_INCLUDES=		php_hash.h php_hash_md.h php_hash_sha.h php_hash_ripemd.h php_hash_haval.h php_hash_tiger.h php_hash_gost.h php_hash_snefru.h php_hash_whirlpool.h php_hash_adler32.h php_hash_crc32.h php_hash_fnv.h php_hash_joaat.h php_hash_types.h
.elif ${PKG_PHP_VERSION} == 56
HASH_INCLUDES=		php_hash_adler32.h php_hash_crc32.h php_hash_gost_tables.h php_hash_haval.h php_hash_md.h php_hash_sha.h php_hash_snefru.h php_hash_tiger.h php_hash_whirlpool.h php_hash_crc32_tables.h php_hash_fnv.h php_hash_gost.h php_hash_joaat.h php_hash_ripemd.h php_hash_snefru_tables.h php_hash_tiger_tables.h php_hash_whirlpool_tables.h php_hash.h
.elif ${PKG_PHP_VERSION} == 70
HASH_INCLUDES=		php_hash_adler32.h php_hash_crc32.h php_hash_crc32_tables.h php_hash_fnv.h php_hash_gost.h php_hash_gost_tables.h php_hash.h php_hash_haval.h php_hash_joaat.h php_hash_md.h php_hash_ripemd.h php_hash_sha.h php_hash_snefru.h php_hash_snefru_tables.h php_hash_tiger.h php_hash_tiger_tables.h php_hash_whirlpool.h php_hash_whirlpool_tables.h
.endif

PLIST_SRC+=		${.CURDIR}/../../base/php-hash/PLIST.hash${PKG_PHP_VERSION}

post-install:
.for inc in ${HASH_INCLUDES}
	${INSTALL_DATA} ${WRKSRC}/${inc} ${DESTDIR}${PREFIX}/include/php/ext/hash/${inc}
.endfor

.include "../../mk/bsd.pkg.mk"