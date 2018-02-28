.if !defined(_ERLANGVERSION_MK)
_ERLANGVERSION_MK=	# defined

.include "../../mk/bsd.prefs.mk"

ERLANG_VERSION_DEFAULT?=	20

ERLANG_VERSION_SUPPORTED?=	18 19 20

ERLANG18_VERSION=		18.3.4.7
ERLANG19_VERSION=		19.3.6.5
ERLANG20_VERSION=		20.2.2

.if defined(ERLANG_VERSION_REQD)
. for ev in ${ERLANG_VERSION_SUPPORTED}
.  if "${ev}" == ${ERLANG_VERSION_REQD}
ERLANG_VER=       ${ev}
.  endif
. endfor
.elif !defined(ERLANG_VER)
. for ev in ${ERLANG_VERSION_SUPPORTED}
.  if "${ev}" == ${ERLANG_VERSION_DEFAULT}
ERLANG_VER=       ${ev}
.  endif
. endfor
.endif

.if !defined(ERLANG_VER)
. for ev in ${ERLANG_VERSION_SUPPORTED}
.  if !defined(ERLANG_VER)
ERLANG_VER=       ${ev}
.  endif
. endfor
.endif

.if ${ERLANG_VER} == "18"
ERLANG_VERSION=		${ERLANG18_VERSION}
ERLANG_VERSION_NEXT=	19.0.0
ERLANG_PKGPREFIX=	erlang18
ERLANG_SRCDIR=		../../base/erlang18
.elif ${ERLANG_VER} == "19"
ERLANG_VERSION=		${ERLANG19_VERSION}
ERLANG_VERSION_NEXT=	20.0.0
ERLANG_PKGPREFIX=	erlang19
ERLANG_SRCDIR=		../../base/erlang19
.elif ${ERLANG_VER} == "20"
ERLANG_VERSION=		${ERLANG20_VERSION}
ERLANG_VERSION_NEXT=	21.0.0
ERLANG_PKGPREFIX=	erlang20
ERLANG_SRCDIR=		../../base/erlang20
.endif

.endif
