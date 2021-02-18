#include "chat.h"

gboolean block_app(GtkWidget *widget, GdkEventButton *event, GtkWidget *form)
{
    g_main_loop_quit( main_form.loop_edit_msgs );
    g_thread_join(main_form.update_edit_msgs);
    g_main_loop_quit( main_form.loop_chat );
    g_thread_join(main_form.update_thread_chat);
    g_main_loop_quit( main_form.loop );
    g_thread_join(main_form.update_thread);
    init_do_once(true);
    free_message_widgets(curr_chat.messages_g);
    free_chat_widgets(chats_f.chat_items);
    free_contact_widgets(contacts_t.widgets);
    free_user_widgets(users_in_chat.users);

    if (chats_f.curr_chat != NULL) {
    	free(chats_f.curr_chat);
    	chats_f.curr_chat = NULL;
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
    free(main_form.last_ms_id);
    main_form.last_ms_id = NULL;
    open_form_pin(data.win, false);
    return false;
}
