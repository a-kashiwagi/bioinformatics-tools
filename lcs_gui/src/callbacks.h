/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/*
 * callbacks.h
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

#ifndef _CALLBACKS_H_DEFINED

#include <gtk/gtk.h>
#include "lcs.h"

					/* Application title                  */
#define APP_TITLE "LCS"
					/* Default file name for save         */
#define SAVEFILENAME "Untitled"
					/* Limit of column to textbuffer      */
#define COLUMN_LIMIT 80 //1000

#define SPLIT_NUM 20
					/* Do warning of Load file size       */
#define WARNINGSIZE 512000
					/* Help file and Command              */
#define HELPFILE "yelp /usr/share/gnome/help/lcs/C/lcs.xml &"

#define WITHOUTREPORT	0
					/* Mode of a without report           */
#define WITHREPORT	1

pthread_mutex_t cb_mutex;
					/* Mode of a with report              */

					/* Function declaration               */

					/* Set objects to scope of callback.c */
int set_objects_to_callback_area( GtkBuilder *builder );

					/* Get sequence string for text buffer*/
long GetSequenceForTextBuffer( char *filename, char *buff );

					/* Clean up sequence                  */
long clean_up_sequence( char *sequence );

					/* Set pointer of answer string       */
					/*           for scope of callback.c  */
int set_ans_str(
        char **v,
        char **w,
        char **v_ans,
        char **w_ans,
        char **gap,
        char **ans,
        char ***eg,
        long ***ss,
        char ***bp,
        long inum,
        long jnum
);

					/* Procedure of execute button        */
void on_exec_clicked( GtkWidget *widget, gpointer user_data );

					/* Function for procedure LCS         */
int lcs_thread(void);

					/* Radio button togged                */
					/*              for each radio button */

					/* Nucleotide                         */
void on_comparemode0_toggled   (GtkRadioButton *self, gpointer user_data);

					/* Amino acid                         */
void on_comparemode1_toggled   (GtkRadioButton *self, gpointer user_data);

					/* Part seqence                       */
void on_sequencemode0_toggled  (GtkRadioButton *self, gpointer user_data);

					/* All sequence                       */
void on_sequencemode1_toggled  (GtkRadioButton *self, gpointer user_data);

					/* Global alignment                   */
void on_alignmentmode0_toggled (GtkRadioButton *self, gpointer user_data);

					/* Local alignment                    */
void on_alignmentmode1_toggled (GtkRadioButton *self, gpointer user_data);

					/* Liner gap score                    */
void on_gapscoremode0_toggled  (GtkRadioButton *self, gpointer user_data);

					/* Affine gap score                   */
void on_gapscoremode1_toggled  (GtkRadioButton *self, gpointer user_data);

					/* Threshold v scale                  */
void on_thresholdvscale_value_changed (GtkVScale *self, gpointer user_data);

					/* Continuity v scale                 */
void on_continuityvscale_value_changed (GtkVScale *self, gpointer user_data);

					/* Procedure of insert to text buffer */
void on_textbuf_insert(
        GtkTextBuffer *self,
        GtkTextIter *iter,
        gchar *text,
        gint len
);

					/* Function of store source filename */
void store_srcfilename ( GtkWidget *self,   gpointer user_data );

					/* Function of store target filename */
void store_trgfilename ( GtkWidget *widget, gpointer user_data );

					/* Function of store save filename   */
void store_savefilename( GtkWidget *widget, gpointer user_data );

					/* Procedure of selection menu item  */

					/* Open source                       */
void on_OpenSrc_item_activate (GtkImageMenuItem *self, gpointer user_data);

					/* Open target                       */
void on_OpenTrg_item_activate (GtkImageMenuItem *self, gpointer user_data);

					/* Save                              */
void on_Save_item_activate    (GtkImageMenuItem *self, gpointer user_data);

					/* Function of save                  */
int SaveFile( void );

					/* Function of file load to text view*/
char *LoadFileToTextView( char *filename, GtkTextView *textview );

					/* Drag & Drop for source area       */
void on_textview1_drag_data_received (
        GtkTextView *self,
        GdkDragContext *drag_context,
        gint arg1,
        gint arg2,
        GtkSelectionData *data,
        guint arg4,
        guint arg5,
        gpointer user_data
);
					/* Drag & Drop for target area       */
void on_textview2_drag_data_received (
        GtkTextView *self,
        GdkDragContext *drag_context,
        gint arg1,
        gint arg2,
        GtkSelectionData *data,
        guint arg4,
        guint arg5,
        gpointer user_data
);
					/* Get a focusing text view          */
GtkTextView *FocusingTextView( int mode );

					/* Procedure of                      */
					/*         cut,copy,paste and delete */

					/* Cut                               */
void on_Cut_item_activate    (GtkImageMenuItem *self, gpointer user_data);

					/* Copy                              */
void on_Copy_item_activate   (GtkImageMenuItem *self, gpointer user_data);

					/* Paste                             */
void on_Paste_item_activate  (GtkImageMenuItem *self, gpointer user_data);

					/* Delete                            */
void on_Delete_item_activate (GtkImageMenuItem *self, gpointer user_data);

					/* Application destroy               */
void destroy (GtkWidget *widget, gpointer data);

					/* For delete event                  */
gint delete_event( GtkWidget *widget, GdkEvent *event, gpointer data );

					/* For draw matrix                   */
int draw_matrix ( GdkPixmap **in_pm );
					/* Call back from menu of file       */
					/*     when activate SaveAsFileOpen  */
void on_SaveAs_item_activate (GtkImageMenuItem *self, gpointer user_data);

#define _CALLBACKS_H_DEFINED
#endif
