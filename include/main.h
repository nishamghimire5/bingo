#include <gtk/gtk.h>
#include "functions.h"

struct udata {
    GtkWidget *window;
    GtkWidget *mainBox;
    GtkWidget *box;
    GtkWidget *entry[5][5];
    gchar *entry_text[5][5];
    GtkWidget *button[5][5];
    gchar *label[5];
    int player_id;
};

extern struct udata *global_player_one_data;
extern struct udata *global_player_two_data;
extern int run_count_one;
extern int run_count_two;
