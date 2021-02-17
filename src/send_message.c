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
    puts("LOCK_prev");
    g_mutex_lock(&main_form.mutex_seding_msg);
    puts("LOCK");
    struct sockaddr_in client_addr;
    update_t *update = malloc(sizeof(update));
    update->socket = socket(AF_INET, SOCK_STREAM, 0);
    int port = 3762;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = INADDR_ANY; // inet_addr("159.224.0.212"); //inet_addr("178.165.30.151");
    client_addr.sin_port = htons(port);

    if (connect(update->socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0)
    {
        puts("Send message\n");
        char *message = get_text_of_textview(GTK_TEXT_VIEW(text_view));
        char *num_f = strdup("13");
        char *arr[] = {chats_f.curr_chat, data.user_id, "0", "0", "0", message, NULL};
        char *json = write_to_json(num_f, arr);
        free(num_f);
        char *response = request_on_server(update->socket, json);
        refresh_chat(update);
        clear_text__buffer(GTK_TEXT_VIEW(text_view));
        g_timeout_add(50, change_insert_to_message, main_form.message_scroll);
        free(json);
        free(response);
    }
    else
    {

        puts("Data sent faild!\n");
    }

    close(update->socket);
    free(update);
    puts("UNLOCK_prev");
    g_mutex_unlock(&main_form.mutex_seding_msg);
    puts("UNLOCK");

    // g_thread_exit(NULL);
    // g_mutex_lock(&main_form.mutex_seding_msg);
    //puts("Lock");

    return NULL;
}
