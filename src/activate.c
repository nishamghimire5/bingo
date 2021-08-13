#include "functions.h"
#include <gtk/gtk.h>
//#include "main.h"

void activate(GApplication *app, gpointer user_data) {
    // definitons
    GtkWidget *win;

    // drawing window
    win = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(win), "BINGO");
    gtk_window_set_default_size(GTK_WINDOW(win), 800, 700);
    gtk_window_set_resizable(GTK_WINDOW(win), FALSE);

    first_screen(win);

    // rendering
    gtk_widget_show(win);
}
