#include "chat.h"

GtkWidget *find_child(GtkWidget *parent, const gchar *name)
{

    GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
    while ((children = g_list_next(children)) != NULL)
    {
        GtkWidget *widget = children->data;
        if (strcmp(gtk_widget_get_name(widget), "name_label") == 0)
        {
            return widget;
        }
    }
    return NULL;
}
