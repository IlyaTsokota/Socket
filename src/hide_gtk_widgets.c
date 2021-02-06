#include "chat.h"

void hide_gtk_widgets(GtkWidget **widgets)
{
    for (int i = 0; widgets[i]; i++)
    {
        if (widgets[i] != NULL)
        {
            gtk_widget_hide(widgets[i]);
        }
    }
}
