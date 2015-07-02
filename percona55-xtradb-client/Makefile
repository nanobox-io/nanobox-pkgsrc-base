# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

PKGNAME=		${DISTNAME:tl:S/cluster-/client-/:S/${VERSION}/${VERSION:S/-/./}/}
COMMENT=		MySQL 5, a free SQL database (client)
# PKGREVISION?=		1
CONFLICTS=		mysql3-client-[0-9]*

.include "Makefile.common"

# CMAKE_ARGS+=		-DWITHOUT_SERVER=ON
CMAKE_ARGS+=		-DWITH_UNIT_TESTS=OFF
CMAKE_ARGS+=		-DENABLE_THREAD_SAFE_CLIENT=1
UNWRAP_FILES+=		scripts/mysql_config
INFO_FILES=		yes
INSTALL_DIRS+=		client include libmysql man scripts tests

REPLACE_PERL=		scripts/mysql_convert_table_format.sh
REPLACE_PERL+=		scripts/mysql_find_rows.sh
REPLACE_PERL+=		scripts/mysql_fix_extensions.sh
REPLACE_PERL+=		scripts/mysql_fix_privilege_tables.sh
REPLACE_PERL+=		scripts/mysql_setpermission.sh
REPLACE_PERL+=		scripts/mysql_zap.sh
REPLACE_PERL+=		scripts/mysqlaccess.sh
REPLACE_PERL+=		scripts/mysqld_multi.sh
REPLACE_PERL+=		scripts/mysqldumpslow.sh
REPLACE_PERL+=		scripts/mysqlhotcopy.sh

.include "../../mk/bsd.pkg.mk"
