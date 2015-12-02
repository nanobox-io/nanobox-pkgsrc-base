# $NetBSD: Makefile.common,v 1.34.2.1 2014/04/14 15:29:21 tron Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

SPHINX=			sphinx-2.2.10-release

DISTFILES+=		${SPHINX}.tar.gz

SITES.${SPHINX}.tar.gz=	http://sphinxsearch.com/files/

.PHONY: sphinx_engine

sphinx_engine:
	${MV} ${WRKDIR}/${SPHINX}/mysqlse ${WRKSRC}/storage/sphinx