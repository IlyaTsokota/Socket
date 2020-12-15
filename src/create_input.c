#include "chat.h"

GtkWidget *create_input(GtkBuilder *builder, char *name_elem, int maxSize)
{
    GtkWidget *input = GTK_WIDGET(gtk_builder_get_object(builder, name_elem));
    gtk_entry_set_alignment(GTK_ENTRY(input), 0.5);
    gtk_entry_set_max_length(GTK_ENTRY(input), maxSize);
    return input;
}
