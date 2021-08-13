#include "functions.h"
#include <gtk/gtk.h>
#include "main.h"

void first_screen(GtkWidget *win) {
    GtkWidget *mainBox, *buttonBox, *image, *btn, *label;
    GtkCssProvider *cssProvider;

    // intializing widgets
    mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(win), mainBox);
    gtk_widget_set_name(mainBox, "mainBox");

    image = gtk_picture_new_for_filename("img/bingo.png");
    gtk_box_append(GTK_BOX(mainBox), image);

    buttonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_append(GTK_BOX(mainBox), buttonBox);
    gtk_widget_set_halign(buttonBox, GTK_ALIGN_CENTER);

    btn = gtk_button_new_with_label("START");
    gtk_box_append(GTK_BOX(buttonBox), btn);
    gtk_button_set_has_frame(GTK_BUTTON(btn), FALSE);


    // initializing the struct data
    global_player_one_data = malloc(sizeof(*global_player_one_data));
    global_player_one_data->window = win;
    global_player_one_data->mainBox = mainBox;

    // setting names
    gtk_widget_set_name(win, "win");
    gtk_widget_set_name(btn, "button");

    // listening to events
    g_signal_connect(btn, "clicked", G_CALLBACK(hide_first), global_player_one_data);

    // loading css
    cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "css/themes.css");
    gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}
