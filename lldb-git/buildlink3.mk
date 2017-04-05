# $NetBSD$

BUILDLINK_TREE+=	lldb

.if !defined(LLDB_BUILDLINK3_MK)
LLDB_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.lldb+=	lldb>=3.9.0nb20160121
BUILDLINK_PKGSRCDIR.lldb?=	../../base/lldb-git

.include "../../textproc/libxml2/buildlink3.mk"
.include "../../base/llvm-git/buildlink3.mk"
.include "../../base/clang-git/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../devel/swig/buildlink3.mk"
.endif	# LLDB_BUILDLINK3_MK

BUILDLINK_TREE+=	-lldb
