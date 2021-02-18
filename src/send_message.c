#include "chat.h"

gboolean send_message(GtkWidget *widget, GdkEventButton *event, GtkTextView *text_view)
{
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    GThread *thread = g_thread_new("send_message", sending, text_view);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), TRUE);

    return false;
}

void *sending(gpointer text_view)
{
    //puts("LOCK_prev");
    g_mutex_lock(&main_form.mutex_seding_msg);
    //puts("LOCK");
    struct sockaddr_in client_addr;
    update_t *update = malloc(sizeof(update));
    update->socket = socket(AF_INET, SOCK_STREAM, 0);
    int port = 3762;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY; // inet_addr("159.224.0.212"); //inet_addr("178.165.30.151");
    client_addr.sin_port = htons(port);

    if (connect(update->socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0)
    {
        //puts("Send message\n");
        char *message = get_text_of_textview(GTK_TEXT_VIEW(text_view));

        if (is_string_spaceless(message))
        {
            char *num_f;
            char *json;
            char *response;
            char *text = trim_white_space_unicode(message);
            if (main_form.msg_event == 0)
            {
                //sending
                num_f = strdup("13");
                char *arr[] = {chats_f.curr_chat, data.user_id, "0", "0", "0", text, NULL};
                json = write_to_json(num_f, arr);
                response = request_on_server(update->socket, json);
                free(response);

            }
            else if (main_form.msg_event == 1)
            {
                //edit
                num_f = strdup("33");
                char *arr[] = {main_form.curr_ms_id, text, NULL};
                json = write_to_json(num_f, arr);
                gtk_label_set_text(GTK_LABEL(main_form.cur_msg), text);
                int index = get_curr_msg_index(main_form.curr_ms_id);
                gtk_label_set_text(GTK_LABEL(curr_chat.messages_g[index]->edited), "[Edited]");
                gtk_widget_set_margin_bottom(curr_chat.messages_g[index]->edited, 10);
                gtk_widget_set_margin_end(curr_chat.messages_g[index]->edited, 10);
                request_to_server(json);
            }
            else if (main_form.msg_event == 2)
            {
                // reply
            }
            clear_text__buffer(GTK_TEXT_VIEW(text_view));
            free(json);
            free(num_f);
            edit_styles_for_widget(text_view, "* {border: none;}");
        }
        else
        {
            edit_styles_for_widget(text_view, "* {border-top: 2px solid red;border-bottom: 2px solid red;}");
        }
    }
    else
    {

        //puts("Data sent faild!\n");
    }
    main_form.msg_event = 0;
    close(update->socket);
    free(update);
    //puts("UNLOCK_prev");
    g_mutex_unlock(&main_form.mutex_seding_msg);

    //puts("UNLOCK");

    // g_thread_exit(NULL);
    // g_mutex_lock(&main_form.mutex_seding_msg);
    // //puts("Lock");

    return NULL;
}

void edit_message(GtkMenuItem *menuitem, GtkWidget *ms_info)
{
    main_form.msg_event = 1;
    clear_text__buffer(GTK_TEXT_VIEW(main_form.text_view));
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(main_form.text_view));
    char *text = (char *)gtk_label_get_text(GTK_LABEL(main_form.cur_msg));
    gtk_text_buffer_set_text(buffer, text, strlen(text));
    gtk_text_view_set_buffer(GTK_TEXT_VIEW(main_form.text_view), buffer);
}

bool is_string_spaceless(char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (!mx_isspace(str[i]))
        {
            return true;
        }
    }
    return false;
}