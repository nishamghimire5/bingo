#include "functions.h"
#include "main.h"
#include <gtk/gtk.h>

void new_game(GtkWidget *widget, gpointer user_data) {
    struct udata *data = user_data;

    GtkWidget *win = data->window;

    //free(global_player_one_data);
    //free(global_player_two_data);
    first_screen(win);
}

void display_win_screen(gpointer user_data) {
    run_count_one = 0;
    run_count_two = 0;
    struct udata *data = user_data;
    gtk_widget_unrealize(data->box);
    GtkWidget *box;

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_window_set_child(GTK_WINDOW(data->window), box);

    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

    GtkWidget *label;

    if (data->player_id == 1) {
      label = gtk_label_new("Player 1 wins!");
      gtk_widget_set_name(label, "winLabel");
    } else {
      label = gtk_label_new("Player 2 wins!");
      gtk_widget_set_name(label, "winLabel");
    }

    GtkWidget *btn;

    btn = gtk_button_new_with_label("NEW GAME");
    g_signal_connect(btn, "clicked", G_CALLBACK(new_game), data);
    gtk_button_set_has_frame(GTK_BUTTON(btn), FALSE);
    gtk_widget_set_name(btn, "button");

    gtk_box_append(GTK_BOX(box), label);
    gtk_box_append(GTK_BOX(box), btn);
}

void check_win(gpointer user_data) {
  struct udata *data = user_data;
  if (!((g_strcmp0(data->label[0], "-") == 0) && (g_strcmp0(data->label[1], "-") == 0) && (g_strcmp0(data->label[2], "-") == 0) && (g_strcmp0(data->label[3], "-") == 0) && (g_strcmp0(data->label[4], "-") == 0))) {
    const gchar* s[5][5];
    static int row_status[5] = {0, 0, 0, 0, 0};
    static int col_status[5] = {0, 0, 0, 0, 0};
    static int diag_status[2] = {0, 0};

    if (run_count_one == 0) {
      for (int i = 0; i < 5; ++i) {
        row_status[i] = 0;
        col_status[i] = 0;
      }
      diag_status[0] = 0;
      diag_status[1] = 0;
    }

    for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 5; ++col) {
        s[row][col] = data->entry_text[row][col];
      }
    }

    for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 5; ++col) {
        if (col == 4) {
          if ((g_strcmp0(s[row][0], "X") == 0) && (g_strcmp0(s[row][1], "X") == 0) && (g_strcmp0(s[row][2], "X") == 0) && (g_strcmp0(s[row][3], "X") == 0) && (g_strcmp0(s[row][4], "X") == 0)) {
            if (row_status[row] != 1) {
              for (int i = 0; i < 5; ++i) {
                if ((g_strcmp0(data->label[i], "-") == 0)) {
                  continue;
                } else {
                  data->label[i] = "-";
                  run_count_one++;
                  if (i > 3) display_win_screen(data);
                  row_status[row] = 1;
                  break;
                }
              }
            }
          } else {
            generate_grid(global_player_two_data);
          }
        } else {
          continue;
        }

        if (col == 4) {
          if ((g_strcmp0(s[0][row], "X") == 0) && (g_strcmp0(s[1][row], "X") == 0) && (g_strcmp0(s[2][row], "X") == 0) && (g_strcmp0(s[3][row], "X") == 0) && (g_strcmp0(s[4][row], "X") == 0)) {
            if (col_status[row] != 1) {
              for (int i = 0; i < 5; ++i) {
                if ((g_strcmp0(data->label[i], "-") == 0)) {
                  continue;
                } else {
                  data->label[i] = "-";
                  run_count_one++;
                  if (i > 3) display_win_screen(data);
                  col_status[row] = 1;
                  break;
                }
              }
            }
          } else {
            generate_grid(global_player_two_data);
          }
        } else {
          continue;
        }
      }
    }

    if ((g_strcmp0(s[0][0], "X") == 0) && (g_strcmp0(s[1][1], "X") == 0) && (g_strcmp0(s[2][2], "X") == 0) && (g_strcmp0(s[3][3], "X") == 0) && (g_strcmp0(s[4][4], "X") == 0)) {
          if (diag_status[0] != 1) {
              for (int i = 0; i < 5; ++i) {
                  if ((g_strcmp0(data->label[i], "-") == 0)) {
                      continue;
                  } else {
                      data->label[i] = "-";
                      run_count_one++;
                      if (i > 3) display_win_screen(data);
                      diag_status[0] = 1;
                      break;
                  }
              }
          }
      } else {
        generate_grid(global_player_two_data);
      }
      if ((g_strcmp0(s[0][4], "X") == 0) && (g_strcmp0(s[1][3], "X") == 0) && (g_strcmp0(s[2][2], "X") == 0) && (g_strcmp0(s[3][1], "X") == 0) && (g_strcmp0(s[4][0], "X") == 0)) {
          if (diag_status[1] != 1) {
              for (int i = 0; i < 5; ++i) {
                  if ((g_strcmp0(data->label[i], "-") == 0)) {
                      continue;
                  } else {
                      data->label[i] = "-";
                      run_count_one++;
                      if (i > 3) display_win_screen(data);
                      diag_status[1] = 1;
                      break;
                  }
              }
          }
      } else {
        generate_grid(global_player_two_data);
      }
  } else {
    display_win_screen(data);
  }
}

void check_win_two(gpointer user_data) {
  struct udata *data = user_data;
  if (!((g_strcmp0(data->label[0], "-") == 0) && (g_strcmp0(data->label[1], "-") == 0) && (g_strcmp0(data->label[2], "-") == 0) && (g_strcmp0(data->label[3], "-") == 0) && (g_strcmp0(data->label[4], "-") == 0))) {
    const gchar* s[5][5];
    static int row_status[5] = {0, 0, 0, 0, 0};
    static int col_status[5] = {0, 0, 0, 0, 0};
    static int diag_status[2] = {0, 0};

    //g_print("got here 2\n");

    if (run_count_two == 0) {
      for (int i = 0; i < 5; ++i) {
        row_status[i] = 0;
        col_status[i] = 0;
      }
      diag_status[0] = 0;
      diag_status[1] = 0;
    }

    for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 5; ++col) {
        s[row][col] = data->entry_text[row][col];
      }
    }

    for (int row = 0; row < 5; ++row) {
      for (int col = 0; col < 5; ++col) {
        if (col == 4) {
          if ((g_strcmp0(s[row][0], "X") == 0) && (g_strcmp0(s[row][1], "X") == 0) && (g_strcmp0(s[row][2], "X") == 0) && (g_strcmp0(s[row][3], "X") == 0) && (g_strcmp0(s[row][4], "X") == 0)) {
            if (row_status[row] != 1) {
              for (int i = 0; i < 5; ++i) {
                if ((g_strcmp0(data->label[i], "-") == 0)) {
                  continue;
                } else {
                  data->label[i] = "-";
                  run_count_two++;
                  if (i > 3) display_win_screen(data);
                  row_status[row] = 1;
                  break;
                }
              }
            }
          } else {
            generate_grid(global_player_one_data);
          }
        } else {
          continue;
        }

        if (col == 4) {
          if ((g_strcmp0(s[0][row], "X") == 0) && (g_strcmp0(s[1][row], "X") == 0) && (g_strcmp0(s[2][row], "X") == 0) && (g_strcmp0(s[3][row], "X") == 0) && (g_strcmp0(s[4][row], "X") == 0)) {
            if (col_status[row] != 1) {
              for (int i = 0; i < 5; ++i) {
                if ((g_strcmp0(data->label[i], "-") == 0)) {
                  continue;
                } else {
                  data->label[i] = "-";
                  run_count_two++;
                  if (i > 3) display_win_screen(data);
                  col_status[row] = 1;
                  break;
                }
              }
            }
          } else {
            generate_grid(global_player_one_data);
          }
        } else {
          continue;
        }
      }
    }

    if ((g_strcmp0(s[0][0], "X") == 0) && (g_strcmp0(s[1][1], "X") == 0) && (g_strcmp0(s[2][2], "X") == 0) && (g_strcmp0(s[3][3], "X") == 0) && (g_strcmp0(s[4][4], "X") == 0)) {
          if (diag_status[0] != 1) {
              for (int i = 0; i < 5; ++i) {
                  if ((g_strcmp0(data->label[i], "-") == 0)) {
                      continue;
                  } else {
                      data->label[i] = "-";
                      run_count_two++;
                      if (i > 3) display_win_screen(data);
                      diag_status[0] = 1;
                      break;
                  }
              }
          }
      } else {
        generate_grid(global_player_one_data);
      }
      if ((g_strcmp0(s[0][4], "X") == 0) && (g_strcmp0(s[1][3], "X") == 0) && (g_strcmp0(s[2][2], "X") == 0) && (g_strcmp0(s[3][1], "X") == 0) && (g_strcmp0(s[4][0], "X") == 0)) {
          if (diag_status[1] != 1) {
              for (int i = 0; i < 5; ++i) {
                  if ((g_strcmp0(data->label[i], "-") == 0)) {
                      continue;
                  } else {
                      data->label[i] = "-";
                      run_count_two++;
                      if (i > 3) display_win_screen(data);
                      diag_status[1] = 1;
                      break;
                  }
              }
          }
      } else {
        generate_grid(global_player_one_data);
      }
  } else {
    display_win_screen(data);
  }
}
