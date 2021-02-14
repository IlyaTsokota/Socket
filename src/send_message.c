#include "chat.h"

gboolean send_message(GtkWidget *widget, GdkEventButton *event, GtkTextView *text_view)
{
    GThread *thread = g_thread_new("send_message", sending, text_view);

    return false;
}

void *sending(gpointer text_view)
{
    g_mutex_lock(&main_form.mutex);
    struct sockaddr_in client_addr;
    update_t *update = malloc(sizeof(update));
    update->socket = socket(AF_INET, SOCK_STREAM, 0);
    int port = 3762;
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("159.224.0.212"); //inet_addr("178.165.30.151");
    client_addr.sin_port = htons(port);

    if (connect(update->socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) == 0)
    {
        puts("Send message\n");
        char *message = get_text_of_textview(GTK_TEXT_VIEW(text_view));
        char *num_f = strdup("13");
        char *arr[] = {chats_f.curr_chat, data.user_id, "0", "0", "0", message, NULL};
        char *json = write_to_json(num_f, arr);
        free(num_f);
        g_mutex_unlock(&main_form.mutex);

        char *response = request_on_server(update->socket, json);

        free(json);
        free(response);
        clear_text__buffer(GTK_TEXT_VIEW(text_view));

        refresh_chat(update);
        g_timeout_add(50, change_insert_to_message, main_form.message_scroll);
        g_thread_exit(NULL);
    }
    else
    {

        puts("Data sent faild!\n");
    }
    close(update->socket);
    free(update);
    // g_mutex_lock(&main_form.mutex_seding_msg);
    //puts("Lock");

    return NULL;
}
