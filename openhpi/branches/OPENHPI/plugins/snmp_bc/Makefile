# Makefile.in generated by automake 1.6.3 from Makefile.am.
# plugins/snmp_bc/Makefile.  Generated from Makefile.in by configure.

# Copyright 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
# Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



# (C) Copyright IBM Corp 2003, 2004
# All rights reserved.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  This
# file and program are licensed under a BSD style license.  See
# the Copying file included with the OpenHPI distribution for
# full licensing terms.
SHELL = /bin/sh

srcdir = .
top_srcdir = ../..

prefix = /usr/local
exec_prefix = /usr/local

bindir = /usr/local/bin
sbindir = /usr/local/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = /usr/local/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = /usr/local/include
oldincludedir = /usr/include
pkgdatadir = $(datadir)/openhpi
pkglibdir = $(libdir)/openhpi
pkgincludedir = $(includedir)/openhpi
top_builddir = ../..

ACLOCAL = ${SHELL} /home/louis/HPI/openhpi/missing --run aclocal-1.6
AUTOCONF = ${SHELL} /home/louis/HPI/openhpi/missing --run autoconf
AUTOMAKE = ${SHELL} /home/louis/HPI/openhpi/missing --run automake-1.6
AUTOHEADER = ${SHELL} /home/louis/HPI/openhpi/missing --run autoheader

am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
INSTALL = /bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_SCRIPT = ${INSTALL}
INSTALL_HEADER = $(INSTALL_DATA)
transform = s,x,x,
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = 
host_triplet = i686-pc-linux-gnu

EXEEXT = 
OBJEXT = o
PATH_SEPARATOR = :
AMTAR = ${SHELL} /home/louis/HPI/openhpi/missing --run tar
AS = @AS@
AWK = gawk
CC = gcc
CPP = gcc -E
CXX = g++
DEPDIR = .deps
DLLTOOL = @DLLTOOL@
DUMMY = dummy
ECHO = echo
ENABLED_DIRS =  examples util
HPI_LIB_VERSION = 3:0:3
HPI_PKG = openhpi
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
IPMI = ipmi
IPMIDIRECT = ipmidirect
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIST_RESOURCES_THREADED = list_resources_threaded
LN_S = ln -s
NOCFLAGS = -g  -I/usr/include/glib-1.2 -I/usr/lib/glib/include -Wall -Wmissing-prototypes -Wmissing-declarations -Wstrict-prototypes -Wpointer-arith -Wformat=2 -Wformat-security -Wformat-nonliteral -Werror -Wcast-qual -Wcast-align -D_GNU_SOURCE -D_REENTRANT -fexceptions
NOCXXFLAGS = -g  -I/usr/include/glib-1.2 -I/usr/lib/glib/include -Wall -Wmissing-prototypes -Wstrict-prototypes -Wpointer-arith -Werror -Wcast-qual -Wcast-align -Wshadow -Wwrite-strings -Wredundant-decls -D_GNU_SOURCE -D_REENTRANT -fexceptions
OBJDUMP = @OBJDUMP@
PACKAGE = openhpi
RANLIB = ranlib
RPM = 
SIMULATOR = simulator
SNMPDIR = snmp
SNMPFLAGS =  -march=i686 -funroll-loops -pipe -Dlinux -I. -I/usr/include
SNMPLIBS = -L/usr/lib -lnetsnmp -lcrypto -lm
SNMP_BC = snmp_bc
SNMP_CLIENT = snmp_client
SSL_LIB = -lssl
STATIC_PLUGIN = 
STATIC_PLUGIN_EXTERN = 
STATIC_PLUGIN_EXTRA_LIBS = 
STATIC_PLUGIN_LIBS = 
STRIP = strip
SYSFS = 
TEST_CLEAN = $(shell ls *.bb* *.da *.gcov *.summary)
VARPATH = /var/lib/openhpi
VERSION = 0.5.0
WATCHDOG = watchdog
ac_configure_args =  'CC=gcc' 'CXX=g++'
am__include = include
am__quote = 
base_includedir = /usr/local/include
found_pkg_config = yes
install_sh = /home/louis/HPI/openhpi/install-sh

MAINTAINERCLEANFILES = Makefile.in

MOSTLYCLEANFILES = $(shell ls *.bb* *.da *.gcov *.summary)

SNMPUTILSDIR = $(top_srcdir)/src/$(SNMPDIR)
SNMPUTILBDIR = $(top_builddir)/src/$(SNMPDIR)

SUBDIRS = t

INCLUDES = -I$(top_srcdir)/include -I$(SNMPUTILSDIR)

AM_CFLAGS = -g -O2 -I/usr/include/glib-1.2 -I/usr/lib/glib/include           -Wall         -Wmissing-prototypes 	-Wmissing-declarations 	-Wstrict-prototypes 	-Wpointer-arith         -Wformat=2         -Wformat-security         -Wformat-nonliteral 	-Werror 	-Wcast-qual 	-Wcast-align -D_GNU_SOURCE -D_REENTRANT -fexceptions  -march=i686 -funroll-loops -pipe -Dlinux -I. -I/usr/include

pkglib_LTLIBRARIES = libsnmp_bc.la

EXTRA_DIST = bc_errorlog.h \
				bc_resources.h \
				bc_str2event.h \
				snmp_bc.h \
				snmp_bc_control.h \
				snmp_bc_event.h \
	     			snmp_bc_discover.h \
				snmp_bc_hotswap.h \
	     			snmp_bc_sel.h \
				snmp_bc_time.h \
				snmp_bc_sensor.h \
				snmp_bc_session.h \
				snmp_bc_utils.h \
				snmp_bc_inventory.h \
				snmp_bc_watchdog.h


libsnmp_bc_la_SOURCES = bc_resources.c \
				bc_str2event.c \
				snmp_bc.c \
				snmp_bc_control.c \
				snmp_bc_event.c \
	     			snmp_bc_discover.c \
				snmp_bc_hotswap.c \
	     			snmp_bc_sel.c \
				snmp_bc_sensor.c \
				snmp_bc_session.c \
				snmp_bc_utils.c \
				snmp_bc_inventory.c \
				snmp_bc_watchdog.c


libsnmp_bc_la_LIBADD = -luuid -L/usr/lib -lnetsnmp -lcrypto -lm $(SNMPUTILBDIR)/libsnmp_util.la
libsnmp_bc_la_LDFLAGS = -avoid-version
subdir = plugins/snmp_bc
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
LTLIBRARIES = $(pkglib_LTLIBRARIES)

libsnmp_bc_la_DEPENDENCIES = $(SNMPUTILBDIR)/libsnmp_util.la
am_libsnmp_bc_la_OBJECTS = bc_resources.lo bc_str2event.lo snmp_bc.lo \
	snmp_bc_control.lo snmp_bc_event.lo snmp_bc_discover.lo \
	snmp_bc_hotswap.lo snmp_bc_sel.lo snmp_bc_sensor.lo \
	snmp_bc_session.lo snmp_bc_utils.lo snmp_bc_inventory.lo \
	snmp_bc_watchdog.lo
libsnmp_bc_la_OBJECTS = $(am_libsnmp_bc_la_OBJECTS)

DEFS = -DHAVE_CONFIG_H
DEFAULT_INCLUDES =  -I. -I$(srcdir) -I$(top_builddir)
CPPFLAGS = 
LDFLAGS = 
LIBS = -lltdl  -lglib   -lm -lpthread
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__depfiles_maybe = depfiles
DEP_FILES = ./$(DEPDIR)/bc_resources.Plo \
	./$(DEPDIR)/bc_str2event.Plo \
	./$(DEPDIR)/snmp_bc.Plo \
	./$(DEPDIR)/snmp_bc_control.Plo \
	./$(DEPDIR)/snmp_bc_discover.Plo \
	./$(DEPDIR)/snmp_bc_event.Plo \
	./$(DEPDIR)/snmp_bc_hotswap.Plo \
	./$(DEPDIR)/snmp_bc_inventory.Plo \
	./$(DEPDIR)/snmp_bc_sel.Plo \
	./$(DEPDIR)/snmp_bc_sensor.Plo \
	./$(DEPDIR)/snmp_bc_session.Plo \
	./$(DEPDIR)/snmp_bc_utils.Plo \
	./$(DEPDIR)/snmp_bc_watchdog.Plo
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) --mode=compile $(CC) $(DEFS) $(DEFAULT_INCLUDES) \
	$(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(LIBTOOL) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
CFLAGS = -g -O2 -I/usr/include/glib-1.2 -I/usr/lib/glib/include           -Wall         -Wmissing-prototypes 	-Wmissing-declarations 	-Wstrict-prototypes 	-Wpointer-arith         -Wformat=2         -Wformat-security         -Wformat-nonliteral 	-Werror 	-Wcast-qual 	-Wcast-align -D_GNU_SOURCE -D_REENTRANT -fexceptions
DIST_SOURCES = $(libsnmp_bc_la_SOURCES)

RECURSIVE_TARGETS = info-recursive dvi-recursive install-info-recursive \
	uninstall-info-recursive all-recursive install-data-recursive \
	install-exec-recursive installdirs-recursive install-recursive \
	uninstall-recursive check-recursive installcheck-recursive
DIST_COMMON = Makefile.am Makefile.in
DIST_SUBDIRS = $(SUBDIRS)
SOURCES = $(libsnmp_bc_la_SOURCES)

all: all-recursive

.SUFFIXES:
.SUFFIXES: .c .lo .o .obj
$(srcdir)/Makefile.in:  Makefile.am  $(top_srcdir)/configure.ac $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --foreign  plugins/snmp_bc/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)
pkglibLTLIBRARIES_INSTALL = $(INSTALL)
install-pkglibLTLIBRARIES: $(pkglib_LTLIBRARIES)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(pkglibdir)
	@list='$(pkglib_LTLIBRARIES)'; for p in $$list; do \
	  if test -f $$p; then \
	    f="`echo $$p | sed -e 's|^.*/||'`"; \
	    echo " $(LIBTOOL) --mode=install $(pkglibLTLIBRARIES_INSTALL) $(INSTALL_STRIP_FLAG) $$p $(DESTDIR)$(pkglibdir)/$$f"; \
	    $(LIBTOOL) --mode=install $(pkglibLTLIBRARIES_INSTALL) $(INSTALL_STRIP_FLAG) $$p $(DESTDIR)$(pkglibdir)/$$f; \
	  else :; fi; \
	done

uninstall-pkglibLTLIBRARIES:
	@$(NORMAL_UNINSTALL)
	@list='$(pkglib_LTLIBRARIES)'; for p in $$list; do \
	    p="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(pkglibdir)/$$p"; \
	  $(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(pkglibdir)/$$p; \
	done

clean-pkglibLTLIBRARIES:
	-test -z "$(pkglib_LTLIBRARIES)" || rm -f $(pkglib_LTLIBRARIES)
	@list='$(pkglib_LTLIBRARIES)'; for p in $$list; do \
	  dir="`echo $$p | sed -e 's|/[^/]*$$||'`"; \
	  test -z "$dir" && dir=.; \
	  echo "rm -f \"$${dir}/so_locations\""; \
	  rm -f "$${dir}/so_locations"; \
	done
libsnmp_bc.la: $(libsnmp_bc_la_OBJECTS) $(libsnmp_bc_la_DEPENDENCIES) 
	$(LINK) -rpath $(pkglibdir) $(libsnmp_bc_la_LDFLAGS) $(libsnmp_bc_la_OBJECTS) $(libsnmp_bc_la_LIBADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT) core *.core

distclean-compile:
	-rm -f *.tab.c

include ./$(DEPDIR)/bc_resources.Plo
include ./$(DEPDIR)/bc_str2event.Plo
include ./$(DEPDIR)/snmp_bc.Plo
include ./$(DEPDIR)/snmp_bc_control.Plo
include ./$(DEPDIR)/snmp_bc_discover.Plo
include ./$(DEPDIR)/snmp_bc_event.Plo
include ./$(DEPDIR)/snmp_bc_hotswap.Plo
include ./$(DEPDIR)/snmp_bc_inventory.Plo
include ./$(DEPDIR)/snmp_bc_sel.Plo
include ./$(DEPDIR)/snmp_bc_sensor.Plo
include ./$(DEPDIR)/snmp_bc_session.Plo
include ./$(DEPDIR)/snmp_bc_utils.Plo
include ./$(DEPDIR)/snmp_bc_watchdog.Plo

distclean-depend:
	-rm -rf ./$(DEPDIR)

.c.o:
	source='$<' object='$@' libtool=no \
	depfile='$(DEPDIR)/$*.Po' tmpdepfile='$(DEPDIR)/$*.TPo' \
	$(CCDEPMODE) $(depcomp) \
	$(COMPILE) -c `test -f '$<' || echo '$(srcdir)/'`$<

.c.obj:
	source='$<' object='$@' libtool=no \
	depfile='$(DEPDIR)/$*.Po' tmpdepfile='$(DEPDIR)/$*.TPo' \
	$(CCDEPMODE) $(depcomp) \
	$(COMPILE) -c `cygpath -w $<`

.c.lo:
	source='$<' object='$@' libtool=yes \
	depfile='$(DEPDIR)/$*.Plo' tmpdepfile='$(DEPDIR)/$*.TPlo' \
	$(CCDEPMODE) $(depcomp) \
	$(LTCOMPILE) -c -o $@ `test -f '$<' || echo '$(srcdir)/'`$<
CCDEPMODE = depmode=gcc3

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool
uninstall-info-am:

# This directory's subdirectories are mostly independent; you can cd
# into them and run `make' without going through this Makefile.
# To change the values of `make' variables: instead of editing Makefiles,
# (1) if the variable is set in `config.status', edit `config.status'
#     (which will cause the Makefiles to be regenerated when you run `make');
# (2) otherwise, pass the desired values on the `make' command line.
$(RECURSIVE_TARGETS):
	@set fnord $$MAKEFLAGS; amf=$$2; \
	dot_seen=no; \
	target=`echo $@ | sed s/-recursive//`; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  echo "Making $$target in $$subdir"; \
	  if test "$$subdir" = "."; then \
	    dot_seen=yes; \
	    local_target="$$target-am"; \
	  else \
	    local_target="$$target"; \
	  fi; \
	  (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$local_target) \
	   || case "$$amf" in *=*) exit 1;; *k*) fail=yes;; *) exit 1;; esac; \
	done; \
	if test "$$dot_seen" = "no"; then \
	  $(MAKE) $(AM_MAKEFLAGS) "$$target-am" || exit 1; \
	fi; test -z "$$fail"

mostlyclean-recursive clean-recursive distclean-recursive \
maintainer-clean-recursive:
	@set fnord $$MAKEFLAGS; amf=$$2; \
	dot_seen=no; \
	case "$@" in \
	  distclean-* | maintainer-clean-*) list='$(DIST_SUBDIRS)' ;; \
	  *) list='$(SUBDIRS)' ;; \
	esac; \
	rev=''; for subdir in $$list; do \
	  if test "$$subdir" = "."; then :; else \
	    rev="$$subdir $$rev"; \
	  fi; \
	done; \
	rev="$$rev ."; \
	target=`echo $@ | sed s/-recursive//`; \
	for subdir in $$rev; do \
	  echo "Making $$target in $$subdir"; \
	  if test "$$subdir" = "."; then \
	    local_target="$$target-am"; \
	  else \
	    local_target="$$target"; \
	  fi; \
	  (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$local_target) \
	   || case "$$amf" in *=*) exit 1;; *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"
tags-recursive:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  test "$$subdir" = . || (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) tags); \
	done

ETAGS = etags
ETAGSFLAGS =

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	mkid -fID $$unique

TAGS: tags-recursive $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test "$$subdir" = .; then :; else \
	    test -f $$subdir/TAGS && tags="$$tags -i $$here/$$subdir/TAGS"; \
	  fi; \
	done; \
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$tags$$unique" \
	  || $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	     $$tags $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && cd $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) $$here

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ../..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	@list='$(DISTFILES)'; for file in $$list; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    dir="/$$dir"; \
	    $(mkinstalldirs) "$(distdir)$$dir"; \
	  else \
	    dir=''; \
	  fi; \
	  if test -d $$d/$$file; then \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -pR $(srcdir)/$$file $(distdir)$$dir || exit 1; \
	    fi; \
	    cp -pR $$d/$$file $(distdir)$$dir || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test "$$subdir" = .; then :; else \
	    test -d $(distdir)/$$subdir \
	    || mkdir $(distdir)/$$subdir \
	    || exit 1; \
	    (cd $$subdir && \
	      $(MAKE) $(AM_MAKEFLAGS) \
	        top_distdir="$(top_distdir)" \
	        distdir=../$(distdir)/$$subdir \
	        distdir) \
	      || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-recursive
all-am: Makefile $(LTLIBRARIES)
installdirs: installdirs-recursive
installdirs-am:
	$(mkinstalldirs) $(DESTDIR)$(pkglibdir)

install: install-recursive
install-exec: install-exec-recursive
install-data: install-data-recursive
uninstall: uninstall-recursive

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-recursive
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  INSTALL_STRIP_FLAG=-s \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:
	-test -z "$(MOSTLYCLEANFILES)" || rm -f $(MOSTLYCLEANFILES)

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
	-test -z "$(MAINTAINERCLEANFILES)" || rm -f $(MAINTAINERCLEANFILES)
clean: clean-recursive

clean-am: clean-generic clean-libtool clean-pkglibLTLIBRARIES \
	mostlyclean-am

distclean: distclean-recursive

distclean-am: clean-am distclean-compile distclean-depend \
	distclean-generic distclean-libtool distclean-tags

dvi: dvi-recursive

dvi-am:

info: info-recursive

info-am:

install-data-am:

install-exec-am: install-pkglibLTLIBRARIES

install-info: install-info-recursive

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-recursive

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-recursive

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

uninstall-am: uninstall-info-am uninstall-pkglibLTLIBRARIES

uninstall-info: uninstall-info-recursive

.PHONY: $(RECURSIVE_TARGETS) GTAGS all all-am check check-am clean \
	clean-generic clean-libtool clean-pkglibLTLIBRARIES \
	clean-recursive distclean distclean-compile distclean-depend \
	distclean-generic distclean-libtool distclean-recursive \
	distclean-tags distdir dvi dvi-am dvi-recursive info info-am \
	info-recursive install install-am install-data install-data-am \
	install-data-recursive install-exec install-exec-am \
	install-exec-recursive install-info install-info-am \
	install-info-recursive install-man install-pkglibLTLIBRARIES \
	install-recursive install-strip installcheck installcheck-am \
	installdirs installdirs-am installdirs-recursive \
	maintainer-clean maintainer-clean-generic \
	maintainer-clean-recursive mostlyclean mostlyclean-compile \
	mostlyclean-generic mostlyclean-libtool mostlyclean-recursive \
	tags tags-recursive uninstall uninstall-am uninstall-info-am \
	uninstall-info-recursive uninstall-pkglibLTLIBRARIES \
	uninstall-recursive

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
