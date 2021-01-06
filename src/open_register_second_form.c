#include "chat.h"

void open_register_second_form(GtkWidget *button, GtkWidget *widget)
{
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(registration.login));
    char *name = (char *)gtk_entry_get_text(GTK_ENTRY(registration.name));
    char *surname = (char *)gtk_entry_get_text(GTK_ENTRY(registration.surname));
    int flag = 0;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;

    is_valid_message_to_entry(login, minSize, &registration.fail_login, &registration.login ,"The field may containt only latin", &flag);
    
    if (flag == 1 && !find_user_by_login(login))
    {
        valid_entry_border_color(&registration.login);
        gtk_label_set_text(GTK_LABEL(registration.fail_login), "This login already exists");
        --flag;
    }
    
    is_valid_message_to_entry(name, minSize, &registration.fail_name, &registration.name ,"The field may containt only latin", &flag);
    is_valid_message_to_entry(surname, minSize, &registration.fail_surname, &registration.surname ,"The field may containt only latin", &flag);
    
    if (flag == 3)
    {
            registration.login_text = g_convert(login, -1, "CP1251", "UTF-8", NULL, NULL, NULL);
            registration.name_text = g_convert(name, -1, "CP1251", "UTF-8", NULL, NULL, NULL);
            registration.surname_text = g_convert(surname, -1, "CP1251", "UTF-8", NULL, NULL, NULL);
            gtk_widget_destroy(widget);
            open_register_second(data.win);
    }
}
