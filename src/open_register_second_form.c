#include "chat.h"

void open_register_second_form(GtkWidget *button, GtkWidget *widget)
{
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(reg_one.login));
    char *name = (char *)gtk_entry_get_text(GTK_ENTRY(reg_one.name));
    char *surname = (char *)gtk_entry_get_text(GTK_ENTRY(reg_one.surname));
    int flag = 0;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    if (!is_login_or_password(strlen(login), minSize, login))
    {
        // label все хуево давай по новой
    }
    else
    {
        ++flag;
    }

    if (!is_only_alpha(strlen(name), minSize, name))
    {
        // label все хуево давай по новой
    }
    else
    {
        ++flag;
    }

    if (!is_only_alpha(strlen(surname), minSize, surname))
    {
        // label все хуево давай по новой
    }
    else
    {
        ++flag;
    }

    if (flag == 3)
    {
        // добавляем в бд
        gtk_widget_destroy(widget);
        open_register_second(data.win);
    }
}
