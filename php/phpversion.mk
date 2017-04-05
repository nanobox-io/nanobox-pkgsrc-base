# $NetBSD: phpversion.mk,v 1.31 2013/03/16 02:02:13 taca Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
#
# This file selects a PHP version, based on the user's preferences and
# the installed packages. It does not add a dependency on the PHP
# package.
#
# === User-settable variables ===
#
# PHP_VERSION_DEFAULT
#	The PHP version to choose when more than one is acceptable to
#	the package.
#
#	Possible: 53 54 55 56 70 71
#	Default: 54
#
# === Infrastructure variables ===
#
# PHP_VERSION_REQD
#	PHP version to use. This variable should not be set in
#	packages.  Normally it is used by bulk build tools.
#
#	Possible: ${PHP_VERSIONS_ACCEPTED}
#	Default:  ${PHP_VERSION_DEFAULT}
#
# === Package-settable variables ===
#
# PHP_VERSIONS_ACCEPTED
#	The PHP versions that are accepted by the package.
#
#	Possible: 53 54 55 56 70 71
#	Default: 54 53 55 56 70 71
#
# === Variables defined by this file ===
#
# PKG_PHP_VERSION
#	The selected PHP version.
#
#	Possible: 53 54 55 56 70 71
#	Default: ${PHP_VERSION_DEFAULT}
#
# PHP_BASE_VERS
#	The selected PHP's full version depends on PKG_PHP_VERSION
#
# PKG_PHP_MAJOR_VERS
#	The selected PHP's major version.
#
#	Possible: 5
#	Default: 5
#
# PKG_PHP
#	The same as ${PKG_PHP_VERSION}, prefixed with "php-".
#
# PHPPKGSRCDIR
#	The directory of the PHP implementation, relative to the
#	package directory.
#
#	Example: ../../base/php54
#
# PHP_PKG_PREFIX
#	The prefix that is prepended to the package name.
#
#	Example: php53, php54
#
# Keywords: php
#

.if !defined(PHPVERSION_MK)
PHPVERSION_MK=			defined

_VARGROUPS+=			php
_USER_VARS.php=			PHP_VERSION_DEFAULT
_PKG_VARS.php=			PHP_VERSIONS_ACCEPTED PHP_VERSION_REQD
_SYS_VARS.php=			PKG_PHP_VERSION PKG_PHP PHPPKGSRCDIR PHP_PKG_PREFIX \
				PKG_PHP_MAJOR_VERS

.include "../../mk/bsd.prefs.mk"

PHP53_VERSION=			5.3.29
PHP54_VERSION=			5.4.45
PHP55_VERSION=			5.5.38
PHP56_VERSION=			5.6.30
PHP70_VERSION=			7.0.17
PHP71_VERSION=                  7.1.3

PHP_VERSION_DEFAULT?=		56
PHP_VERSIONS_ACCEPTED?=		54 53 55 56 70 71

# transform the list into individual variables
.for pv in ${PHP_VERSIONS_ACCEPTED}
_PHP_VERSION_${pv}_OK=		yes
.endfor

# check what is installed
.if exists(${LOCALBASE}/lib/php/20160303)
_PHP_VERSION_71_INSTALLED=      yes
_PHP_INSTALLED=                 yes
.elif exists(${LOCALBASE}/lib/php/20151012)
_PHP_VERSION_70_INSTALLED=	yes
_PHP_INSTALLED=			yes
.elif exists(${LOCALBASE}/lib/php/20131226)
_PHP_VERSION_56_INSTALLED=	yes
_PHP_INSTALLED=			yes
.elif exists(${LOCALBASE}/lib/php/20121212)
_PHP_VERSION_55_INSTALLED=	yes
_PHP_INSTALLED=			yes
.elif exists(${LOCALBASE}/lib/php/20100525)
_PHP_VERSION_54_INSTALLED=	yes
_PHP_INSTALLED=			yes
.elif exists(${LOCALBASE}/lib/php/20090626)
_PHP_VERSION_53_INSTALLED=	yes
_PHP_INSTALLED=			yes
.endif

# if a version is explicitely required, take it
.if defined(PHP_VERSION_REQD)
_PHP_VERSION=			${PHP_VERSION_REQD}
.endif
# if the default is already installed, it is first choice
.if !defined(_PHP_VERSION)
.if defined(_PHP_VERSION_${PHP_VERSION_DEFAULT}_OK)
.if defined(_PHP_VERSION_${PHP_VERSION_DEFAULT}_INSTALLED)
_PHP_VERSION=			${PHP_VERSION_DEFAULT}
.endif
.endif
.endif
# prefer an already installed version, in order of "accepted"
.if !defined(_PHP_VERSION)
.for pv in ${PHP_VERSIONS_ACCEPTED}
.if defined(_PHP_VERSION_${pv}_INSTALLED)
_PHP_VERSION?=			${pv}
.else
# keep information as last resort - see below
_PHP_VERSION_FIRSTACCEPTED?=	${pv}
.endif
.endfor
.endif
# if the default is OK for the addon pkg, take this
.if !defined(_PHP_VERSION)
.if defined(_PHP_VERSION_${PHP_VERSION_DEFAULT}_OK)
_PHP_VERSION=			${PHP_VERSION_DEFAULT}
.endif
.endif
# take the first one accepted by the package
.if !defined(_PHP_VERSION)
_PHP_VERSION=			${_PHP_VERSION_FIRSTACCEPTED}
.endif

#
# Variable assignment for multi-PHP packages
MULTI+=	PHP_VERSION_REQD=	${_PHP_VERSION}

# export some of internal variables
PKG_PHP_VERSION:=		${_PHP_VERSION:C/\.[0-9]//}
PKG_PHP:=			PHP${_PHP_VERSION:C/([0-9])([0-9])/\1.\2/}

# currently only 7.0 is not a PHP 5.x packages.
.if ${_PHP_VERSION} == "70" || ${_PHP_VERSION} == "71"
PKG_PHP_MAJOR_VERS:=		7
.else
PKG_PHP_MAJOR_VERS:=		5
.endif

# if installed PHP isn't compatible with required PHP, bail out
.if defined(_PHP_INSTALLED) && !defined(_PHP_VERSION_${_PHP_VERSION}_INSTALLED)
PKG_SKIP_REASON+=		"Package accepts ${PKG_PHP}, but different version is installed"
.endif

MESSAGE_SUBST+=			PKG_PHP_VERSION=${PKG_PHP_VERSION} \
				PKG_PHP=${PKG_PHP}
PLIST_SUBST+=			PKG_PHP_VERSION=${PKG_PHP_VERSION} \
				PKG_PHP_MAJOR_VERS=${PKG_PHP_MAJOR_VERS} \
				PHP_EXTENSION_DIR=${PHP_EXTENSION_DIR}

# force the selected PHP version for recursive builds
PHP_VERSION_REQD:=	${PKG_PHP_VERSION}

#
# set variables for the version we decided to use:
#
.if ${_PHP_VERSION} == "53"
PHPPKGSRCDIR=			../../base/php53
PHP_BASE_VERS=			${PHP53_VERSION}
PHP_NEXT_VERS=			5.4
PHP_PKG_PREFIX=			php53
.elif ${_PHP_VERSION} == "54"
PHPPKGSRCDIR=			../../base/php54
PHP_BASE_VERS=			${PHP54_VERSION}
PHP_NEXT_VERS=			5.5
PHP_PKG_PREFIX=			php54
.elif ${_PHP_VERSION} == "55"
PHPPKGSRCDIR=			../../base/php55
PHP_BASE_VERS=			${PHP55_VERSION}
PHP_NEXT_VERS=			5.6
PHP_PKG_PREFIX=			php55
.elif ${_PHP_VERSION} == "56"
PHPPKGSRCDIR=			../../base/php56
PHP_BASE_VERS=			${PHP56_VERSION}
PHP_NEXT_VERS=			5.7
PHP_PKG_PREFIX=			php56
.elif ${_PHP_VERSION} == "70"
PHPPKGSRCDIR=			../../base/php70
PHP_BASE_VERS=			${PHP70_VERSION}
PHP_NEXT_VERS=			7.1
PHP_PKG_PREFIX=			php70
.elif ${_PHP_VERSION} == "71"
PHPPKGSRCDIR=                   ../../base/php71
PHP_BASE_VERS=                  ${PHP71_VERSION}
PHP_NEXT_VERS=                  7.2
PHP_PKG_PREFIX=                 php71
.else
# force an error
PKG_SKIP_REASON+=		"${PKG_PHP} is not a valid package"
.endif

#
# check installed version aginst required:
#
.if defined(_PHP_VERSION_INSTALLED)
.if ${_PHP_VERSION} != ${_PHP_VERSION_INSTALLED}
PKG_SKIP_REASON+=		"${PKGBASE} requires ${PKG_PHP}, but php-${_PHP_VERSION_INSTALLED} is already installed."
.endif
.endif

.endif	# PHPVERSION_MK
