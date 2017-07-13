# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet
# This file provides simple access to svn repositories, so that packages
# can be created from svn instead of from released tarballs.
#
# A package using this file shall define the following variables:
#
#	SVN_REPOSITORIES
#		A list of unique identifiers /id/ for which appropriate
#		SVN_REPO must be defined.
#
#	SVN_REPO.${id}
#		The svn repository
#
# It may define the following variables:
#
#	SVN_BRANCH.${id}
#		The branch to check out.

.if !defined(_PKG_MK_SVN_PACKAGE_MK)
_PKG_MK_SVN_PACKAGE_MK=	# defined

BUILD_DEPENDS+=         subversion-base>=1.9.5:../../devel/subversion-base

#
# defaults for user-visible input variables
#

DISTFILES?=		# empty
PKGREVISION?=		${_SVN_PKGVERSION:S/.//g}

#
# End of the interface part. Start of the implementation part.
#

#
# Input validation
#

.if !defined(SVN_REPOSITORIES)
PKG_FAIL_REASON+=	"[svn-package.mk] SVN_REPOSITORIES must be set."
SVN_REPOSITORIES?=	# none
.endif

.for _repo_ in ${SVN_REPOSITORIES}
.  if !defined(SVN_REPO.${_repo_})
PKG_FAIL_REASON+=	"[svn-package.mk] SVN_REPO."${_repo_:Q}" must be set."
.  endif
.endfor

#
# Internal variables
#

USE_TOOLS+=		date pax

_SVN_CMD=		svn
_SVN_PKGVERSION_CMD=	${DATE} -u +'%Y.%m.%d'
_SVN_PKGVERSION=	${_SVN_PKGVERSION_CMD:sh}
_SVN_DISTDIR=		${DISTDIR}/svn-packages

#
# Generation of repository-specific variables


.for repo in ${SVN_REPOSITORIES}
SVN_MODULE.${repo}?=	${repo}
_SVN_ENV.${repo}=	${SVN_ENV.${repo}}

# determine appropriate checkout branch or tag
.  if defined(SVN_BRANCH.${repo})
_SVN_DISTFILE.${repo}=  ${PKGBASE}-${SVN_MODULE.${repo}}-${SVN_BRANCH.${repo}}-${_SVN_PKGVERSION}.tar.gz
.  elif defined(SVN_REVISION.${repo})
_SVN_DISTFILE.${repo}=  ${PKGBASE}-${SVN_MODULE.${repo}}-${SVN_REVISION.${repo}}.tar.gz
.  elif defined(SVN_TAG.${repo})
_SVN_PKGVERSION=	# none
_SVN_DISTFILE.${repo}=  ${PKGBASE}-${SVN_MODULE.${repo}}-${SVN_TAG.${repo}}.tar.gz
.  endif


# Cache support:
#   cache file name
_SVN_DISTFILE.${repo}?=	${PKGBASE}-${SVN_MODULE.${repo}}-svnarchive.tar.gz

#   command to extract cache file
_SVN_EXTRACT_CACHED.${repo}=	\
	if [ -f ${_SVN_DISTDIR}/${_SVN_DISTFILE.${repo}:Q} ]; then		\
	  ${STEP_MSG} "Extracting cached SVN archive "${_SVN_DISTFILE.${repo}:Q}"."; \
	  gzip -d -c ${_SVN_DISTDIR}/${_SVN_DISTFILE.${repo}:Q} | pax -r;	\
	fi

#   create cache archive
_SVN_CREATE_CACHE.${repo}=	\
	${STEP_MSG} "Creating cached SVN archive "${_SVN_DISTFILE.${repo}:Q}"."; \
	${MKDIR} ${_SVN_DISTDIR:Q};					\
	pax -w ${SVN_MODULE.${repo}:Q} | gzip > ${_SVN_DISTDIR}/${_SVN_DISTFILE.${repo}:Q}.tmp;	\
	${MV} '${_SVN_DISTDIR}/${_SVN_DISTFILE.${repo}:Q}.tmp' '${_SVN_DISTDIR}/${_SVN_DISTFILE.${repo}:Q}'

#   fetch svn repo or update cached one
_SVN_FETCH_REPO.${repo}=	\
	if [ ! -d ${SVN_MODULE.${repo}:Q} ]; then				\
	  ${STEP_MSG} "Cloning SVN archive "${SVN_MODULE.${repo}:Q}".";		\
	  ${SETENV} ${_SVN_ENV.${repo}} ${_SVN_CMD}				\
	    co ${SVN_REPO.${repo}}/${SVN_BRANCH.${repo}}					\
	    ${SVN_MODULE.${repo}:Q};			\
	fi
.endfor

pre-extract: do-svn-extract

.PHONY: do-svn-extract
do-svn-extract:
.for _repo_ in ${SVN_REPOSITORIES}
	${RUN} cd ${WRKDIR};							\
	if [ ! -d ${_SVN_DISTDIR:Q} ]; then mkdir -p ${_SVN_DISTDIR:Q}; fi;	\
	${_SVN_EXTRACT_CACHED.${_repo_}};					\
	${_SVN_FETCH_REPO.${_repo_}};						\
	${_SVN_CREATE_CACHE.${_repo_}};

.endfor

.PHONY: clean-distfiles

clean-distfiles: clean
.for _repo_ in ${SVN_REPOSITORIES}
	if [ -f ${_SVN_DISTDIR}/${_SVN_DISTFILE.${_repo_}:Q} ]; then ${RM} ${_SVN_DISTDIR}/${_SVN_DISTFILE.${_repo_}:Q}; fi
.endfor

.endif
