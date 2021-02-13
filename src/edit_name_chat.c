#include "chat.h"

void edit_name_chat(GtkWidget *button){

    char *chat_name = (char *)gtk_entry_get_text(GTK_ENTRY( main_form.chat_name_input)); 
    char *num_f = strdup("29");
    char *arr[] = {chats_f.curr_chat, chat_name, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    request_to_server(json);
    free(json);
    int index = get_curr_chat_index();
    gtk_label_set_text(GTK_LABEL(chats_f.chat_items[index]->contact_name_lable), chat_name);
    set_chat_name_top();
    set_chat_name_in_info_chat();
}
