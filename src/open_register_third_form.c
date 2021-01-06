#include "chat.h"

void open_register_third_form(GtkWidget *button, GtkWidget *widget)
{
    char *password = (char *)gtk_entry_get_text(GTK_ENTRY(registration.password));
    char *pin = (char *)gtk_entry_get_text(GTK_ENTRY(registration.pin));
    int flag = 0;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;

    is_valid_message_to_entry(is_login_or_password, password, minSize, &registration.fail_password, &registration.password, "The field may containt only latin or numerals", &flag);
    is_valid_message_to_entry(is_pin, pin, minSize, &registration.fail_pin, &registration.pin, "The field may containt only numerals", &flag);
    free(minSize);
    if (flag == 2)
    {
        create_new_user(registration.login_text, registration.name_text, registration.surname_text, password, pin);
        gtk_widget_destroy(widget);
        open_register_third(data.win);
    }
}
