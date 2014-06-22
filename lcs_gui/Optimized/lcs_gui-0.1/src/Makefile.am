## Process this file with automake to produce Makefile.in

## Created by Anjuta

uidir = $(datadir)/lcs_gui/ui
ui_DATA = lcs_gui.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	$(LCS_GUI_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = lcs_gui

lcs_gui_SOURCES = \
	callbacks.c \
	callbacks.h \
	main.c \
	lcs.h \
	lcs.c

lcs_gui_LDFLAGS = \
	-Wl,--export-dynamic

lcs_gui_LDADD = $(LCS_GUI_LIBS)

EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(datadir)/lcs_gui
