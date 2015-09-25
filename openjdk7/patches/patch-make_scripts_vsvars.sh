$NetBSD$

--- make/scripts/vsvars.sh.orig	2015-01-26 15:21:23.000000000 +0000
+++ make/scripts/vsvars.sh
@@ -282,7 +282,7 @@ set -e
 # Different systems have different awk's
 if [ -f /usr/bin/nawk ] ; then
   awk="nawk"
-elif [ -f /usr/bin/gawk ] ; then
+elif [ -f @PREFIX@/bin/gawk ] ; then
   awk="gawk"
 else
   awk="awk"
