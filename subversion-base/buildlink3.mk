# $NetBSD: buildlink3.mk,v 1.36 2013/12/01 10:18:02 ryoon Exp $

.include "../../mk/bsd.fast.prefs.mk"
.include "../../base/subversion/Makefile.version"

BUILDLINK_TREE+=	subversion-base

.if !defined(SUBVERSION_BASE_BUILDLINK3_MK)
SUBVERSION_BASE_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.subversion-base+=	subversion-base>=1.8.13
BUILDLINK_ABI_DEPENDS.subversion-base+=	subversion-base>=1.8.13
BUILDLINK_PKGSRCDIR.subversion-base?=	../../base/subversion-base

BUILDLINK_FILES.subversion-base+=	bin/svn-config

pkgbase := subversion-base
.include "../../mk/pkg-build-options.mk"

.if !empty(PKG_BUILD_OPTIONS.subversion-base:Msasl)
.include "../../security/cyrus-sasl/buildlink3.mk"
.endif

.if !empty(PKG_BUILD_OPTIONS.subversion-base:Mapr1)
.  include "../../base/apr/buildlink3.mk"
.  include "../../base/apr-util/buildlink3.mk"
.else
.  include "../../base/apr0/buildlink3.mk"
.endif

# If serf and -apr1 are selected, the build will probably fail.
.if !empty(PKG_BUILD_OPTIONS.subversion-base:Mserf)
.  include "../../base/serf/buildlink3.mk"
.endif

BUILDLINK_API_DEPENDS.sqlite3+=	sqlite3>=3.7.15.1
.include "../../databases/sqlite3/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.endif # SUBVERSION_BASE_BUILDLINK3_MK

BUILDLINK_TREE+=	-subversion-base
