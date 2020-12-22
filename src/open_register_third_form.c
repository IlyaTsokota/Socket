#include "chat.h"

void open_register_third_form(GtkWidget *button, GtkWidget *widget)
{
    char *password = (char *)gtk_entry_get_text(GTK_ENTRY(registration.password));
    char *pin = (char *)gtk_entry_get_text(GTK_ENTRY(registration.pin));
    int flag = 0;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    if (!is_login_or_password(strlen(password), minSize, password))
    {
        // label все хуево давай по новой
    }
    else
    {
        ++flag;
    }

    if (!is_pin(strlen(pin), minSize, pin))
    {
        // label все хуево давай по новой
    }
    else
    {
        ++flag;
    }

    if (flag == 2)
    {
        gtk_widget_destroy(widget);
        open_register_third(data.win);
    }
}
