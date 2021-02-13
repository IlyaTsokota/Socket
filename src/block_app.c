#include "chat.h"

gboolean block_app(GtkWidget *widget, GdkEventButton *event, GtkWidget *form)
{
    g_main_loop_quit( main_form.loop );
    init_do_once(true);
    free_message_widgets(curr_chat.messages_g);
    free_chat_widgets(chats_f.chat_items);
    
    if (chats_f.curr_chat != NULL) {
    	free(chats_f.curr_chat);
    	chats_f.curr_chat = NULL;
    }
    if (main_form.last_ms_id != NULL) {
    	free(main_form.last_ms_id);
    	main_form.last_ms_id = NULL;
    }
    if (data.user_id != NULL) {
    	free(data.user_id);
    	data.user_id = NULL;
    }
    if (data.user_login != NULL) {
    	free(data.user_login);
    	data.user_login = NULL;
    }
    if (data.picture_name != NULL) {
    	free(data.picture_name);
    	data.picture_name = NULL;
    }
    clear_interface();
    if (form != NULL) {
    	gtk_widget_destroy(form);
   	form = NULL;
    }
    remove("messages.json");
    open_form_pin(data.win, false);
    return false;
}
