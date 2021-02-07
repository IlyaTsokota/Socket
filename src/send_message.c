#include "chat.h"

gboolean send_message(GtkWidget *widget, GdkEventButton *event, GtkTextView *text_view)
{
    GThread *thread = g_thread_new("send_message", sending, text_view);
    
    return false;
}


void* sending(gpointer text_view)
{
    g_mutex_lock(&main_form.mutex);
    // g_mutex_lock(&main_form.mutex_seding_msg);
    puts("Lock");
    char *message = get_text_of_textview(GTK_TEXT_VIEW(text_view));
    clear_text__buffer(GTK_TEXT_VIEW(text_view));
    char *num_f = strdup("13");
    char *arr[] = {chats_f.curr_chat, data.user_id, "0", "0", "0", message, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);

    puts(json);
    char *response = request_on_server(json);
    puts(response);
    free(json);
    free(response);
    g_mutex_unlock(&main_form.mutex);
    puts("UnLock");
    refresh_chat();
    // g_mutex_unlock(&main_form.mutex_seding_msg);
    g_timeout_add(50, change_insert_to_message, main_form.message_scroll);

    g_thread_exit(NULL);
    return NULL;
}
