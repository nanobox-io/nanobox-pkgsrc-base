# $NetBSD: Makefile,v 1.21 2015/03/13 14:34:12 taca Exp $

DISTNAME=	bundler-1.15.4
#PKGREVISION=	1
CATEGORIES=	misc

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://gembundler.com/
COMMENT=	Manage your application's dependencies
LICENSE=	mit

RUBYGEM_OPTIONS+=	--no-format-executable
RUBY_BUILD_RDOC=	No
RUBY_BUILD_RI=		No

.include "../../base/ruby/gem.mk"
.include "../../mk/bsd.pkg.mk"
