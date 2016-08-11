# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

# PHP_BUNDLE_PATCH= 1

PHP_EXTENSION_LIST= dom filter hash json mbstring pdo session xml \
	igbinary propro \
	bcmath bz2 calendar ctype curl dba enchant exif fileinfo ftp gd \
	gettext gmp iconv imap intl ldap mcrypt mysqli opcache \
	pcntl pdo_dblib pdo_mysql pdo_odbc pdo_pgsql pdo_sqlite pgsql phar \
	posix pspell recode shmop simplexml snmp soap sockets sysvmsg \
	sysvsem sysvshm tidy tokenizer wddx xmlreader xmlrpc xmlwriter \
	xsl zip zlib \
	amqp apcu apfd apm gender http imagick json_post lzf memcached mogilefs mongodb newrelic oauth readline redis ssh2 stats stomp timezonedb xdebug