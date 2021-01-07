#include "chat.h"

void is_valid_message_to_entry(bool (*is_success)(int, int*, char*), char *value, int *minSize, GtkWidget **label_fail, GtkWidget **entry, char *message, int *flag){
    GtkWidget *widget = *entry;
    if (strlen(value) == 0)
    {
        gtk_label_set_text(GTK_LABEL(*label_fail), "The field can't be empty");
        valid_entry_border_color(&widget);
    }
    else if (!is_success(strlen(value), minSize, value))
    {
        gtk_label_set_text(GTK_LABEL(*label_fail), message);
    }

    else
    {
        gtk_label_set_text(GTK_LABEL(*label_fail), "");
       (*flag)++;
    }
}
