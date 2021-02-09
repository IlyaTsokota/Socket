#include "chat.h"

gboolean block_app(GtkWidget *widget, GdkEventButton *event, GtkWidget *form)
{
    g_main_loop_quit( main_form.loop );
    init_do_once(true);
    free_message_widgets(curr_chat.messages_g);
    
    puts("0");
    free_chat_widgets(chats_f.chat_items);
    
    puts("1");
    if (chats_f.curr_chat != NULL) {
    	free(chats_f.curr_chat);
    	chats_f.curr_chat = NULL;
    }
    
    puts("2");
    if (main_form.last_ms_id != NULL) {
    	free(main_form.last_ms_id);
    	main_form.last_ms_id = NULL;
    }
    puts("3");
    if (data.user_id != NULL) {
    	free(data.user_id);
    	data.user_id = NULL;
    }
    puts("4");
    if (data.user_login != NULL) {
    	free(data.user_login);
    	data.user_login = NULL;
    }
    
    puts("5");
    if (data.picture_name != NULL) {
    	free(data.picture_name);
    	data.picture_name = NULL;
    }
    puts("6");
    clear_interface();
    puts("7");
    if (form != NULL) {
    	gtk_widget_destroy(form);
   	form = NULL;
    }
    puts("8");
    remove("messages.json");
    puts("9");
    open_form_pin(data.win, false);
    puts("10");
    return false;
}
