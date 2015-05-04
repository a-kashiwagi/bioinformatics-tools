/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/*
 * main.c
 *
 * Generated anjuta and glade. and writed by Kashiwagi Akihiro.
 *
 * Copyright (C) Kashiwagi Akihiro 2010 <a-kashiwagi@mippi-mail.com>
 * 
 * LCS is free software and shareware : you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version. and you must pay 10[%] part of profit
 * to me that case of you used this software for business.
 * 
 * lcs_gui is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include <config.h>

#include <gtk/gtk.h>
#include "lcs.h"

/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define N_(String) (String)
#endif



#include "callbacks.h"

//For testing propose use the local (not installed) ui file
//#define UI_FILE PACKAGE_DATA_DIR"/lcs/ui/lcs_gui.ui"
#define UI_FILE "src/lcs_gui.ui"
//#define UI_FILE "/home/a-kashiwagi/etc/lcs_gui.ui"

						/* Function create window     */
GtkWidget *create_window ( void );
						/* Function clean up sequence */
long clean_up_sequence( char *sequence );
						/* Function set tags          */
						/*            to text buffer  */
GtkTextBuffer *set_tags_to_textbuffer( GtkTextBuffer *textbuf );
						/* Function put sequence      */
int put_sequence(
        GtkTextBuffer *textbuf,
        char ch,
        long eg,
        int compare_mode
);
						/* Function print out         */
						/*           for text view    */
int PrintOutForTextViwe(
	char *v,
	char *w,
	char **eg,
	long **ss,
	char **bp,
	char *v_ans,
	char *w_ans,
	char *ans,
	char *eg_arr,
	long *ss_arr,
	char *bp_arr,
	long  inum,
	long  jnum,
	long  vnum,
	long  wnum,
	long  ansnum,
	long  egnum,
	long  ssnum,
	long  bpnum,
	long  v_lc_from,
	long  v_lc_to,
	long  w_lc_from,
	long  w_lc_to,
	long  ident_cnt,
	double ident_rate,
	long score,
	int compare_mode,
	int scan_mode,
	int matrix_on,
	int region_order,
	long *prescan_orders_p,
	long *prescan_v_loc_p,
	long *prescan_w_loc_p,
	double *prescan_hmm_orders_p,
	long *prescan_hmm_s_loc_p,
	long *prescan_hmm_e_loc_p
);

					/* declare pointer of each object     */
					/*                in created builder  */

					/* Main window                        */
GtkWidget *window;
					/* All in this widget                 */
GtkWidget *vbox1;
					/* Parameter in this widget           */
GtkWidget *hbox1;
					/* For source textview                */
GtkWidget *scrolledwindow1;
					/* For target textview                */
GtkWidget *scrolledwindow2;
					/* For source area                    */
GtkWidget     *textview1;
GtkTextBuffer *textbuf1;
					/* For target area                    */
GtkWidget     *textview2;
GtkTextBuffer *textbuf2;
					/* For allocated sequence area        */
GtkWidget     *textview3;
GtkTextBuffer *textbuf3;
					/* For report                         */
GtkWidget     *textview4;
GtkTextBuffer *textbuf4;
GtkWidget     *textview5;
GtkTextBuffer *textbuf5;
GtkWidget     *textview6;
GtkTextBuffer *textbuf6;
GtkWidget     *textview7;
GtkTextBuffer *textbuf7;
GtkWidget     *textview8;
GtkTextBuffer *textbuf8;
					/* Nucreotide                         */
GtkWidget *comparetype0_radio;
					/* Amino Acid                         */
GtkWidget *comparetype1_radio;
					/* Part mode                          */
GtkWidget *sequencemode0_radio;
					/* All  mode                          */
GtkWidget *sequencemode1_radio;
					/* Identity match mode                */
GtkWidget *scanmode0_radio;
					/* HMM mode                           */
GtkWidget *scanmode1_radio;
					/* Global alignment                   */
GtkWidget *alignmentmode0_radio;
					/* Local  alignment                   */
GtkWidget *alignmentmode1_radio;
					/* Liner gap score                    */
GtkWidget *gapscoremode0_radio;
					/* Affine gap score                   */
GtkWidget *gapscoremode1_radio;
					/* For "Match" label                  */
GtkWidget *label1;
					/* For "Unmatch" label                */
GtkWidget *label2;
					/* For "No." label                    */
GtkWidget *Location_label;
					/* For "ID" label                     */
GtkWidget *Rate_label;
					/* For "SCR" label                    */
GtkWidget *Score_label;
					/* Affine gap number                  */
GtkWidget *e_num_spin;
					/* Liner gap number                   */
GtkWidget *d_num_spin;
					/* Match number                       */
GtkWidget *match_num_spin;
					/* Unmatch number                     */
GtkWidget *unmatch_num_spin;
					/* Threshold number for matrix        */
GtkWidget *threshold_num_vscale;
					/* Continuity number for matrix       */
GtkWidget *continuity_num_vscale;
					/* For affine gap number              */
GtkAdjustment *adjustment1;
					/* For Liner gap number               */
GtkAdjustment *adjustment2;
					/* For Match number                   */
GtkAdjustment *adjustment3;
					/* For Unmatch number                 */
GtkAdjustment *adjustment4;
					/* For Threshld number for matrix     */
GtkAdjustment *adjustment5;
					/* For Continuity number for matrix   */
GtkAdjustment *adjustment6;
					/* For Combo box of Region            */
GtkWidget *RegionCombo;
					/* For List store of Region           */
GtkListStore *regionliststore;
					/* For Renderer of Region             */
GtkCellRenderer *renderer;
					/* For matrix                         */
GtkWidget *drawingArea1;
GdkPixmap *pmap = NULL;

/******************************************************************************/
/*                                                                            */
/* Title  : Create window                                                     */
/* Function Name : create_window                                              */
/*                                                                            */
/* Detail : Create                                                            */
/* Date   : 2010/09/16                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
/* Output : GtkWidget *window : Pointer of window                             */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

GtkWidget*
create_window (	void )
{
	GtkBuilder *builder;
	GError* error = NULL;
	PangoFontDescription *font_desc;

	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_warning ("Couldn't load builder file: %s", error->message);
		g_error_free (error);
	}

	/* This is important */
	gtk_builder_connect_signals (builder, NULL);

					/* Get each object                    */
					/*             in created by builder  */

					/* Get window object                  */
	window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));

					/* Get vbox1 object                   */
	vbox1 = GTK_WIDGET (gtk_builder_get_object (builder, "vbox1"));

					/* Get hbox1 object                   */
	hbox1 = GTK_WIDGET (gtk_builder_get_object (builder, "hbox1"));

					/* Get scrolledwindow1 object         */
	scrolledwindow1 = GTK_WIDGET (
	    gtk_builder_get_object (builder, "scrolledwindow1")
	);
					/* Get scrolledwindow2 object         */
	scrolledwindow2 = GTK_WIDGET (
	    gtk_builder_get_object (builder, "scrolledwindow2")
	);
					/* Get textview1 object               */
	textview1 = GTK_WIDGET (gtk_builder_get_object (builder, "textview1"));

					/* Get textview2 object               */
	textview2 = GTK_WIDGET (gtk_builder_get_object (builder, "textview2"));

					/* Get textview3 object               */
	textview3 = GTK_WIDGET (gtk_builder_get_object (builder, "textview3"));

					/* Get textview4 object               */
	textview4 = GTK_WIDGET (gtk_builder_get_object (builder, "textview4"));

					/* Get textview5 object               */
	textview5 = GTK_WIDGET (gtk_builder_get_object (builder, "textview5"));

					/* Get textview6 object               */
	textview6 = GTK_WIDGET (gtk_builder_get_object (builder, "textview6"));

					/* Get textview7 object               */
	textview7 = GTK_WIDGET (gtk_builder_get_object (builder, "textview7"));

					/* Get textview8 object               */
	textview8 = GTK_WIDGET (gtk_builder_get_object (builder, "textview8"));

					/* Get comparetype0 object            */
	comparetype0_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "comparetype0")
	);
					/* Get comparetype1 object            */
	comparetype1_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "comparetype1")
	);
					/* Get comparemode0 object            */
	sequencemode0_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "comparemode0")
	);
					/* Get comparemode1 object            */
	sequencemode1_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "comparemode1")
	);
					/* Get scanmode0 object               */
	scanmode0_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "scanmode0")
	);
					/* Get scanmode1 object               */
	scanmode1_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "scanmode1")
	);
					/* Get alignmentmode0 object          */
	alignmentmode0_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "alignmentmode0")
	);
					/* Get alignmentmode1 object          */
	alignmentmode1_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "alignmentmode1")
	);
					/* Get gapmode1 object                */
	gapscoremode1_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "gapmode1")
	);
					/* Get gapmode0 object                */
	gapscoremode0_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "gapmode0")
	);
					/* Get label1 object                  */
	label1 = GTK_WIDGET (gtk_builder_get_object (builder, "label1"));

					/* Get label2 object                  */
	label2 = GTK_WIDGET (gtk_builder_get_object (builder, "label2"));

					/* Get Location object                */
	Location_label = GTK_WIDGET (
	        gtk_builder_get_object (builder, "Location")
	);
					/* Get Rate object                    */
	Rate_label = GTK_WIDGET (gtk_builder_get_object (builder, "Rate"));

					/* Get Score object                   */
	Score_label = GTK_WIDGET (gtk_builder_get_object (builder, "Score"));

					/* Get e_num object                   */
	e_num_spin = GTK_WIDGET (
	        gtk_builder_get_object (builder, "e_num")
	);
					/* Get d_num object                   */
	d_num_spin = GTK_WIDGET (
	        gtk_builder_get_object (builder, "d_num")
	);
					/* Get match_num object               */
	match_num_spin = GTK_WIDGET (
	        gtk_builder_get_object (builder, "match_num")
	);
					/* Get unmatch_num object             */
	unmatch_num_spin = GTK_WIDGET (
	        gtk_builder_get_object (builder, "unmatch_num")
	);
					/* Get threshold_num_vscale object    */
	threshold_num_vscale = GTK_WIDGET (
		gtk_builder_get_object (builder, "thresholdvscale" )
	);
					/* Get continuity_num_vscale object   */
	continuity_num_vscale = GTK_WIDGET (
		gtk_builder_get_object (builder, "continuityvscale" )
	);
					/* Threshold vscale un sensitive      */
	//gtk_widget_set_sensitive( GTK_WIDGET( threshold_num_vscale ), FALSE );

					/* Get adjustment1 object             */
	adjustment1 = GTK_ADJUSTMENT (
	        gtk_builder_get_object (builder, "adjustment1")
	);
					/* Get adjustment2 object             */
	adjustment2 = GTK_ADJUSTMENT (
	        gtk_builder_get_object (builder, "adjustment2")
	);
					/* Get adjustmnet3 object             */
	adjustment3 = GTK_ADJUSTMENT (
	        gtk_builder_get_object (builder, "adjustment3")
	);
					/* Get adjustment4 object             */
	adjustment4 = GTK_ADJUSTMENT (
	        gtk_builder_get_object (builder, "adjustment4")
	);
					/* Get adjustment5 object             */
	adjustment5 = GTK_ADJUSTMENT (
	        gtk_builder_get_object (builder, "adjustment5")
	);
					/* Get adjustment6 object             */
	adjustment6 = GTK_ADJUSTMENT (
	        gtk_builder_get_object (builder, "adjustment6")
	);
					/* Set object to callback area too    */
	set_objects_to_callback_area( GTK_BUILDER(builder) );
					/* Set value to spin button e_num     */
	gtk_spin_button_set_value(
		GTK_SPIN_BUTTON( e_num_spin ),
		(gdouble)DEF_E_NUM
	);
					/* Set value to spin button d_num     */
	gtk_spin_button_set_value(
		GTK_SPIN_BUTTON( d_num_spin ),
		(gdouble)DEF_D_NUM
	);
					/* Set value to spin button match_num */
	gtk_spin_button_set_value(
		GTK_SPIN_BUTTON( match_num_spin ),
		(gdouble)DEF_MATCH_NUM
	);
					/* Set value to spin button           */
					/*                      unmatch_num   */
	gtk_spin_button_set_value(
		GTK_SPIN_BUTTON( unmatch_num_spin ),
		(gdouble)DEF_UNMATCH_NUM
	);
					/* Set value to adjustment            */
					/*        threshold number for matrix */
	gtk_adjustment_set_value(
	    GTK_ADJUSTMENT( adjustment5 ),
	    MATRIXTHRESHOLD
	);
					/* Set value to adjustment            */
					/*       continuity number for matrix */
	gtk_adjustment_set_value(
	    GTK_ADJUSTMENT( adjustment6 ),
	    MATRIXCONTINUITY
	);
					/* TextBuffer get from textview1      */
	textbuf1 = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview1) );
					/* Set tags to textview1              */
	set_tags_to_textbuffer( textbuf1 );
					/* Set callback function              */
					/*           when after signal        */
	g_signal_connect_after(
	        G_OBJECT(textbuf1),
	        "insert-text",
	        G_CALLBACK( on_textbuf_insert ),
	        NULL
	);

					/* TextBuffer get from textview2      */
	textbuf2 = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview2) );
					/* Set tags to textview2              */
	set_tags_to_textbuffer( textbuf2 );
					/* Set callback function              */
					/*           when after signal        */
	g_signal_connect_after(
	        G_OBJECT(textbuf2),
	        "insert-text",
	        G_CALLBACK( on_textbuf_insert ),
	        NULL
	);
	
					/* TextBuffer get from textview3      */
	textbuf3 = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview3) );
					/* Set tags to textview3              */
	set_tags_to_textbuffer( textbuf3 );
					/* Set callback function              */
					/*           when after signal        */
	g_signal_connect_after(
	        G_OBJECT(textbuf3),
	        "insert-text",
	        G_CALLBACK( on_textbuf_insert ),
	        NULL
	);
	
					/* TextBuffer get from textview4      */
	textbuf4 = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview4) );
					/* Set tags to textview4              */
	set_tags_to_textbuffer( textbuf4 );
	
					/* TextBuffer get from textview5      */
	textbuf5 = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview5) );
					/* Set tags to textview5              */
	set_tags_to_textbuffer( textbuf5 );
	
					/* TextBuffer get from textview6      */
	textbuf6 = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview6) );
					/* Set tags to textview6              */
	set_tags_to_textbuffer( textbuf6 );
	
					/* TextBuffer get from textview7      */
	textbuf7 = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview7) );
					/* Set tags to textview7              */
	set_tags_to_textbuffer( textbuf7 );
	
					/* TextBuffer get from textview8      */
	textbuf8 = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview8) );
					/* Set tags to textview8              */
	set_tags_to_textbuffer( textbuf8 );

					/* Set wedget fonts                   */
	font_desc = pango_font_description_from_string("Courier 10 Pitch 10");
	gtk_widget_modify_font(textview1, font_desc);
	gtk_widget_modify_font(textview2, font_desc);
	gtk_widget_modify_font(textview3, font_desc);
	gtk_widget_modify_font(textview4, font_desc);
	gtk_widget_modify_font(textview5, font_desc);
	gtk_widget_modify_font(textview6, font_desc);
	gtk_widget_modify_font(textview7, font_desc);
	gtk_widget_modify_font(textview8, font_desc);
	pango_font_description_free( font_desc );
/*
	font_desc = pango_font_description_from_string("Times New Roman 10");
	gtk_widget_modify_font(comparetype0_radio, font_desc);
	gtk_widget_modify_font(comparetype1_radio, font_desc);
	gtk_widget_modify_font(sequencemode0_radio, font_desc);
	gtk_widget_modify_font(sequencemode1_radio, font_desc);
	gtk_widget_modify_font(alignmentmode0_radio, font_desc);
	gtk_widget_modify_font(alignmentmode1_radio, font_desc);
	gtk_widget_modify_font(gapscoremode0_radio, font_desc);
	gtk_widget_modify_font(gapscoremode1_radio, font_desc);
	gtk_widget_modify_font(label1, font_desc);
	gtk_widget_modify_font(label2, font_desc);
	gtk_widget_modify_font(Location_label, font_desc);
	gtk_widget_modify_font(Rate_label, font_desc);
	gtk_widget_modify_font(Score_label, font_desc);
	gtk_widget_modify_font(e_num_spin, font_desc);
	gtk_widget_modify_font(d_num_spin, font_desc);
	gtk_widget_modify_font(match_num_spin, font_desc);
	gtk_widget_modify_font(unmatch_num_spin, font_desc);
	pango_font_description_free( font_desc );
*/
					/* Get drawingArea1 object            */
	drawingArea1 = GTK_WIDGET (
	        gtk_builder_get_object (builder, "drawingarea1")
	);
                                        /* Get RegionCombo object             */
        RegionCombo = GTK_WIDGET (
                gtk_builder_get_object (builder, "RegionCombo")
        );
                                        /* Get RegionListStore object         */
        regionliststore = GTK_LIST_STORE(
                gtk_builder_get_object (builder, "regionliststore")
        );
					/* Set column type of list store      */
        regionliststore = gtk_list_store_new (1, G_TYPE_STRING);
	//gtk_list_store_set_column_types( regionliststore, 1, G_TYPE_STRING );

	/*
        gchar *SEQUENCE[] = {
                "ATGCATGC",
                "TGCATGCA",
                "GCATGCAT",
                NULL
        };

        GtkTreeIter iter;

        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, " ", -1);
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, " ", -1);
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, " ", -1);
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, " ", -1);
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, " ", -1);
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, " ", -1);
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, " ", -1);
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, " ", -1);
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, " ", -1);
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, " ", -1);
	*/

        gtk_combo_box_set_model(RegionCombo,regionliststore);
        renderer = gtk_cell_renderer_text_new ();
        gtk_cell_layout_pack_start (
                GTK_CELL_LAYOUT (RegionCombo),
                renderer,
                FALSE
        );

        gtk_cell_layout_set_attributes (
                GTK_CELL_LAYOUT (RegionCombo),
                renderer,
                "text",
                0,
                NULL
        );

        //gtk_combo_box_set_active (GTK_COMBO_BOX (RegionCombo), 0);

	/*
	GtkTreeIter iter;
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, SEQUENCE[0], -1);
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, SEQUENCE[1], -1);
        gtk_list_store_append (regionliststore, &iter);
        gtk_list_store_set (regionliststore, &iter, 0, SEQUENCE[2], -1);
	*/
					/* Unreference builder object         */
	g_object_unref (builder);
	
	return window;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Clean up sequence                                                 */
/* Function Name : clean_up_sequence()                                        */
/*                                                                            */
/* Detail : Create                                                            */
/* Date   : 2010/09/30                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *sequence : Pointer of sequence string                       */
/* Output : long           : Location of end of cleanuped sequence string     */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

long clean_up_sequence( char *sequence ){

	long seq_cnt;
					/* Count of input sequence            */
	long cls_cnt;
					/* Count of cleanuped sequence        */

					/* Counter reset                      */
	seq_cnt = 0;
	cls_cnt = 0;

					/* Loop of sequence                   */
	while( sequence[seq_cnt] != '\0' ){

		if( isspace(sequence[seq_cnt]) ){
					/* Case of LF when continue           */
			seq_cnt++;
			continue;

		}else if( sequence[seq_cnt] == '>' ){
					/* Case of Fasta header               */

			while( sequence[seq_cnt] != '\n' ){
					/* Counter forward until LF           */
				seq_cnt++;
			}
			seq_cnt++;

			continue;
		}
					/* Copy to cleanuped sequence         */
					/*      from input sequence           */
		sequence[cls_cnt] = sequence[seq_cnt];

					/* Counter increment                  */
		cls_cnt++;
		seq_cnt++;
	}
					/* Insert null terminater             */
	sequence[cls_cnt] = '\0';
					/* Retuern cleanuped sequence length  */
	return( cls_cnt );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Set tags to text buffer                                           */
/* Function Name : set_tags_to_textbuffer                                     */
/*                                                                            */
/* Detail : Create                                                            */
/* Date   : 2010/09/16                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkTextBuffer *textbuf : Pointer of text buffer                   */
/* Output : GtkTextBuffer *        : Pointer of modifyed text buffer          */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/10/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added tag that is background color.                               */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

GtkTextBuffer *set_tags_to_textbuffer( GtkTextBuffer *textbuf ){

					/* Nucleotide Acid                    */

					/* Create tag for Adenine(red)        */
	gtk_text_buffer_create_tag(
		textbuf, "Adenine",
		"foreground", "#FF0000",
		NULL
	);
					/* Create tag for Thymine(green)      */
	gtk_text_buffer_create_tag(
		textbuf, "Thymine",
		"foreground", "#00FF00",
		NULL
	);
					/* Create tag for Guanine(blue)       */
	gtk_text_buffer_create_tag(
		textbuf, "Guanine",
		"foreground", "#0000FF",
		NULL
	);
					/* Create tag for Cytosine(purple)    */
	gtk_text_buffer_create_tag(
		textbuf, "Cytosine",
		"foreground", "#7F007F",
		NULL
	);

					/* Amino Acid                         */

					/*    Hydrophilic                     */

					/*        Basic(yellow)               */

					/* Create tag for R:Arginine          */
	gtk_text_buffer_create_tag(
		textbuf, "Arginine",
		"foreground", "#FF8000",
		NULL
	);
					/* Create tag for K:Lysine            */
	gtk_text_buffer_create_tag(
		textbuf, "Lysine",
		"foreground", "#FFBB00",
		NULL
	);
					/* Create tag for H:Histidine         */
	gtk_text_buffer_create_tag(
		textbuf, "Histidine",
		"foreground", "#FFFF00",
		NULL
	);
					/*        Acidic(brown)               */

					/* Create tag for D:AsparagineAcid    */
	gtk_text_buffer_create_tag(
		textbuf, "AsparagineAcid",
		"foreground", "#800000",
		NULL
	);
					/* Create tag for E:GlutamicAcid      */
	gtk_text_buffer_create_tag(
		textbuf, "GlutamicAcid",
		"foreground", "#400000",
		NULL
	);
					/*        Neutral Polar(green)        */

					/* Create tag for N:Asparagine        */
	gtk_text_buffer_create_tag(
		textbuf, "Asparagine",
		"foreground", "#80FF80",
		NULL
	);
					/* Create tag for Q:Glutamine         */
	gtk_text_buffer_create_tag(
		textbuf, "Glutamine",
		"foreground", "#80FF00",
		NULL
	);
					/* Create tag for S:Serine            */
	gtk_text_buffer_create_tag(
		textbuf, "Serine",
		"foreground", "#008000",
		NULL
	);
					/* Create tag for T:Threonine         */
	gtk_text_buffer_create_tag(
		textbuf, "Threonine",
		"foreground", "#80FFFF",
		NULL
	);
					/* Create tag for Y:Tyrosine          */
	gtk_text_buffer_create_tag(
		textbuf, "Tyrosine",
		"foreground", "#004000",
		NULL
	);
					/* Hydrophobic(blue,purple,red)       */

					/* Create tag for G:Glycine           */
	gtk_text_buffer_create_tag(
		textbuf, "Glycine",
		"foreground", "#00FF00",
		NULL
	);
					/* Create tag for F:Phenylalane       */
	gtk_text_buffer_create_tag(
		textbuf, "Phenylalane",
		"foreground", "#008080",
		NULL
	);
					/* Create tag for L:Leucine           */
	gtk_text_buffer_create_tag(
		textbuf, "Leucine",
		"foreground", "#8080FF",
		NULL
	);
					/* Create tag for C:Cysteine          */
	gtk_text_buffer_create_tag(
		textbuf, "Cysteine",
		"foreground", "#7F007F",
		NULL
	);
					/* Create tag for W:Tryptophan        */
	gtk_text_buffer_create_tag(
		textbuf, "Tryptophan",
		"foreground", "#8000FF",
		NULL
	);
					/* Create tag for P:Proline           */
	gtk_text_buffer_create_tag(
		textbuf, "Proline",
		"foreground", "#800080",
		NULL
	);
					/* Create tag for I:Isoleucine        */
	gtk_text_buffer_create_tag(
		textbuf, "Isoleucine",
		"foreground", "#808080",
		NULL
	);
					/* Create tag for A:Alanine           */
	gtk_text_buffer_create_tag(
		textbuf, "Alanine",
		"foreground", "#FF0000",
		NULL
	);
					/* Create tag for M:Methionine        */
	gtk_text_buffer_create_tag(
		textbuf, "Methionine",
		"foreground", "#FF80FF",
		NULL
	);
					/* Create tag for V:Valine            */
	gtk_text_buffer_create_tag(
		textbuf, "Valine",
		"foreground", "#FF8080",
		NULL
	);
					/* Create tag for Normal(black)       */
	gtk_text_buffer_create_tag(
		textbuf, "Normal",
		"foreground", "#000000",
		NULL
	);
					/* Create tag for Background -15      */
	gtk_text_buffer_create_tag(
		textbuf, "-15",
		"background", "#D000FF",
		NULL
	);
					/* Create tag for Background -14      */
	gtk_text_buffer_create_tag(
		textbuf, "-14",
		"background", "#B000FF",
		NULL
	);
					/* Create tag for Background -13      */
	gtk_text_buffer_create_tag(
		textbuf, "-13",
		"background", "#9000FF",
		NULL
	);
					/* Create tag for Background -12      */
	gtk_text_buffer_create_tag(
		textbuf, "-12",
		"background", "#7000FF",
		NULL
	);
					/* Create tag for Background -11      */
	gtk_text_buffer_create_tag(
		textbuf, "-11",
		"background", "#5000FF",
		NULL
	);
					/* Create tag for Background -10      */
	gtk_text_buffer_create_tag(
		textbuf, "-10",
		"background", "#3000FF",
		NULL
	);
					/* Create tag for Background -9       */
	gtk_text_buffer_create_tag(
		textbuf, "-9",
		"background", "#1000FF",
		NULL
	);
					/* Create tag for Background -8       */
	gtk_text_buffer_create_tag(
		textbuf, "-8",
		"background", "#000FFF",
		NULL
	);
					/* Create tag for Background -7       */
	gtk_text_buffer_create_tag(
		textbuf, "-7",
		"background", "#002FFF",
		NULL
	);
					/* Create tag for Background -6       */
	gtk_text_buffer_create_tag(
		textbuf, "-6",
		"background", "#004FFF",
		NULL
	);
					/* Create tag for Background -5       */
	gtk_text_buffer_create_tag(
		textbuf, "-5",
		"background", "#006FFF",
		NULL
	);
					/* Create tag for Background -4       */
	gtk_text_buffer_create_tag(
		textbuf, "-4",
		"background", "#008FFF",
		NULL
	);
					/* Create tag for Background -3       */
	gtk_text_buffer_create_tag(
		textbuf, "-3",
		"background", "#00AFFF",
		NULL
	);
					/* Create tag for Background -2       */
	gtk_text_buffer_create_tag(
		textbuf, "-2",
		"background", "#00BFFF",
		NULL
	);
					/* Create tag for Background -1       */
	gtk_text_buffer_create_tag(
		textbuf, "-1",
		"background", "#00DFFF",
		NULL
	);
					/* Create tag for Background  0       */
	gtk_text_buffer_create_tag(
		textbuf, "0",
		"background", "#00FFFF",
		NULL
	);
					/* Create tag for Background  1       */
	gtk_text_buffer_create_tag(
		textbuf, "1",
		"background", "#00FFD0",
		NULL
	);
					/* Create tag for Background  2       */
	gtk_text_buffer_create_tag(
		textbuf, "2",
		"background", "#00FFB0",
		NULL
	);
					/* Create tag for Background  3       */
	gtk_text_buffer_create_tag(
		textbuf, "3",
		"background", "#00FF90",
		NULL
	);
					/* Create tag for Background  4       */
	gtk_text_buffer_create_tag(
		textbuf, "4",
		"background", "#00FF70",
		NULL
	);
					/* Create tag for Background  5       */
	gtk_text_buffer_create_tag(
		textbuf, "5",
		"background", "#00FF50",
		NULL
	);
					/* Create tag for Background  6       */
	gtk_text_buffer_create_tag(
		textbuf, "6",
		"background", "#00FF30",
		NULL
	);
					/* Create tag for Background  7       */
	gtk_text_buffer_create_tag(
		textbuf, "7",
		"background", "#00FF10",
		NULL
	);
					/* Create tag for Background  8       */
	gtk_text_buffer_create_tag(
		textbuf, "8",
		"background", "#10FF00",
		NULL
	);
					/* Create tag for Background  9       */
	gtk_text_buffer_create_tag(
		textbuf, "9",
		"background", "#30FF00",
		NULL
	);
					/* Create tag for Background 10       */
	gtk_text_buffer_create_tag(
		textbuf, "10",
		"background", "#50FF00",
		NULL
	);
					/* Create tag for Background 11       */
	gtk_text_buffer_create_tag(
		textbuf, "11",
		"background", "#70FF00",
		NULL
	);
					/* Create tag for Background 12       */
	gtk_text_buffer_create_tag(
		textbuf, "12",
		"background", "#90FF00",
		NULL
	);
					/* Create tag for Background 13       */
	gtk_text_buffer_create_tag(
		textbuf, "13",
		"background", "#B0FF00",
		NULL
	);
					/* Create tag for Background 14       */
	gtk_text_buffer_create_tag(
		textbuf, "14",
		"background", "#D0FF00",
		NULL
	);
					/* Create tag for Background 15       */
	gtk_text_buffer_create_tag(
		textbuf, "15",
		"background", "#FFFF00",
		NULL
	);
					/* Create tag for Background 99       */
	gtk_text_buffer_create_tag(
		textbuf, "99",
		"background", "#FFFFFF",
		NULL
	);
					/* Create tag for Number              */
					/* Create tag for Number              */
	gtk_text_buffer_create_tag(
		textbuf, "NUMBER",
		"foreground", "#666666",
		"background", "#CCCCCC",
		NULL
	);
					/* Return with *textbuf               */
	return( textbuf );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Put sequence character to text buffer with tag                    */
/* Function Name : put_sequence                                               */
/*                                                                            */
/* Detail : Create                                                            */
/* Date   : 2010/09/16                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkTextBuffer *textbuf : Pointer of text buffer                   */
/*        : char ch                : Character for ouotput                    */
/*        : long eg                : Character for ouotput                    */
/*        : int  compare_mode      : Sequence compare mode                    */
/*                                                                            */
/* Output : int : NormalTerminate [0]                                         */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/10/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure that is score chromatography :-)                  */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int put_sequence(
        GtkTextBuffer *textbuf,
        char ch,
        long eg,
        int compare_mode
){

					/* Buffer for output                  */
	char buf[4];
					/* Forground  Tagname for output      */
	char fgtagname[20];
					/* Background Tagname for output      */
	char bgtagname[20];
					/* Iterator of current cursor         */
	GtkTextIter cur;

					/* Set tag name                       */
	switch(ch){
					/* for Adenine                        */
		case 'A':
			strcpy( fgtagname, "Adenine");
			break;
					/* for Thymine                        */
		case 'T':
			strcpy( fgtagname, "Thymine");
			break;
					/* for Guanine                        */
		case 'G':
			strcpy( fgtagname, "Guanine");
			break;
					/* for Cytosine                       */
		case 'C':
			strcpy( fgtagname, "Cytosine");
			break;
					/* Set tag name of Phenylalane       */
		case 'F':
			strcpy( fgtagname, "Phenylalane");
			break;
					/* Set tag name of Leucine           */
		case 'L':
			strcpy( fgtagname, "Leucine");
			break;
					/* Set tag name of Serine            */
		case 'S':
			strcpy( fgtagname, "Serine");
			break;
					/* Set tag name of Tyrosine          */
		case 'Y':
			strcpy( fgtagname, "Tyrosine");
			break;
					/* Set tag name of Cysteine          */
		/*
		case 'C':
			strcpy( fgtagname, "Cysteine");
			break;
		*/
					/* Set tag name of Tryptophan        */
		case 'W':
			strcpy( fgtagname, "Tryptophan");
			break;
					/* Set tag name of Proline           */
		case 'P':
			strcpy( fgtagname, "Proline");
			break;
					/* Set tag name of Histidine         */
		case 'H':
			strcpy( fgtagname, "Histidine");
			break;
					/* Set tag name of Glutamine         */
		case 'Q':
			strcpy( fgtagname, "Glutamine");
			break;
					/* Set tag name of Arginine          */
		case 'R':
			strcpy( fgtagname, "Arginine");
			break;
					/* Set tag name of Isoleucine        */
		case 'I':
			strcpy( fgtagname, "Isoleucine");
			break;
					/* Set tag name of Methionine        */
		case 'M':
			strcpy( fgtagname, "Methionine");
			break;
					/* Set tag name of Threonine         */
		/*
		case 'T':
			strcpy( fgtagname, "Threonine");
			break;
		*/
					/* Set tag name of Asparagine        */
		case 'N':
			strcpy( fgtagname, "Asparagine");
			break;
					/* Set tag name of Lysine            */
		case 'K':
			strcpy( fgtagname, "Lysine");
			break;
					/* Set tag name of Valine            */
		case 'V':
			strcpy( fgtagname, "Valine");
			break;
					/* Set tag name of Alanine           */
		/*
		case 'A':
			strcpy( fgtagname, "Alanine");
			break;
		*/
					/* Set tag name of AsparagineAcid    */
		case 'D':
			strcpy( fgtagname, "AsparagineAcid");
			break;
					/* Set tag name of GlutamicAcid      */
		case 'E':
			strcpy( fgtagname, "GlutamicAcid");
			break;
					/* Set tag name of Glycine           */
		/*
		case 'G':
			strcpy( fgtagname, "Glycine");
			break;
		*/
					/* for Other                          */
		default:
			strcpy( fgtagname, "Normal");
			break;
	}
					/* Set background color               */

	if( compare_mode == NUCLEOTIDE ){
					/* Case of Nucleotide mode            */
					/*            Adjustment eg score     */
		if( eg == 999 ){

			eg = 999;

		}else if( eg == 0 ){

			eg = 0;

		}else if( eg < 0 ){

			eg = -13;

		}else if( eg > 0 ){

			eg = 13;
		}
	}
					/* Case of Amino Acid mode            */
	switch( eg ){

		case -15:
			strcpy( bgtagname, "-15" );
			break;

		case -14:
			strcpy( bgtagname, "-14" );
			break;

		case -13:
			strcpy( bgtagname, "-13" );
			break;

		case -12:
			strcpy( bgtagname, "-12" );
			break;

		case -11:
			strcpy( bgtagname, "-11" );
			break;

		case -10:
			strcpy( bgtagname, "-10" );
			break;

		case -9:
			strcpy( bgtagname, "-9" );
			break;

		case -8:
			strcpy( bgtagname, "-8" );
			break;

		case -7:
			strcpy( bgtagname, "-7" );
			break;

		case -6:
			strcpy( bgtagname, "-6" );
			break;

		case -5:
			strcpy( bgtagname, "-5" );
			break;

		case -4:
			strcpy( bgtagname, "-4" );
			break;

		case -3:
			strcpy( bgtagname, "-3" );
			break;

		case -2:
			strcpy( bgtagname, "-2" );
			break;

		case -1:
			strcpy( bgtagname, "-2" );
			break;

		case 0:
			strcpy( bgtagname, "0" );
			break;

		case 1:
			strcpy( bgtagname, "1" );
			break;

		case 2:
			strcpy( bgtagname, "2" );
			break;

		case 3:
			strcpy( bgtagname, "3" );
			break;

		case 4:
			strcpy( bgtagname, "4" );
			break;

		case 5:
			strcpy( bgtagname, "5" );
			break;

		case 6:
			strcpy( bgtagname, "6" );
			break;

		case 7:
			strcpy( bgtagname, "7" );
			break;

		case 8:
			strcpy( bgtagname, "8" );
			break;

		case 9:
			strcpy( bgtagname, "9" );
			break;

		case 10:
			strcpy( bgtagname, "10" );
			break;

		case 11:
			strcpy( bgtagname, "11" );
			break;

		case 12:
			strcpy( bgtagname, "12" );
			break;

		case 13:
			strcpy( bgtagname, "13" );
			break;

		case 14:
			strcpy( bgtagname, "14" );
			break;

		case 15:
			strcpy( bgtagname, "15" );
			break;

		default:
			strcpy( bgtagname, "99" );
			break;
	}


					/* Set buffer                         */
	sprintf( buf, "%c", ch );
					/* Get end iterator                   */
	gtk_text_buffer_get_end_iter( textbuf, &cur );

					/* Put character with tag             */
	gtk_text_buffer_insert_with_tags_by_name(
	        textbuf, &cur, buf, strlen(buf),
	        fgtagname,
	        bgtagname,
	        NULL
	);
					/* Return normal terminate            */
	return(0);
}

/* Function for test */
void put_message( char *str ){

	gtk_text_buffer_insert_at_cursor( textbuf3, str, strlen(str) );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Count to digit                                                    */
/* Function Name : max_digit()                                                */
/*                                                                            */
/* Detail : Create                                                            */
/* Date   : 2015/04/18                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : long *num : pointer of number array                               */
/*        : int n     : number of array                                       */
/*                                                                            */
/* Output : int : number of digit                                             */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int max_digit( long *num, int n ){

	double max;
					/* Max number of array                */
	int cnt;
					/* Counter                            */
	int digit;
					/* Number of digit                    */
	max = 0;

	for( cnt = 0; cnt < n; cnt++ ){
					/* Search max item                    */
		if( (double)num[cnt] > max ){
			max = (double)num[cnt];
		}
	}

	digit = 0;

	while( LOOP ){

		if( max < 1 ){
					/* Count complete                     */
			break;
		}else{
			max = max * 0.1;
		}
					/* Count up                           */
		digit++;
	}

	return digit;
}

/******************************************************************************/
/*                                                                            */
/* Title  : Print out for text view                                           */
/* Function Name : PrintOutForTextView()                                      */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2010/09/10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  :                                                                   */
/*          char **eg      : Buffer of Edit Graph                             */
/*          long **ss      : Buffer of Similary Score                         */
/*          char **bp      : Buffer of Back Tracking                          */
/*          char *v_ans    : Answer of calculation of v                       */
/*          char *w_ans    : Answer of calcularion of w                       */
/*          char *ans      : Answer of LCS                                    */
/*          char *eg_arr   : Buffer of Edit graph pointer                     */
/*          long *ss_arr   : Buffer of Similary score pointer                 */
/*          char *bp_arr   : Buffer of Back tracking pointer                  */
/*          long  inum     : Number of i array                                */
/*          long  jnum     : Number of j array                                */
/*          long  vnum     : Number of w array                                */
/*          long  wnum     : Number of w array                                */
/*          long  ansnum   : Number of anser array                            */
/*          long  egnum    : Number of Edit graph arrary                      */
/*          long  ssnum    : Number of Similary score arrary                  */
/*          long  bpnum    : Number of back tracking arrary                   */
/*          long  v_lc_from: location number of v sequence at start           */
/*          long  v_lc_to  : location number of v sequence at end             */
/*          long  w_lc_from: location number of w sequence at start           */
/*          long  w_lc_to  : location number of v sequence at end             */
/*          long   ident_cnt  : Count of identities                           */
/*          double ident_rate : Rate  of identities                           */
/*          long   score      : Similary Score of blosum                      */
/*          int  compare_mode : Sequence compare mode                         */
/*          int  sequence_mode: Part or ALL                                   */
/*          int  scan_mode    : Ident or HMM                                  */
/*          int  matrix_on    : Use a dot matrix                              */
/*          long   *prescan_orders_p     : Pointer of a number of order       */
/*          long   *prescan_v_loc_p      : Pointer of a v locations           */
/*          long   *prescan_w_loc_p      : Pointer of a w locations           */
/*          double *prescan_hmm_orders_p : Pointer of a number of order(hmm)  */
/*          long   *prescan_hmm_s_loc_p  : Pointer of a start locations(hmm)  */
/*          long   *prescan_hmm_e_loc_p  : Pointer of a end   locations(hmm)  */
/*                                                                            */
/* Output : int : [ 0 : Normal Terminate ] [ -1 : Error Terminate ]           */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/09/30                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added arguments that is identites count, rate and score           */
/*                                                                            */
/* Date   : 2014/06/10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modify calculation method of v_lc_to and w_lc_to.                 */
/*                                                                            */
/* Date   : 2014/12/08                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Modified Adjustment output location of information.               */
/*                                                                            */
/* Date   : 2015/04/18                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Add procedure that an prescan order.                              */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int PrintOutForTextView(
	char *v,
	char *w,
	char **eg,
	long **ss,
	char **bp,
	char *v_ans,
	char *w_ans,
	char *ans,
	char *eg_arr,
	long *ss_arr,
	char *bp_arr,
	long  inum,
	long  jnum,
	long  vnum,
	long  wnum,
	long  ansnum,
	long  egnum,
	long  ssnum,
	long  bpnum,
	long  v_lc_from,
	long  v_lc_to,
	long  w_lc_from,
	long  w_lc_to,
        long   ident_cnt,
        double ident_rate,
        long  score,
        int   compare_mode,
	int   sequence_mode,
	int   scan_mode,
	int matrix_on,
	int region_order,
	long *prescan_orders_p,
	long *prescan_v_loc_p,
	long *prescan_w_loc_p,
	double *prescan_hmm_orders_p,
	long *prescan_hmm_s_loc_p,
	long *prescan_hmm_e_loc_p
){
	int ret;				/* Return value              */
	long cnt;				/* Counter                   */
	long cnt_buf;				/* Counter for buffer        */
	long i;					/* Loop counter i            */
	long j;					/* Loop counter j            */
	char buf[BUFFER_SIZE];			/* Buffer for sprintf        */
	GtkTextBuffer *textbuf;			/* TextBuffer for answer     */
	GtkTextIter    start;			/* TextIter at start         */
	GtkTextIter    end;			/* TextIter at start         */
	int x_min;				/* x axsis minimum           */
	int y_min;				/* y axsis munimum           */
	int s_digit;
	int e_digit;

						/* Variable for digit        */
	float calc_digit;
						/* Number of digit           */
	int digit_num;
						/* Number of out put textbuf */
	int  put_to;
						/* Number of current         */
	long current_no;
						/* Number of fifth(1/5)      */
	long fifth_num;
						/* Format string             */
						/*           for column no   */
 	char format_str[BUFFER_SIZE];
						/* Pointer of msgbox         */
	GtkWidget *msgbox;
	char  *stored_v;
	char  *stored_w;
	char  *stored_gap;
	char  *stored_ans;
	char **stored_eg;
	long **stored_ss;
	char **stored_bp;
						/* Color for background      */
	GdkColor color;
						/* Array of pre-scan orders  */
	long prescan_orders[PRESCNRANK];
	long prescan_v_loc[PRESCNRANK];
	long prescan_w_loc[PRESCNRANK];

	double prescan_hmm_orders[PRESCNRANK];
	long   prescan_hmm_s_loc[PRESCNRANK];
	long   prescan_hmm_e_loc[PRESCNRANK];
						/* Enter Gtk threads         */
	gdk_threads_enter();
						/* Iterater                  */
						/*       for pre-scan orders */
	GtkTreeIter iter;
	GtkTreeIter iter_rm;
	int active_id;

	for( cnt = PRESCNRANK - 1; cnt >= 0; cnt-- ){

		if( gtk_tree_model_iter_nth_child(
			GTK_TREE_MODEL(regionliststore), &iter_rm, NULL, cnt)
		){
			gtk_list_store_remove (regionliststore, &iter_rm );
		}
	}
						/* Copy prescan orders       */
	if( scan_mode == HMMSCAN && sequence_mode == PARTOFSEQUENCE ){

		memcpy( prescan_hmm_orders,
			prescan_hmm_orders_p,
			sizeof(double) * PRESCNRANK
		);

		memcpy( prescan_hmm_s_loc,
			prescan_hmm_s_loc_p,
			sizeof(long) * PRESCNRANK
		);

		memcpy( prescan_hmm_e_loc,
			prescan_hmm_e_loc_p,
			sizeof(long) * PRESCNRANK
		);

		s_digit = max_digit( prescan_hmm_s_loc, PRESCNRANK );
		e_digit = max_digit( prescan_hmm_e_loc, PRESCNRANK );

		sprintf( format_str, "%%.3f : %%0%dld(%%ld)",
			s_digit
		);

		for( cnt = 0; cnt < PRESCNRANK; cnt++ ){

			sprintf( buf, format_str,
				prescan_hmm_orders[cnt],
				prescan_hmm_s_loc[cnt],
				prescan_hmm_e_loc[cnt] -
				prescan_hmm_s_loc[cnt] + 1
			);

			gtk_list_store_append (regionliststore, &iter);

			gtk_list_store_set(
				regionliststore,
				&iter,
				0,
				buf,
				-1
			);
		}

		if( region_order >= 0 ){

			active_id = region_order;
		}else{
			active_id = 0;
		}

		gtk_combo_box_set_active (
			GTK_COMBO_BOX (RegionCombo),
			active_id
		);

	}else if( sequence_mode == PARTOFSEQUENCE ){

		memcpy( prescan_orders,
			prescan_orders_p,
			sizeof(long) * PRESCNRANK
		);

		memcpy( prescan_v_loc,
			prescan_v_loc_p,
			sizeof(long) * PRESCNRANK
		);

		memcpy( prescan_w_loc,
			prescan_w_loc_p,
			sizeof(long) * PRESCNRANK
		);

		s_digit = max_digit( prescan_v_loc, PRESCNRANK );
		e_digit = max_digit( prescan_w_loc, PRESCNRANK );

		sprintf( format_str, "%%ld : %%0%dld(%%0%dld)",
			s_digit, e_digit
		);

		for( cnt = 0; cnt < PRESCNRANK; cnt++ ){

			sprintf(buf, format_str,
				prescan_orders[cnt],
				prescan_v_loc[cnt],
				prescan_orders[cnt]
			);

			//	prescan_w_loc[cnt]
			//);

			gtk_list_store_append (regionliststore, &iter);

			gtk_list_store_set(
				regionliststore,
				&iter,
				0,
				buf,
				-1
			);
		}

		if( region_order >= 0 ){

			active_id = region_order;
		}else{
			active_id = 0;
		}

		gtk_combo_box_set_active (
			GTK_COMBO_BOX (RegionCombo),
			active_id
		);
	}

	int disp_flg = ANS_DISP_FLG | V_DISP_FLG | GAP_DISP_FLG | W_DISP_FLG;
						/* TextBuffer get            */
	textbuf = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview3) );

						/* TextBuffer clear          */
	gtk_text_buffer_get_start_iter( textbuf, &start );
	gtk_text_buffer_get_end_iter( textbuf, &end );
	gtk_text_buffer_delete( textbuf, &start, &end );

						/* TextBuffer4 clear          */
	gtk_text_buffer_get_start_iter( textbuf4, &start );
	gtk_text_buffer_get_end_iter( textbuf4, &end );
	gtk_text_buffer_delete( textbuf4, &start, &end );

						/* TextBuffer5 clear          */
	gtk_text_buffer_get_start_iter( textbuf5, &start );
	gtk_text_buffer_get_end_iter( textbuf5, &end );
	gtk_text_buffer_delete( textbuf5, &start, &end );

						/* TextBuffer6 clear          */
	gtk_text_buffer_get_start_iter( textbuf6, &start );
	gtk_text_buffer_get_end_iter( textbuf6, &end );
	gtk_text_buffer_delete( textbuf6, &start, &end );

						/* TextBuffer7 clear          */
	gtk_text_buffer_get_start_iter( textbuf7, &start );
	gtk_text_buffer_get_end_iter( textbuf7, &end );
	gtk_text_buffer_delete( textbuf7, &start, &end );

						/* TextBuffer8 clear          */
	gtk_text_buffer_get_start_iter( textbuf8, &start );
	gtk_text_buffer_get_end_iter( textbuf8, &end );
	gtk_text_buffer_delete( textbuf8, &start, &end );

						/* Memory allocate            */
						/*  for stored arrarys        */
	stored_v   = g_malloc(
	        sizeof(char) * strlen(v_ans)  + 1 + BUFFER_SIZE
	);

	stored_w   = g_malloc(
	        sizeof(char) * strlen(w_ans)  + 1 + BUFFER_SIZE
	);

	stored_gap = g_malloc(
	        sizeof(char) * strlen(bp_arr) + 1 + BUFFER_SIZE
	);

	stored_ans = g_malloc(
	        sizeof(char) * strlen(ans)    + 1 + BUFFER_SIZE
	);

						/* Memory allocate            */
						/*    of Edit Graph           */
	stored_eg = g_malloc( sizeof(char *) * inum );

	for( i = 0; i < inum; i++ ){
		stored_eg[i] = g_malloc( sizeof(char) * jnum );
	}
	
						/* Memory allocate            */
						/*    of Similary Score       */
	stored_ss = malloc( sizeof(long *) * inum );

	for( i = 0; i < inum; i++ ){
		stored_ss[i] = malloc( sizeof(long) * jnum );
		memset( stored_ss[i], '\0', (sizeof(long) * jnum) );
	}
	
						/* Memory allocate            */
						/*   of Back tracking pointer */
	stored_bp = malloc( sizeof(char *) * inum );

	for( i = 0; i < inum; i++ ){
		stored_bp[i] = malloc( sizeof(char) * jnum );
		memset( stored_bp[i], '\0', (sizeof(char) * jnum) );
	}

						/* Check for allocated        */
	if(     (stored_v   == NULL) ||
	        (stored_w   == NULL) ||
	        (stored_gap == NULL) ||
	        (stored_ans == NULL) ||
	        (stored_eg  == NULL) ||
	        (stored_ss  == NULL) ||
	        (stored_bp  == NULL)
	){
						/* Case of error when return  */

						/* Output error dialog        */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_CLOSE,
			"Deficient memory."
		);
		gtk_dialog_run( GTK_DIALOG( msgbox ) );
		gtk_widget_destroy( msgbox );
					/* Return with error terminate        */
		return(-1);
	}

						/* Output of v_ans           */
	if( disp_flg & V_DISP_FLG ){

		for( cnt = vnum - 1, cnt_buf = 0; cnt >= 0; cnt--, cnt_buf++ ){
			stored_v[cnt_buf] = v_ans[cnt];
		}
		stored_v[cnt_buf] = '\0';
						/* Output of sequence number */
		v_lc_to = v_lc_from + strlen(stored_v) - 1;

		sprintf( buf, ",%ld,%ld", v_lc_from, v_lc_to );
		strcat( stored_v, buf );
	}
						/* Output of bp_arr          */
	if( disp_flg & GAP_DISP_FLG ){
	
		for( cnt = bpnum - 1, cnt_buf = 0; cnt >= 0; cnt--, cnt_buf++ ){
			stored_gap[cnt_buf] = bp_arr[cnt];
		}
		stored_gap[cnt_buf] = '\0';
	}
						/* Output of w_ans           */
	if( disp_flg & W_DISP_FLG ){

		for( cnt = wnum - 1, cnt_buf = 0; cnt >= 0; cnt--, cnt_buf++ ){
			stored_w[cnt_buf] = w_ans[cnt];
		}
		stored_w[cnt_buf] = '\0';
						/* Output of sequence number */
		w_lc_to = w_lc_from + strlen(stored_w) - 1;

		sprintf( buf, ",%ld,%ld", w_lc_from, w_lc_to );
		strcat( stored_w, buf );
	}
						/* Output of ans             */
	if( disp_flg & ANS_DISP_FLG ){

		for(    cnt = ansnum - 1, cnt_buf = 0;
		        cnt >= 0;
		        cnt--, cnt_buf++
		){
			stored_ans[cnt_buf] = ans[cnt];

			put_sequence(
			        textbuf,
			        ans[cnt],
			        eg_arr[cnt] / 10,
			        compare_mode
			);

			if( (cnt % COLUMN_LIMIT) == 0 && (cnt != 0) ){
				put_sequence(
	 				textbuf,
					'\n',
					999,
					compare_mode
				);
			}
		}
		stored_ans[cnt_buf] = '\0';
						/* Output of sequence number */
		sprintf(buf,
			",1,%ld,%ld,%.2f,%ld",
			cnt_buf, ident_cnt, ident_rate, score / 10
		);
		strcat( stored_ans, buf );

		//gtk_text_buffer_insert_at_cursor( textbuf, buf, strlen(buf) );
	}
						/* Output of EditGraph       */
	if( disp_flg & EG_DISP_FLG ){
						/* Header (w sequence)       */
		sprintf(buf,"v\\w");
		gtk_text_buffer_insert_at_cursor( textbuf, buf, strlen(buf) );	

		for( j = 1; j < jnum - 1; j++ ){
			sprintf(buf,",%c",w[j]);
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	
		}				/* -1 mean footer null       */

		sprintf(buf,"\n");
		gtk_text_buffer_insert_at_cursor( textbuf, buf, strlen(buf) );	

                for( i = 1; i < inum - 1; i++ ){
						/* Header (v sequence)       */
						/* -1 mean footer null       */
			sprintf(buf,"%c",v[i]);
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	

			for( j = 1; j < jnum - 1; j++ ){
         
				sprintf(buf, ",%d",eg[i][j]);
				gtk_text_buffer_insert_at_cursor(
					textbuf, buf, strlen(buf)
				);	
			}
 
			sprintf(buf, "\n");
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	
		}
	}
						/* Output of SimilaryScore   */
	if( disp_flg & SS_DISP_FLG ){
						/* Header (w sequence)       */
		sprintf(buf,"v\\w");
		gtk_text_buffer_insert_at_cursor( textbuf, buf, strlen(buf) );	

		for( j = 1; j < jnum - 1; j++ ){
			sprintf(buf,",%c",w[j]);
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	
		}				/* -1 mean footer null       */

		sprintf(buf,"\n");
		gtk_text_buffer_insert_at_cursor( textbuf, buf, strlen(buf) );	

		for( i = 1; i < inum - 1; i++ ){
						/* Header (v sequence)       */
						/* -1 mean footer null       */
			sprintf(buf,"%c",v[i]);
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	

			for( j = 1; j < jnum - 1; j++ ){
         
				sprintf(buf, ",%ld",ss[i][j]);
				gtk_text_buffer_insert_at_cursor(
					textbuf, buf, strlen(buf)
				);	
			}
 
			sprintf(buf, "\n");
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	
		}
	}
						/* Output of                 */
						/*       BacktrackingPointer */
	if( disp_flg & BP_DISP_FLG ){
						/* Header (w sequence)       */
		sprintf(buf,"v\\w");
		gtk_text_buffer_insert_at_cursor( textbuf, buf, strlen(buf) );	

		for( j = 1; j < jnum - 1; j++ ){
			sprintf(buf,",%c",w[j]);
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	
		}				/* -1 mean footer null       */

		sprintf(buf,"\n");
		gtk_text_buffer_insert_at_cursor( textbuf, buf, strlen(buf) );	

                for( i = 1; i < inum - 1; i++ ){
						/* Header (v sequence)       */
						/* -1 mean footer null       */
			sprintf(buf,"%c",v[i]);
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	
            
			for( j = 1; j < jnum - 1; j++ ){
         
				sprintf(buf, ",%c",bp[i][j]);
				gtk_text_buffer_insert_at_cursor(
					textbuf, buf, strlen(buf)
				);	
			}
 
			sprintf(buf, "\n");
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	
		}
	}

						/* Copy to stored buffer      */
						/* from calculated edit graph */
	for( i = 0; i < inum; i++ ){
		for( j = 0; j < jnum; j++ ){
			stored_eg[i][j] = eg[i][j];
		}
	}
						/* Copy to stored buffer from */
						/* calculated similarly score */
	for( i = 0; i < inum; i++ ){
		for( j = 0; j < jnum; j++ ){
			stored_ss[i][j] = ss[i][j];
		}
	}
						/* Copy to stored buffer      */
						/* from calculated            */
						/* back traking pointer       */
	for( i = 0; i < inum; i++ ){
		for( j = 0; j < jnum; j++ ){
			stored_bp[i][j] = bp[i][j];
		}
	}
						/* Set stored arrary pointer  */
						/*     to scope in callback.c */
	ret = set_ans_str(
		&v,
		&w,
		&stored_v,
	        &stored_w,
	        &stored_gap,
	        &stored_ans,
	        &stored_eg,
	        &stored_ss,
	        &stored_bp,
	        inum,
	        jnum
	);

	if( ret != 0 ){
						/* Error return               */
		return(-1);
	}
						/* Put identify count         */
	sprintf( buf, "No.%ld-%ld", v_lc_from, v_lc_to );
	gtk_label_set_text( GTK_LABEL(Location_label), buf );

						/* Put identify rate          */
	sprintf(buf,
		"ID %.0f%c(%ld)",
	        ident_rate * 100,
		'%',
	        ident_cnt
	);
	gtk_label_set_text( GTK_LABEL(Rate_label), buf );

						/* Put score                  */
	sprintf( buf, "SCR %ld", score / 10 );
	gtk_label_set_text( GTK_LABEL(Score_label), buf );

	if(matrix_on == OFF){
						/* Leave Gtk threads          */
		gdk_flush();
		gdk_threads_leave();
	
		return(0);
	}
						/* Output of report           */

						/* Calculate digit            */

						/* Initialize digit_num       */
	digit_num = 0;
						/* Set vnum number            */
	calc_digit = (float)vnum;
	while( calc_digit > 1 ){
						/* Increment digit            */
		digit_num++;
						/* Divide by 10 (1/10)        */
		calc_digit = calc_digit / 10;
	}
						/* Initialize current number  */
	current_no = 0;
	
						/* Calculate 1/5              */
	if( vnum > SPLIT_NUM ){
		fifth_num = (vnum - 1) / 5;
	}else{
		fifth_num = SPLIT_NUM / 5;
	}

						/* Initialize number          */
						/*     of out put textbuffer  */
	put_to = 3;
						/* Out put loop               */
	for( cnt = vnum - 1; cnt >= 0; cnt--, current_no++ ){

						/* Change to next textbuffer  */
		if( (current_no % fifth_num) == 0 ){
						/* Interval 1/5 times         */

						/* Increment buffer no        */
			put_to++;

			switch( put_to ){
				case 4:
						/* Change to Textbuffer4      */
					textbuf = textbuf4;
					break;
				case 5:
						/* Change to Textbuffer5      */
					textbuf = textbuf5;
					break;
				case 6:
						/* Change to Textbuffer6      */
					textbuf = textbuf6;
					break;
				case 7:
						/* Change to Textbuffer7      */
					textbuf = textbuf7;
					break;
				case 8:
						/* Change to Textbuffer8      */
					textbuf = textbuf8;
					break;
			}
		}
						/* Output number of row       */
		
						/* Set digit format           */
		sprintf( format_str, "%%0%dld", digit_num );
		sprintf( buf, format_str, current_no );

						/* Get position of output     */
		gtk_text_buffer_get_end_iter( textbuf, &end );

						/* Output number              */
		gtk_text_buffer_insert_with_tags_by_name(
		        textbuf,
		        &end,
		        buf,
		        strlen(buf),
		        "NUMBER",
		        NULL
		);

						/* Change from '-' to '|'     */
						/*                  in v_ans  */
		if( v_ans[cnt] == '-' ){
			put_sequence(textbuf,'|',        999,compare_mode);
		}else{
			put_sequence(textbuf,v_ans[cnt], 999,compare_mode);
		}
						/* Change from '|' to '-'     */
						/*                  in bp_arr */
		if( bp_arr[cnt] == '|' ){
			put_sequence(textbuf,'=',        999,compare_mode);
		}else{
			put_sequence(textbuf,bp_arr[cnt], 999,compare_mode);
		}
						/* Change from '-' to '|'     */
						/*                  in w_ans  */
		if( w_ans[cnt] == '-' ){
			put_sequence(textbuf,'|',        999,compare_mode);
		}else{
			put_sequence(textbuf,w_ans[cnt], 999,compare_mode);
		}
						/* Output ans                 */
		put_sequence(textbuf,ans[cnt],   999,compare_mode);

						/* Out put score with color   */

						/* Set digit 3                */
		sprintf( buf, "%3d", eg_arr[cnt] / 10 );
						/* Get position of output     */
		gtk_text_buffer_get_end_iter( textbuf, &end );
						/* Put part of number string  */
		put_sequence(textbuf,buf[0],eg_arr[cnt] / 10,compare_mode);

						/* Get position of output     */
		gtk_text_buffer_get_end_iter( textbuf, &end );
						/* Put part of number string  */
		put_sequence(textbuf,buf[1],eg_arr[cnt] / 10,compare_mode);

						/* Get position of output     */
		gtk_text_buffer_get_end_iter( textbuf, &end );
						/* Put part of number string  */
		put_sequence(textbuf,buf[2],eg_arr[cnt] / 10,compare_mode);

						/* Output LF                  */
		put_sequence(textbuf,'\n', 999,compare_mode);
	}
						/* Copy to stored buffer      */
						/* from calculated edit graph */
	//for( i = 0; i < inum; i++ ){
	//	for( j = 0; j < jnum; j++ ){
	//		stored_eg[i][j] = eg[i][j];
	//	}
	//}
						/* Copy to stored buffer from */
						/* calculated similarly score */
	//for( i = 0; i < inum; i++ ){
	//	for( j = 0; j < jnum; j++ ){
	//		stored_ss[i][j] = ss[i][j];
	//	}
	//}
						/* Copy to stored buffer      */
						/* from calculated            */
						/* back traking pointer       */
	//for( i = 0; i < inum; i++ ){
	//	for( j = 0; j < jnum; j++ ){
	//		stored_bp[i][j] = bp[i][j];
	//	}
	//}
						/* Set stored arrary pointer  */
						/*     to scope in callback.c */
	//ret = set_ans_str(
	//	&v,
	//	&w,
	//	&stored_v,
	//      &stored_w,
	//      &stored_gap,
	//      &stored_ans,
	//      &stored_eg,
	//      &stored_ss,
	//      &stored_bp,
	//      inum,
	//      jnum
	//);

	//if( ret != 0 ){
						/* Error return               */
	//	return(-1);
	//}
						/* Put identify count         */
	//sprintf( buf, "No.%ld-%ld", v_lc_from, v_lc_to );
	//gtk_label_set_text( GTK_LABEL(Location_label), buf );

						/* Put identify rate          */
	//sprintf(buf,
	//	"ID %.0f%c(%ld)",
	//      ident_rate * 100,
	//	'%',
	//      ident_cnt
	//);
	//gtk_label_set_text( GTK_LABEL(Rate_label), buf );

						/* Put score                  */
	//sprintf( buf, "SCR %ld", score / 10 );
	//gtk_label_set_text( GTK_LABEL(Score_label), buf );

						/* Set mininum sizes          */
	if(inum <= 200){
		x_min = 200 - inum;
	}else{
		x_min = 50;
	}

	if(jnum <= 180){
		y_min = 180 - jnum;
	}else{
		y_min = 60;
	}
						/* Resize drawing area        */
	gtk_drawing_area_size(
		GTK_DRAWING_AREA(drawingArea1),
		(gint)inum + x_min,
		(gint)jnum + y_min 
	);
						/* Set background color(white)*/
						/*            of drawing area */
	color.red   = 65535;
	color.green = 65535;
	color.blue  = 65535;
						/* Set color to drawing area  */
	gtk_widget_modify_bg(
	        drawingArea1,
	        GTK_WIDGET_STATE(drawingArea1),
	        &color
	);
						/* Create new pixmap          */
	if( pmap != NULL ){
		g_object_unref( pmap );
	}
	pmap = gdk_pixmap_new(
		NULL,
	        (gint)inum + x_min,
	        (gint)jnum + y_min,
	        24
	);

	ret = draw_matrix( &pmap );
						/* Request draw               */
	gtk_widget_queue_draw( drawingArea1 );
						/* Threshold vscale sensitie  */
	//gtk_widget_set_sensitive( GTK_WIDGET( threshold_num_vscale ), TRUE );

						/* Leave Gtk threads          */
	gdk_flush();
	gdk_threads_leave();
	
	return(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Function of main()                                                */
/* Function Name : main()                                                     */
/*                                                                            */
/* Detail : main                                                              */
/* Date   : 2010/09/16                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-main.com                                        */
/*                                                                            */
/* Input  : int   argc   : Arguments count                                    */
/*        : char *argv[] : Arguments value                                    */
/* Output : int : return code  NormalTerminate[0]  Error[!=0]                 */
/*                                                                            */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int main (int argc, char *argv[]){

					/* Pointer of window                  */
 	GtkWidget *window;
					/* Pointer of buffer for textview     */
	GtkTextBuffer *buf;
					/* Return value                       */
	int ret;
					/* General purpose counter            */
	int cnt;

	int output_mode;

#ifdef ENABLE_NLS
	bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);
#endif
					/* Set gtk locale                     */
	gtk_set_locale ();
					/* Set default output mode            */
	output_mode = GUI_MODE;
					/* Get arguments                      */
        for( cnt = 0; cnt < argc; cnt++ ){

		if( strcmp( argv[cnt], "-h" ) == 0 ){
					/*                      Help          */
			output_mode = CUI_MODE;
			break;

		}else if( strcmp( argv[cnt], "-cui" ) == 0 ){
					/*                      CUI mode      */
			output_mode = CUI_MODE;
			break;

		}else if( strcmp( argv[cnt], "-gui" ) == 0 ){
					/*                      GUI mode      */
			output_mode = GUI_MODE;
			break;
		}
        }
					/* Mode CUI                           */
	if( output_mode == CUI_MODE ){	
					/* Call to cui_main()                 */
		ret = cui_main( argc, argv );

	}else{
					/* Mode GUI                           */

					/* Initializes thread                 */
		g_thread_init(NULL);
		gdk_threads_init();
					/* Check for gtk initialize           */
		if( gtk_init_check( &argc, &argv ) == FALSE ){

					/* Call to cui_main()                 */
			ret = cui_main( argc, argv );
		}
					/* Create window                      */
		window = create_window ();
					/* Swap delete event                  */
		g_signal_connect_swapped(
				GTK_WINDOW(window),
				"delete_event",
				GTK_SIGNAL_FUNC( delete_event ),
				NULL
		);
					/* Put message to textview1           */
		buf = gtk_text_view_get_buffer(	GTK_TEXT_VIEW(textview1) );
					/* Get pointer of buffer              */
		gtk_text_buffer_set_text(
					/* Set message                        */
		        buf,
		        "Please paste [SOURCE DATA] at this area,"\
			" or drag & drop."
		        , -1
		);

					/* Put message to textview2           */
		buf = gtk_text_view_get_buffer(	GTK_TEXT_VIEW(textview2) );
					/* Get pointer of buffer              */
		gtk_text_buffer_set_text(
					/* Set message                        */
		        buf,
		        "Please paste [TARGET DATA] at this area,"\
		        " or drag & drop.",
		        -1
		);
					/* Show window                        */
		gtk_widget_show (window);
					/* Call gtk_main()                    */
		gtk_main ();
					/* Set return value                   */
		ret = 0;
	}
					/* Return                             */
	return( ret );
}
