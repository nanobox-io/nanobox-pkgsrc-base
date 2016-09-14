# $NetBSD: dist.mk,v 1.4 2015/02/26 06:23:06 adam Exp $

PY_DISTVERSION=	3.5.2
DISTNAME=	Python-${PY_DISTVERSION}
EXTRACT_SUFX=	.tar.xz
DISTINFO_FILE=	${.CURDIR}/../../base/python35/distinfo
PATCHDIR=	${.CURDIR}/../../base/python35/patches
MASTER_SITES=	http://www.python.org/ftp/python/${PY_DISTVERSION}/
