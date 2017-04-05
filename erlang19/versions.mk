# $NetBSD: Makefile.versions,v 1.17 2013/10/20 18:37:49 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

ERLANG_VERSION=			19.2.1
DIST_VERSION_MAJOR=		19.2.1
#DIST_VERSION_MINOR=		1

_VERSIONS=				\
	asn1			4.0.4	\
	common_test		1.13	\
	compiler		7.0.3	\
	cosEvent		2.2.1	\
	cosEventDomain		1.2.1	\
	cosFileTransfer		1.2.1	\
	cosNotification		1.2.2	\
	cosProperty		1.2.1	\
	cosTime			1.2.2	\
	cosTransactions		1.3.2	\
	crypto			3.7.2	\
	debugger		4.2.1	\
	dialyzer		3.0.3	\
	diameter		1.12.1	\
	edoc			0.8.1	\
	eldap			1.2.2	\
	erl_docgen		0.6.1	\
	erl_interface		3.9.2	\
	erts			8.2.1	\
	et			1.6	\
	eunit			2.3.2	\
	gs			1.6.2	\
	hipe			3.15.3	\
	ic			4.4.2	\
	inets			6.3.4	\
	jinterface		1.7.1	\
	kernel			5.1.1	\
	megaco			3.18.1	\
	mnesia			4.14.2	\
	observer		2.3	\
	odbc			2.12	\
	orber			3.8.2	\
	os_mon			2.4.1	\
	otp_mibs		1.1.1	\
	parsetools		2.1.4	\
	percept			0.9	\
	public_key		1.3	\
	reltool			0.7.2	\
	runtime_tools		1.11	\
	sasl			3.0.2	\
	snmp			5.2.4	\
	ssh			4.4	\
	ssl			8.1	\
	stdlib			3.2	\
	syntax_tools		2.1.1	\
	tools			2.9	\
	typer			0.9.11	\
	wx			1.8	\
	xmerl			1.3.12

PLIST_SUBST+=	VERSION=${DIST_VERSION_MAJOR}

.for name version in ${_VERSIONS}
VERSION.${name}=${version}
PLIST_SUBST+=	VERSION.${name}=${version}
.endfor

# Generate PLIST
.for _pkg_ _version_ in $(_VERSIONS)
PRINT_PLIST_AWK+=	{if ($$0 ~ /\/$(_pkg_)-$(_version_)\//) {sub(/\/$(_pkg_)-$(_version_)\//,"/$(_pkg_)-$${VERSION.$(_pkg_)}/", $$0);}}
# documentation:
PRINT_PLIST_AWK+=	{gsub(/\/$(_pkg_)-$(_version_)\.pdf/,"/$(_pkg_)-$${VERSION.$(_pkg_)}.pdf", $$0);}
.endfor
PRINT_PLIST_AWK+=	{if ($$0 ~ /\/releases\/${DIST_VERSION_MAJOR}\//) {sub(/\/releases\/${DIST_VERSION_MAJOR}\//,"/releases/$${VERSION}/", $$0);}}
# documentation:
PRINT_PLIST_AWK+=	{gsub(/\/otp-system-documentation-$(VERSION.erts)\.pdf/,"/otp-system-documentation-$${VERSION.erts}.pdf", $$0);}
