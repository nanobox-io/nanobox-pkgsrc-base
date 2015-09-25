# $NetBSD: dist.mk,v 1.9 2014/12/16 07:07:32 chopps Exp $

PY_DISTVERSION=	2.7.10
DISTNAME=	Python-${PY_DISTVERSION}
EXTRACT_SUFX=	.tar.xz
DISTINFO_FILE=	${.CURDIR}/../../base/python27/distinfo
PATCHDIR=	${.CURDIR}/../../base/python27/patches
MASTER_SITES=	http://www.python.org/ftp/python/${PY_DISTVERSION}/
