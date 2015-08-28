# $NetBSD$
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
# git@github.com:pagodabox/git.git

VERSION=		2.5.0
# PKGREVISION=		1
DISTNAME=		git-${VERSION}
CATEGORIES=		nanobox
MASTER_SITES=		github.com/pagodabox/git

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		github.com/pagodabox/git
COMMENT= 		Git - the stupid content tracker
LICENSE=		gnu-gpl-v2

GIT_REPOSITORIES=	git
GIT_REPO.git=		git@github.com:pagodabox/git.git
GIT_TAG=		v${VERSION}-no-sideband-allow-archive-commit
# GIT_TAG=		bugfix/syntax

WRKSRC=			${WRKDIR}/git

.include "../../mk/bsd.prefs.mk"
.include "../../mk/bsd.fast.prefs.mk"

USE_TOOLS+=		gmake tar sh autoconf automake

PKG_SYSCONFSUBDIR=	git

GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--with-shell=${SH:Q}
CONFIGURE_ARGS+=	TAR=${TAR:Q}
CONFIGURE_ARGS+=	--mandir=${${PREFIX}/${PKGMANDIR}:L:Q}
CONFIGURE_ARGS+=	--sysconfdir=${PKG_SYSCONFDIR}

DEPENDS+=		p5-Error>=0.17015:../../devel/p5-Error
# for git-send-email
DEPENDS+=		{perl>=5.13.8,p5-MIME-Base64>=3.13}:../../converters/p5-MIME-Base64
DEPENDS+=		p5-Email-Valid>=0.190:../../mail/p5-Email-Valid
DEPENDS+=		p5-MailTools>=2.11:../../mail/p5-MailTools
DEPENDS+=		p5-Net-SMTP-SSL>=1.01:../../mail/p5-Net-SMTP-SSL
DEPENDS+=		p5-Authen-SASL>=1.0:../../security/p5-Authen-SASL

USE_LANGUAGES=		c99
USE_TOOLS+=		perl:run sh:run msgfmt

PERL5_CONFIGURE=	no
PERL5_PACKLIST=		auto/Git/.packlist
REPLACE_PERL+=		*.perl */*.perl */*/*.perl
REPLACE_PERL+=		contrib/hooks/update-paranoid

CFLAGS.NetBSD+=		-D_NETBSD_SOURCE

PY_PATCHPLIST=	yes
CONFIGURE_ARGS+=	--with-python=${PYTHONBIN}
CONFIGURE_ARGS+=	--with-openssl=${SSLBASE}
CONFIGURE_ARGS+=	--with-curl=${BUILDLINK_PREFIX.curl}
CONFIGURE_ARGS+=	--with-expat=${BUILDLINK_PREFIX.expat}
CONFIGURE_ARGS+=	--with-iconv=${BUILDLINK_PREFIX.iconv}
CONFIGURE_ARGS+=	--with-perl=${PERL5:Q}
CONFIGURE_ARGS+=	--with-zlib=${BUILDLINK_PREFIX.zlib}
CONFIGURE_ARGS+=	--without-tcltk

BUILD_TARGET=		all

CHECK_INTERPRETER_SKIP+= ${PYSITELIB}/git_remote_helpers/*.py
CHECK_INTERPRETER_SKIP+= ${PYSITELIB}/git_remote_helpers/git/*.py

REPLACE_SH+=		contrib/hooks/post-receive-email
REPLACE_SH+=		contrib/hooks/pre-auto-gc-battery

MAKE_FLAGS+=		NO_APPLE_COMMON_CRYPTO=1

EGDIR=			${PREFIX}/share/examples/git

GIT_COREDIR=		git-core
GIT_TEMPLATEDIR=	templates

GIT_TEMPLATES=		description info/exclude
GIT_TEMPLATES+=		hooks/applypatch-msg.sample hooks/commit-msg.sample
GIT_TEMPLATES+=		hooks/post-update.sample hooks/pre-applypatch.sample
GIT_TEMPLATES+=		hooks/pre-commit.sample hooks/pre-rebase.sample
GIT_TEMPLATES+=		hooks/prepare-commit-msg.sample hooks/update.sample

# XXX unused as of now
#GIT_CORE_EXECDIR=	libexec/${GIT_COREDIR}
GIT_CORE_DATADIR=	share/${GIT_COREDIR}
GIT_CORE_TEMPLATEDIR=	${GIT_CORE_DATADIR}/${GIT_TEMPLATEDIR}

MAKE_DIRS=		${GIT_CORE_TEMPLATEDIR}
MAKE_DIRS+=		${GIT_CORE_TEMPLATEDIR}/hooks
MAKE_DIRS+=		${GIT_CORE_TEMPLATEDIR}/info

REQD_FILES+=		${GIT_TEMPLATES:@.t.@\
				${EGDIR}/${GIT_TEMPLATEDIR}/${.t.}\
				${PREFIX}/${GIT_CORE_TEMPLATEDIR}/${.t.}\
			@:M*}

CONFIGURE_ENV+=		HOME=${PREFIX}
CONFIGURE_ENV+=		gitexecdir=${GITCOREDIR}

MAKE_FLAGS+=		INSTALL=${INSTALL:Q}

GIT_TEMPLATE_INSTDIR=	${EGDIR}/${GIT_TEMPLATEDIR}
MAKE_ENV+=		GIT_TEMPLATE_INSTDIR=${GIT_TEMPLATE_INSTDIR}
MESSAGE_SUBST+=		GIT_TEMPLATE_INSTDIR=${GIT_TEMPLATE_INSTDIR}

SUBST_CLASSES+=		fix-paths
SUBST_FILES.fix-paths=	templates/hooks--post-receive.sample
SUBST_MESSAGE.fix-paths=Fixing hard-coded pathnames
SUBST_STAGE.fix-paths=	pre-build
SUBST_VARS.fix-paths=	PREFIX

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "NetBSD" || ${OPSYS} == "SunOS" || ${OPSYS} == "OSF1" || ${OPSYS} == "HPUX" || ${OPSYS} == "QNX" || ${OPSYS} == "UnixWare"
SUBST_CLASSES+=		fix-cd-P
SUBST_FILES.fix-cd-P=	git-sh-setup.sh
SUBST_FILES.fix-cd-P+=	t/test-lib.sh
SUBST_MESSAGE.fix-cd-P=	Fixing cd arguments.
SUBST_STAGE.fix-cd-P=	pre-build
SUBST_SED.fix-cd-P=	-e "s/cd -P/cd/g"
.endif

LDFLAGS.SunOS+=		-lintl -lnsl

.include "../../mk/compiler.mk"
.if !empty(PKGSRC_COMPILER:Mclang)
# configure test gets confused by wrappers dropping -R /
CONFIGURE_ARGS+=	git_cv_ld_dashr=no
.endif

post-install:
	${INSTALL_DATA_DIR} ${DESTDIR}${EGDIR}
	${INSTALL_DATA} ${WRKSRC}/contrib/completion/git-completion.bash \
		${DESTDIR}${EGDIR}
	${INSTALL_DATA} ${WRKSRC}/contrib/completion/git-prompt.sh \
		${DESTDIR}${EGDIR}

pre-configure:
	cd ${WRKSRC}; gmake configure

.include "../../lang/python/application.mk"
.include "../../lang/python/extension.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../lang/perl5/module.mk"
.include "../../textproc/expat/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../base/git/git-package.mk"
.include "../../mk/bsd.pkg.mk"
