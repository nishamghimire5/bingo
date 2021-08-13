#include "functions.h"
#include "main.h"
#include <gtk/gtk.h>

void player_two(gpointer user_data) {
    struct udata *data = user_data;

    global_player_two_data = malloc(sizeof(*global_player_two_data));
    global_player_two_data->window = data->window;
    global_player_two_data->mainBox = data->mainBox;
    global_player_two_data->player_id = 2;
    draw_input_grid(global_player_two_data);
}

void player_two_new(gpointer user_data) {
  struct udata *data = user_data;
  gtk_widget_hide(data->box);
  generate_grid(global_player_one_data);
}

void player_two_generate(GtkWidget *widget, gpointer user_data) {
  struct udata *data = user_data;
  get_entry_text(data);
  player_two_new(data);
}
