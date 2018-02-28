# $NetBSD: Makefile.versions,v 1.17 2013/10/20 18:37:49 asau Exp $
# -*- mode: makefile; tab-width: 8; indent-tabs-mode: 1 -*-
# vim: ts=8 sw=8 ft=make noet

ERLANG_VERSION=			20.2.2
DIST_VERSION_MAJOR=		20
#DIST_VERSION_MINOR=		1

_VERSIONS=				\
	asn1			5.0.4	\
	common_test		1.15.3	\
	compiler		7.1.4	\
	cosEvent		2.2.2	\
	cosEventDomain		1.2.2	\
	cosFileTransfer		1.2.2	\
	cosNotification		1.2.3	\
	cosProperty		1.2.3	\
	cosTime			1.2.3	\
	cosTransactions		1.3.3	\
	crypto			4.2	\
	debugger		4.2.4	\
	dialyzer		3.2.3	\
	diameter		2.1.3	\
	edoc			0.9.2	\
	eldap			1.2.3	\
	erl_docgen		0.7.2	\
	erl_interface		3.10.1	\
	erts			9.2	\
	et			1.6.1	\
	eunit			2.3.5	\
	gs			1.6.2	\
	hipe			3.17	\
	ic			4.4.3	\
	inets			6.4.5	\
	jinterface		1.8.1	\
	kernel			5.4.1	\
	megaco			3.18.3	\
	mnesia			4.15.3	\
	observer		2.6	\
	odbc			2.12.1	\
	orber			3.8.4	\
	os_mon			2.4.4	\
	otp_mibs		1.1.2	\
	parsetools		2.1.6	\
	percept			0.9	\
	public_key		1.5.2	\
	reltool			0.7.5	\
	runtime_tools		1.12.3	\
	sasl			3.1.1	\
	snmp			5.2.9	\
	ssh			4.6.4	\
	ssl			8.2.3	\
	stdlib			3.4.3	\
	syntax_tools		2.1.4	\
	tools			2.11.1	\
	typer			0.9.12	\
	wx			1.8.3	\
	xmerl			1.3.16

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
