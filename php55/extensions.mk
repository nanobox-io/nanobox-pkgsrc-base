# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

# PHP_BUNDLE_PATCH= 1

PHP_EXTENSION_LIST= dom filter hash json mbstring pdo session xml \
	igbinary imagick raphf propro \
	bcmath bz2 calendar ctype curl dba enchant exif fileinfo ftp gd \
	gettext gmp iconv imap intl ldap mcrypt mssql mysql mysqli opcache \
	pcntl pdo_dblib pdo_mysql pdo_odbc pdo_pgsql pdo_sqlite pgsql phar \
	posix pspell recode shmop simplexml snmp soap sockets sysvmsg \
	sysvsem sysvshm tidy tokenizer wddx xmlreader xmlrpc xmlwriter \
	xsl zip zlib \
	amqp apcu apfd apm gender geoip gnupg htscanner http ioncube_loader \
	json_post lzf magickwand memcache memcached mogilefs mongo mongodb \
	ncurses newrelic newt oauth phalcon phpwkhtmltox radius rar readline \
	redis sphinx ssh2 stats stomp svn timezonedb txforward uploadprogress \
	xcache xdebug yaml 