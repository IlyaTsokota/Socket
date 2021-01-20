#include "chat.h"
void autorization_in_app(GtkWidget *button, GtkWidget *grid)
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
        // pthread_t ptid; 
        // cur_grid->spinner = gtk_spinner_new();
        // pthread_create(&ptid, NULL, start_spinner, cur_grid); 
        // pthread_join(ptid, NULL); 
       
        if (is_autorization_user(login, password))
        {
            // gtk_widget_destroy(spinner);

            autorization.login_text = g_locale_to_utf8(login, strlen(login), NULL, NULL, NULL);
            char* settings = mx_file_to_str("settings.json");
            settings_t *settings_field = get_settings(settings);
            create_settings_json(autorization.login_text, settings_field->theme, settings_field->language, "TRUE");
            free_settings(settings_field); 
            gtk_widget_destroy(grid);
            open_form_pin(data.win, false);
        }
        else
        {
            // gtk_widget_destroy(spinner);
            // gtk_widget_set_opacity (cur_grid->btn, 1);
            // gtk_widget_set_margin_top(cur_grid->btn, 50); 
            gtk_label_set_text(GTK_LABEL(autorization.fail_auth), "Invalid login or password!");
            valid_entry_border_color(&autorization.login);
            valid_entry_border_color(&autorization.password);
        }
         
    }
}
