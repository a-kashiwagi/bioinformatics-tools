## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/lcs/ui
ui_DATA = lcs_gui.ui

LIBS = -pthread -lgthread-2.0 -lrt -lglib-2.0

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(LCS_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = lcs

lcs_SOURCES = \
	callbacks.c \
	callbacks.h \
	main.c \
	lcs.h \
	lcs.c \
	hmm.c \
	hmm_procedure.c \
	hmm.h

lcs_LDFLAGS = \
	-Wl,--export-dynamic

lcs_LDADD = $(LCS_LIBS)

EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/lcs
