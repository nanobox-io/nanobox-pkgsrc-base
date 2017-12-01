# $NetBSD: builtin.mk,v 1.1 2015/05/30 09:51:11 ryoon Exp $

BUILTIN_PKG:=	oracle-jdk9

BUILTIN_FIND_FILES_VAR:=	JDK9
BUILTIN_FIND_FILES.JDK9=	\
	/System/Library/Frameworks/JavaVM.framework/Versions/1.9/Commands/javac\
	/usr/jdk/instances/jdk1.9.0/bin/javac

###
### On Darwin, there are no 1.9 symlinks that would enable us to find a
### 1.9 JDK.  Instead, the best method is to use the java_home system
### program to find the default 1.9 JDK if it exists.
###
.if ${OPSYS} == "Darwin"
_JAVA_HOME_ANSWER!=	\
	if [ -x /usr/libexec/java_home ]; then \
		result=`/usr/libexec/java_home -v 1.9 2> /dev/null`; \
		if [ $$? -eq 0 ]; then \
			echo "$$result"; \
		else \
			echo; \
		fi; \
	fi
BUILTIN_FIND_FILES.JDK9+=	${_JAVA_HOME_ANSWER}/bin/javac
.endif

.include "../../mk/buildlink3/bsd.builtin.mk"

###
### Determine if there is a built-in implementation of the package and
### set IS_BUILTIN.<pkg> appropriately ("yes" or "no").
###
.if !defined(IS_BUILTIN.oracle-jdk9)
.  if empty(JDK9:M__nonexistent__)
IS_BUILTIN.oracle-jdk9=	yes
.  else
IS_BUILTIN.oracle-jdk9=	no
.  endif
.endif
MAKEVARS+=	IS_BUILTIN.oracle-jdk9

###
### If there is a built-in implementation, then set BUILTIN_PKG.<pkg> to
### a package name to represent the built-in package.
###
.if !defined(BUILTIN_PKG.oracle-jdk9) && \
    !empty(IS_BUILTIN.oracle-jdk9:M[yY][eE][sS]) && \
    empty(JDK9:M__nonexistent__)

BUILTIN_VERSION.oracle-jdk9!= ${JDK9} -version 2>&1 | \
	${AWK} '{print $$2; exit}' | \
	${AWK} '{sub(/^1\./,"");sub(/_/,".");print $$1}'

BUILTIN_PKG.oracle-jdk9=	oracle-jdk9-${BUILTIN_VERSION.oracle-jdk9}
.endif
MAKEVARS+=	BUILTIN_PKG.oracle-jdk9

###
### Determine whether we should use the built-in implementation if it
### exists, and set USE_BUILTIN.<pkg> appropriate ("yes" or "no").
###
.if !defined(USE_BUILTIN.oracle-jdk9)
.  if ${PREFER.oracle-jdk9} == "pkgsrc"
USE_BUILTIN.oracle-jdk9=	no
.  else
USE_BUILTIN.oracle-jdk9=	${IS_BUILTIN.oracle-jdk9}
.    if defined(BUILTIN_PKG.oracle-jdk9) && \
        !empty(IS_BUILTIN.oracle-jdk9:M[yY][eE][sS])
USE_BUILTIN.oracle-jdk9=	yes
.      for _dep_ in ${BUILDLINK_API_DEPENDS.oracle-jdk9}
.        if !empty(USE_BUILTIN.oracle-jdk9:M[yY][eE][sS])
USE_BUILTIN.oracle-jdk9!=						\
	if ${PKG_ADMIN} pmatch ${_dep_:Q} ${BUILTIN_PKG.oracle-jdk9:Q}; then \
		${ECHO} yes;						\
	else								\
		${ECHO} no;						\
	fi
.        endif
.      endfor
.    endif
.  endif  # PREFER.oracle-jdk9
.endif
