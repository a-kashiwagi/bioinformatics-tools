/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/*
 * main.c
 *
 * Generated anjuta and glade. and writed by Kashiwagi Akihiro.
 *
 * Copyright (C) Kashiwagi Akihiro 2010 <a-kashiwagi@mippi-mail.com>
 * 
 * lcs_gui is free software and shareware : you can redistribute it and/or
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

#define UI_FILE PACKAGE_DATA_DIR"/lcs_gui/ui/lcs_gui.ui"

GtkWidget *create_window ( void );
int set_tags_to_textbuffer( GtkTextBuffer *textbuf );
int put_sequence( GtkTextBuffer *textbuf, char ch);
int PrintOutForTextViwe(
	char *v,
	char *w,
	char **eg,
	long **ss,
	char **bp,
	char *v_ans,
	char *w_ans,
	char *ans,
	char *bp_arr,
	long  inum,
	long  jnum,
	long  vnum,
	long  wnum,
	long  ansnum,
	long  bpnum,
	long  v_lc_from,
	long  v_lc_to,
	long  w_lc_from,
	long  w_lc_to
);

					/* declare pointer of each object     */
					/*                in created builder  */
GtkWidget *vbox1;
GtkWidget *hbox1;
GtkWidget *scrolledwindow1;
GtkWidget *scrolledwindow2;
GtkWidget *textview1;
GtkTextBuffer *textbuf1;
GtkWidget *textview2;
GtkTextBuffer *textbuf2;
GtkWidget *textview3;
GtkTextBuffer *textbuf3;
GtkWidget *comparetype0_radio;
GtkWidget *comparetype1_radio;
GtkWidget *comparemode0_radio;
GtkWidget *comparemode1_radio;
GtkWidget *alignmentmode0_radio;
GtkWidget *alignmentmode1_radio;
GtkWidget *gapscoremode0_radio;
GtkWidget *gapscoremode1_radio;
GtkWidget *label1;
GtkWidget *label2;
GtkWidget *e_num_spin;
GtkWidget *d_num_spin;
GtkWidget *match_num_spin;
GtkWidget *unmatch_num_spin;
GtkWidget *adjustment1;
GtkWidget *adjustment2;
GtkWidget *adjustment3;
GtkWidget *adjustment4;

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
	GtkWidget *window;
	GtkBuilder *builder;
	GError* error = NULL;
	GtkTextBuffer *textbuf;

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

					/* Get comparetype0 object            */
	comparetype0_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "comparetype0")
	);
					/* Get comparetype1 object            */
	comparetype1_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "comparetype1")
	);
					/* Get comparemode0 object            */
	comparemode0_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "comparemode0")
	);
					/* Get comparemode1 object            */
	comparemode1_radio = GTK_WIDGET (
	    gtk_builder_get_object (builder, "comparemode1")
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
					/* Get adjustment1 object             */
	adjustment1 = GTK_WIDGET (
	        gtk_builder_get_object (builder, "adjustment1")
	);
					/* Get adjustment2 object             */
	adjustment2 = GTK_WIDGET (
	        gtk_builder_get_object (builder, "adjustment2")
	);
					/* Get adjustmnet3 object             */
	adjustment3 = GTK_WIDGET (
	        gtk_builder_get_object (builder, "adjustment3")
	);
					/* Get adjustment4 object             */
	adjustment4 = GTK_WIDGET (
	        gtk_builder_get_object (builder, "adjustment4")
	);
					/* Set object to callback area too    */
	set_objects_to_callback_area( GTK_BUILDER(builder) );
					/* Set value to spin button e_num     */
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( e_num_spin ), (gdouble)5 );
					/* Set value to spin button d_num     */
	gtk_spin_button_set_value( GTK_SPIN_BUTTON( d_num_spin ), (gdouble)10 );
					/* Set value to spin button match_num */
	gtk_spin_button_set_value(
		GTK_SPIN_BUTTON( match_num_spin ), (gdouble)10
	);
					/* Set value to spin button           */
					/*                      unmatch_num   */
	gtk_spin_button_set_value(
	        GTK_SPIN_BUTTON( unmatch_num_spin ), (gdouble)0
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

					/* Unreference builder object         */
	g_object_unref (builder);
	
	return window;
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
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int set_tags_to_textbuffer( GtkTextBuffer *textbuf ){

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
/* Output : int : NormalTerminate [0]                                         */
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

int put_sequence( GtkTextBuffer *textbuf, char ch){

					/* Buffer for output                  */
	char buf[4];
					/* Tagname for output                 */
	char tagname[20];
					/* Iterator of current cursor         */
	GtkTextIter cur;

					/* Set tag name                       */
	switch(ch){
					/* for Adenine                        */
		case 'A':
			strcpy( tagname, "Adenine");
			break;
					/* for Thymine                        */
		case 'T':
			strcpy( tagname, "Thymine");
			break;
					/* for Guanine                        */
		case 'G':
			strcpy( tagname, "Guanine");
			break;
					/* for Cytosine                       */
		case 'C':
			strcpy( tagname, "Cytosine");
			break;
					/* Set tag name of Phenylalane       */
		case 'F':
			strcpy( tagname, "Phenylalane");
			break;
					/* Set tag name of Leucine           */
		case 'L':
			strcpy( tagname, "Leucine");
			break;
					/* Set tag name of Serine            */
		case 'S':
			strcpy( tagname, "Serine");
			break;
					/* Set tag name of Tyrosine          */
		case 'Y':
			strcpy( tagname, "Tyrosine");
			break;
					/* Set tag name of Cysteine          */
		/*
		case 'C':
			strcpy( tagname, "Cysteine");
			break;
		*/
					/* Set tag name of Tryptophan        */
		case 'W':
			strcpy( tagname, "Tryptophan");
			break;
					/* Set tag name of Proline           */
		case 'P':
			strcpy( tagname, "Proline");
			break;
					/* Set tag name of Histidine         */
		case 'H':
			strcpy( tagname, "Histidine");
			break;
					/* Set tag name of Glutamine         */
		case 'Q':
			strcpy( tagname, "Glutamine");
			break;
					/* Set tag name of Arginine          */
		case 'R':
			strcpy( tagname, "Arginine");
			break;
					/* Set tag name of Isoleucine        */
		case 'I':
			strcpy( tagname, "Isoleucine");
			break;
					/* Set tag name of Methionine        */
		case 'M':
			strcpy( tagname, "Methionine");
			break;
					/* Set tag name of Threonine         */
		/*
		case 'T':
			strcpy( tagname, "Threonine");
			break;
		*/
					/* Set tag name of Asparagine        */
		case 'N':
			strcpy( tagname, "Asparagine");
			break;
					/* Set tag name of Lysine            */
		case 'K':
			strcpy( tagname, "Lysine");
			break;
					/* Set tag name of Valine            */
		case 'V':
			strcpy( tagname, "Valine");
			break;
					/* Set tag name of Alanine           */
		/*
		case 'A':
			strcpy( tagname, "Alanine");
			break;
		*/
					/* Set tag name of AsparagineAcid    */
		case 'D':
			strcpy( tagname, "AsparagineAcid");
			break;
					/* Set tag name of GlutamicAcid      */
		case 'E':
			strcpy( tagname, "GlutamicAcid");
			break;
					/* Set tag name of Glycine           */
		/*
		case 'G':
			strcpy( tagname, "Glycine");
			break;
		*/
					/* for Other                          */
		default:
			strcpy( tagname, "Normal");
			break;
	}
					/* Set buffer                         */
	sprintf( buf, "%c", ch );
					/* Get end iterator                   */
	gtk_text_buffer_get_end_iter( textbuf, &cur );

					/* Put character with tag             */
	gtk_text_buffer_insert_with_tags_by_name(
	        textbuf, &cur, buf, strlen(buf),
	        tagname,
	        NULL
	);
					/* Return normal terminate            */
	return(0);
}

/* Function for test */
int put_message( char *str ){

	gtk_text_buffer_insert_at_cursor( textbuf3, str, strlen(str) );
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
/*          char *bp_arr   : Buffer of Back tracking pointer                  */
/*          long  inum     : Number of i array                                */
/*          long  jnum     : Number of j array                                */
/*          long  vnum     : Number of w array                                */
/*          long  wnum     : Number of w array                                */
/*          long  ansnum   : Number of anser array                            */
/*          long  bpnum    : Number of back tracking arrary                   */
/*          long  v_lc_from: location number of v sequence at start           */
/*          long  v_lc_to  : location number of v sequence at end             */
/*          long  w_lc_from: location number of w sequence at start           */
/*          long  w_lc_to  : location number of v sequence at end             */
/*                                                                            */
/* Output : int : [ 0 : Normal Terminate ]                                    */
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

int PrintOutForTextViwe(
	char *v,
	char *w,
	char **eg,
	long **ss,
	char **bp,
	char *v_ans,
	char *w_ans,
	char *ans,
	char *bp_arr,
	long  inum,
	long  jnum,
	long  vnum,
	long  wnum,
	long  ansnum,
	long  bpnum,
	long  v_lc_from,
	long  v_lc_to,
	long  w_lc_from,
	long  w_lc_to
){
	long cnt;				/* Counter                   */
	long i;					/* Loop counter i            */
	long j;					/* Loop counter j            */
	long ident_cnt;				/* Counter of Identify number*/
	double ident_rate;			/* Rate of Identify number   */
	char buf[BUFFER_SIZE];			/* Buffer for sprintf        */
	GtkTextBuffer *textbuf;			/* TextBuffer for answer     */
	GtkTextIter   start;			/* TextIter at start         */
	GtkTextIter   end;			/* TextIter at start         */

	int disp_flg = ANS_DISP_FLG;
						/* TextBuffer get            */
	textbuf = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview3) );

						/* TextBuffer clear          */
	gtk_text_buffer_get_start_iter( textbuf, &start );
	gtk_text_buffer_get_end_iter( textbuf, &end );
	gtk_text_buffer_delete( textbuf, &start, &end );
	
	ident_cnt = 0;
	for( cnt = bpnum - 1; cnt > 0; cnt-- ){
		if( bp_arr[cnt] == '|' ){
			ident_cnt++;
		}
	}
	ident_rate = (double)ident_cnt / (double)(bpnum - 1);
						/* Output of v_ans           */
	if( disp_flg & V_DISP_FLG ){

		for( cnt = vnum - 1; cnt > 0; cnt-- ){
			sprintf(buf,"%c", v_ans[cnt] );
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	
		}
						/* Output of sequence number */
		sprintf(buf,
			",%ld,%ld,%ld,%.2f,v\n",
			v_lc_from, v_lc_to, ident_cnt, ident_rate
		);
		gtk_text_buffer_insert_at_cursor( textbuf, buf, strlen(buf) );	
	}
						/* Output of bp_arr          */
	if( disp_flg & GAP_DISP_FLG ){
	
		for( cnt = bpnum - 1; cnt > 0; cnt-- ){
			sprintf( buf, "%c", bp_arr[cnt] );
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	
		}
						/* Output LF                 */
		sprintf(buf, "\n");
		gtk_text_buffer_insert_at_cursor( textbuf, buf, strlen(buf) );	
	}
						/* Output of w_ans           */
	if( disp_flg & W_DISP_FLG ){

		for( cnt = wnum - 1; cnt > 0; cnt-- ){
			sprintf( buf, "%c", w_ans[cnt] );
			gtk_text_buffer_insert_at_cursor(
				textbuf, buf, strlen(buf)
			);	
		}
						/* Output of sequence number */
		sprintf(buf,
			",%ld,%ld,%ld,%.2f\n,w",
			w_lc_from, w_lc_to, ident_cnt, ident_rate
		);
		gtk_text_buffer_insert_at_cursor( textbuf, buf, strlen(buf) );	
	}
						/* Output of ans             */
	if( disp_flg & ANS_DISP_FLG ){
	
		for( cnt = ansnum - 1; cnt >= 0; cnt-- ){
			put_sequence( textbuf, ans[cnt] );
		}
						/* Output of sequence number */
		sprintf(buf,
			",%ld,%ld,%ld,%.2f\n",
			v_lc_from, v_lc_to, ident_cnt, ident_rate
		);
		gtk_text_buffer_insert_at_cursor( textbuf, buf, strlen(buf) );	
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

int
main (int argc, char *argv[])
{
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

					/* Check for gtk initialize           */
	}else if( gtk_init_check( &argc, &argv ) == FALSE ){

					/* Call to cui_main()                 */
		ret = cui_main( argc, argv );

	}else{
					/* Mode GUI                           */

					/* Create window                      */
		window = create_window ();
					/* Show window                        */
		gtk_widget_show (window);

					/* Put message to textview1           */
		buf = gtk_text_view_get_buffer(	GTK_TEXT_VIEW(textview1) );
					/* Get pointer of buffer              */
		gtk_text_buffer_set_text(
					/* Set message                        */
		        buf, "Please paste [SOURCE DATA] at this area.", -1
		);

					/* Put message to textview2           */
		buf = gtk_text_view_get_buffer(	GTK_TEXT_VIEW(textview2) );
					/* Get pointer of buffer              */
		gtk_text_buffer_set_text(
					/* Set message                        */
		        buf, "Please paste [TARGET DATA] at this area.", -1
		);
					/* Call gtk_main()                    */
		gtk_main ();
					/* Set return value                   */
		ret = 0;
	}
					/* Return                             */
	return( ret );
}
