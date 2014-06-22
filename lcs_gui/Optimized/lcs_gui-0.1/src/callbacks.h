/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/*
 * callbacks.h
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

#include <gtk/gtk.h>
#include "lcs.h"

int set_objects_to_callback_area( GtkBuilder *builder );

void on_exec_clicked( GtkWidget *widget, gpointer user_data );
void on_comparemode0_toggled (GtkRadioButton *self, gpointer user_data);
void on_comparemode1_toggled (GtkRadioButton *self, gpointer user_data);
void on_sequencemode0_toggled (GtkRadioButton *self, gpointer user_data);
void on_sequencemode1_toggled (GtkRadioButton *self, gpointer user_data);
void on_alignmentmode0_toggled (GtkRadioButton *self, gpointer user_data);
void on_alignmentmode1_toggled (GtkRadioButton *self, gpointer user_data);
void on_gapscoremode0_toggled (GtkRadioButton *self, gpointer user_data);
void on_gapscoremode1_toggled (GtkRadioButton *self, gpointer user_data);

void on_textbuf_insert( GtkTextBuffer *self, GtkTextIter *iter, gchar *text, gint len );

void destroy (GtkWidget *widget, gpointer data);

