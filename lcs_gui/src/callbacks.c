/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/*
 * callbacks.c
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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <pthread.h>
#include <math.h>
#include "callbacks.h"

					/* Declare GtkWidget                  */
					/*            for each object         */

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
GtkWidget *textview1;
					/* For target area                    */
GtkWidget *textview2;
					/* For allocated sequence area        */
GtkWidget *textview3;
					/* For report                         */
GtkWidget *textview4;
GtkWidget *textview5;
GtkWidget *textview6;
GtkWidget *textview7;
GtkWidget *textview8;
					/* For source sequence                */
GtkTextBuffer *textbuf1;
					/* For target sequence                */
GtkTextBuffer *textbuf2;
					/* For allocated seqence              */
GtkTextBuffer *textbuf3;
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
					/* Quit button                        */
GtkWidget *quit_button;
					/* Excecute button                    */
GtkWidget *exec_button;
					/* For affine gap number              */
GtkAdjustment *adjustment1;
					/* For Liner gap number               */
GtkAdjustment *adjustment2;
					/* For Match number                   */
GtkAdjustment *adjustment3;
					/* For Unmatch number                 */
GtkAdjustment *adjustment4;
					/* For matrix                         */
GtkWidget *drawingArea1;
					/* For matrix                         */
GdkPixmap *pm = NULL;


					/* Display flag                       */
int  disp_flg = ANS_DISP_FLG;
					/* Pre scan mode                      */
int  scan_mode = HMMSCAN;
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
					/* Saving flag                        */
int now_saving;

					/* Number of Replace score            */
					/*    amplification                   */
long rs_num;
					/* SourceFileName                     */
char SourceFileName[BUFFER_SIZE];
					/* TargetFileName                     */
char TargetFileName[BUFFER_SIZE];
					/* SaveFileName                       */
char SaveFileName[BUFFER_SIZE];
					/* Pointer of source sequence         */
char *SourceSequence = NULL;
					/* Pointer of target sequence         */
char *TargetSequence = NULL;
		
					/* Pointer for stored                 */

					/* Sequence v                         */
char  *stored_v   = NULL;
					/* Sequence w                         */
char  *stored_w   = NULL;
					/* Sequence gap                       */
char  *stored_gap = NULL;
					/* Sequence ans                       */
char  *stored_ans = NULL;
					/* Sequence edit graph                */
char **stored_eg  = NULL;
					/* Sequence similary score            */
char **stored_ss  = NULL;
					/* Sequence back tracking pointer     */
char **stored_bp  = NULL;
					/* inum stored                        */
long stored_inum;
					/* jnum stored                        */
long stored_jnum;

/******************************************************************************/
/*                                                                            */
/* Title  : Function of setter of stored arrays.                              */
/* Function Name : lcs_quit()                                                 */
/*                                                                            */
/* Detail : Set pointer of v,w,gap,ans to each pointers.                      */
/* Date   : 2010/11/04                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char **v   : Pointer of v   : &(char *v)                          */
/*          char **w   : Pointer of w   : &(char *w)                          */
/*          char **gap : Pointer of gap : &(char *gap)                        */
/*          char **ans : Pointer of ans : &(char *ans)                        */
/*          char ***eg : Pointer of eg  : &(char **eg)                        */
/*          char ***ss : Pointer of ss  : &(char **ss)                        */
/*          char ***bp : Pointer of eg  : &(char **bp)                        */
/* Output : int : [ 0 : Normal terminate ]                                    */
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
int set_ans_str(
        char **v,
        char **w,
        char **gap,
        char **ans,
        char ***eg,
        char ***ss,
        char ***bp,
        long inum,
        long jnum
){

	long i;
						/* Check for pointer          */
	if( stored_v != NULL ){
						/* Case of already set        */
						/*        when free memory    */
		g_free(stored_v);
	}
						/* Set pointer address        */
	stored_v = *v;

						/* Check for pointer          */
	if( stored_w != NULL ){
						/* Case of already set        */
						/*        when free memory    */
		g_free(stored_w);
	}
						/* Set pointer address        */
	stored_w = *w;

						/* Check for pointer          */
	if( stored_gap != NULL ){
						/* Case of already set        */
						/*        when free memory    */
		g_free(stored_gap);
	}
						/* Set pointer address        */
	stored_gap = *gap;

						/* Check for pointer          */
	if( stored_ans != NULL ){
						/* Case of already set        */
						/*        when free memory    */
		g_free(stored_ans);
	}
						/* Set pointer address        */
	stored_ans = *ans;
						/* Check for pointer          */
	if( stored_eg != NULL ){
						/* Case of already set        */
						/*        when free memory    */
		for( i = 0; i < stored_inum; i++ ){
			g_free(stored_eg[i]);
		}
		g_free(stored_eg);
	}
						/* Check for pointer          */
	if( stored_ss != NULL ){
						/* Case of already set        */
						/*        when free memory    */
		for( i = 0; i < stored_inum; i++ ){
			g_free(stored_ss[i]);
		}
		g_free(stored_ss);
	}
						/* Check for pointer          */
	if( stored_bp != NULL ){
						/* Case of already set        */
						/*        when free memory    */
		for( i = 0; i < stored_inum; i++ ){
			g_free(stored_bp[i]);
		}
		g_free(stored_bp);
	}
						/* Set pointer address        */
	stored_eg = *eg;
	stored_ss = *ss;
	stored_bp = *bp;
	stored_inum = inum;
	stored_jnum = jnum;
						/* Normal terminate           */
	return(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Function of LCS quit                                              */
/* Function Name : lcs_quit()                                                 */
/*                                                                            */
/* Detail : Check textview3 modified, put comfirm dialog, save and quit.      */
/* Date   : 2010/10/17                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
/* Output : int TRUE:Don't quit  FALSE:Quit                                   */
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

int lcs_quit( void ){

						/* Pointer of Text Buffer     */
	GtkTextBuffer *textbuffer;
						/* Pointer of GtkMessageDialog*/
	GtkWidget *msgbox;
						/* Get pointer of textbuffer  */
	textbuffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview3) );

						/* Check modified flag        */
	if( gtk_text_buffer_get_modified( textbuffer ) == TRUE ){

						/* Case of modified           */

						/* Output question dialog     */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			"You didn't save yet.\n\n"\
			"file : [%s]\n\n"\
			"Will you quit?",
			SaveFileName
		);

		if( gtk_dialog_run(GTK_DIALOG(msgbox)) == GTK_RESPONSE_NO ){

						/* Don't quit                 */
			gtk_widget_destroy( msgbox );
			return(TRUE);
		}
		gtk_widget_destroy( msgbox );
	}
						/* Quit                       */
	return(FALSE);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Call back function of object destroy                              */
/* Function Name : destroy                                                    */
/*                                                                            */
/* Detail : Call back function of object destroy,from QUIT button, QUIT menu. */
/* Date   : 2010/11/01                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkWidget *widget                                                 */
/*          gpointer data                                                     */
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

void
destroy (GtkWidget *widget, gpointer data)
{
					/* Call quiestion to quit or continue */
	if( lcs_quit () == FALSE ){
					/* Quit                               */
		gtk_main_quit();
	}
					/* Don't quit                         */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Signal function of object delete.                                 */
/* Function Name : lcs_quit()                                                 */
/*                                                                            */
/* Detail : Signal function of object delete,from destroy button in window.   */
/* Date   : 2010/11/01                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkWidget *widget                                                 */
/*          GdkEvent  *event                                                  */
/*          gpointer   data                                                   */
/* Output : int : FALSE:Quit  TRUE:Don't quit                                 */
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

gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data ){

					/* Call quiestion to quit or continue */
	return( lcs_quit() );
					/* FALSE:Quit  TRUE:Don't quit        */
}

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

					/* Title message                      */
	char title_msg[BUFFER_SIZE];

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

					/* Get text buffer 1                  */
	textbuf1 = GTK_TEXT_BUFFER(
	        gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview1) )
	);
					/* Get text buffer 2                  */
	textbuf2 = GTK_TEXT_BUFFER(
	        gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview2) )
	);
					/* Get text buffer 3                  */
	textbuf3 = GTK_TEXT_BUFFER(
	        gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview3) )
	);
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
					/* Get scanmode1 object            */
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
					/* Get quit                           */
	quit_button = GTK_WIDGET (
		gtk_builder_get_object (builder, "quit" )
	); 
					/* Get exec                           */
	exec_button = GTK_WIDGET (
		gtk_builder_get_object (builder, "exec" )
	);
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
					/* Get drawingArea1 object            */
	drawingArea1 = GTK_WIDGET (
	        gtk_builder_get_object (builder, "drawingarea1")
	);

					/* Initialize SaveFileName            */
	strcpy( SaveFileName, SAVEFILENAME );
					/* Make title message                 */
	sprintf( title_msg, "%s - %s", APP_TITLE, SaveFileName );
					/* Set title                          */
	gtk_window_set_title( GTK_WINDOW(window), title_msg );

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

pthread_t thread;
int on_thread_flg;

void on_exec_clicked( GtkWidget *widget, gpointer user_data ){

						/* Threading flag ON          */
	on_thread_flg = ON;
						/* Call to lcs_thread()       */
						/*                  in thread */
	pthread_create( &thread, NULL, (void *)lcs_thread, NULL );
	//lcs_thread();
}


/******************************************************************************/
/*                                                                            */
/* Title  : Function of lcs thread                                            */
/* Function Name : lcs_thread()                                               */
/*                                                                            */
/* Detail : Call to lcs() in thread                                           */
/* Date   : 2010/09/23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
/* Output : int : [Normal Terminate 0]  [Error 1]                             */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/10/29                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure that when big size file.                          */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int lcs_thread(void){

					/* Pointer of sequence v              */
	char *v;
					/* Pointer of sequence w              */
	char *w;
					/* Number of i                        */
	long inum;
					/* Number of j                        */
	long jnum;
					/* Return code                        */
	int ret;
					/* Text buffer for work               */
	GtkTextBuffer *work;
					/* Text Itereter of start             */
	GtkTextIter start;
					/* Text Itereter of end               */
	GtkTextIter end;
					/* Label string for store             */
	char label_str[BUFFER_SIZE];

	// char param_text[1024];
					/* Pointer of widget                  */
	GtkWidget *msgbox;
					/* Thread in                          */
	on_thread_flg = ON;
					/* Set grayed out to exec_button      */
	gtk_widget_set_sensitive( GTK_WIDGET(exec_button), FALSE );
	
					/* Get label for store                */
	strcpy( label_str, gtk_button_get_label( GTK_BUTTON(exec_button) ) );

					/* Set label "Processing..."          */
	gtk_button_set_label( GTK_BUTTON(exec_button), "Processing..." );

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
	        "scan_mode[%d]," \
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
		scan_mode,
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
	set_lcs_param(
		0,
		alignment_mode,	
		gapscore_mode,
		scan_mode,
		compare_mode,
		sequence_mode,
	        match_num,
	        unmatch_num,
	        d_num,
	        e_num,
	        rs_num
	);
	
	work = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview1) );
						/* get pointer of text buffer */
	if( gtk_text_buffer_get_modified( work ) == TRUE ){
						/* When modified              */
		if( SourceSequence != NULL ){
						/* Free SourceSequence buffer */
						/* because this buffer        */
						/*     was not using already. */
			free( SourceSequence );
			SourceSequence = NULL;
		}
	}

	if( SourceSequence != NULL ){
						/* Memory allocate to v       */
						/* because v buffer           */
						/*        is freed by lcs()   */
		v = malloc( strlen( SourceSequence ) + 1 );

		if( v == NULL ){
					/* Case of error when return          */

					/* Output error dialog                */
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
			return(1);
		}
						/* Copy sequence to v buffer  */
		strcpy( v, SourceSequence );
			
						/* Set sequence data          */
		//v = SourceSequence;

	}else{
						/* Get sequence of w          */

		gtk_text_buffer_get_start_iter( work, &start );
						/* get start iterator         */

		gtk_text_buffer_get_end_iter( work, &end );
						/* get end iterator           */

		v = gtk_text_buffer_get_text( work, &start, &end, TRUE );
	}
						/* get string from text buffer*/
	inum = clean_up_sequence( v );
						/* clean up sequence string   */

						/* get pointer of text buffer */
	work = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview2) );

	if( gtk_text_buffer_get_modified( work ) == TRUE ){
						/* When modified              */
		if( TargetSequence != NULL ){
						/* Free TargetSequence buffer */
						/* because this buffer        */
						/*     was not using already. */
			free( TargetSequence );
			TargetSequence = NULL;
		}
	}

	if( TargetSequence != NULL ){
						/* Memory allocate to w       */
						/* because w buffer           */
						/*        is freed by lcs()   */
		w = malloc( strlen( TargetSequence ) + 1 );

		if( w == NULL ){
					/* Case of error when return          */

					/* Output error dialog                */
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
			return(1);
		}
						/* Copy sequence to w buffer  */
		strcpy( w, TargetSequence );

						/* Set sequence data          */
		//w = TargetSequence;

	}else{
						/* Get sequence of w          */

		gtk_text_buffer_get_start_iter( work, &start );
						/* get start iterator         */

		gtk_text_buffer_get_end_iter( work, &end );
						/* get end iterator           */

		w = gtk_text_buffer_get_text( work, &start, &end, TRUE );
	}
						/* get string from text buffer*/
	jnum = clean_up_sequence( w );
						/* clean up sequence string   */

						/* Call lcs function          */
	ret = lcs( v, w, inum, jnum );

						/* Set label to exec_button   */
	gtk_button_set_label( GTK_BUTTON(exec_button), label_str );
	
					        /* Set active to exec_button  */
	gtk_widget_set_sensitive( GTK_WIDGET(exec_button), TRUE );
	
						/* Thread out                 */
	on_thread_flg = OFF;
						/* Return code                */
	return(ret);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Following functions is callback for each radio buttons.           */
/* Function Name : on_[RADIO BUTTON NAME]_toggled()                           */
/*                                                                            */
/* Detail : Call to lcs() in thread                                           */
/* Date   : 2010/09/23                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkRadioButton *self : Called pointer of radio_button             */
/*        : gpointer user_data   : Non use                                    */
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
					/* Set acitivate to scan mode radio   */
	gtk_widget_set_sensitive( scanmode0_radio, TRUE );
	gtk_widget_set_sensitive( scanmode1_radio, TRUE );
}

						/* Call back function         */
						/*   of sequencemode 1 togged */
void
on_sequencemode1_toggled (GtkRadioButton *self, gpointer user_data)
{
						/* Set sequence_mode          */
						/*        to all sequence (1) */
	sequence_mode = ALLSEQUENCE;

					/* Set grayed out to scan mode radio  */
	gtk_widget_set_sensitive( scanmode0_radio, FALSE );
	gtk_widget_set_sensitive( scanmode1_radio, FALSE );

						/* Change status              */
	gtk_toggle_button_set_active( scanmode0_radio, TRUE );
	gtk_toggle_button_set_active( scanmode1_radio, FALSE );
}

						/* Call back function         */
						/*   of scanmode 0 togged     */
void
on_scanmode0_toggled (GtkRadioButton *self, gpointer user_data)
{
						/* Set scan_mode              */
						/*   to part of sequence (0)  */
	scan_mode = IDENTSCAN;
}

						/* Call back function         */
						/*   of scanmode 1 togged     */
void
on_scanmode1_toggled (GtkRadioButton *self, gpointer user_data)
{
						/* Set scan_mode              */
						/*        to all sequence (1) */
	scan_mode = HMMSCAN;
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
/******************************************************************************/
/*                                                                            */
/* Title  : Get sequence function for text buffer                             */
/* Function Name : GetSequence                                                */
/*                                                                            */
/* Detail :                                                                   */
/* Date   : 2010/10/03                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* E-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : char *filename : Target file name                                 */
/*          char *buff : Buffer of data of sequence                           */
/*                                                                            */
/* Output : long : [ Count of loaded charactar : Normal Terminate ]           */
/*                 [ -1                        : Error            ]           */
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

long GetSequenceForTextBuffer( char *filename, char *buff ){

	FILE *fp;				/* File pointer               */
	long cnt;				/* Counter                    */
	long in_char;				/* In character               */
	long column_cnt;			/* Column counter             */
	
	fp = fopen( filename, "r" );		/* File open                  */
	if( fp == NULL ){			/* Error                      */
		return(-1);
	}
	
	in_char = fgetc( fp );			/* Get a character from file  */
	cnt = 0;				/* Counter initialize         */
	column_cnt = 0;
	
	while( in_char != EOF ){
	
		in_char = toupper( in_char );	/* Convert to upper           */

		buff[cnt] = in_char;		/* Copy to buffer             */
		cnt++;				/* Counter increment          */

		if( column_cnt == COLUMN_LIMIT ){
						/* Case of column limit to LF */
			buff[cnt] = '\n';
			cnt++;

			column_cnt = 0;

		}else if( in_char == '\n' ){
						/* Case of LF                 */
						/*        to counter reset    */
			column_cnt = 0;
		}else{
						/* Other charactar            */
						/*    to counter increment    */
			column_cnt++;
		}
		
		in_char = fgetc( fp );		/* Get next character         */
	}

	buff[cnt] = '\0';			/* Set null at footer         */
	
	fclose( fp );				/* File close                 */
	return(cnt + 1);			/* Normal terminate           */
}

/******************************************************************************/
/*                                                                            */
/* Title  : Store source file name from file select dialog                    */
/* Function Name : store_srcfilename()                                        */
/*                                                                            */
/* Detail : Store source file name from file select dialog                    */
/*          and read source file.                                             */
/* Date   : 2010/10/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkWidget    *self : Pointer of text buffer                       */
/*        : gpointer user_data : Pointer of gtk_file_selection                */
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

void store_srcfilename( GtkWidget *self, gpointer user_data ){

					/* Pointer of file selection dialog   */
	GtkWidget *fileselector;
					/* Converted file name                */
	char *fname;
                                        /* for store bytes_read parameter     */
        gsize *bytes_read;
                                        /* for store bytes_write parameter    */
        gsize *bytes_write;
                                        /* for store error parameter          */
        GError **error;

					/* Cast to GtkWidget                  */
	fileselector = GTK_WIDGET( user_data );
					/* Convert to UTF-8                   */ 
					/*       from GLib file name encoding */
	fname = g_filename_to_utf8(
					/* Get file name                      */ 
	 				/*         from file selection dialog */
	        gtk_file_selection_get_filename(
		        GTK_FILE_SELECTION( fileselector )
		),
	        -1,
	        bytes_read,
	        bytes_write,
	        error
	);
					/* Store filename                     */
	strcpy( SourceFileName, fname );
					/* Free to fname buffer               */
	g_free( fname );
					/* Load file to text view             */
	SourceSequence = LoadFileToTextView(
	        SourceFileName,
	        GTK_TEXT_VIEW(textview1)
	);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Store target file name from file select dialog                    */
/* Function Name : store_srcfilename()                                        */
/*                                                                            */
/* Detail : Store target file name from file select dialog                    */
/*          and read target file.                                             */
/* Date   : 2010/10/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkWidget    *self : Pointer of text buffer                       */
/*        : gpointer user_data : Pointer of gtk_file_selection                */
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

void store_trgfilename( GtkWidget *widget, gpointer user_data ){

					/* Pointer of file selection dialog   */
	GtkWidget *fileselector;
					/* Converted file name                */
	char *fname;
                                        /* for store bytes_read parameter     */
        gsize *bytes_read;
                                        /* for store bytes_write parameter    */
        gsize *bytes_write;
                                        /* for store error parameter          */
        GError **error;

					/* Cast to GtkWidget                  */
	fileselector = GTK_WIDGET( user_data );
					/* Convert to UTF-8                   */ 
					/*       from GLib file name encoding */
	fname = g_filename_to_utf8(
					/* Get file name                      */ 
	 				/*         from file selection dialog */
	        gtk_file_selection_get_filename(
		        GTK_FILE_SELECTION( fileselector )
		),
	        -1,
	        bytes_read,
	        bytes_write,
	        error
	);
					/* Store filename                     */
	strcpy( TargetFileName, fname );
					/* Free to fname buffer               */
	g_free( fname );
					/* Load file to text view             */
	TargetSequence = LoadFileToTextView(
	        TargetFileName,
	        GTK_TEXT_VIEW(textview2)
	);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Store save file name from file select dialog                      */
/* Function Name : save_srcfilename()                                         */
/*                                                                            */
/* Detail : Store save file name from file select dialog                      */
/* Date   : 2010/10/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkWidget    *self : Pointer of text buffer                       */
/*        : gpointer user_data : Pointer of gtk_file_selection                */
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

void store_savefilename( GtkWidget *widget, gpointer user_data ){

					/* Pointer of file selection dialog   */
	GtkWidget *fileselector;
					/* For function of g_filename_to_utf8 */

					/* Converted file name                */
	char *fname;
					/* for store bytes_read parameter     */
	gsize *bytes_read;
					/* for store bytes_write parameter    */
	gsize *bytes_write;
					/* for store error parameter          */
	GError **error;
					/* Title message                      */
	char title_msg[BUFFER_SIZE];

					/* Cast to GtkWidget                  */
	fileselector = GTK_WIDGET( user_data );
					/* Convert to UTF-8                   */ 
					/*       from GLib file name encoding */
	fname = g_filename_to_utf8(
					/* Get file name                      */ 
	 				/*         from file selection dialog */
	        gtk_file_selection_get_filename(
		        GTK_FILE_SELECTION( fileselector )
		),
	        -1,
	        bytes_read,
	        bytes_write,
	        error
	);
					/* Store filename                     */
	strcpy( SaveFileName, fname );
					/* Free to fname buffer               */
	g_free( fname );
					/* Make title message                 */
	sprintf( title_msg, "%s [%s]", APP_TITLE, SaveFileName );
					/* Set title                          */
	gtk_window_set_title( GTK_WINDOW(window), title_msg );
					/* Save file                          */
	SaveFile();
}

/******************************************************************************/
/*                                                                            */
/* Title  : Call back from menu of file when activate SourceFileOpen          */
/* Function Name : on_OpenSrc_item_activate()                                 */
/*                                                                            */
/* Detail : Call back from menu of file when activate SourceFileOpen          */
/* Date   : 2010/10/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkImageMenuItem *self : Pointer of text buffer                   */
/*        : gpointer user_data     :                                          */
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

void on_OpenSrc_item_activate (GtkImageMenuItem *self, gpointer user_data){
	
					/* Pointer of file selection dialog   */
	GtkWidget *fileselector;
					/* Create new file selection dialog   */
	fileselector = gtk_file_selection_new(
	        "Please select SOURCE file."
	);
					/* Set signal connect                 */
					/*         to store_srcfilename       */
					/*       from file selection dialog   */
	g_signal_connect(
	        GTK_FILE_SELECTION( fileselector )->ok_button,
	        "clicked",
	        G_CALLBACK( store_srcfilename ),
	        fileselector
	);
					/* Set signal connect                 */
					/*          when push OK button       */
	g_signal_connect_swapped(
	        GTK_FILE_SELECTION( fileselector )->ok_button,
	        "clicked",
	        G_CALLBACK( gtk_widget_destroy ),
	        fileselector
	);
					/* Set signal connect                 */
					/*          when push CANCEL button   */
	g_signal_connect_swapped(
	        GTK_FILE_SELECTION( fileselector )->cancel_button,
	        "clicked",
	        G_CALLBACK( gtk_widget_destroy ),
	        fileselector
	);

	if( SourceFileName[0] != '\0' ){
					/* Set default directory and file     */
		gtk_file_selection_set_filename(
		        GTK_FILE_SELECTION(fileselector),
		        SourceFileName
		);
	}
					/* Show dialog                        */
	gtk_widget_show( fileselector );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Call back from menu of file when activate TargetFileOpen          */
/* Function Name : on_OpenSrc_item_activate()                                 */
/*                                                                            */
/* Detail : Call back from menu of file when activate TargetFileOpen          */
/* Date   : 2010/10/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkImageMenuItem *self : Pointer of text buffer                   */
/*        : gpointer user_data     :                                          */
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

void on_OpenTrg_item_activate (GtkImageMenuItem *self, gpointer user_data){
	
					/* Pointer of file selection dialog   */
	GtkWidget *fileselector;

					/* Create new file selection dialog   */
	fileselector = gtk_file_selection_new(
	        "Please select TARGET file."
	);
					/* Set signal connect                 */
					/*         to store_trgfilename       */
					/*       from file selection dialog   */
	g_signal_connect(
	        GTK_FILE_SELECTION( fileselector )->ok_button,
	        "clicked",
	        G_CALLBACK( store_trgfilename ),
	        fileselector
	);
					/* Set signal connect                 */
					/*          when push OK button       */
	g_signal_connect_swapped(
	        GTK_FILE_SELECTION( fileselector )->ok_button,
	        "clicked",
	        G_CALLBACK( gtk_widget_destroy ),
	        fileselector
	);
					/* Set signal connect                 */
					/*          when push CANCEL button   */
	g_signal_connect_swapped(
	        GTK_FILE_SELECTION( fileselector )->cancel_button,
	        "clicked",
	        G_CALLBACK( gtk_widget_destroy ),
	        fileselector
	);

	if( TargetFileName[0] != '\0' ){
					/* Set default directory and file     */
		gtk_file_selection_set_filename(
		        GTK_FILE_SELECTION(fileselector),
		        TargetFileName
		);
	}
					/* Show dialog                        */
	gtk_widget_show( fileselector );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Call back from menu of file when activate SaveFileOpen Item       */
/* Function Name : on_Save_item_activate()                                    */
/*                                                                            */
/* Detail : Call function SaveFile()                                          */
/* Date   : 2010/10/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkImageMenuItem *self : Pointer of text buffer                   */
/*        : gpointer user_data     :                                          */
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

void on_Save_item_activate (GtkImageMenuItem *self, gpointer user_data){

						/* Call SaveFile() function   */
	SaveFile();
}

/******************************************************************************/
/*                                                                            */
/* Title  : Save file                                                         */
/* Function Name : SaveFile()                                                 */
/*                                                                            */
/* Detail : The file [SaveFileName] save.                                     */
/* Date   : 2010/10/17                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
/* Output : void                                                              */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2010/10/29                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure that filename convert to file system encoding.    */
/*                                                                            */
/* Date   : 2010/12/04                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure that matrix picture save to file.                 */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

int SaveFile( void ){
						/* Pointer of message dialog  */
	GtkWidget *msgbox;
						/* Counter                    */
	long cnt;
						/* File pointer               */
	FILE *fp;
					/* Converted file name                */
					/* from Gtk encoding(utf)             */
					/*            to File system encoding */
 	char *fname;
	                                /* for store bytes_read parameter     */
        gsize *bytes_read;
                                        /* for store bytes_write parameter    */
        gsize *bytes_write;
                                        /* for store error parameter          */
        GError **error;
					/* Pointer of pixbuf for save         */
	GdkPixbuf *pb;
					/* File name for pixbuf               */
	char fname_for_pb[BUFFER_SIZE];
					/* File name for cvs                  */
	char fname_for_cvs[BUFFER_SIZE];
					/* Width of pixmap                    */
	int pm_width;
					/* Height of pixmap                   */
	int pm_height;
					/* Counter of i                       */
	long i;
					/* Counter of j                       */
	long j;

					/* Allocated sequence save to file    */

					/* Get Save file name                 */
	strcpy(fname_for_cvs, SaveFileName);
					/* Added suffix                       */
	strcat(fname_for_cvs, ".csv");

					/* Convert to File system encoding    */
					/*       from GLib file name encoding */
	fname = g_filename_from_utf8(
		fname_for_cvs,
		-1,
		bytes_read,
		bytes_write,
		error
	);
						/* Check for file exist       */
	if( ChkFileSize( fname ) != -1 ){
						/* Case of file existed       */

						/* Output error dialog        */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			"This file existed.\n\n"\
		        "file : [%s].\n\n"\
		        "Will you over write?",
			fname_for_cvs
		);
						/* Will not over write        */
		if( gtk_dialog_run( GTK_DIALOG( msgbox ) ) == GTK_RESPONSE_NO ){

						/* Window close               */
			gtk_widget_destroy( msgbox );
						/* Open file selection dialog */
			on_SaveAs_item_activate( NULL, NULL );
						/* Free to fname buffer       */
			g_free( fname );
						/* Return with error terminate*/
			return(-1);
		}
						/* Window close               */
		gtk_widget_destroy( msgbox );
	}

	fp = fopen( fname, "w" );
						/* File open                  */
	if( fp == NULL ){
						/* Case of error when return  */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_CLOSE,
			"Can not open %s.",
			SaveFileName
		);
		gtk_dialog_run( GTK_DIALOG( msgbox ) );
		gtk_widget_destroy( msgbox );
						/* Free to fname buffer       */
		g_free( fname );
						/* Return                     */
		return(-1);
	}
						/* Check for array            */
	if(	(stored_v   == NULL) ||
		(stored_w   == NULL) ||
		(stored_gap == NULL) ||
		(stored_ans == NULL)
	){
						/* If stored array is NULL    */
						/*               then return  */
		return(0);
	}
						/* Counter reset              */
	cnt = 0;
						/* Loop of output             */
	while( stored_v[cnt] != '\0' ){
						/* Put sequence v             */
		fputc( stored_v[cnt], fp );
						/* Counter increment          */
		cnt++;
	}
	fputc( '\n', fp );
						/* Counter reset              */
	cnt = 0;
						/* Loop of output             */
	while( stored_gap[cnt] != '\0' ){
						/* Put sequence gap           */
		fputc( stored_gap[cnt], fp );
						/* Counter increment          */
		cnt++;
	}
	fputc( '\n', fp );
						/* Counter reset              */
	cnt = 0;
						/* Loop of output             */
	while( stored_w[cnt] != '\0' ){
						/* Put sequence w             */
		fputc( stored_w[cnt], fp );
						/* Counter increment          */
		cnt++;
	}
	fputc( '\n', fp );
						/* Counter reset              */
	cnt = 0;
						/* Loop of output             */
	while( stored_ans[cnt] != '\0' ){
						/* Put sequence ans           */
		fputc( stored_ans[cnt], fp );
						/* Counter increment          */
		cnt++;
	}
	fputc( '\n', fp );
						/* File close                 */
	fclose( fp );
						/* Free to fname buffer       */
	g_free( fname );
						/* Set modifiy TRUE           */
	gtk_text_buffer_set_modified( GTK_TEXT_BUFFER(textbuf3), FALSE );


					/* Matrix save to file                */

						/* Get save file name         */
	strcpy(fname_for_pb, SaveFileName);
						/* Added suffix               */
	strcat(fname_for_pb, ".png");
					/* Convert to File system encoding    */
					/*       from GLib file name encoding */
	fname = g_filename_from_utf8(
		fname_for_pb,
		-1,
		bytes_read,
		bytes_write,
		error
	);
						/* Check for file exist       */
	if( ChkFileSize( fname ) != -1 ){
						/* Case of file existed       */

						/* Output error dialog        */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			"This file existed.\n\n"\
		        "file : [%s].\n\n"\
		        "Will you over write?",
			fname_for_pb
		);
						/* Will not over write        */
		if( gtk_dialog_run( GTK_DIALOG( msgbox ) ) == GTK_RESPONSE_NO ){

						/* Window close               */
			gtk_widget_destroy( msgbox );
						/* Open file selection dialog */
			on_SaveAs_item_activate( NULL, NULL );
						/* Free to fname buffer       */
			g_free( fname );
						/* Return with error terminate*/
			return(-1);
		}
						/* Window close               */
		gtk_widget_destroy( msgbox );
	}

						/* Get matrix picture         */
						/*                from pixmap */
	if( pm != NULL ){

						/* Get size of pixmap         */
		gdk_drawable_get_size(
			GDK_DRAWABLE(pm),
			&pm_width,
			&pm_height
		);

						/* Get pixbuf from pixmap     */
		pb = gdk_pixbuf_get_from_drawable(
			NULL,
			pm,
			gdk_drawable_get_colormap( GDK_DRAWABLE(pm) ),
			0,0,
			0,0,
			pm_width,
			pm_height
		);

	}else{
						/* If pixmap is null          */
						/*        then pixbuf is null */
		pb = NULL;
	}
						/* Save pixbuf to file        */
	if( pb != NULL ){
	
		gdk_pixbuf_save(
			pb,
			fname,
			"png",
			error,
			"compression",
			"9",
			NULL
		);
	}
					/* Edit graph save to file            */

						/* Get save file name         */
	strcpy(fname_for_pb, SaveFileName);
						/* Added suffix               */
	strcat(fname_for_pb, "_eg.csv");
					/* Convert to File system encoding    */
					/*       from GLib file name encoding */
	fname = g_filename_from_utf8(
		fname_for_pb,
		-1,
		bytes_read,
		bytes_write,
		error
	);
						/* Check for file exist       */
	if( ChkFileSize( fname ) != -1 ){
						/* Case of file existed       */

						/* Output error dialog        */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			"This file existed.\n\n"\
		        "file : [%s].\n\n"\
		        "Will you over write?",
			fname_for_pb
		);
						/* Will not over write        */
		if( gtk_dialog_run( GTK_DIALOG( msgbox ) ) == GTK_RESPONSE_NO ){

						/* Window close               */
			gtk_widget_destroy( msgbox );
						/* Open file selection dialog */
			on_SaveAs_item_activate( NULL, NULL );
						/* Free to fname buffer       */
			g_free( fname );
						/* Return with error terminate*/
			return(-1);
		}
						/* Window close               */
		gtk_widget_destroy( msgbox );
	}

	fp = fopen( fname, "w" );
						/* File open                  */
	if( fp == NULL ){
						/* Case of error when return  */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_CLOSE,
			"Can not open %s.",
			SaveFileName
		);
		gtk_dialog_run( GTK_DIALOG( msgbox ) );
		gtk_widget_destroy( msgbox );
						/* Free to fname buffer       */
		g_free( fname );
						/* Return                     */
		return(-1);
	}
						/* Check for array            */
	if( stored_eg == NULL ){
						/* If stored array is NULL    */
						/*               then return  */
		return(0);
	}
						/* Header (w sequence)       */
	fprintf(fp,"v\\w");

	for( j = 1; j < stored_jnum - 1; j++ ){
						/* Change gap charactar      */
		if( stored_w[j] == '-' ){
						/* '-' to '*'                */
			fprintf(fp,",*");
		}else{
			fprintf(fp,",%c",stored_w[j]);
		}
	}					/* -1 mean footer null       */

	fprintf(fp,"\n");

	for( i = 1; i < stored_inum - 1; i++ ){
						/* Header (v sequence)       */
						/* -1 mean footer null       */

						/* Change gap charactoar     */
		if( stored_v[i] == '-' ){
						/* '-' to '*'                */
			fprintf(fp,"*");
		}else{
			fprintf(fp,"%c",stored_v[i]);
		}	

		for( j = 1; j < stored_jnum - 1; j++ ){

			fprintf(fp, ",%d",stored_eg[i][j]);
		}
 
		fprintf(fp, "\n");
	}
						/* File close                 */
	fclose( fp );
						/* Free to fname buffer       */
	g_free( fname );
					/* Similary score save to file        */

						/* Get save file name         */
	strcpy(fname_for_pb, SaveFileName);
						/* Added suffix               */
	strcat(fname_for_pb, "_ss.csv");
					/* Convert to File system encoding    */
					/*       from GLib file name encoding */
	fname = g_filename_from_utf8(
		fname_for_pb,
		-1,
		bytes_read,
		bytes_write,
		error
	);
						/* Check for file exist       */
	if( ChkFileSize( fname ) != -1 ){
						/* Case of file existed       */

						/* Output error dialog        */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			"This file existed.\n\n"\
		        "file : [%s].\n\n"\
		        "Will you over write?",
			fname_for_pb
		);
						/* Will not over write        */
		if( gtk_dialog_run( GTK_DIALOG( msgbox ) ) == GTK_RESPONSE_NO ){

						/* Window close               */
			gtk_widget_destroy( msgbox );
						/* Open file selection dialog */
			on_SaveAs_item_activate( NULL, NULL );
						/* Free to fname buffer       */
			g_free( fname );
						/* Return with error terminate*/
			return(-1);
		}
						/* Window close               */
		gtk_widget_destroy( msgbox );
	}

	fp = fopen( fname, "w" );
						/* File open                  */
	if( fp == NULL ){
						/* Case of error when return  */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_CLOSE,
			"Can not open %s.",
			SaveFileName
		);
		gtk_dialog_run( GTK_DIALOG( msgbox ) );
		gtk_widget_destroy( msgbox );
						/* Free to fname buffer       */
		g_free( fname );
						/* Return                     */
		return(-1);
	}
						/* Check for array            */
	if( stored_ss == NULL ){
						/* If stored array is NULL    */
						/*               then return  */
		return(0);
	}
						/* Header (w sequence)       */
	fprintf(fp,"v\\w");

	for( j = 1; j < stored_jnum - 1; j++ ){
						/* Change gap charactar      */
		if( stored_w[j] == '-' ){
						/* '-' to '*'                */
			fprintf(fp,",*");
		}else{
			fprintf(fp,",%c",stored_w[j]);
		}
	}					/* -1 mean footer null       */

	fprintf(fp,"\n");

	for( i = 1; i < stored_inum - 1; i++ ){
						/* Header (v sequence)       */
						/* -1 mean footer null       */
		
						/* Change gap charactoar     */
		if( stored_v[i] == '-' ){
						/* '-' to '*'                */
			fprintf(fp,"*");
		}else{
			fprintf(fp,"%c",stored_v[i]);
		}	

		for( j = 1; j < stored_jnum - 1; j++ ){

			fprintf(fp, ",%d",stored_ss[i][j]);
		}
 
		fprintf(fp, "\n");
	}
						/* File close                 */
	fclose( fp );
						/* Free to fname buffer       */
	g_free( fname );
					/* Back tracking pointer save to file */

						/* Get save file name         */
	strcpy(fname_for_pb, SaveFileName);
						/* Added suffix               */
	strcat(fname_for_pb, "_bp.csv");
					/* Convert to File system encoding    */
					/*       from GLib file name encoding */
	fname = g_filename_from_utf8(
		fname_for_pb,
		-1,
		bytes_read,
		bytes_write,
		error
	);
						/* Check for file exist       */
	if( ChkFileSize( fname ) != -1 ){
						/* Case of file existed       */

						/* Output error dialog        */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_QUESTION,
			GTK_BUTTONS_YES_NO,
			"This file existed.\n\n"\
		        "file : [%s].\n\n"\
		        "Will you over write?",
			fname_for_pb
		);
						/* Will not over write        */
		if( gtk_dialog_run( GTK_DIALOG( msgbox ) ) == GTK_RESPONSE_NO ){

						/* Window close               */
			gtk_widget_destroy( msgbox );
						/* Open file selection dialog */
			on_SaveAs_item_activate( NULL, NULL );
						/* Free to fname buffer       */
			g_free( fname );
						/* Return with error terminate*/
			return(-1);
		}
						/* Window close               */
		gtk_widget_destroy( msgbox );
	}

	fp = fopen( fname, "w" );
						/* File open                  */
	if( fp == NULL ){
						/* Case of error when return  */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_CLOSE,
			"Can not open %s.",
			SaveFileName
		);
		gtk_dialog_run( GTK_DIALOG( msgbox ) );
		gtk_widget_destroy( msgbox );
						/* Free to fname buffer       */
		g_free( fname );
						/* Return                     */
		return(-1);
	}
						/* Check for array            */
	if( stored_bp == NULL ){
						/* If stored array is NULL    */
						/*               then return  */
		return(0);
	}
						/* Header (w sequence)       */
	fprintf(fp,"v\\w");

	for( j = 1; j < stored_jnum - 1; j++ ){
						/* Change gap charactar      */
		if( stored_w[j] == '-' ){
						/* '-' to '*'                */
			fprintf(fp,",*");
		}else{
			fprintf(fp,",%c",stored_w[j]);
		}
	}					/* -1 mean footer null       */

	fprintf(fp,"\n");

	for( i = 1; i < stored_inum - 1; i++ ){
						/* Header (v sequence)       */
						/* -1 mean footer null       */
		
						/* Change gap charactoar     */
		if( stored_v[i] == '-' ){
						/* '-' to '*'                */
			fprintf(fp,"*");
		}else{
			fprintf(fp,"%c",stored_v[i]);
		}	

		for( j = 1; j < stored_jnum - 1; j++ ){

			fprintf(fp, ",%c",stored_bp[i][j]);
		}
 
		fprintf(fp, "\n");
	}
						/* File close                 */
	fclose( fp );
						/* Free to fname buffer       */
	g_free( fname );
						/* Set modifiy TRUE           */
	gtk_text_buffer_set_modified( GTK_TEXT_BUFFER(textbuf3), FALSE );

						/* Check for file exist       */
						/* Saving flag OFF            */
	now_saving == OFF;
						/* Return                     */
						/*      with normal terminate */
	return(0);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Call back from menu of file when activate SaveAsFileOpen          */
/* Function Name : on_Save_item_activate()                                    */
/*                                                                            */
/* Detail : Call back from menu of file when activate SaveAsFileOpen          */
/* Date   : 2010/10/02                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkImageMenuItem *self : Pointer of text buffer                   */
/*        : gpointer user_data     :                                          */
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

void on_SaveAs_item_activate (GtkImageMenuItem *self, gpointer user_data){

					/* Pointer of file selection dialog   */
	GtkWidget *fileselector;
					/* Create new file selection dialog   */
	fileselector = gtk_file_selection_new(
	        "Please select or input SAVE file."
	);
					/* Set signal connect                 */
					/*         to store_trgfilename       */
					/*       from file selection dialog   */
	g_signal_connect(
	        GTK_FILE_SELECTION( fileselector )->ok_button,
	        "clicked",
	        G_CALLBACK( store_savefilename ),
	        fileselector
	);
					/* Set signal connect                 */
					/*          when push OK button       */
	g_signal_connect_swapped(
	        GTK_FILE_SELECTION( fileselector )->ok_button,
	        "clicked",
	        G_CALLBACK( gtk_widget_destroy ),
	        fileselector
	);
					/* Set signal connect                 */
					/*          when push CANCEL button   */
	g_signal_connect_swapped(
	        GTK_FILE_SELECTION( fileselector )->cancel_button,
	        "clicked",
	        G_CALLBACK( gtk_widget_destroy ),
	        fileselector
	);
	
	if( SaveFileName[0] != '\0' ){
					/* Set default directory and file     */
		gtk_file_selection_set_filename(
		        GTK_FILE_SELECTION(fileselector),
		        SaveFileName
		);
	}
					/* Show dialog                        */
	gtk_widget_show( fileselector );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Call back function on about item active                           */
/* Function Name : on_Abou_item_activate()                                    */
/*                                                                            */
/* Detail : Call back from menu of help when activate about                   */
/* Date   : 2010/10/10                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkImageMenuItem *self : Pointer of text buffer                   */
/*        : gpointer user_data     :                                          */
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

void on_About_item_activate (GtkImageMenuItem *self, gpointer user_data)
{
						/* Authors                    */
	//gchar *authors[] = { "Akihiro Kashiwagi", NULL };

						/* Open about dialog          */
	gtk_show_about_dialog(
		NULL,
						/* Logo icon name             */
	        "logo-icon-name","lcs",
						/* Program name               */
		"program-name", "LCS",
						/* Version                    */
		"version", "0.1",
						/* License                    */
		"license",
		"LCS is free software and shareware:\n"\
		"    under GPLv3, LGPLv2(part of Gtk+).\n"\
		"    and case of business use, "\
		"Please 10[%] part of profit pay for me.\n"\
		"    because I must eat bread every day. "\
		"(see Genesis 3:19)\n"\
		"    please you will inquire to me "\
		"about detail information.\n\n"\
		"Copyright(C) Since 2010 Akihiro Kashiwagi\n"\
		"    e-mail: a-kashiwagi@mippi-mail.com\n\n"\
		"and I thanks for YHWH GOD, your creation is wonderful.",

						/* Web site                   */
		"website", "http://sites.google.com/site/kashiwagiakihiro/",

						/* Copyright                  */
		"copyright", "Copyright(C) Akihiro Kashiwagi",

						/* Authors                    */
		// "authors", authors,
						/* Comment                    */
	        "comments",
	        "This program is calculate Longest Common Subsequence.\n"\
	        "for Nucleotide and Amino acide sequence.",

		NULL
	);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Get a focusing Text View                                          */
/* Function Name : FocusingTextView()                                         */
/*                                                                            */
/* Detail : Get a focusing Text View in textview1,textview2 and textview3.    */
/* Date   : 2010/10/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
/* Output : GtkTextView * : Pointer of focusing(Selecting) text view          */
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

GtkTextView *FocusingTextView( void ){
						/* Pointer of Text View       */
	GtkTextView *tv;
	
	if( GTK_WIDGET_HAS_FOCUS( textview1 ) == TRUE ){
						/* textview1 have focus       */
		tv = GTK_TEXT_VIEW( textview1 );
		
	}else 	if( GTK_WIDGET_HAS_FOCUS( textview2 ) == TRUE ){
						/* textview2 have focus       */
		tv = GTK_TEXT_VIEW( textview2 );
		
	}else 	if( GTK_WIDGET_HAS_FOCUS( textview3 ) == TRUE ){
						/* textview3 have focus       */
		tv = GTK_TEXT_VIEW( textview3 );
	}
						/* Pointer of textview return */
	return( tv );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Callback Function of on cut item activate                         */
/* Function Name : on_Cut_item_activate()                                     */
/*                                                                            */
/* Detail : Selection charactars cut to clipboard                             */
/* Date   : 2010/10/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkImageMenuItem *self : Called pointer of menu item              */
/*          gpointer user_data     : Non use                                  */
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

void
on_Cut_item_activate (GtkImageMenuItem *self, gpointer user_data)
{
	GtkTextBuffer *buffer;
	GtkClipboard *clip;
						/* Get selection clipboard    */
	clip = gtk_clipboard_get( GDK_SELECTION_CLIPBOARD );
						/* Get focusing textbuffer    */
	buffer = gtk_text_view_get_buffer( FocusingTextView() );
						/* Cut from buffer            */
						/*    and Paste to clipboard  */
	gtk_text_buffer_cut_clipboard( buffer, clip, TRUE );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Callback Function of on copy item activate                        */
/* Function Name : on_Copy_item_activate()                                    */
/*                                                                            */
/* Detail : Selection charactars copy to clipboard                            */
/* Date   : 2010/10/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkImageMenuItem *self : Called pointer of menu item              */
/*          gpointer user_data     : Non use                                  */
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

void
on_Copy_item_activate (GtkImageMenuItem *self, gpointer user_data)
{
	GtkTextBuffer *buffer;
	GtkClipboard *clip;
						/* Get selection clipboard    */
	clip = gtk_clipboard_get( GDK_SELECTION_CLIPBOARD );
						/* Get focusing textbuffer    */
	buffer = gtk_text_view_get_buffer( FocusingTextView() );
						/* Copy from buffer           */
						/*    and Paste to clipboard  */
	gtk_text_buffer_copy_clipboard( buffer, clip );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Callback Function of on paste item activate                       */
/* Function Name : on_Paste_item_activate()                                   */
/*                                                                            */
/* Detail : Selection charactars paste from clipboard                         */
/* Date   : 2010/10/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkImageMenuItem *self : Called pointer of menu item              */
/*          gpointer user_data     : Non use                                  */
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

void
on_Paste_item_activate (GtkImageMenuItem *self, gpointer user_data)
{
	GtkTextBuffer *buffer;
	GtkClipboard *clip;
						/* Get selection clipboard    */
	clip = gtk_clipboard_get( GDK_SELECTION_CLIPBOARD );
						/* Get focusing textbuffer    */
	buffer = gtk_text_view_get_buffer( FocusingTextView() );
						/* Paste to buffer            */
						/*           from clipboard   */
	gtk_text_buffer_paste_clipboard( buffer, clip, NULL, TRUE );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Callback Function of on delete item activate                      */
/* Function Name : on_delete_item_activate()                                  */
/*                                                                            */
/* Detail : Selection charactars delete                                       */
/* Date   : 2010/10/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkImageMenuItem *self : Called pointer of menu item              */
/*          gpointer user_data     : Non use                                  */
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

void
on_Delete_item_activate (GtkImageMenuItem *self, gpointer user_data)
{
	GtkTextBuffer *buffer;
	GtkClipboard *clip;
						/* Get selection clipboard    */
	clip = gtk_clipboard_get( GDK_SELECTION_CLIPBOARD );
						/* Get focusing textbuffer    */
	buffer = gtk_text_view_get_buffer( FocusingTextView() );
						/* Delete selection string    */
	//gtk_text_buffer_delete_selection( buffer, clip, TRUE );
	gtk_text_buffer_delete_selection( buffer, FALSE, TRUE );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Callback Function of on Select All item activate                  */
/* Function Name : on_SelectAll_item_activate()                               */
/*                                                                            */
/* Detail : Selection all charactars                                          */
/* Date   : 2010/10/16                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkImageMenuItem *self : Called pointer of menu item              */
/*          gpointer user_data     : Non use                                  */
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
void
on_SelectAll_item_activate (GtkImageMenuItem *self, gpointer user_data)
{
	GtkTextBuffer *buffer;
	GtkClipboard *clip;
	GtkTextIter start;
	GtkTextIter end;
						/* Get selection clipboard    */
	clip = gtk_clipboard_get( GDK_SELECTION_CLIPBOARD );
						/* Get focusing textbuffer    */
	buffer = gtk_text_view_get_buffer( FocusingTextView() );
						/* Get start position         */
	gtk_text_buffer_get_start_iter( buffer, &start);
						/* Get end position           */
	gtk_text_buffer_get_end_iter( buffer, &end );
						/* Selection All              */
	gtk_text_buffer_select_range( buffer, &start, &end );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Load file to text view                                            */
/* Function Name : LoadFileToTextView()                                       */
/*                                                                            */
/* Detail : Load file to text view.                                           */
/* Date   : 2010/10/15                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
/* Output : char * : Pointer of sequence.                                     */
/*                   case of normal is NULL. (Loaded to text buffer)          */
/*                   case of big sequence file is loaded buffer pointer.      */
/*                   case of error is NULL.                                   */
/*                                                                            */
/* Replace -------------------------------------------------------------------*/
/*                                                                            */
/* Date   : 2020/10/29                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* Deteil : Added procedure that case of big size sequence file.              */
/*                                                                            */
/* Date   :                                                                   */
/* Author :                                                                   */
/* Deteil :                                                                   */
/*                                                                            */
/*-------+---------+---------+---------+---------+---------+---------+--------*/
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/******************************************************************************/

char *LoadFileToTextView(
	char *filename,
	GtkTextView *textview
){

					/* Pointer of message dialog          */
	GtkWidget *msgbox;
					/* File size                          */
	long filesize;
					/* Pointer for sequence string        */
	char *sequence;
                                        /* Pointer of buffer for textview     */
        GtkTextBuffer *buf;
					/* Buffer for work                    */
        char *work;
					/* Counter                            */
        int cnt;
					/* Converted file name                */
					/* from Gtk encoding(utf)             */
					/*            to File system encoding */
 	char *fname;
	                                /* for store bytes_read parameter     */
        gsize *bytes_read;
                                        /* for store bytes_write parameter    */
        gsize *bytes_write;
                                        /* for store error parameter          */
        GError **error;


					/* Counter reset                      */
	cnt = 0;
	while( filename[cnt] != '\0' ){
					/* Change charactar from CR/LF to NULL*/
		if( iscntrl(filename[cnt] ) ){
			filename[cnt] = '\0';
			break;
		}
		cnt++;
	}
					/* Search data type header            */
					/*    ex. file://, http://, ftp://    */
	work = strstr( filename, "://" );
	if( work != NULL ){
					/* Adjustment start point             */
					/*    to skip over data type header   */
		strcpy( filename, &work[3] );
	}
					/* Convert to File system encoding    */
					/*       from GLib file name encoding */
	fname = g_filename_from_utf8(
		filename,
		-1,
		bytes_read,
		bytes_write,
		error
	);
					/* Check for file size                */
	filesize = ChkFileSize( fname );
	if( filesize == -1 ){
					/* Case of error when return          */

					/* Output error dialog                */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_CLOSE,
			"Can not open [%s].",
			fname
		);
		gtk_dialog_run( GTK_DIALOG( msgbox ) );
		gtk_widget_destroy( msgbox );
					/* Return with error terminate        */
		return(NULL);

	}
					/* Allocate memory                    */
	sequence = malloc(
	        sizeof(char) * filesize
	        + ((int)floor(filesize / COLUMN_LIMIT) + 1)
					/* Added size for LF, each row        */
	);
	if( sequence == NULL ){
					/* Case of error when return          */

					/* Output error dialog                */
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
		return(NULL);
	}
					/* Get sequence data                  */
	if( GetSequenceForTextBuffer( fname, sequence ) == -1 ){
					/* Case of error when return          */

					/* Output error dialog                */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_ERROR,
			GTK_BUTTONS_CLOSE,
			"Can not read sequence file. [%s]",
			fname
		);
		gtk_dialog_run( GTK_DIALOG( msgbox ) );
		gtk_widget_destroy( msgbox );
					/* Return with error terminate        */
		return(NULL);
	}

					/* Get pointer of buffer              */
	buf = gtk_text_view_get_buffer(	GTK_TEXT_VIEW(textview) );

	if( filesize > WARNINGSIZE ){
					/* Case of file size big              */
					/*             than WARNINGSIZE       */

					/* Output error dialog                */
		msgbox = gtk_message_dialog_new(
			GTK_WINDOW(window),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_WARNING,
			GTK_BUTTONS_OK,
			"Loaded to memory.\n\n"\
			"file : [%s].\n\n"
			"but do not output to display, "\
			"because this file is too big.",
			fname
		);
					/* Window open                        */
		gtk_dialog_run( GTK_DIALOG( msgbox ) );
					/* Window close                       */
		gtk_widget_destroy( msgbox );
					/* Set message                        */
		gtk_text_buffer_set_text( buf, filename, -1 );
	}else{
					/* Load to textview                   */
 
					/* Set message                        */
		gtk_text_buffer_set_text( buf, sequence, -1 );
					/* free to memory                     */
		free(sequence);
					/* Set null                           */
		sequence = NULL;
	}
					/* Reset modified flag                */
	gtk_text_buffer_set_modified( buf, FALSE );
					/* Free to fname buffer               */
	g_free( fname );
					/* Return with normal terminate       */
	return(sequence);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Callback function on textview1 drag data received.                */
/* Function Name : on_textview1_drag_data_received()                          */
/*                                                                            */
/* Detail : Get drop file name and load file to textview1                     */
/* Date   : 2010/10/16                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
/*          GtkTextView *self : Pointer of textview                           */
/*          GdkDragContext *drag_context : Pointer of DragContext struct      */
/*          gint arg1 : non use                                               */
/*          gint arg2 : non use                                               */
/*          GtkSelectionData *data : Pointer of SelectionData struct          */
/*          guint arg4 : non use                                              */
/*          guint arg5 : non use                                              */
/*          gpointer user_data : non use                                      */
/*                                                                            */
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

void on_textview1_drag_data_received (
        GtkTextView *self,
        GdkDragContext *drag_context,
        gint arg1,
        gint arg2,
        GtkSelectionData *data,
        guint arg4,
        guint arg5,
        gpointer user_data
){
					/* Converted file name                */
 	char *fname;
                                        /* for store bytes_read parameter     */
        gsize *bytes_read;
                                        /* for store bytes_write parameter    */
        gsize *bytes_write;
                                        /* for store error parameter          */
        GError **error;
					/* TextIter at start                  */
	GtkTextIter   start;
					/* TextIter at start                  */
	GtkTextIter   end;
					/* TextBuffer for answer              */
	GtkTextBuffer *textbuf;

					/* Get text buffer                    */
	textbuf = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview1) );

					/* TextBuffer1 clear                  */
	gtk_text_buffer_get_start_iter( textbuf, &start );
	gtk_text_buffer_get_end_iter( textbuf, &end );
	gtk_text_buffer_delete( textbuf, &start, &end );

	if(( data->length >= 0 ) && ( data->format == 8)){

		if( drag_context->action == GDK_ACTION_COPY){

					/* Convert to UTF-8                   */
					/*       from GLib file name encoding */
			fname = g_filename_to_utf8(
				(gchar *)data->data,
				-1,
				bytes_read,
				bytes_write,
				error
			);
					/* Store filename                     */
					/* with convert from uri to utf8      */
			strcpy(
				SourceFileName,
				g_filename_from_uri( fname, NULL, NULL )
			);
					/* Free to fname buffer               */
			g_free( fname );
					/* Load file to textview              */
			SourceSequence = LoadFileToTextView(
			        SourceFileName,
			        GTK_TEXT_VIEW(textview1)
			);
		}
					/* Procedure for drag finished,       */
					/*        "succsess" and "not delete" */
		gtk_drag_finish( drag_context, TRUE, FALSE, (guint32)time );
		return;
	}
					/* Procedure for drag finished        */
					/*        "fail" and "not delete"     */
	gtk_drag_finish( drag_context, FALSE, FALSE, (guint32)time );
}


/******************************************************************************/
/*                                                                            */
/* Title  : Callback function on textview2 drag data received.                */
/* Function Name : on_textview2_drag_data_received()                          */
/*                                                                            */
/* Detail : Get drop file name and load file to textview2                     */
/* Date   : 2010/10/16                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : void                                                              */
/*          GtkTextView *self : Pointer of textview                           */
/*          GdkDragContext *drag_context : Pointer of DragContext struct      */
/*          gint arg1 : non use                                               */
/*          gint arg2 : non use                                               */
/*          GtkSelectionData *data : Pointer of SelectionData struct          */
/*          guint arg4 : non use                                              */
/*          guint arg5 : non use                                              */
/*          gpointer user_data : non use                                      */
/*                                                                            */
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

void on_textview2_drag_data_received (
        GtkTextView *self,
        GdkDragContext *drag_context,
        gint arg1,
        gint arg2,
        GtkSelectionData *data,
        guint arg4,
        guint arg5,
        gpointer user_data
){
					/* Converted file name                */
	char *fname;
                                        /* for store bytes_read parameter     */
        gsize *bytes_read;
                                        /* for store bytes_write parameter    */
        gsize *bytes_write;
                                        /* for store error parameter          */
        GError **error;
					/* TextIter at start                  */
	GtkTextIter   start;
					/* TextIter at start                  */
	GtkTextIter   end;
					/* TextBuffer for answer              */
	GtkTextBuffer *textbuf;

					/* Get text buffer                    */
	textbuf = gtk_text_view_get_buffer( GTK_TEXT_VIEW(textview2) );

					/* TextBuffer1 clear                  */
	gtk_text_buffer_get_start_iter( textbuf, &start );
	gtk_text_buffer_get_end_iter( textbuf, &end );
	gtk_text_buffer_delete( textbuf, &start, &end );

	if(( data->length >= 0 ) && ( data->format == 8)){

		if( drag_context->action == GDK_ACTION_COPY){

					/* Convert to UTF-8                   */
					/*       from GLib file name encoding */
			fname = g_filename_to_utf8(
				(gchar *)data->data,
				-1,
				bytes_read,
				bytes_write,
				error
			);
					/* Store filename                     */
			strcpy(
			        TargetFileName,
			        g_filename_from_uri( fname, NULL, NULL )
			);
					/* Free to fname buffer               */
			g_free( fname );
					/* Load file to textview              */
			TargetSequence = LoadFileToTextView(
			        TargetFileName,
			        GTK_TEXT_VIEW(textview2)
			);
		}
					/* Procedure for drag finished,       */
					/*        "succsess" and "not delete" */
		gtk_drag_finish( drag_context, TRUE, FALSE, (guint32)time );
		return;
	}
					/* Procedure for drag finished        */
					/*        "fail" and "not delete"     */
	gtk_drag_finish( drag_context, FALSE, FALSE, (guint32)time );
}

/******************************************************************************/
/*                                                                            */
/* Title  : Function of callback on_Help_item_activate                        */
/* Function Name : on_Help_item_activate()                                    */
/*                                                                            */
/* Detail : Start up help(lcs.xml) for yelp.                                  */
/* Date   : 2010/10/22                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkImageMenuItem * : Pointer of called GtkImageMenuItem           */
/* Output : non use                                                           */
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

void
on_Help_item_activate (GtkImageMenuItem *self, gpointer user_data)
{
					/* Return value                       */
	int ret;
					/* fork "/bin/bash HELPFILE"          */
	ret = system( HELPFILE);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Function of on_drawingarea1_expose_event                          */
/* Function Name : on_drawingarea1_expose_event()                             */
/*                                                                            */
/* Detail : Drawing pixmap of dot matrix to GtkDrawingArea                    */
/* Date   : 2010/11/11                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GtkDrawingArea *self : Pointer of drawingArea1                    */
/*          GdkEvent *arg0       : unused                                     */
/*          gpointer user_data   : unused                                     */
/* Output : gboolean             :                                            */
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
gboolean on_drawingarea1_expose_event (
        GtkDrawingArea *self,
        GdkEvent *arg0,
        gpointer user_data
){
						/* Style for getting gc       */
	GtkStyle *stl;
						/* Graphic context            */
	GdkGC *gc;

	if( pm == NULL ){
		return(TRUE);
	}
						/* Get style for gc           */
	stl = gtk_widget_get_style( GTK_WIDGET(self) );
						/* Get GC from state No.5     */
	gc = stl->fg_gc[ GTK_WIDGET_STATE(self) ];
						/* Put pixmap to drawable area*/
	gdk_draw_drawable(
	        gtk_widget_get_window( GTK_WIDGET(self) ),
	        gc,
	        GDK_DRAWABLE(pm),
	        0,0,
	        0,0,
	        -1,-1
	);

	return(FALSE);
}

/******************************************************************************/
/*                                                                            */
/* Title  : Function of draw dot matrix plot                                  */
/* Function Name : draw_matrix()                                              */
/*                                                                            */
/* Detail : Drawing dot matrix to GdkPixmap                                   */
/* Date   : 2010/11/21                                                        */
/* Author : Akihiro Kashiwagi                                                 */
/* e-mail : a-kashiwagi@mippi-mail.com                                        */
/*                                                                            */
/* Input  : GdkPixmap **in_pm : Pointer of GdkPixmap                          */
/* Output : int               : [ 0: NormalTerminate ]                        */
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

int draw_matrix ( GdkPixmap **in_pm ){
						/* Graphic context            */
	GdkGC *gc;
						/* Allocation in drawing area */
	gint width;
	gint height;
						/* Colormap                   */
	GdkColormap *cm;
	GdkColor white;
	GdkColor black;
						/* Counter of inum            */
	long i;
						/* Counter of jnum            */
	long j;
						/* Graph space                */
	int sp;
						/* Width of font              */
	int font_width;
						/* Heigth of font             */
	int font_height;
						/* Term of measure            */
	int measure_term;
						/* Pango(font) Layout         */
	PangoLayout *pl;
						/* Buffer of measure text     */
	char buf[32];

						/* Set values                 */

						/* Store pointer of pixmap    */
	pm = *in_pm;
						/* Get color map from system  */
	cm = gdk_colormap_get_system();
						/* Get color of white         */
	gdk_color_white( cm, &white );
						/* Get color of black         */
	gdk_color_black( cm, &black );
						/* Set background color(white)*/
	//gdk_gc_set_background( gc, &white );
						/* Set foreground color(black)*/
	//gdk_gc_set_foreground( gc, &black );


	if( stored_eg == NULL ){
						/* Case of no data of eg      */
		return(TRUE);
	}
						/* Set default space          */
	sp = 10;
						/* Set measure term           */
	measure_term = 50;
						/* Get style for gc           */
	//stl = gtk_widget_get_style(pm);
						/* Get GC from state No.5     */
	//gc = stl->fg_gc[ GTK_WIDGET_STATE(pm) ];
						/* New graphic context        */
	gc = gdk_gc_new(pm);

						/* Get allocation             */
						/*            in drawing area */
	gdk_drawable_get_size( pm, &width, &height);

						/* Change foreground color    */
						/*                   to white */
	gdk_gc_set_foreground( gc, &white );
						/* Fill background by white   */
	gdk_draw_rectangle (
		pm,
		gc,
		TRUE,
		0, 0,
		width, height
	);
						/* Change foreground color    */
						/*                   to black */
	gdk_gc_set_foreground( gc, &black );

						/* Create pango(font) layout  */
	pl = gtk_widget_create_pango_layout(drawingArea1, NULL);
						/* Memo:                      */
						/*   Create pango layouot     */
						/*     from drawingArea1(Gtk) */
						/*   because pixmap is Gdk.   */

						/* Get max size text for test */
	sprintf( buf, "%ld", stored_inum );
						/* Set text to pango          */
	pango_layout_set_text(pl, buf, -1);
						/* Get pixel size of font     */
	pango_layout_get_pixel_size(pl,&font_width,&font_height);
	
						/* Case of bigger than sp     */
	if( sp < font_width + 5 ){
						/* Set new sp                 */
		sp = font_width + 5;
	}

						/* Get max size text for test */
	sprintf( buf, "%ld", stored_jnum );
						/* Set text to pango          */
	pango_layout_set_text(pl, buf, -1);
						/* Get pixel size of font     */
	pango_layout_get_pixel_size(pl,&font_width,&font_height);

						/* Case of bigger than sp     */
	if( sp < font_width + 5 ){
						/* Set new sp                 */
		sp = font_width + 5;
	}
						/* Put measure line x axis    */
	gdk_draw_line( pm, gc,
	        (gint)          0 + sp, (gint)0 + sp,
	        (gint)stored_inum + sp, (gint)0 + sp
	);
						/* Put measure for x axis     */

						/* Set j is zero for y axis   */
	j = 0;
						/* Loop for x axis            */
	for( i = 0; i < stored_inum; i++ ){
						/* Case of come measure point */
		if( (i % measure_term) == 0 && (i != 0) ){
						/* Put measure                */
			gdk_draw_line( pm, gc,
				(gint)i + sp, (gint)0 + sp - 1,
				(gint)i + sp, (gint)0 + sp - 3
			);
						/* Set measure number         */
			sprintf( buf, "%ld", i );
						/* Set text for pango(font)   */
			pango_layout_set_text(pl, buf, -1); 
						/* Get font size              */
			pango_layout_get_pixel_size(
			        pl,&font_width,&font_height
			);
						/* Put measure number         */
			gdk_draw_layout( pm, gc,
			        (gint)i + sp, (gint)0 + sp - 3 - font_height, pl
			);
		}
	}
	
						/* Put measure line y axis    */
	gdk_draw_line( pm, gc,
	        (gint)0 + sp, (gint)          0 + sp + 1,
	        (gint)0 + sp, (gint)stored_jnum + sp
	);
						/* Put measure for y axis     */

						/* Set j is zero for x axis   */
	i = 0;
						/* Loop for y axis            */
	for( j = 0; j < stored_jnum; j++ ){
						/* Case of come measure point */
		if( (j % measure_term) == 0 && (j != 0) ){
						/* Put measure                */
			gdk_draw_line( pm, gc,
				(gint)i + sp - 1, (gint)j + sp,
				(gint)i + sp - 3, (gint)j + sp
			);
						/* Set measure number         */
			sprintf( buf, "%ld", j );
						/* Set text for pango(font)   */
			pango_layout_set_text(pl, buf, -1); 
						/* Get font size              */
			pango_layout_get_pixel_size(
			        pl,&font_width,&font_height
			);
						/* Put measure number         */
			gdk_draw_layout( pm, gc,
			        (gint)i + sp - 3 - font_width, (gint)j + sp, pl
			);
		}
	}

						/* Drawing dot matrix from eg */
	for( i = 0; i < stored_inum; i++ ){
		for( j = 0; j < stored_jnum; j++ ){
						/* Case of bigger than zero   */
			if( stored_eg[i][j] > 0 ){
						/* Put dot                    */
				gdk_draw_point(
					pm,
					gc,
					(gint)i + sp,
				        (gint)j + sp
				);
			}
		}
	}
						/* Unreference graphic context*/
	g_object_unref( gc );
						/* Unreference color map      */
	g_object_unref( cm );
						/* Return                     */
	return(0);
}
