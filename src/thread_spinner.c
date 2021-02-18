#include "chat.h"

void *start_spinner(void *cur_g)
{
    cur_grid_t *current = (cur_grid_t *)cur_g;
    // pthread_detach(pthread_self());
    gtk_widget_set_opacity((GtkWidget *)current->btn, 0);
    gtk_widget_set_margin_top((GtkWidget *)current->btn, 20);
    gtk_spinner_start(GTK_SPINNER(current->spinner));
    gtk_widget_set_size_request(current->spinner, 65, 35);
    gtk_grid_attach(GTK_GRID(current->btn_container), current->spinner, 0, 1, 1, 1);
    pthread_exit(NULL);
}

void *auth_check_f(void *auth_s)
{
    auth_check_t *auth = (auth_check_t *)auth_s;
    if (is_autorization_user(auth->login, auth->password))
    {
        gtk_widget_destroy(auth->current_grid->spinner);
        autorization.login_text = g_locale_to_utf8(auth->login, strlen(auth->login), NULL, NULL, NULL);
        gtk_widget_destroy(auth->current_grid->grid);
        open_form_pin(data.win, false);
    }
    else
    {
        gtk_widget_destroy(auth->current_grid->spinner);
        gtk_widget_set_opacity(auth->current_grid->btn, 1);
        gtk_widget_set_margin_top(auth->current_grid->btn, 50);
        gtk_label_set_text(GTK_LABEL(autorization.fail_auth), "Invalid login or password!");
        valid_entry_border_color(&autorization.login);
        valid_entry_border_color(&autorization.password);
    }
    pthread_exit(NULL);
}
// void fun()
// {
//     //printf("This line may be printed"
//            " before thread terminates\n");

//     // The following line terminates
//     // the thread manually   gtk_widget_set_opacity (cur_grid->btn, 0);
//     //

//     // Compare the two threads created
//     if(pthread_equal(ptid, pthread_self())
//         //printf("Threads are equal\n");
//     else
//         //printf("Threads are not equal\n");

//     // Waiting for the created thread to terminate
//     pthread_join(ptid, NULL);

//     pthread_exit(NULL);
// }
