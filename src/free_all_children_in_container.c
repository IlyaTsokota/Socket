#include "chat.h"

void free_all_children_in_container(GtkWidget *container)
{
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(container));
    for (iter = children; iter != NULL; iter = g_list_next(iter))
    {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);
}
