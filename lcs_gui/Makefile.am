## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src po man

lcs_docdir = ${prefix}/doc/lcs
lcs_doc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = $(lcs_doc_DATA) \
	$(INTLTOOL_FILES) \
	data/blosum62 \
	icon/lcs.png \
	man/lcs.1 \
	manual/lcs/C/lcs.xml \
	manual/lcs/C/figures/lcs_window.gif \
	manual/lcs/C/figures/lcs_chromatography.gif \
	manual/lcs/C/figures/lcs_chromatography_nuc.gif \
	manual/lcs/C/figures/lcs_report.gif \
	manual/lcs/C/figures/lcs_matrix.gif \
	manual/lcs/C/figures/MG235-1xp3a_ts3_cn4.gif

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(lcs_docdir)
