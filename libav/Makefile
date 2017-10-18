# $NetBSD: Makefile,v 1.1 2015/02/23 16:11:05 leot1990 Exp $
#

VERSION=	12.2
DISTNAME=	libav-${VERSION}
PKGNAME=	libav-${VERSION}
CATEGORIES=	multimedia
MASTER_SITES=	https://www.libav.org/releases/
EXTRACT_SUFX=	.tar.gz

MAINTAINER=	braxton@nanobox.io
HOMEPAGE=	http://libav.org/
COMMENT=	Open source audio and video processing tools
LICENSE=	gnu-lgpl-v2.1 gnu-gpl-v2

USE_TOOLS+=		gmake pkg-config perl pod2man
USE_LIBTOOL=		yes

HAS_CONFIGURE=		yes

CONFIGURE_ARGS+=	--prefix=${PREFIX}
CONFIGURE_ARGS+=	--enable-avfilter
CONFIGURE_ARGS+=	--enable-libfreetype
CONFIGURE_ARGS+=	--disable-gnutls
CONFIGURE_ARGS+=	--enable-libopencore-amrnb
CONFIGURE_ARGS+=	--enable-libopencore-amrwb
CONFIGURE_ARGS+=	--enable-nonfree
CONFIGURE_ARGS+=	--enable-openssl
CONFIGURE_ARGS+=	--enable-libtheora
CONFIGURE_ARGS+=	--enable-libvorbis
CONFIGURE_ARGS+=	--enable-libmp3lame
CONFIGURE_ARGS+=	--enable-libxvid
CONFIGURE_ARGS+=	--enable-libx264
CONFIGURE_ARGS+=	--enable-libx265
CONFIGURE_ARGS+=	--enable-vdpau
CONFIGURE_ARGS+=	--enable-vaapi
CONFIGURE_ARGS+=	--enable-libvpx
CONFIGURE_ARGS+=	--enable-libxcb
CONFIGURE_ARGS+=	--disable-debug
CONFIGURE_ARGS+=	--disable-optimizations
CONFIGURE_ARGS+=	--enable-shared
CONFIGURE_ARGS+=	--enable-pthreads
CONFIGURE_ARGS+=	--enable-gpl
CONFIGURE_ARGS+=	--enable-runtime-cpudetect
CONFIGURE_ARGS+=	--enable-version3
CONFIGURE_ARGS+=	--extra-cflags=${CFLAGS:Q}
CONFIGURE_ARGS+=	--extra-ldflags=${LDFLAGS:Q}

BUILD_DEPENDS+=	yasm>=0.7.2:../../devel/yasm

.include "../../mk/compiler.mk"
.include "../../archivers/bzip2/buildlink3.mk"
.include "../../archivers/xz/buildlink3.mk"
.include "../../devel/libgetopt/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../multimedia/libvdpau/buildlink3.mk"
.include "../../multimedia/libva/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
.include "../../audio/fdk-aac/buildlink3.mk"
.include "../../security/gnutls/buildlink3.mk"
.include "../../audio/opencore-amr/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../multimedia/libtheora/buildlink3.mk"
.include "../../audio/libvorbis/buildlink3.mk"
.include "../../audio/lame/buildlink3.mk"
.include "../../audio/libopus/buildlink3.mk"
.include "../../multimedia/xvidcore/buildlink3.mk"
.include "../../multimedia/x264-devel/buildlink3.mk"
.include "../../multimedia/x265/buildlink3.mk"
.include "../../multimedia/libvdpau/buildlink3.mk"
.include "../../multimedia/libva/buildlink3.mk"
.include "../../multimedia/libvpx/buildlink3.mk"
.include "../../x11/libxcb/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
