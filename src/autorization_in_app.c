#include "chat.h"
void autorization_in_app(GtkWidget *button, GtkWidget *widget)
{
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(autorization.login));
    char *password = (char *)gtk_entry_get_text(GTK_ENTRY(autorization.password));
    int flag = 0;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    is_valid_message_to_entry(is_login_or_password, login, minSize, &autorization.fail_login, &autorization.login, "The field may containt only latin or numerals", &flag);
    is_valid_message_to_entry(is_login_or_password, password, minSize, &autorization.fail_password, &autorization.password, "The field may containt only latin or numerals", &flag);
    free(minSize);
    if (flag == 2)
    {
        if (is_autorization_user(login, password))
        {
            // открывать окно с pincode
            g_print("вы авторизованы!");
        }
        else
        {
            gtk_label_set_text(GTK_LABEL(autorization.fail_auth), "Invalid login or password!");
            valid_entry_border_color(&autorization.login);
            valid_entry_border_color(&autorization.password);
        }
    }
}
