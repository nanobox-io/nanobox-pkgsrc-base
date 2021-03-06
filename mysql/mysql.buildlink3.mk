# $NetBSD: mysql.buildlink3.mk,v 1.18 2013/09/13 11:53:24 obache Exp $
#
# This file is included by packages that require some version of the
# MySQL database client.
#
# === User-settable variables ===
#
# MYSQL_VERSION_DEFAULT
#	The preferred MySQL version.
#
#	Possible: 56 55 51 percona56 percona55 percona55-cluster
#	Default: 56
#
# === Package-settable variables ===
#
# MYSQL_VERSIONS_ACCEPTED
#	The list of MySQL versions that the package accepts.
#
#	Possible: (see MYSQL_VERSION_DEFAULT)
#	Default: (all)
#
# === Variables defined by this file ===
#
# MYSQL_VERSION
#	The MySQL version that is actually used.
#
#	Possible: (see MYSQL_VERSION_DEFAULT)
#
# MYSQL_PKG_PREFIX
# 	The package name prefix for the selected version.
#
# 	Possible: mysql56 mysql55 mysql51 mysql5 percona56 percona55 percona55-cluster
#

.if !defined(MYSQL_VERSION_MK)
MYSQL_VERSION_MK=	# defined

_VARGROUPS+=		mysql
_USER_VARS.mysql=	MYSQL_VERSION_DEFAULT
_PKG_VARS.mysql=	MYSQL_VERSIONS_ACCEPTED
_SYS_VARS.mysql=	MYSQL_VERSION MYSQL_PKG_PREFIX

.include "../../mk/bsd.prefs.mk"

MYSQL_VERSION_DEFAULT?=		56
BUILD_DEFS+=			MYSQL_VERSION_DEFAULT
BUILD_DEFS_EFFECTS+=		MYSQL_VERSION MYSQL_PKG_PREFIX

# Package-settable variables
MYSQL_VERSIONS_ACCEPTED?=	${_PKG_MYSQLS}

# The available MySQL packages:
_PKG_MYSQLS=			56 55 51 percona56 percona55 percona55-cluster

_MYSQL_PKGBASE.56=		mysql-client-5.6.*
_MYSQL_PKGSRCDIR.56=		../../base/mysql56-client
_MYSQL_PKG_PREFIX.56=		mysql56

_MYSQL_PKGBASE.55=		mysql-client-5.5.*
_MYSQL_PKGSRCDIR.55=		../../base/mysql55-client
_MYSQL_PKG_PREFIX.55=		mysql55

_MYSQL_PKGBASE.51=		mysql-client-5.1.*
_MYSQL_PKGSRCDIR.51=		../../base/mysql51-client
_MYSQL_PKG_PREFIX.51=		mysql51

_MYSQL_PKGBASE.percona56=	percona-client-5.6.*
_MYSQL_PKGSRCDIR.percona56=	../../joyent/percona56-client
_MYSQL_PKG_PREFIX.percona56=	percona56

_MYSQL_PKGBASE.percona55=	percona-client-5.5.*
_MYSQL_PKGSRCDIR.percona55=	../../joyent/percona55-client
_MYSQL_PKG_PREFIX.percona55=	percona55

_MYSQL_PKGBASE.percona55-cluster=	percona-cluster-5.5.*
_MYSQL_PKGSRCDIR.percona55-cluster=	../../joyent/percona55-cluster
_MYSQL_PKG_PREFIX.percona55-cluster=	percona55-cluster

#
# Sanity checks
#
.if empty(_PKG_MYSQLS:M${MYSQL_VERSION_DEFAULT})
PKG_FAIL_REASON+=	"[mysql.buildlink3.mk] Invalid mysql package \""${MYSQL_VERSION_DEFAULT:Q}"\" in MYSQL_VERSION_DEFAULT."
.endif

.for _myver_ in ${MYSQL_VERSIONS_ACCEPTED}
.  if empty(_PKG_MYSQLS:M${_myver_})
PKG_FAIL_REASON+=		"[mysql.buildlink3.mk] Invalid mysql package \""${_myver_:Q}"\" in MYSQL_VERSIONS_ACCEPTED."
MYSQL_VERSIONS_ACCEPTED=	# none
.  endif
.endfor

#
# Mark the acceptable versions and check which packages are installed.
#
.for _myver_ in ${MYSQL_VERSIONS_ACCEPTED}
_MYSQL_OK.${_myver_}=	yes
_MYSQL_INSTALLED.${_myver_}!=					\
	if ${PKG_INFO} -qe ${_MYSQL_PKGBASE.${_myver_}:Q}; then	\
		${ECHO} yes;					\
	else							\
		${ECHO} no;					\
	fi
.endfor
.for _myver_ in ${_PKG_MYSQLS}
_MYSQL_OK.${_myver_}?=	no
.endfor

# If a version is explicitely required, take it...
.if defined(MYSQL_VERSION_REQD)
MYSQL_VERSION=		${MYSQL_VERSION_REQD}
.endif

# ...otherwise use one of the installed MySQL packages...
.if !defined(MYSQL_VERSION)
.  for _myver_ in ${MYSQL_VERSIONS_ACCEPTED}
.    if ${_MYSQL_INSTALLED.${_myver_}} == "yes"
MYSQL_VERSION?=		${_myver_}
.    endif
.  endfor
.endif

# ...otherwise prefer the default one if it is accepted...
.if !defined(MYSQL_VERSION)
.  if defined(_MYSQL_OK.${MYSQL_VERSION_DEFAULT}) && \
    ${_MYSQL_OK.${MYSQL_VERSION_DEFAULT}} == "yes"
MYSQL_VERSION?=		${MYSQL_VERSION_DEFAULT}
.  endif
.endif

# ...otherwise just use the first default accepted.
.if !defined(MYSQL_VERSION)
.  for _myver_ in ${MYSQL_VERSIONS_ACCEPTED}
MYSQL_VERSION?=		${_myver_}
.  endfor
.endif

.if defined(MYSQL_VERSION)
.  include "${_MYSQL_PKGSRCDIR.${MYSQL_VERSION}}/buildlink3.mk"
.else
PKG_FAIL_REASON+=	"[mysql.buildlink3.mk] No acceptable mysql version found."
MYSQL_VERSION=		none
.endif

MYSQL_PKG_PREFIX=	${_MYSQL_PKG_PREFIX.${MYSQL_VERSION}}

# Variable assignment for multi-mysql packages
MULTI+=		MYSQL_VERSION=${MYSQL_VERSION}

.endif	# MYSQL_VERSION_MK
