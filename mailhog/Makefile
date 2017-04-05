# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

DISTNAME=		mailhog-${VERSION}
VERSION?=		0.2.1
# PKGREVISION?=		1
CATEGORIES=		pagoda
MASTER_SITES=		github.com/mailhog/MailHog

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		github.com/mailhog/MailHog
COMMENT=		MailHog is an email testing tool for developers
LICENSE=       		MIT

WRKSRC=			${WRKDIR}/mailhog

USE_LANGUAGES=		c

GIT_REPOSITORIES=	mailhog
GIT_REPO.mailhog=	git@github.com:mailhog/MailHog.git
GIT_TAG.mailhog=	v${VERSION}

GO_DOMAIN=		github.com
GO_USER=		mailhog
GO_PROJECT=		MailHog

.include "../../base/git/git-package.mk"
.include "../../base/go/go-app.mk"
.include "../../mk/bsd.pkg.mk"

