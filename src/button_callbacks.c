#include "functions.h"
#include "main.h"
#include <gtk/gtk.h>

void hide_first(GtkButton *button, gpointer user_data) {
    struct udata *data = user_data;
    gtk_widget_hide(data->mainBox);
    player_one(data);
}

void replace(GtkWidget *widget, gpointer user_data) {
    struct udata *data = user_data;
    const gchar *btn_label = gtk_button_get_label(GTK_BUTTON(widget));
    for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 5; ++col) {
        if (g_strcmp0(global_player_one_data->entry_text[row][col], btn_label) == 0) {
          global_player_one_data->entry_text[row][col] = "X";
          break;
        }
      }
    }
    for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 5; ++col) {
        if (g_strcmp0(global_player_two_data->entry_text[row][col], btn_label) == 0) {
          global_player_two_data->entry_text[row][col] = "X";
          break;
        }
      }
    }
    //gtk_button_set_label(GTK_BUTTON(widget), "X");
    if (data->player_id == 1) {
      check_win(data);
    } else {
      check_win_two(data);
    }
}
