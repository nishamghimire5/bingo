#include "functions.h"
#include "main.h"
#include <gtk/gtk.h>

void player_one(gpointer user_data) {
    struct udata *data = user_data;
    data->player_id = 1;
    draw_input_grid(data);
}

void player_one_new(gpointer user_data) {
  struct udata *data = user_data;
  gtk_widget_hide(data->box);
  player_two(data);
}

void player_one_generate(GtkWidget *widget, gpointer user_data) {
  struct udata *data = user_data;
  get_entry_text(data);
  player_one_new(data);
}
