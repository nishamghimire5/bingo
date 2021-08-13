#include "functions.h"
#include "main.h"
#include <gtk/gtk.h>

void generate_grid(gpointer user_data) {
    struct udata *data = user_data;
    static int count = 0;

    GtkWidget *box, *player_id, *grid, *label[5], *btn[5][5];

    //g_print("got here 1: %d\n", count);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(data->window), box);

    if (data->player_id == 1) {
      player_id = gtk_label_new("Player 1");
      gtk_widget_set_name(player_id, "playerLabel");
    } else {
      player_id = gtk_label_new("Player 2");
      gtk_widget_set_name(player_id, "playerLabel");
    }

    gtk_box_append(GTK_BOX(box), player_id);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_box_append(GTK_BOX(box), grid);
    //g_print("got here 0: %d\n", count);
    data->box = box;

    label[0] = gtk_label_new(data->label[0]);
    gtk_widget_set_name(label[0], "gridlabel");
    label[1] = gtk_label_new(data->label[1]);
    gtk_widget_set_name(label[1], "gridlabel");
    label[2] = gtk_label_new(data->label[2]);
    gtk_widget_set_name(label[2], "gridlabel");
    label[3] = gtk_label_new(data->label[3]);
    gtk_widget_set_name(label[3], "gridlabel");
    label[4] = gtk_label_new(data->label[4]);
    gtk_widget_set_name(label[4], "gridlabel");

    //g_print("got here -1: %d\n", count);

    for (int i = 0; i < 5; ++i) {
        if (i == 0) gtk_grid_attach(GTK_GRID(grid), label[i], 1, 1, 2, 2);
        else gtk_grid_attach_next_to(GTK_GRID(grid), label[i], label[i-1], GTK_POS_RIGHT, 2, 2);
    }

    //g_print("got here 2: %d\n", count);

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            btn[row][col] = gtk_button_new_with_label(data->entry_text[row][col]);
            data->button[row][col] = btn[row][col];
            gtk_widget_set_name(btn[row][col], "gridbtn");
            //g_print("got here 3: %d\n", count);
            if (row == 0 && col == 0) {
                gtk_grid_attach(GTK_GRID(grid), btn[row][col], 1, 4, 2, 2);
            } else if (row > 0 && col == 0) {
                gtk_grid_attach(GTK_GRID(grid), btn[row][col], col + 1, (row * 4) + 2, 2, 2);
            } else if (row > 0 || col > 0) {
                gtk_grid_attach_next_to(GTK_GRID(grid), btn[row][col], btn[row][col-1], GTK_POS_RIGHT, 2, 2);
            }
            gtk_button_set_has_frame(GTK_BUTTON(btn[row][col]), FALSE);
            g_signal_connect(btn[row][col], "clicked", G_CALLBACK(replace), data);
        }
    }

    count++;

    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
}

void get_entry_text(gpointer user_data) {
  GtkEntryBuffer *buffer_text[5][5];
  const gchar *text[5][5];
  struct udata *data = user_data;

  data->label[0] = "B";
  data->label[1] = "I";
  data->label[2] = "N";
  data->label[3] = "G";
  data->label[4] = "O";

  for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 5; ++col) {
          buffer_text[row][col] = gtk_entry_get_buffer(GTK_ENTRY(data->entry[row][col]));
          text[row][col] = gtk_entry_buffer_get_text(buffer_text[row][col]);
          data->entry_text[row][col] = (gchar*)text[row][col];
      }
  }
}

void draw_input_grid(gpointer user_data) {
    GtkEntryBuffer *entry_buffer[5][5];
    const gchar *entry_text[5][5];
    GtkWidget *box, *grid, *label, *entry[5][5], *btn;
    struct udata *secondSc_data = user_data;

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(secondSc_data->window), box);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

    if (secondSc_data->player_id == 1) {
      label = gtk_label_new("Player 1");
      gtk_widget_set_name(label, "playerLabel");
    } else {
      label = gtk_label_new("Player 2");
      gtk_widget_set_name(label, "playerLabel");
    }

    gtk_box_append(GTK_BOX(box), label);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_box_append(GTK_BOX(box), grid);

    secondSc_data->box = box;

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            entry[row][col] = gtk_entry_new();
            entry_buffer[row][col] = gtk_entry_buffer_new(NULL, -1);
            gtk_entry_set_buffer(GTK_ENTRY(entry[row][col]), entry_buffer[row][col]);
            gtk_grid_attach(GTK_GRID(grid), entry[row][col], col + 1, row + 1, 1, 1);
        }
    }

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            secondSc_data->entry[row][col] = entry[row][col];
        }
    }

    btn = gtk_button_new_with_label("OK");
    gtk_grid_attach(GTK_GRID(grid), btn, 3, 6, 1, 1);
    if (secondSc_data->player_id == 1) {
      g_signal_connect(btn, "clicked", G_CALLBACK(player_one_generate), secondSc_data);
    } else if (secondSc_data->player_id == 2){
      g_signal_connect(btn, "clicked", G_CALLBACK(player_two_generate), secondSc_data);
    }

}
