$NetBSD$

--- src/syscall/syscall_solaris.go.orig	2018-02-16 17:12:19.000000000 +0000
+++ src/syscall/syscall_solaris.go
@@ -436,6 +436,7 @@ func SendmsgN(fd int, p, oob []byte, to
 //sys	Chroot(path string) (err error)
 //sys	Close(fd int) (err error)
 //sys	Dup(fd int) (nfd int, err error)
+//sys   Dup2(from int, to int) (err error)
 //sys	Fchdir(fd int) (err error)
 //sys	Fchmod(fd int, mode uint32) (err error)
 //sys	Fchown(fd int, uid int, gid int) (err error)
