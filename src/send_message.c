#include "chat.h"

gboolean send_message(GtkWidget *widget, GtkTextView *text_view)
{

    char *message = strdup(main_form.message);
    puts(message);
    char *num_f = strdup("13");
    char *arr[] = {chats_f.curr_chat, data.user_id, "0", "0", "0", message, NULL};

    char *json = write_to_json(num_f, arr);
    free(num_f);
    free(message);
    free(main_form.message);
    char *response = request_on_server(json);
    free(response);
    char *last_ms_id = get_last_mesage_id("messages.json");
    get_all_messages(data.user_id, last_ms_id);
    free(last_ms_id);
    gtk_widget_destroy(main_form.right_content);
    show_opened_chat(main_form.main_grid, chats_f.curr_chat);

    return false;
}
