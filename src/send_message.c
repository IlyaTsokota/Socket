#include "chat.h"

gboolean send_message(GtkWidget *widget, GdkEventButton *event, GtkTextView *text_view)
{
    char *message = get_text_of_textview(text_view);
    clear_text__buffer(text_view);
    puts(message);
    char *num_f = strdup("13");
    char *arr[] = {chats_f.curr_chat, data.user_id, "0", "0", "0", message, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(json);
    free(response);
    char *last_ms_id = get_last_mesage_id("messages.json");
    get_all_messages(data.user_id, last_ms_id);
    free(last_ms_id);
    gtk_widget_destroy(main_form.left_content);
    show_chats(main_form.main_grid);
    message_arr *message_last = get_messages_from_file("messages.json", chats_f.curr_chat);
    create_one_messages(*message_last->length, message_last->messages[*message_last->length - 1], main_form.message_line);
    free_messages(message_last);
    gtk_widget_show_all(main_form.message_line);
    g_timeout_add(50, change_insert_to_message, main_form.message_scroll);

    // show_opened_chat(main_form.main_grid, chats_f.curr_chat);
   
    return false;
}
