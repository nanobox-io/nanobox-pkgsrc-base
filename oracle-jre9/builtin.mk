# $NetBSD: builtin.mk,v 1.1 2015/05/30 09:49:43 ryoon Exp $

BUILTIN_PKG:=	oracle-jre9

BUILTIN_FIND_FILES_VAR:=	JAVAVM9
BUILTIN_FIND_FILES.JAVAVM9=	\
	/System/Library/Frameworks/JavaVM.framework/Versions/1.8/Home \
	/usr/jdk/instances/jdk1.8.0

.include "../../mk/buildlink3/bsd.builtin.mk"

###
### On Darwin, if a suitable JRE has not already been found, try to find
### it in the standard JRE location.  Normally, we would just add the
### standard JRE location path to BUILTIN_FIND_FILES.JAVAVM9 above, but
### unfortunately, the path contains a space, and the BUILTIN_FIND_FILES
### "subroutine" can't handle paths containing whitespace (because it
### iterates over the paths in a for-loop).  So, we perform the check by
### hand.
###
.if ${OPSYS} == "Darwin" && \
    !empty(JAVAVM9:M__nonexistent__)
_JRE_HOME=	\
	/Library/Internet Plug-Ins/JavaAppletPlugin.plugin/Contents/Home
.  if exists(${_JRE_HOME})
JAVAVM9=	${_JRE_HOME}
.  endif
.endif

###
### Determine if there is a built-in implementation of the package and
### set IS_BUILTIN.<pkg> appropriately ("yes" or "no").
###
.if !defined(IS_BUILTIN.oracle-jre9)
.  if empty(JAVAVM9:M__nonexistent__)
IS_BUILTIN.oracle-jre9=	yes
.  else
IS_BUILTIN.oracle-jre9=	no
.  endif
.endif
MAKEVARS+=	IS_BUILTIN.oracle-jre9

###
### If there is a built-in implementation, then set BUILTIN_PKG.<pkg> to
### a package name to represent the built-in package.
###
.if !defined(BUILTIN_PKG.oracle-jre9) && \
    !empty(IS_BUILTIN.oracle-jre9:M[yY][eE][sS]) && \
    empty(JAVAVM9:M__nonexistent__)

BUILTIN_VERSION.oracle-jre9!= ${JAVAVM9:Q}/bin/java -version 2>&1 | \
	${AWK} -F \" '{print $$2; exit}' | \
	${AWK} '{sub(/^1\./,"");sub(/_/,".");print $$1}'

BUILTIN_PKG.oracle-jre9=	oracle-jre9-${BUILTIN_VERSION.oracle-jre9}
.endif
MAKEVARS+=	BUILTIN_PKG.oracle-jre9

###
### Determine whether we should use the built-in implementation if it
### exists, and set USE_BUILTIN.<pkg> appropriate ("yes" or "no").
###
.if !defined(USE_BUILTIN.oracle-jre9)
.  if ${PREFER.oracle-jre9} == "pkgsrc"
USE_BUILTIN.oracle-jre9=	no
.  else
USE_BUILTIN.oracle-jre9=	${IS_BUILTIN.oracle-jre9}
.    if defined(BUILTIN_PKG.oracle-jre9) && \
        !empty(IS_BUILTIN.oracle-jre9:M[yY][eE][sS])
USE_BUILTIN.oracle-jre9=	yes
.      for _dep_ in ${BUILDLINK_API_DEPENDS.oracle-jre9}
.        if !empty(USE_BUILTIN.oracle-jre9:M[yY][eE][sS])
USE_BUILTIN.oracle-jre9!=						\
	if ${PKG_ADMIN} pmatch ${_dep_:Q} ${BUILTIN_PKG.oracle-jre9:Q}; then \
		${ECHO} yes;						\
	else								\
		${ECHO} no;						\
	fi
.        endif
.      endfor
.    endif
.  endif  # PREFER.oracle-jre9
.endif
MAKEVARS+=	USE_BUILTIN.oracle-jre9

###
### The section below only applies if we are not including this file
### solely to determine whether a built-in implementation exists.
###
CHECK_BUILTIN.oracle-jre9?=	no
.if !empty(CHECK_BUILTIN.oracle-jre9:M[nN][oO])
.  if !empty(USE_BUILTIN.oracle-jre9:M[yY][eE][sS])
PKG_JAVA_HOME=	${JAVAVM9}
.  endif
.endif
