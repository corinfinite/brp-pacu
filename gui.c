/*
* gui.c : Creates the gui, updates the gui, and handles or triggers
*       all gui events.
*
*
* Copyright (C) 2007-2008 Brian Phelps(lm317t@gmail.com)
* Macintosh code Copyright (C) 2009-2013 Andreas Schwab
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Library General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <stdio.h>
#ifdef MAC_INTEGRATION
#include <CoreFoundation/CoreFoundation.h>
#include <gtkosxapplication.h>
#endif

#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <gtkdatabox.h>
#include "config.h"
#include "gui.h"
#include "testfft.h"
#include <errno.h>
#include <math.h>
#include <string.h>
#define COLOR_T                                                                \
    { 0, 90, 90, 90 }

/////////////////////////////////////////////
// LED Pixmap stuff
static GtkWidget *measured_draw;
static GtkWidget *reference_draw;
/////////////////////////////////////////////
static GtkDataboxGraph **graph;
static GtkDataboxGraph *graph_impulse;
static GtkWidget *window = NULL;
static GtkWidget *box;
static GtkWidget *impulse_box;
static GtkWidget *about_me_window = NULL;
static GtkWidget *about_ok = NULL;
static GtkWidget *delay_window = NULL;
static GtkWidget *impulse_window = NULL;
static GtkWidget *volume_pink_gui = NULL;
static GtkWidget *transfer_function_toggle = NULL;
static GAction *transfer_function_menu = NULL;
static GtkWidget *buffer_button[N_BUFF] = {NULL, NULL, NULL, NULL, NULL};
static GAction *buffer_menu[N_BUFF] = {NULL, NULL, NULL, NULL, NULL};
static GtkWidget *preferences_dialog = NULL;
static GtkWidget *smoothing_spin_button = NULL;
static GtkWidget *averaging_spin_button = NULL;
static gfloat volume_pink_value = 0;
static gfloat *guiX = NULL;
static gfloat *guiY = NULL;
static gfloat *gui_impulse_Y = NULL;
static gfloat *gui_impulse_X = NULL;
static gfloat guiYBuf[N_BUFF][PLOT_PTS];
static gfloat guiYBufAvgHold[PLOT_PTS];
static GString *file_name_str = NULL;
static GString *save_name_str = NULL;
static char *home_string, *file_path1, *file_path2;

static char pinknoise_muted = 0;
static char update_delay = 0;
static char buffer[N_BUFF] = {2, 2, 2, 2, 2};
static gfloat grid_x[] = {32.0,   64.0,   128.0,  256.0,  512.0,
                          1024.0, 2048.0, 4096.0, 8192.0, 16384.0};
static guint avg_num;
static gfloat avg_gain = 0;
static int buffer_last_clicked;
static GtkWidget *bkg_dialog;

// static GtkWidget *cb;
static GAction *save_now;
static GAction *save_as;
static GAction *open_menuitem;

static gint avg_index = 0;
static gchar tf = 1;
static gfloat avgY[PLOT_PTS][MAX_AVG_NUM];

static gint gui_idle = 0;
static gfloat gui_frequency = 3. * G_PI / 2.;
static GtkWidget *gui_label = NULL;
static GtkWidget *gui_db_label = NULL;
static GtkWidget *gui_status_delay_label = NULL;
static GtkWidget *gui_sb_label = NULL;
static GtkWidget *gui_sb = NULL;
static GtkWidget *open_dialog = NULL;
static GtkWidget *save_as_dialog = NULL;
static guint gui_counter = 0;
static guint smooth_factor;
static guint smooth_constant;

static GdkRGBA background_color;
static GdkRGBA grid_color;
static GdkRGBA trace_transfer_color;
static GdkRGBA trace_impulse_color;
static GdkRGBA line_color[N_BUFF] = {
    // unused, red, green, blue
    {0, 16384, 16384, 65535},
    {0, 0, 62000, 0},
    {0, 65535, 0, 0},
    {0, 65535, 16384, 65535},
    {0, 65535, 65535, 65535}};
static GdkRGBA myColor1 = {0.3, 0.3, 0.3, 1.0};
static GdkRGBA myColor2 = {0.3, 0.3, 0.3, 1.0};

void message(char *format, char *text, gboolean error) {
    GtkWidget *dialog = gtk_message_dialog_new(
        GTK_WINDOW(window), GTK_DIALOG_DESTROY_WITH_PARENT,
        error ? GTK_MESSAGE_ERROR : GTK_MESSAGE_WARNING, GTK_BUTTONS_CLOSE,
        format, text);
#ifdef MAC_INTEGRATION
    GtkosxApplication *theApp = g_object_new(GTKOSX_TYPE_APPLICATION, NULL);
    // Bounce icon in dock
    gtkosx_application_attention_request(theApp, error ? CRITICAL_REQUEST
                                                       : INFO_REQUEST);
#endif
    fprintf(stderr, error ? "BRP-PACU error: " : "BRP-PACU warning: ");
    fprintf(stderr, format, text);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    gtk_window_set_decorated(GTK_WINDOW(dialog), FALSE);
    gtk_window_present(GTK_WINDOW(dialog));
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

gboolean gui_idle_func(struct FFT_Frame *data) {
    gfloat tmp[PLOT_PTS];
    gint smoothing;
    gint index;
    gint i;
    gint j, k;
    gint max;
    gfloat temp, max_x, min_x, max_y, min_y, tmp_spin;
    gchar *label = NULL;
    //GdkGC *gc1 = NULL;
    //GdkGC *gc2 = NULL;

    if (!GTK_IS_DATABOX(box)) {
        fprintf(stderr, "Box not a gtk_databox\n");
        return FALSE;
    }
	
    //gc1 = gdk_gc_new(gtk_widget_get_window(measured_draw));
    //gc2 = gdk_gc_new(gtk_widget_get_window(reference_draw));
    /////   label = g_new0(gchar*, 10);
    data->pink_muted = pinknoise_muted;

    data->volume_pink = volume_pink_value;
    avg_index++;
    if (avg_index >= avg_num)
        avg_index = 0;
    min_y = 0.0;
    max_y = 0.0;

    if (data->find_impulse == 2) {
        for (i = 0; i < N_FFT; i++) {
            index = i;
            temp = (gfloat)data->rfft_returned_1[index];
            gui_impulse_Y[i] = temp;
            // printf(" %g %g ", temp,  gui_impulse_Y[i]);
            if (temp > max_y)
                max_y = temp;
            if (temp < min_y)
                min_y = temp;
        }
    } else {
        for (i = 0; i < PLOT_PTS; i++) {
            if (tf)
                avgY[i][avg_index] =
                    (0.0 +
                     20.0 * log10((gfloat)data->fft_returned_1[i] /
                                  (gfloat)data->fft_returned_2[i]));
            else
                avgY[i][avg_index] =
                    (0.0 + 20.0 * log10((gfloat)data->fft_returned_1[i]));
            //      avgY[i][avg_index] =
            //      (20*log10((gfloat)data->fft_returned_1[index]+1));

            tmp[i] = 0;
            for (k = 0; k < avg_num; k++) {
                tmp[i] += avgY[i][k];
            }
            tmp[i] /= avg_num;
            // guiY[i] = avgY[i][0];
        }
    }

    smoothing = 1;
    for (i = 0; i < PLOT_PTS; i += smoothing) {
        guiY[i] = tmp[i];
        for (j = 1; j <= smoothing; j++) {
            guiY[i] += tmp[(i - j) >= 0 ? (i - j) : 0];
            guiY[i] += tmp[(i + j) < PLOT_PTS ? (i + j) : (PLOT_PTS - 1)];
        }

        guiY[i] /= (smoothing * 2.0 + 1);

        for (j = 1; j <= smoothing; j++) {
            guiY[(i - j) >= 0 ? (i - j) : 0] =
                guiY[i] * (smoothing - j) / smoothing +
                guiY[(i - smoothing) >= 0 ? (i - smoothing) : 0] * (j) /
                    smoothing;
            guiY[(i + j) < PLOT_PTS ? (i + j) : (PLOT_PTS - 1)] =
                guiY[i] * (smoothing - j) / smoothing +
                guiY[(i + smoothing) < (PLOT_PTS) ? (i + smoothing)
                                                  : (PLOT_PTS - 1)] *
                    (j) / smoothing;
        }
        smoothing = (int)pow(2.0, (((float)i) / (((float)N_FFT / 2.0)) +
                                   smooth_factor)) -
                    smooth_constant; // Apply smoothing more at higher
                                     // frequencies than lower
                                     // frequencies
    }

    if (data->find_impulse == 2) {
        min_x = 0.0;
        max_x = ((gfloat)N_FFT) / NYQUIST;
        gtk_databox_set_total_limits(GTK_DATABOX(impulse_box), min_x, max_x,
                                     max_y, min_y);
        gtk_widget_queue_draw(GTK_WIDGET(impulse_box));
        data->find_impulse = 0;
    }
    if (data->find_delay == 1) {
        label =
            g_strdup_printf("<b>Finding Delay.....</b>"); // data->delay_size);
        gtk_label_set_markup(GTK_LABEL(gui_sb_label), label);
        g_free((gpointer)label);
    }

    if (data->find_delay == 2) {
        label = g_strdup_printf("<b> Found:  %g secs </b>",
                                (float)data->delay_size *
                                    (1.0 / (float)FSAMP)); // data->delay_size);
        gtk_label_set_markup(GTK_LABEL(gui_sb_label), label);
        g_free((gpointer)label);
        data->find_delay = 0;
    }
    if (update_delay) {
        tmp_spin = gtk_spin_button_get_value(GTK_SPIN_BUTTON(gui_sb));
        data->delay_size = (int)(((gfloat)tmp_spin) * (gfloat)FSAMP);
        update_delay = 0;
        gtk_widget_hide(delay_window);
    }
    label =
        g_strdup_printf("Delay %3.2f msecs", (float)data->delay_size *
                                                 (1.0 / (float)FSAMP) * 1000.0);
    gtk_label_set_text(GTK_LABEL(gui_status_delay_label), label);
    g_free((gpointer)label);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // LED Color Choosing & rendering
    max = 0;
    for (k = N_FFT - 2000; k < N_FFT; k++) {
        if (max < data->buffer_data_1[k])
            max = data->buffer_data_1[k];
    }
	
    if (max > 20000) {
        myColor1.red = 1.0;
        myColor1.green = 0.3;
        myColor1.blue = 0.3;
    } else if (max > 5000) {
        myColor1.red = 0.8;
        myColor1.green = 1.0;
        myColor1.blue = 0.3;
    } else if (max > 1000) {
        myColor1.red = 0.3;
        myColor1.green = 0.85;
        myColor1.blue = 0.3;
    } else if (max > 40) {
        myColor1.red = 0.3;
        myColor1.green = 0.9;
        myColor1.blue = 0.3;
    } else {
        myColor1.red = 0.0;
        myColor1.green = 0.0;
        myColor1.blue = 0.0;
    }

	cairo_t *cr;
	cr = gdk_cairo_create (gtk_widget_get_window (measured_draw));
	cairo_pattern_set_extend (cairo_get_source (cr), CAIRO_EXTEND_REPEAT);
	
	cairo_rectangle (cr, 0, 7, 16, 16);
	gdk_cairo_set_source_rgba(cr, &myColor1);
	cairo_fill (cr);
	cairo_destroy (cr);

    max = 0;
    for (k = N_FFT - 2000; k < N_FFT; k++) {
        if (max < data->buffer_data_2[k])
            max = data->buffer_data_2[k];
    }

    if (max > 20000) {
        myColor2.red = 1.0;
        myColor2.green = 0.3;
        myColor2.blue = 0.3;
    } else if (max > 5000) {
        myColor2.red = 0.8;
        myColor2.green = 1.0;
        myColor2.blue = 0.3;
    } else if (max > 1000) {
        myColor2.red = 0.3;
        myColor2.green = 0.85;
        myColor2.blue = 0.3;
    } else if (max > 40) {
        myColor2.red = 0.3;
        myColor2.green = 0.9;
        myColor2.blue = 0.3;
    } else {
        myColor2.red = 0.0;
        myColor2.green = 0.0;
        myColor2.blue = 0.0;
    }
	
	cr = gdk_cairo_create (gtk_widget_get_window (reference_draw));
	cairo_pattern_set_extend (cairo_get_source (cr), CAIRO_EXTEND_REPEAT);
	
	cairo_rectangle (cr, 0, 7, 16, 16);
	gdk_cairo_set_source_rgba(cr, &myColor2);
	cairo_fill (cr);
	cairo_destroy (cr);
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    gtk_widget_queue_draw(GTK_WIDGET(box));
    //g_object_unref(gc1);
    //g_object_unref(gc2);
    return TRUE;
}

static void delay_custom_cb(GtkWidget *widget) // , gtkwidget *widget)
{
    update_delay = 1;
}

void pinknoise_button_toggled_cb(GtkWidget *widget,
                                        char* user_data)
{
	// TODO: change the state of the menu item to be in sync.
	pinknoise_muted ^= 1;
}

static void volume_gui(GtkWidget *widget) // , gtkwidget *widget)
{
    volume_pink_value =
        gtk_spin_button_get_value(GTK_SPIN_BUTTON(volume_pink_gui));
}
static void delay_keep_cb(GtkWidget *widget) // , gtkwidget *widget)
{
    gtk_widget_hide
(delay_window);
}
static gboolean about_ok_cb(GtkWidget *widget) // , gtkwidget *widget)
{
    gtk_widget_hide(about_me_window);
    return TRUE;
}
static void about_me_cb(GtkWidget *widget) // , gtkwidget *widget)
{
    gtk_widget_show_all(about_me_window);
    gtk_window_present(GTK_WINDOW(about_me_window));
}
// Trigger the gui to do the transfer function
static void transfer_function_toggled_cb(GtkWidget *widget) {
    if (gtk_toggle_button_get_active(
            GTK_TOGGLE_BUTTON(transfer_function_toggle))) {
        if (tf == 0) // Don't do anything if initiated by transfer_fxn_cb()
        {
            tf = 1;
            gtk_toggle_action_set_active(
                GTK_TOGGLE_ACTION(transfer_function_menu), TRUE);
        }
    } else {
        if (tf != 0) // Don't do anything if initiated by transfer_fxn_cb()
        {
            tf = 0;
            gtk_toggle_action_set_active(
                GTK_TOGGLE_ACTION(transfer_function_menu), FALSE);
        }
    }
}

static void transfer_fxn_cb(GtkWidget *widget) {
    if (gtk_toggle_action_get_active(
            GTK_TOGGLE_ACTION(transfer_function_menu))) {
        if (tf != 1) // Don't do anything if initiated by
                     // transfer_function_toggled_cb()
        {
            tf = 1;
            gtk_toggle_button_set_active(
                GTK_TOGGLE_BUTTON(transfer_function_toggle), TRUE);
        }
    } else {
        if (tf == 1) // Don't do anything if initiated by
                     // transfer_function_toggled_cb()
        {
            tf = 0;
            gtk_toggle_button_set_active(
                GTK_TOGGLE_BUTTON(transfer_function_toggle), FALSE);
        }
    }
}

// capture call back
static void capture_cb(GtkWidget *widget,
                       GtkWidget *box) // , gtkwidget *widget)
{
    int i, k, write_output;
    float avg_avg = 0;
    FILE *file_handle;
    gint tmp_array[1];

    if (buffer[buffer_last_clicked] == 1) // Is it on the screen?
    {
        if (buffer_last_clicked == N_BUFF - 1) // Is it the average buffer?
        {
            for (k = 0; k < PLOT_PTS; k++) {
                guiYBuf[N_BUFF - 1][k] = 0.0;
                for (i = 0; i < N_BUFF - 1; i++)
                    guiYBuf[N_BUFF - 1][k] += guiYBuf[i][k];
                guiYBuf[N_BUFF - 1][k] /= 4.0;
                avg_avg += guiYBuf[N_BUFF - 1][k] *
                           (1.0 / ((float)PLOT_PTS)); // avg_avg gives us the
                // location of the preflipped avg on the dB
                // scale
            }
            //         printf("\n");

            for (k = 0; k < PLOT_PTS; k++) {
                guiYBufAvgHold[k] =
                    0.0 - guiYBuf[N_BUFF - 1][k] + (avg_avg * 2);
                guiYBuf[N_BUFF - 1][k] = avg_gain + guiYBufAvgHold[k];
                // printf(" %g ",guiYBuf[N_BUFF-1][k]);
            }
            //         printf("\n");
        } else // it is a regular buffer
            for (k = 0; k < PLOT_PTS; k++)
                guiYBuf[buffer_last_clicked][k] = guiY[k];
        write_output = mkdir(file_path1, 0770);
        if (((write_output == -1) && (errno == EEXIST)) || (write_output == 0))
            write_output = 1;
        if (write_output == 1) // The directory exists or was created
        {
            file_handle = fopen(file_path2, "wb");
            if (file_handle == NULL) {
                write_output = 0;
                message("Could not open file %s, permissions "
                        "issue?",
                        file_path2, TRUE);
            }
        }
        if (write_output == 1) {
            tmp_array[0] = PLOT_PTS;
            printf("Writing %d elements per buffer to %s\n", tmp_array[0],
                   file_path2);
            fwrite(tmp_array, sizeof(gint), 1, file_handle);
            for (i = 0; i < N_BUFF; i++)
                fwrite(guiYBuf[i], sizeof(gfloat), PLOT_PTS, file_handle);
            fclose(file_handle);
        }
    }
}

// Increase/Decrease the gain of Averaging buffer
static void gain_cb(GtkWidget *widget, GtkSpinButton *spin) {
    int k;
    avg_gain = gtk_spin_button_get_value(spin);
    for (k = 0; k < PLOT_PTS; k++)
        guiYBuf[N_BUFF - 1][k] = avg_gain + guiYBufAvgHold[k];
}
// Handle addition/removal of the individual buffers
static void buffer_button_cb(GtkWidget *widget, gpointer p) {
    gint i;
    i = GPOINTER_TO_INT(p);
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(buffer_button[i]))) {
        if (buffer[i] !=
            1) // Don't do anything if initiated by buffer_button_cb()
        {
            gtk_databox_graph_add(GTK_DATABOX(box), graph[i + 1]);
            buffer[i] = 1; // Its not on the screen
            gtk_toggle_action_set_active(buffer_menu[i], TRUE);
        }
    } else {
        if (buffer[i] ==
            1) // Don't do anything if initiated by buffer_button_cb()
        {
            gtk_databox_graph_remove(GTK_DATABOX(box), graph[i + 1]);
            buffer[i] = 0; // Its on the screen
            gtk_toggle_action_set_active(buffer_menu[i], FALSE);
        }
    }
    buffer_last_clicked = i;
}

static void buffer_menu_cb(GtkWidget *widget, gpointer p) {
    gint i;
    i = GPOINTER_TO_INT(p);

    if (gtk_toggle_action_get_active(buffer_menu[i])) {
        if (buffer[i] !=
            1) // Don't do anything if initiated by buffer_button_cb()
        {
            gtk_databox_graph_add(GTK_DATABOX(box), graph[i + 1]);
            buffer[i] = 1; // Its not on the screen
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(buffer_button[i]),
                                         TRUE);
        }
    } else {
        if (buffer[i] ==
            1) // Don't do anything if initiated by buffer_button_cb()
        {
            gtk_databox_graph_remove(GTK_DATABOX(box), graph[i + 1]);
            buffer[i] = 0; // Its on the screen
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(buffer_button[i]),
                                         FALSE);
        }
    }
    buffer_last_clicked = i;
}

// cleanup and quit
static void cleanup_gui(GtkWidget *widget, struct FFT_Frame *data) {
    if (open_dialog)
        gtk_widget_destroy(GTK_WIDGET(open_dialog));
    if (save_as_dialog)
        gtk_widget_destroy(GTK_WIDGET(save_as_dialog));
    gtk_main_quit();
    printf("GUI is done with cleanup\n");
}

gboolean open_file(gchar *fn) {
    int k;
    FILE *file_handle;
    gint read_plot_pts[1];
    printf("%s is being opened\n", fn);
    file_handle = fopen(fn, "rb");
    if (file_handle != NULL) {
        fread(read_plot_pts, sizeof(gint), 1, file_handle);
        if (read_plot_pts[0] == PLOT_PTS) {
            for (k = 0; k < N_BUFF; k++)
                fread(guiYBuf[k], sizeof(gfloat), PLOT_PTS, file_handle);
            if (save_name_str)
                g_string_assign(save_name_str, fn);
            else
                save_name_str = g_string_new(fn);
            return TRUE;
        } else {
            message("Wrong file format", NULL, TRUE);
            fprintf(stderr, "PLOT_PTS is different from PLOT_PTS "
                            "last captured size.");
            fprintf(stderr, "N_FFT has been changed from N_FFT=%d "
                            "* 2 since your last capture.\n",
                    (int)read_plot_pts);
            return FALSE;
        }
    } else {
        message("Couldn't open file %s for reading\n", fn, TRUE);
        return FALSE;
    }
    fclose(file_handle);
}

static void save_file(char *fn) {
    int k;
    gint tmp_array[1];
    FILE *file_handle;
    printf("%s is being saved\n", fn);
    /*      for (k = 0; k < PLOT_PTS; k++)
          {
              printf("%g*",guiYBufAvg[k]);
          } */
    file_handle = fopen(fn, "wb");
    if (file_handle != NULL) {
        tmp_array[0] = PLOT_PTS;
        fwrite(tmp_array, sizeof(gint), 1, file_handle);
        for (k = 0; k < N_BUFF; k++)
            fwrite(guiYBuf[k], sizeof(gfloat), PLOT_PTS, file_handle);
        if (save_name_str)
            g_string_assign(save_name_str, fn);
        else
            save_name_str = g_string_new(fn);
        fclose(file_handle);
    } else
        message("Couldn't open file %s for writing. Usually this is a "
                "permissions issue.",
                fn, TRUE);
}

/* #ifdef MAC_INTEGRATION

static char strBuffer[PATH_MAX];

// To open a file, pass docList containing one record with the file to open
//     and set basename to NULL.
// To save a flle, pass basename with the file name
//     and docList containing one record with the encloseing folder
// doclist must contain exactly one entry.

static OSStatus DoOpenSave(AEDescList docList, CFStringRef basename)

{
    int i; // Loop counter.

    // Create the File Open Dialog class.
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];

    // Enable the selection of files in the dialog.
    [openDlg setCanChooseFiles:YES];

    // Disable the selection of directories in the dialog.
    [openDlg setCanChooseDirectories:NO];

    // Disable multiple selections.
    [openDlg setAllowsMultipleSelection:NO];

    // Display the dialog.  If the OK button was pressed,
    // process the files.
    if ( [openDlg runModalForDirectory:nil file:nil] == NSOKButton )
    {
        // Get an array containing the full filenames of all
        // files and directories selected.
        NSArray* files = [openDlg filenames];

        // Loop through all the files and process them.
        if ( [files count] == 1)
        {
            NSString* fileName = [files objectAtIndex:0];

            return fileName
        }
        else
            message("Cannot open more than one file at a time.", NULL, TRUE);
            return(0);
        }
    }
}

// Handler function for opening files from the OS X finder
// such as double-click on a data file
OSErr
openAndPrintDocsEventHandler(AppleEvent *theAppleEvent, AppleEvent *reply,
                                       SInt32 handlerRefcon)
{
   AEDescList  docList;
   OSErr       osError;

   osError = AEGetParamDesc(theAppleEvent, keyDirectObject,
                            typeAEList, &docList);

   if (osError == noErr)
      osError = DoOpenSave(docList, NULL);
   fprintf(stderr, "OS X error %d\n", (int)osError);
   return(0);
}

static void
open_cb(GtkWidget *widget, char *data)
{
   OSStatus status;
   NavDialogCreationOptions navOptions;
   CFStringRef              uti;
   CFMutableArrayRef		 identifiers;
   NavDialogRef             theDialog = NULL;

   status = NavGetDefaultDialogCreationOptions(&navOptions);
   require_noerr(status, NavGetDefaultDialogCreationOptions);

   navOptions.preferenceKey = 1;
   navOptions.optionFlags &= ~kNavAllowMultipleFiles;

   gtk_action_set_sensitive(open_menuitem, 0);
   gtk_action_set_sensitive(save_as, 0);
   gtk_action_set_sensitive(save_now, 0);

   status = NavCreateGetFileDialog(&navOptions, NULL, NULL, NULL, NULL, NULL,
&theDialog);
   require_noerr(status, NavCreateChooseFileDialog);

   // BRP-PACU can open files with the ".brp" extension
   identifiers = CFArrayCreateMutable( kCFAllocatorDefault, 0,
&kCFTypeArrayCallBacks );
   require_action( identifiers != NULL, CantCreateChooseFileFilterIdentifiers,
status = coreFoundationUnknownErr );

   // create the image browser UTI conforming to "public.data" because it's a
data file rather than a bundle
   uti = UTTypeCreatePreferredIdentifierForTag( kUTTagClassFilenameExtension,
CFSTR("brp"),
         kUTTypeData );
   require_action( uti != NULL, CantCreateImageBrowserUTI, status =
coreFoundationUnknownErr );

   CFArrayAppendValue( identifiers, uti );

   // filter by image browser UTI
   status = NavDialogSetFilterTypeIdentifiers( theDialog, identifiers );
   require_noerr( status, CantSetChooseFileFilterIdentifiers );

   status = NavDialogRun(theDialog);
   require_noerr(status, NavDialogRun);

   NavReplyRecord aNavReplyRecord;
   status = NavDialogGetReply(theDialog, &aNavReplyRecord);
   require((status == noErr) || (status == userCanceledErr), NavDialogGetReply);

   if (aNavReplyRecord.validRecord)
      status = DoOpenSave(aNavReplyRecord.selection, NULL);
   else
      status = userCanceledErr;

NavDialogGetReply:

   NavDisposeReply(&aNavReplyRecord);

CantCreateChooseFileFilterIdentifiers:
CantCreateImageBrowserUTI:
// coreFoundationUnknownErr:
CantSetChooseFileFilterIdentifiers:
NavDialogRun:
NavCreateChooseFileDialog:
NavGetDefaultDialogCreationOptions:

   if (status && status != userCanceledErr)
      fprintf(stderr, "OS X error %d\n", (int) status);
   if (theDialog != NULL)
      NavDialogDispose(theDialog);

   gtk_action_set_sensitive(save_as, 1);
   gtk_action_set_sensitive(save_now, 1);
   gtk_action_set_sensitive(open_menuitem, 1);
   return;
}

// static OSStatus Do_SaveAs(WindowRef inWindow)
static void
save_as_cb(GtkWidget *widget, char *data)
{
   OSStatus status = noErr;
   CFStringRef theFileName;

   NavDialogCreationOptions navOptions;
   status = NavGetDefaultDialogCreationOptions(&navOptions);
   require_noerr(status, NavGetDefaultDialogCreationOptions);

   theFileName = CFStringCreateWithCString
                 (NULL, save_name_str ? strrchr(save_name_str->str, '/') + 1 :
"Untitled.brp",
                  kCFStringEncodingUTF8);
   CFMutableStringRef newFileName = CFStringCreateMutableCopy(NULL, 0,
theFileName);
   CFRelease(theFileName);

   CFIndex len = CFStringGetLength(newFileName);
   if (len > 255)
      len = 255;

   UniChar buffer[255];
   CFStringGetCharacters(newFileName, CFRangeMake(0, len), buffer);

   UniCharCount extIndex;
   status = LSGetExtensionInfo(len, buffer, &extIndex);
   require_noerr(status, LSGetExtensionInfo);

   if (extIndex != kLSInvalidExtensionIndex)
      CFStringReplace(newFileName, CFRangeMake(extIndex, len - extIndex),
CFSTR("brp"));
   else
      CFStringAppend(newFileName, CFSTR(".brp"));

   navOptions.preferenceKey = 2;
   navOptions.optionFlags |= kNavPreserveSaveFileExtension;
   navOptions.saveFileName = newFileName;

   NavDialogRef theDialog = NULL;
   gtk_action_set_sensitive(open_menuitem, 0);
   gtk_action_set_sensitive(save_as, 0);
   gtk_action_set_sensitive(save_now, 0);

   status = NavCreatePutFileDialog(&navOptions, (OSType) NULL, (OSType) "BRPP",
NULL, NULL, &theDialog);
   CFRelease(newFileName);
   require_noerr(status, NavCreatePutFileDialog);

   status = NavDialogRun(theDialog);
   require_noerr(status, NavDialogRun);

   NavReplyRecord aNavReplyRecord;
   status = NavDialogGetReply(theDialog, &aNavReplyRecord);
   require((status == noErr) || (status == userCanceledErr), NavDialogGetReply);

   if (aNavReplyRecord.validRecord)
      status = DoOpenSave(aNavReplyRecord.selection,
aNavReplyRecord.saveFileName);
   else
      status = userCanceledErr;

NavDialogRun:
NavCreatePutFileDialog:
LSGetExtensionInfo:
NavGetDefaultDialogCreationOptions:
NavDialogGetReply:

   if (status && status != userCanceledErr)
      fprintf(stderr, "OS X error %d\n", (int) status);
   if (theDialog != NULL)
      NavDialogDispose(theDialog);

   gtk_action_set_sensitive(save_as, 1);
   gtk_action_set_sensitive(save_now, 1);
   gtk_action_set_sensitive(open_menuitem, 1);
   return;
}   // Do_SaveAs

     #else */
static void open_cb(GtkWidget *widget, gchar *data) {
    GtkFileFilter *file_filter = NULL;
    gint result;

    if (open_dialog != NULL) {
        gtk_window_present(GTK_WINDOW(open_dialog));
    }
    open_dialog = gtk_file_chooser_dialog_new(
        "Open Capture Buffers From", GTK_WINDOW(bkg_dialog),
        GTK_FILE_CHOOSER_ACTION_OPEN, ("_Cancel"), GTK_RESPONSE_CANCEL,
        ("_Open"), GTK_RESPONSE_ACCEPT, NULL);
    //   if(save_name_str)
    //      gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(open_dialog),save_name_str->str);
    //   else
    //      gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(open_dialog),home_string);
    file_filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(file_filter, "*.brp");
    gtk_file_filter_set_name(file_filter, "BRP-PACU files");
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(open_dialog),
                                GTK_FILE_FILTER(file_filter));
    gtk_window_set_transient_for(GTK_WINDOW(open_dialog), GTK_WINDOW(window));
    gtk_action_set_sensitive(save_as, 0);
    gtk_action_set_sensitive(save_now, 0);
    result = gtk_dialog_run(GTK_DIALOG(open_dialog));
    switch (result) {
    case GTK_RESPONSE_ACCEPT:
        open_file(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(open_dialog)));
        break;
    default:
        break;
    }
    gtk_widget_destroy(open_dialog);
    gtk_action_set_sensitive(save_as, 1);
    gtk_action_set_sensitive(save_now, 1);
    open_dialog = NULL;
    return;
}

static void save_as_cb(GtkWidget *widget, char *data) {
    gint result;
    GtkFileFilter *file_filter = NULL;
    char *file_name, *extension;

    if (save_as_dialog != NULL) {
        gtk_window_present(GTK_WINDOW(save_as_dialog));
        return;
    }

    save_as_dialog = gtk_file_chooser_dialog_new(
        "Save Capture Buffers As (*.brp recommended)", GTK_WINDOW(bkg_dialog),
        GTK_FILE_CHOOSER_ACTION_SAVE, ("_Cancel"), GTK_RESPONSE_CANCEL,
        ("_Save_As"), GTK_RESPONSE_ACCEPT, NULL);
    if (save_name_str)
        gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(save_as_dialog),
                                      save_name_str->str);

    file_filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(file_filter, "*.brp");
    gtk_file_filter_set_name(file_filter, "BRP-PACU files");
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(save_as_dialog),
                                GTK_FILE_FILTER(file_filter));
    gtk_window_set_transient_for(GTK_WINDOW(save_as_dialog),
                                 GTK_WINDOW(window));

    gtk_file_chooser_set_do_overwrite_confirmation(
        GTK_FILE_CHOOSER(save_as_dialog), TRUE);

    gtk_action_set_sensitive(open_menuitem, 0);
    if (save_name_str)
        g_string_assign(file_name_str, save_name_str->str);
    while (TRUE) {
        file_name = strrchr(file_name_str->str, '/');
        file_name = file_name ? file_name + 1 : file_name_str->str;
        gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(save_as_dialog),
                                          file_name);
        result = gtk_dialog_run(GTK_DIALOG(save_as_dialog));
        file_name =
            gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(save_as_dialog));
        g_string_assign(file_name_str, file_name);
        file_name = file_name_str->str;
        extension = strrchr(file_name, '.');
        if (extension && !strcmp(extension, ".brp"))
            break;
        g_string_append(file_name_str, ".brp");
    }
    switch (result) {
    case GTK_RESPONSE_ACCEPT:
        save_file(file_name);
        break;
    default:
        break;
    }
    gtk_widget_destroy(save_as_dialog);
    save_as_dialog = NULL;
    gtk_action_set_sensitive(open_menuitem, 1);
    return;
}
///   #endif  ** ****** */
static void save_now_cb(GtkWidget *widget, char *data) {
    if (save_name_str)
        save_file(save_name_str->str);
    else
        save_as_cb(widget, data);
}

// Trigger the gtk callback to find the impulse response in BRP_PACU.c
static void impulse_cb(GtkWidget *widget,
                       struct FFT_Frame *data) // , gtkwidget *widget)
{
    gtk_widget_show_all(impulse_window);
    gtk_window_present(GTK_WINDOW(impulse_window));
    data->find_impulse = 1; // signal for Fill_Buffer fxn to find delay
    data->find_delay = 1;   // signal for Fill_Buffer fxn to find delay
}

// Trigger the gtk callback to find the delay in BRP_PACU.c
static void delay_cb(GtkWidget *widget,
                     struct FFT_Frame *data) // , gtkwidget *widget)
{
    gtk_window_set_transient_for(GTK_WINDOW(delay_window), GTK_WINDOW(window));
    gtk_window_set_decorated(GTK_WINDOW(delay_window), FALSE);
    gtk_widget_show_all(delay_window);
    gtk_window_present(GTK_WINDOW(delay_window));

    data->find_delay = 1; // signal for Fill_Buffer fxn to find delay
}

static void resize_default_cb(GtkWidget *widget,
                              GtkWidget *box) // , GtkWidget *widget)
{
    gfloat min_x, min_y, max_x, max_y;
    min_x = 20.0;
    max_x = (gfloat)NYQUIST;
    min_y = -100.0;
    max_y = 100.0;
    gtk_databox_set_total_limits(GTK_DATABOX(box), min_x, max_x, max_y, min_y);
    gtk_widget_queue_draw(GTK_WIDGET(box));
}
// Auto-resizing function
static void resize_cb(GtkWidget *widget, GtkWidget *box) // , GtkWidget *widget)
{
    gint k;
    gfloat min_x, min_y, max_x, max_y, tempY;
    min_x = 20.0;
    max_x = (gfloat)NYQUIST;
    max_y = -100.0;
    min_y = 100.0;
    for (k = (int)(min_x / (gfloat)FBIN); k < PLOT_PTS - 10; k++) {
        tempY = guiY[k];
        max_y = (max_y > tempY) ? max_y : tempY;
        min_y = (min_y < tempY) ? min_y : tempY;
    }
    gtk_databox_set_visible_limits(GTK_DATABOX(box), min_x, max_x, max_y + 5.0,
                                   min_y - 5.0);
    gtk_widget_queue_draw(GTK_WIDGET(box));
}

// update the frequency and dB level labels
static gint show_motion_notify_cb(GtkWidget *widget,
                                  GdkEventMotion *event) // , GtkWidget *widget)
{
    gfloat x;
    gfloat y;
    GtkDatabox *box_coords = GTK_DATABOX(widget);
    //   GtkDataboxValueRectangle  value;
    x = gtk_databox_pixel_to_value_x(box_coords, event->x);
    y = gtk_databox_pixel_to_value_y(box_coords, event->y);
    gchar *label;

    // y= (gfloat)y;
    label = g_strdup_printf("%5.1f Hz", x);
    gtk_label_set_text(GTK_LABEL(gui_label), label);
    g_free((gpointer)label);
    label = g_strdup_printf("%3.2f dB", (y));
    gtk_label_set_text(GTK_LABEL(gui_db_label), label);
    g_free((gpointer)label);
    return FALSE;
}

static void preferences_dialog_cb(GtkWidget *widget) // , gtkwidget *widget)
{
    gtk_window_set_transient_for(GTK_WINDOW(preferences_dialog),
                                 GTK_WINDOW(window));
    gtk_window_set_decorated(GTK_WINDOW(preferences_dialog), FALSE);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(smoothing_spin_button),
                              (gdouble)smooth_factor);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(averaging_spin_button),
                              (gdouble)avg_num);

    gtk_widget_show_all(preferences_dialog);
    gtk_window_present(GTK_WINDOW(preferences_dialog));
}

static gboolean close_preferences_cb(GtkWidget *widget) // , gtkwidget *widget)
{
    gtk_widget_hide(preferences_dialog);
    return TRUE;
}

static void apply_preferences_cb(GtkWidget *widget) {
    smooth_factor = gtk_spin_button_get_value_as_int(
        GTK_SPIN_BUTTON(smoothing_spin_button));
    smooth_constant = pow(2, smooth_factor) - 1;
    avg_num = gtk_spin_button_get_value_as_int(
        GTK_SPIN_BUTTON(averaging_spin_button));
}

/*#ifdef MAC_INTEGRATION
static gboolean deal_with_quit(GtkosxApplication *app, gpointer user_data) {
    if (open_dialog)
        gtk_widget_destroy(GTK_WIDGET(open_dialog));
    if (save_as_dialog)
        gtk_widget_destroy(GTK_WIDGET(save_as_dialog));
    gtk_main_quit();
    printf("GUI is done with cleanup\n");
    return TRUE;
}

static gboolean deal_with_open(GtkosxApplication *app, gchar *path,
                               gpointer user_data) {
    return open_file(path);
}
#endif*/

gboolean create_gui(struct FFT_Frame *data, char *datadir) {
/*#ifdef MAC_INTEGRATION
    GtkosxApplication *theApp = g_object_new(GTKOSX_TYPE_APPLICATION, NULL);
#endif*/
    GtkWidget *box_container;
    GtkWidget *box_container_impulse;
    /////   GtkWidget *label;
    GtkWidget *table;
    GtkWidget *table_impulse;
    GtkWidget *separator;
    ////   GtkRuler * hruler;
    GtkDataboxGraph *my_grid;
    GtkBuilder *builder = gtk_builder_new();
    avg_num = 32;
    smooth_factor = 5;
    smooth_constant = pow(2, smooth_factor) - 1;

    FILE *file_handle;
    gint read_plot_pts[1];
    file_name_str = g_string_new("Untitled.brp");

    char tmp_string[] = "BRP-PACU vxx.xx.xxxxxxx ";
    char gtkbuilder_path[400];
    graph = g_new0(GtkDataboxGraph *, 10);      // allocate memory graph array
    graph_impulse = g_new0(GtkDataboxGraph, 1); // allocate memory graph array
    gint k;
    gint i;
    gfloat min_x, max_x, min_y, max_y;
    /* set the extrema */
    min_x = 20.0;
    max_x = (gfloat)NYQUIST;
    min_y = -100.0;
    max_y = 100.0;

    GError *error = NULL;

/*#ifdef MAC_INTEGRATION
    // Find GtkBuilder file in application resource directory first
    datadir = gtkosx_application_get_resource_path();
#endif*/
    sprintf(gtkbuilder_path, "%s/BRP_PACU.ui", datadir);
    if (access(gtkbuilder_path, R_OK) != 0 ) {
        fprintf(stderr, "Notice: system-wide UI file %s doesn't exist, assume we're running from the build environment and try './'",
                gtkbuilder_path);
        sprintf(gtkbuilder_path, "./BRP_PACU.ui");
    }
    if (gtk_builder_add_from_file(builder, gtkbuilder_path, &error) == 0) {
        // gtk_builder_add_from_file throws error about the path
        message("Couldn't load builder file: %s", gtkbuilder_path, TRUE);
        //printf(1,"\n\n-----------Error--------------\n\n\n");
        return (FALSE);
    }

    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    bkg_dialog = GTK_WIDGET(gtk_builder_get_object(builder, "bkg_dialog"));
    about_me_window =
        GTK_WIDGET(gtk_builder_get_object(builder, "about_me_window"));
    about_ok = GTK_WIDGET(gtk_builder_get_object(builder, "about_ok"));
    delay_window = GTK_WIDGET(gtk_builder_get_object(builder, "delay1"));
    impulse_window =
        GTK_WIDGET(gtk_builder_get_object(builder, "impulse_window"));
    box_container = GTK_WIDGET(gtk_builder_get_object(builder, "vbox1"));
    gui_label = GTK_WIDGET(gtk_builder_get_object(builder, "label3"));
    gui_sb_label = GTK_WIDGET(gtk_builder_get_object(builder, "delay_label"));
    gui_sb = GTK_WIDGET(gtk_builder_get_object(builder, "spinbutton1"));
    gui_db_label = GTK_WIDGET(gtk_builder_get_object(builder, "label4"));
    save_as = G_ACTION(gtk_builder_get_object(builder, "save_as"));
    save_now = G_ACTION(gtk_builder_get_object(builder, "save_now"));
    open_menuitem = G_ACTION(gtk_builder_get_object(builder, "open"));
    box_container_impulse =
        GTK_WIDGET(gtk_builder_get_object(builder, "impulse_box"));
    measured_draw =
        GTK_WIDGET(gtk_builder_get_object(builder, "Measured_Draw"));
    reference_draw =
        GTK_WIDGET(gtk_builder_get_object(builder, "Reference_Draw"));
    gui_status_delay_label =
        GTK_WIDGET(gtk_builder_get_object(builder, "delay_status_label"));

	// Pink noise
	volume_pink_gui =
        GTK_WIDGET(gtk_builder_get_object(builder, "volumebutton1"));
	g_signal_connect(
        G_OBJECT(gtk_builder_get_object(builder, "pinknoise_button")),
        "toggled", G_CALLBACK(pinknoise_button_toggled_cb), NULL);

	transfer_function_toggle =
        GTK_WIDGET(gtk_builder_get_object(builder, "TransferFxn"));
    transfer_function_menu =
        GTK_TOGGLE_ACTION(gtk_builder_get_object(builder, "transfer_fxn"));
    preferences_dialog =
        GTK_WIDGET(gtk_builder_get_object(builder, "preferences_dialog"));
    smoothing_spin_button =
        GTK_WIDGET(gtk_builder_get_object(builder, "spinbutton_smoothing"));
    averaging_spin_button =
        GTK_WIDGET(gtk_builder_get_object(builder, "spinbutton_averaging"));
    g_signal_connect(
        G_OBJECT(gtk_builder_get_object(builder, "plot_preferences")),
        "activate", G_CALLBACK(preferences_dialog_cb), NULL);
    g_signal_connect(
        G_OBJECT(gtk_builder_get_object(builder, "close_preferences")),
        "clicked", G_CALLBACK(close_preferences_cb), NULL);
    g_signal_connect(
        G_OBJECT(gtk_builder_get_object(builder, "apply_preferences")),
        "clicked", G_CALLBACK(apply_preferences_cb), NULL);
    g_signal_connect(G_OBJECT(preferences_dialog), "delete_event",
                     G_CALLBACK(gtk_widget_hide_on_delete), NULL);
    gtk_window_set_decorated(GTK_WINDOW(preferences_dialog), FALSE);

    // g_signal_connect (G_OBJECT (gtk_builder_get_object (builder,
    // "volumebutton1")), "popdown", G_CALLBACK (volume_popdown_gui), NULL);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "volumebutton1")),
                     "value-changed", G_CALLBACK(volume_gui), NULL);
    //  g_signal_connect (G_OBJECT (gtk_builder_get_object (builder,
    //  "volumebutton1")), "clicked", G_CALLBACK (volume_popup_gui), NULL);

    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "quit_ap")),
                     "activate", G_CALLBACK(cleanup_gui), NULL);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "save_as")),
                     "activate", G_CALLBACK(save_as_cb), NULL);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "save_now")),
                     "activate", G_CALLBACK(save_now_cb), NULL);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "open")),
                     "activate", G_CALLBACK(open_cb), NULL);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "about_me")),
                     "activate", G_CALLBACK(about_me_cb), NULL);
    g_signal_connect(G_OBJECT(about_me_window), "delete_event",
                     G_CALLBACK(gtk_widget_hide_on_delete), NULL);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "about_ok")),
                     "clicked", G_CALLBACK(about_ok_cb), NULL);
    g_signal_connect(G_OBJECT(transfer_function_menu), "activate",
                     G_CALLBACK(transfer_fxn_cb), NULL);
    g_signal_connect(G_OBJECT(transfer_function_toggle), "clicked",
                     G_CALLBACK(transfer_function_toggled_cb), NULL);
    g_signal_connect(GTK_BUTTON(gtk_builder_get_object(builder, "find_delay")),
                     "clicked", G_CALLBACK(delay_cb), data);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "find_delay_m")),
                     "activate", G_CALLBACK(delay_cb), data);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(cleanup_gui),
                     NULL);
    g_signal_connect(G_OBJECT(window), "delete_event",
                     G_CALLBACK(cleanup_gui), NULL);
    g_signal_connect(G_OBJECT(delay_window), "delete_event",
                     G_CALLBACK(gtk_widget_hide_on_delete), NULL);
    g_signal_connect(
        G_OBJECT(gtk_builder_get_object(builder, "delay_keep_button")),
        "clicked", G_CALLBACK(delay_keep_cb), NULL);
    g_signal_connect(
        G_OBJECT(gtk_builder_get_object(builder, "impulse_response")),
        "activate", G_CALLBACK(impulse_cb), data);
    g_signal_connect(G_OBJECT(impulse_window), "delete_event",
                     G_CALLBACK(gtk_widget_hide_on_delete), NULL);

    g_signal_connect(
        G_OBJECT(gtk_builder_get_object(builder, "delay_custom_button")),
        "clicked", G_CALLBACK(delay_custom_cb), NULL);

    gui_frequency = 0;
    gtk_widget_set_size_request(GTK_WIDGET(window), WINDOW_W, WINDOW_H);

    sprintf(tmp_string, "BRP-PACU v%s", VERSION);
    gtk_window_set_title(GTK_WINDOW(window), tmp_string);
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);

    ///// Impulse response Window  /////////////////////////
    gtk_widget_set_size_request(impulse_window, IMPULSE_WINDOW_W,
                                IMPULSE_WINDOW_H);

    sprintf(tmp_string, "BRP-PACU Impulse");
    gtk_window_set_title(GTK_WINDOW(impulse_window), tmp_string);
    gtk_container_set_border_width(GTK_CONTAINER(impulse_window), 0);
    ////////////////////////////////////////////////////////

    separator = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(box_container), separator, FALSE, FALSE, 0);
    gtk_label_set_text(GTK_LABEL(gui_label), "0");

    gui_idle = 0;
    gui_frequency = 3. * G_PI / 2.;
    gui_counter = 0;

    // Create a GtkDatabox widget along with scrollbars and rulers
    gtk_databox_create_box_with_scrollbars_and_rulers(&box, &table, TRUE, TRUE,
                                                      TRUE, TRUE);
    // Create a GtkDatabox widget for impulse response along with scrollbars
    // and rulers
    gtk_databox_create_box_with_scrollbars_and_rulers(
        &impulse_box, &table_impulse, TRUE, TRUE, TRUE, TRUE);

    gtk_databox_set_total_limits(GTK_DATABOX(box), min_x, max_x, max_y, min_y);

    min_x = 30.0;
    max_x = (gfloat)NYQUIST;
    min_y = -100.0;
    max_y = 100.0;
    gtk_databox_set_total_limits(GTK_DATABOX(impulse_box), min_x, max_x, max_y,
                                 min_y);

    // hruler = gtk_databox_get_hruler (GTK_DATABOX(box));
    // gtk_databox_set_scale_type_x (GTK_DATABOX (box),
    // GTK_DATABOX_SCALE_LOG);
    gtk_databox_set_scale_type_x(GTK_DATABOX(box), GTK_DATABOX_SCALE_LOG2);
    gtk_databox_set_scale_type_y(GTK_DATABOX(box), GTK_DATABOX_SCALE_LINEAR);
    /*for(index=0; index<10; index++)
       hruler->metric->ruler_scale[index] = lscale[index];
    */
    // gtk_databox_set_hruler (box,hruler);
    g_signal_connect(G_OBJECT(box), "motion_notify_event",
                     G_CALLBACK(show_motion_notify_cb), NULL);
    // g_signal_connect (G_OBJECT (hruler), "state_changed", G_CALLBACK
    // (show_motion_notify_cb),NULL);

    gtk_box_pack_start(GTK_BOX(box_container), table, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box_container_impulse), table_impulse, TRUE,
                       TRUE, 0);
	
    background_color.red = 0.0;
    background_color.green = 0.0;
    background_color.blue = 0.0;
	background_color.alpha = 1.0;

    gtk_widget_modify_bg(box, GTK_STATE_NORMAL, &background_color);

    guiX = g_new0(gfloat, PLOT_PTS);
    guiY = g_new0(gfloat, PLOT_PTS);
    gui_impulse_Y = g_new0(gfloat, N_FFT);
    gui_impulse_X = g_new0(gfloat, N_FFT);

    for (i = 0; i < N_FFT / 2; i++) {
        gui_impulse_Y[i] = .01;
        gui_impulse_X[i] = ((gfloat)i) / ((gfloat)FSAMP);
    }
    for (i = 0; i < PLOT_PTS; i++) {
        guiX[i] = ((gfloat)i) * (gfloat)FBIN;
        for (k = 0; k < MAX_AVG_NUM; k++)
            avgY[i][k] = .01;
        guiY[i] = .01;
        for (k = 0; k < N_BUFF; k++)
            guiYBuf[k][i] = 0.0;
        guiYBufAvgHold[i] = 0.0;
        // guiY[i] = i * 40.0 / (float) PLOT_PTS - 20;
    }
    trace_transfer_color.red = 1.0;
    trace_transfer_color.green = 1.0;
    trace_transfer_color.blue = 1.0;
	trace_transfer_color.alpha = 1.0;

    graph[0] =
        gtk_databox_lines_new(PLOT_PTS, guiX, guiY, &trace_transfer_color, 1);
    gtk_databox_graph_add(GTK_DATABOX(box), graph[0]);
    for (i = 0; i < N_BUFF; i++)
        graph[i + 1] = gtk_databox_lines_new(PLOT_PTS, guiX, guiYBuf[i],
                                             &line_color[i], 1);
    grid_color.red = 1.0;
    grid_color.green = 1.0;
    grid_color.blue = 0.5;
	grid_color.alpha = 0.5;
    my_grid = gtk_databox_grid_array_new(19, 10, NULL, grid_x, &grid_color, 1);
    // my_grid = gtk_databox_grid_new (19, 21.5, &grid_color, 1);
    gtk_databox_graph_add(GTK_DATABOX(box), my_grid);

    trace_impulse_color.red = 0.25;
    trace_impulse_color.green = 0.25;
    trace_impulse_color.blue = 1.0;
	trace_impulse_color.alpha = 1.0;
	
    graph_impulse = gtk_databox_lines_new(
        PLOT_PTS, gui_impulse_X, gui_impulse_Y, &trace_impulse_color, 1);
    gtk_databox_graph_add(GTK_DATABOX(impulse_box), graph_impulse);

    buffer_button[0] = GTK_WIDGET(gtk_builder_get_object(builder, "buff1"));
    buffer_button[1] = GTK_WIDGET(gtk_builder_get_object(builder, "buff2"));
    buffer_button[2] = GTK_WIDGET(gtk_builder_get_object(builder, "buff3"));
    buffer_button[3] = GTK_WIDGET(gtk_builder_get_object(builder, "buff4"));
    buffer_button[4] = GTK_WIDGET(gtk_builder_get_object(builder, "buffAvg"));
    buffer_menu[0] =
        GTK_TOGGLE_ACTION(gtk_builder_get_object(builder, "buffer_1"));
    buffer_menu[1] =
        GTK_TOGGLE_ACTION(gtk_builder_get_object(builder, "buffer_2"));
    buffer_menu[2] =
        GTK_TOGGLE_ACTION(gtk_builder_get_object(builder, "buffer_3"));
    buffer_menu[3] =
        GTK_TOGGLE_ACTION(gtk_builder_get_object(builder, "buffer_4"));
    buffer_menu[4] =
        GTK_TOGGLE_ACTION(gtk_builder_get_object(builder, "bufferAvg"));

    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "auto_resize")),
                     "clicked", G_CALLBACK(resize_cb), (gpointer)box);
    g_signal_connect(
        G_OBJECT(gtk_builder_get_object(builder, "resize_default")), "clicked",
        G_CALLBACK(resize_default_cb), (gpointer)box);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "auto_resize_m")),
                     "activate", G_CALLBACK(resize_cb), (gpointer)box);
    g_signal_connect(
        G_OBJECT(gtk_builder_get_object(builder, "resize_default_m")),
        "activate", G_CALLBACK(resize_default_cb), (gpointer)box);
    for (i = 0; i < N_BUFF; i++) {
        g_signal_connect(G_OBJECT(buffer_button[i]), "clicked",
                         G_CALLBACK(buffer_button_cb),
                         GINT_TO_POINTER((gint)i));
        g_signal_connect(G_OBJECT(buffer_menu[i]), "activate",
                         G_CALLBACK(buffer_menu_cb), GINT_TO_POINTER((gint)i));
    }
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "capt")),
                     "clicked", G_CALLBACK(capture_cb), (gpointer)box);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "capt_m")),
                     "activate", G_CALLBACK(capture_cb), (gpointer)box);
    g_signal_connect(G_OBJECT(gtk_builder_get_object(builder, "gain1")),
                     "value-changed", G_CALLBACK(gain_cb),
                     (G_OBJECT(gtk_builder_get_object(builder, "gain1"))));

    volume_pink_value =
        gtk_spin_button_get_value(GTK_SPIN_BUTTON(volume_pink_gui));
    gtk_widget_show_all(window);

/////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef MAC_INTEGRATION
    GtkWidget *menubar1;
    GtkAction *quit_ap;
    GtkWidget *about_item;

    menubar1 = GTK_WIDGET(gtk_builder_get_object(builder, "menubar1"));
    quit_ap = GTK_ACTION(gtk_builder_get_object(builder, "quit_ap"));
    about_item = GTK_WIDGET(gtk_menu_item_new_with_label("About BRP-PACU"));
    gtk_widget_hide(menubar1);
    // Put menu bar to the top of the screen
    gtkosx_application_set_menu_bar(theApp, GTK_MENU_SHELL(menubar1));

    // move "About BRP-PACU" menu item to application menu
    g_signal_connect(about_item, "activate", G_CALLBACK(about_me_cb),
                     "about_me");
    gtkosx_application_insert_app_menu_item(theApp, GTK_WIDGET(about_item), 0);
    gtkosx_application_ready(theApp);
    gtk_action_set_visible(
        GTK_ACTION(gtk_builder_get_object(builder, "about_me")), FALSE);
    gtk_action_set_visible(
        GTK_ACTION(gtk_builder_get_object(builder, "quit_ap")), FALSE);
    // Enable file open from Mac OS
    g_signal_connect(theApp, "NSApplicationOpenFile",
                     G_CALLBACK(deal_with_open), NULL);
    // Quit from Mac OS
    g_signal_connect(theApp, "NSApplicationBlockTermination",
                     G_CALLBACK(deal_with_quit), NULL);
// use command key as accelerator
//    gtk_accel_map_load("mac_accel_map"); // does not work for GtkToggleButton
#endif
    home_string = getenv("HOME");
    file_path1 = malloc(sizeof(home_string) + 50);
    file_path2 = malloc(sizeof(home_string) + 50);

#ifdef MAC_INTEGRATION
    sprintf(file_path1, "%s/Library/Caches/BRP-PACU", home_string);
#else
    sprintf(file_path1, "%s/.BRP_PACU", home_string);
#endif
    sprintf(file_path2, "%s/buff_store.brp", file_path1);
    if ((file_handle = fopen(file_path2, "rb")) <= 0)
        message("No BRP_PACU initialization file yet\nAre you running "
                "BRP_PACU for the 1st time?\nIf so, a file will be "
                "created for you on your next capture.",
                NULL, FALSE);
    else {
        fread(read_plot_pts, sizeof(gint), 1, file_handle);
        if (read_plot_pts[0] == PLOT_PTS) {
            for (i = 0; i < N_BUFF; i++)
                fread(guiYBuf[i], sizeof(gfloat), PLOT_PTS, file_handle);
        } else {
            message("The BRP_PACU initialization file has the "
                    "wrong format. An initialization file will be "
                    "created for you on your next capture.",
                    NULL, FALSE);
            fprintf(stderr, "PLOT_PTS is different from PLOT_PTS "
                            "saved size, this is because you have "
                            "changed N_FFT since your last "
                            "capture.  Please change it back to %d "
                            "* 2. Otherwise making a new capture "
                            "should overwrite the old file\n",
                    (int)read_plot_pts);
        }
        fclose(file_handle);
    }
    g_object_unref(G_OBJECT(builder));
    return (TRUE);
}
