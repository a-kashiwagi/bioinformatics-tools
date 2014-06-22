/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/*
 * callbacks.c
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "callbacks.h"

					/* Declare GtkWidget                  */
					/*            for each object         */
GtkWidget *window;
GtkWidget *vbox1;
GtkWidget *hbox1;
GtkWidget *scrolledwindow1;
GtkWidget *scrolledwindow2;
GtkWidget *textview1;
GtkWidget *textview2;
GtkWidget *textview3;
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

					/* Display flag                       */
int  disp_flg = ANS_DISP_FLG;
					/* Aligment mode                      */
int  alignment_mode = LOCAL_ALIGNMENT;
					/* Gap score mode                     */
int  gapscore_mode = LINER_GAP_SCORE;
					/* Compare mode                       */
int  compare_mode = AMINOACID;
					/* Sequence mode                      */
int  sequence_mode = PARTOFSEQUENCE;

					/* Number of match                    */
long match_num = 10;
					/* Number of unmatch                  */
long unmatch_num = 0;
					/* Number of gap penalty              */
long d_num = 10;
					/* Number of                          */
					/*    affine gap penalty              */
long e_num = 5;

					/* Number of Replace score            */
					/*    amplification                   */
long rs_num;

/******************************************************************************/
/*                                                                            */
/* Title  : Set object to callback area                                       */
/* Function Name : set_object_to_callback_area()                              */
/*                                                                            */
/* Detail : set object to callback area                                       */
/* Date   : 2010/09/12                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkBuilder *builder : Pointer of builder                          */
/* Output : Rerutn code : NormalTerminate [0]                                 */
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

int set_objects_to_callback_area( GtkBuilder *builder ){

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

	return(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : On exec button clicked                                            */
/* Function Name : on_exec_clicked()                                          */
/*                                                                            */
/* Detail : On exec button clicked                                            */
/* Date   : 2010/09/12                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkWidget *widget : Pointer of button                             */
/*        : gpointer user_data                                                */
/* Output : void                                                              */
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
void on_exec_clicked( GtkWidget *widget, gpointer user_data ){

					/* Pointer of sequence v              */
	char *v;
					/* Pointer of sequence w              */
	char *w;
					/* Number of i                        */
	long inum;
					/* Number of j                        */
	long jnum;
					/* Text buffer for work               */
	GtkTextBuffer *work;
					/* Text Itereter of start             */
	GtkTextIter start;
					/* Text Itereter of end               */
	GtkTextIter end;

	// char param_text[1024];

					/* Set match number from spin button  */
	match_num       = gtk_spin_button_get_value_as_int(
				GTK_SPIN_BUTTON(match_num_spin)
			);
					/* Set unmatch number                 */
					/*        from spin button            */
	unmatch_num     = gtk_spin_button_get_value_as_int(
				GTK_SPIN_BUTTON(unmatch_num_spin)
			);
					/* Set d number from spin button      */
	d_num		= gtk_spin_button_get_value_as_int(
				GTK_SPIN_BUTTON(d_num_spin)
			);
					/* Set e number from spin button      */
	e_num		= gtk_spin_button_get_value_as_int(
				GTK_SPIN_BUTTON(e_num_spin)
			);
					/* Set number of replace score        */
					/*    amplification                   */
	rs_num = 10;
/*
	sprintf( param_text, "%d," \
	        "alignment_mode[%d]," \
	        "gapscore_mode[%d]," \
	        "compare_mode[%d]," \
	        "sequence_mode[%d],\n" \
	        "match_num[%d]," \
	        "unmatch_num[%d]," \
	        "d_num[%d]," \
	        "e_num[%d]," \
	        "rs_num[%d]\n",
	        0,
		alignment_mode,	
		gapscore_mode,
		compare_mode,
		sequence_mode,
	        match_num,
	        unmatch_num,
	        d_num,
	        e_num,
	        rs_num
	);
	work = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview2) );
	gtk_text_buffer_set_text( work, param_text, -1 );
*/
						/* Set parameter to lcs scope */
	set_lcs_param( 0,
		alignment_mode,	
		gapscore_mode,
		compare_mode,
		sequence_mode,
	        match_num,
	        unmatch_num,
	        d_num,
	        e_num,
	        rs_num
	);

						/* Get sequence of v          */

	work = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview1) );
						/* get pointer of text buffer */

	gtk_text_buffer_get_start_iter( work, &start );
						/* get start iterator         */

	gtk_text_buffer_get_end_iter( work, &end );
						/* get end iterator           */

	v = gtk_text_buffer_get_text( work, &start, &end, TRUE );
						/* get string from text buffer*/

	inum = strlen( v ) + 1;
						/* set string length          */

	
						/* Get sequence of w          */

	work = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview2) );
						/* get pointer of text buffer */

	gtk_text_buffer_get_start_iter( work, &start );
						/* get start iterator         */

	gtk_text_buffer_get_end_iter( work, &end );
						/* get end iterator           */

	w = gtk_text_buffer_get_text( work, &start, &end, TRUE );
						/* get string from text buffer*/

	jnum = strlen( w ) + 1;
						/* set string length          */

						/* Call lcs function          */
	lcs( v, w, inum, jnum );
}

						/* Call back function         */
						/*       of object destroy    */
void
destroy (GtkWidget *widget, gpointer data)
{
						/* Call destractor            */
	gtk_main_quit ();
}

						/* Call back function         */
						/*    of comparemode 0 togged */
void
on_comparemode0_toggled (GtkRadioButton *self, gpointer user_data)
{
						/* Set comapre_mode           */
						/*       to Nucleotide (0)    */
	compare_mode = NUCLEOTIDE;
}

						/* Call back function         */
						/*    of comparemode 1 togged */
void
on_comparemode1_toggled (GtkRadioButton *self, gpointer user_data)
{
						/* Set comapre_mode           */
						/*       to Amino Acid (1)    */
	compare_mode = AMINOACID;
}

						/* Call back function         */
						/*   of sequencemode 0 togged */
void
on_sequencemode0_toggled (GtkRadioButton *self, gpointer user_data)
{
						/* Set sequence_mode          */
						/*   to part of sequence (0)  */
	sequence_mode = PARTOFSEQUENCE;
}

						/* Call back function         */
						/*   of sequencemode 1 togged */
void
on_sequencemode1_toggled (GtkRadioButton *self, gpointer user_data)
{
						/* Set sequence_mode          */
						/*        to all sequence (1) */
	sequence_mode = ALLSEQUENCE;
}

						/* Call back function         */
						/*  of alignmentmode 0 togged */
void
on_alignmentmode0_toggled (GtkRadioButton *self, gpointer user_data)
{
						/* Set alignment_mode         */
						/*   to global aliginment (0) */
	alignment_mode = GLOBAL_ALIGNMENT;
}

						/* Call back function         */
						/*  of alignmentmode 1 togged */
void
on_alignmentmode1_toggled (GtkRadioButton *self, gpointer user_data)
{
						/* Set alignment_mode         */
						/*     to local alignment (1) */
	alignment_mode = LOCAL_ALIGNMENT;
}

						/* Call back function         */
						/*  of gapscoremode 0 toggled */
void
on_gapscoremode0_toggled (GtkRadioButton *self, gpointer user_data)
{
						/* Set gapscore_mode          */
						/*     to liner gap score (0) */
	gapscore_mode = LINER_GAP_SCORE;
}

						/* Call back function         */
						/*  of gapscoremode 1 toggled */
void
on_gapscoremode1_toggled (GtkRadioButton *self, gpointer user_data)
{
						/* Set alignment_mode         */
						/*    to affine gap score (1) */
	gapscore_mode = AFFINE_GAP_SCORE;
}

void
on_textview1_backspace (GtkTextView *self, gpointer user_data)
{
	put_message( "on_textview1_backspace!\n" );

}

void
on_textview1_paste_clipboard (GtkTextView *self, gpointer user_data)
{
	put_message( "on_textview1_paste_clipboard!\n" );
	
}

void
on_textview1_insert_at_cursor (GtkTextView *self, gchararray arg0, gpointer user_data)
{
	put_message( "on_textview1_insert_at_cursor!\n" );

}

/******************************************************************************/
/*                                                                            */
/* Title  : Call back on textbuf insert                                       */
/* Function Name : on_textbuf_insert()                                        */
/*                                                                            */
/* Detail : Call back on textbuf insert                                       */
/* Date   : 2010/09/18                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkWidget   *self : Pointer of text buffer                        */
/*        : GtkTextIter *iter : Iterator of text buffer                       */
/*        : gchar       *text : Insert text                                   */
/*        : gint         len  : Length of insert text                         */
/*        :                                                                   */
/* Output : void                                                              */
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

void on_textbuf_insert(
	GtkTextBuffer *self,
	GtkTextIter *iter,
	gchar *text,
	gint len
){
					/* General purpose counter            */
	long cnt;
					/* Number of offsert from start       */
	gint offset;
					/* Tag name                           */
	char tagname[20];
					/* Iterator of start                  */
	GtkTextIter start;
					/* Iterator of end                    */
	GtkTextIter end;
					/* Get offset of iter                 */
	offset = gtk_text_iter_get_offset( iter );

					/* Set iterator at start of text      */
	gtk_text_buffer_get_iter_at_offset( self, &start, offset - len + 0 );

					/* Set iterator at end of text        */
	gtk_text_buffer_get_iter_at_offset( self, &end  , offset - len + 1 );

					/* Set tag name                       */
	for( cnt = 0; cnt < len; cnt++ ){

		switch( text[cnt] ){
					/* Set tag name of Adenine           */
			case 'A':
				strcpy( tagname, "Adenine");
				break;
					/* Set tag name of Thymine           */
			case 'T':
				strcpy( tagname, "Thymine");
				break;
					/* Set tag name of Guanine           */
			case 'G':
				strcpy( tagname, "Guanine");
				break;
					/* Set tag name of Cytosine          */
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
					/* Set tag name of other             */
			default:
				strcpy( tagname, "Normal");
				break;
		}
					/* Apply tag                         */
		gtk_text_buffer_apply_tag_by_name( self, tagname, &start, &end );

					/* Increment iterator                */
		gtk_text_iter_forward_char( &start );
		gtk_text_iter_forward_char( &end );
	}
}
