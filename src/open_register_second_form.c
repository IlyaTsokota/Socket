#include "chat.h"

void open_register_second_form(GtkWidget *button, GtkWidget *widget)
{
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(registration.login));
    char *name = (char *)gtk_entry_get_text(GTK_ENTRY(registration.name));
    char *surname = (char *)gtk_entry_get_text(GTK_ENTRY(registration.surname));
    int flag = 0;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    is_valid_message_to_entry(is_login_or_password, login, minSize, &registration.fail_login, &registration.login, "The field may containt only latin or numerals", &flag);
    is_valid_message_to_entry(is_only_alpha, name, minSize, &registration.fail_name, &registration.name, "The field may containt only latin", &flag);
    is_valid_message_to_entry(is_only_alpha, surname, minSize, &registration.fail_surname, &registration.surname, "The field may containt only latin", &flag);
    free(minSize);
    if (flag == 3)
    {
        if (find_user_by_login(login))
        {
            valid_entry_border_color(&registration.login);
            gtk_label_set_text(GTK_LABEL(registration.fail_login), "This login already exists");
        }
        else
        {
            registration.login_text = g_locale_to_utf8(login, strlen(login), NULL, NULL, NULL);
            registration.name_text = g_locale_to_utf8(name, strlen(name), NULL, NULL, NULL);
            registration.surname_text = g_locale_to_utf8(surname, strlen(surname), NULL, NULL, NULL);
            gtk_widget_destroy(widget);
            open_register_second(data.win);
        }
    }
}
