# $NetBSD: Makefile.common,v 1.34.2.1 2014/04/14 15:29:21 tron Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
#  # vim: ts=8 sw=8 ft=make noet

#.if exists(../../base/git/Makefile)
#BUILD_DEPENDS+=         git>=1.6.4:../../base/git
.if exists(../../devel/git/Makefile)
BUILD_DEPENDS+=         git-base>=1.6.4:../../devel/git-base
.else
BUILD_DEPENDS+=         scmgit-base>=1.6.4:../../devel/scmgit-base
.endif

.PHONY: disable_myisam

disable_myisam:
	git clone git@github.com:xiezhenye/mysql-plugin-disable-myisam.git ${WRKDIR}/mysql-plugin-disable-myisam
	${CP} -r ${WRKDIR}/mysql-plugin-disable-myisam/src ${WRKSRC}/plugin/disable_myisam