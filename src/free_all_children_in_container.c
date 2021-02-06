#include "chat.h"

void free_all_children_in_container(GtkWidget *container)
{
    gpointer garb;


    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(container));
    for (iter = children; iter != NULL; iter = g_list_next(iter))
    {
        garb = g_object_ref(iter->data);
        gtk_container_remove (GTK_CONTAINER(container), (GTK_WIDGET(iter->data)));
        iter->data = GTK_WIDGET(garb);
    }
    g_list_free(children);
}
