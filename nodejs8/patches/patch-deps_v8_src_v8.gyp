$NetBSD$

--- deps/v8/src/v8.gyp.orig	2017-08-15 16:42:33.000000000 +0000
+++ deps/v8/src/v8.gyp
@@ -2375,14 +2375,14 @@
                       '<(PRODUCT_DIR)/natives_blob_host.bin',
                     ],
                     'action': [
-                      'python', '<@(_inputs)', '<(PRODUCT_DIR)/natives_blob_host.bin'
+                      '@PYTHONBIN@', '<@(_inputs)', '<(PRODUCT_DIR)/natives_blob_host.bin'
                     ],
                   }, {
                     'outputs': [
                       '<(PRODUCT_DIR)/natives_blob.bin',
                     ],
                     'action': [
-                      'python', '<@(_inputs)', '<(PRODUCT_DIR)/natives_blob.bin'
+                      '@PYTHONBIN@', '<@(_inputs)', '<(PRODUCT_DIR)/natives_blob.bin'
                     ],
                   }],
                 ],
@@ -2391,7 +2391,7 @@
                   '<(PRODUCT_DIR)/natives_blob.bin',
                 ],
                 'action': [
-                  'python', '<@(_inputs)', '<(PRODUCT_DIR)/natives_blob.bin'
+                  '@PYTHONBIN@', '<@(_inputs)', '<(PRODUCT_DIR)/natives_blob.bin'
                 ],
               }],
             ],
@@ -2454,7 +2454,7 @@
           ],
           'outputs': ['<(SHARED_INTERMEDIATE_DIR)/libraries.cc'],
           'action': [
-            'python',
+            '@PYTHONBIN@',
             '../tools/js2c.py',
             '<(SHARED_INTERMEDIATE_DIR)/libraries.cc',
             'CORE',
@@ -2469,7 +2469,7 @@
           ],
           'outputs': ['<@(libraries_bin_file)'],
           'action': [
-            'python',
+            '@PYTHONBIN@',
             '../tools/js2c.py',
             '<(SHARED_INTERMEDIATE_DIR)/libraries.cc',
             'CORE',
@@ -2486,7 +2486,7 @@
           ],
           'outputs': ['<(SHARED_INTERMEDIATE_DIR)/extras-libraries.cc'],
           'action': [
-            'python',
+            '@PYTHONBIN@',
             '../tools/js2c.py',
             '<(SHARED_INTERMEDIATE_DIR)/extras-libraries.cc',
             'EXTRAS',
@@ -2501,7 +2501,7 @@
           ],
           'outputs': ['<@(libraries_extras_bin_file)'],
           'action': [
-            'python',
+            '@PYTHONBIN@',
             '../tools/js2c.py',
             '<(SHARED_INTERMEDIATE_DIR)/extras-libraries.cc',
             'EXTRAS',
@@ -2520,7 +2520,7 @@
             '<(SHARED_INTERMEDIATE_DIR)/experimental-extras-libraries.cc',
           ],
           'action': [
-            'python',
+            '@PYTHONBIN@',
             '../tools/js2c.py',
             '<(SHARED_INTERMEDIATE_DIR)/experimental-extras-libraries.cc',
             'EXPERIMENTAL_EXTRAS',
@@ -2535,7 +2535,7 @@
           ],
           'outputs': ['<@(libraries_experimental_extras_bin_file)'],
           'action': [
-            'python',
+            '@PYTHONBIN@',
             '../tools/js2c.py',
             '<(SHARED_INTERMEDIATE_DIR)/experimental-extras-libraries.cc',
             'EXPERIMENTAL_EXTRAS',
@@ -2568,7 +2568,7 @@
               '<(SHARED_INTERMEDIATE_DIR)/debug-support.cc',
             ],
             'action': [
-              'python',
+              '@PYTHONBIN@',
               '../tools/gen-postmortem-metadata.py',
               '<@(_outputs)',
               '<@(heapobject_files)'
