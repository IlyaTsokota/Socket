#include "chat.h"

GtkBuilder *glade_file_to_interface(char *path_to_glade_file)
{
    GError *error = NULL;
    GtkBuilder *builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, path_to_glade_file, &error) == 0)
    {
         //g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        exit(0);
    }
    return builder;
}
