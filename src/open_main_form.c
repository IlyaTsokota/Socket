#include "chat.h"
void open_main_form(GtkWidget *window)
{
    gtk_window_resize(GTK_WINDOW(window), 1300, 740);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
    
    GtkBuilder *builder = glade_file_to_interface("share/main.glade");
    GtkWidget *main_form = GTK_WIDGET(gtk_builder_get_object(builder, "main_form"));
    GtkWidget *left_panel = GTK_WIDGET(gtk_builder_get_object(builder, "left_panel"));

    GtkWidget *event_box_lock = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_lock"));
    GtkWidget *lock_img = GTK_WIDGET(gtk_builder_get_object(builder, "lock_img"));

    GtkWidget *event_box_setting = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_setting"));
    GtkWidget *setting_img = GTK_WIDGET(gtk_builder_get_object(builder, "setting_img"));

    GtkWidget *is_connection = GTK_WIDGET(gtk_builder_get_object(builder, "is_connection"));
    GtkWidget *con_img = GTK_WIDGET(gtk_builder_get_object(builder, "con_img"));

    GtkWidget *event_box_profile = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_profile"));
    GtkWidget *profile_img = GTK_WIDGET(gtk_builder_get_object(builder, "profile_img"));

    GtkWidget *top_panel = GTK_WIDGET(gtk_builder_get_object(builder, "top_panel"));
    GtkWidget *search_entry = GTK_WIDGET(gtk_builder_get_object(builder, "search_entry"));
    GtkWidget *chat_name_lable = GTK_WIDGET(gtk_builder_get_object(builder, "chat_name_lable"));
    GtkWidget *user_is_online_in_chat = GTK_WIDGET(gtk_builder_get_object(builder, "user_is_online_in_chat"));

    GtkWidget *box_contacts = GTK_WIDGET(gtk_builder_get_object(builder, "box_contacts"));
    GtkWidget *grid_contacts = GTK_WIDGET(gtk_builder_get_object(builder, "grid_contacts"));
    GtkWidget *contacts_panel = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_panel"));
    GtkWidget *contacts_container = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_container"));
    GtkWidget *event_box_contact = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_contact"));
    GtkWidget *contact_container = GTK_WIDGET(gtk_builder_get_object(builder, "contact_container"));
    GtkWidget *time_last_message = GTK_WIDGET(gtk_builder_get_object(builder, "time_last_message"));
    GtkWidget *login_last_message = GTK_WIDGET(gtk_builder_get_object(builder, "login_last_message"));
    GtkWidget *text_last_message = GTK_WIDGET(gtk_builder_get_object(builder, "text_last_message"));
    GtkWidget *contact_name_lable = GTK_WIDGET(gtk_builder_get_object(builder, "contact_name_lable"));
    GtkWidget *user_is_online = GTK_WIDGET(gtk_builder_get_object(builder, "user_is_online"));
    GtkWidget *contact_info = GTK_WIDGET(gtk_builder_get_object(builder, "contact_info"));
    GtkWidget *contact_last_msg = GTK_WIDGET(gtk_builder_get_object(builder, "contact_last_msg"));
    GtkWidget *contact_name_container = GTK_WIDGET(gtk_builder_get_object(builder, "contact_name_container"));
    GtkWidget *img_contact = GTK_WIDGET(gtk_builder_get_object(builder, "img_contact"));
    GtkWidget *contact_img_container = GTK_WIDGET(gtk_builder_get_object(builder, "contact_img_container"));

    GtkWidget *message_panel = GTK_WIDGET(gtk_builder_get_object(builder, "message_panel"));
    GtkWidget *messages_container = GTK_WIDGET(gtk_builder_get_object(builder, "messages_container"));
    GtkWidget *message_line = GTK_WIDGET(gtk_builder_get_object(builder, "message_line"));
    GtkWidget *event_box_message = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_message"));
    GtkWidget *message = GTK_WIDGET(gtk_builder_get_object(builder, "message"));
    GtkWidget *message_time = GTK_WIDGET(gtk_builder_get_object(builder, "message_time"));
    GtkWidget *message_info = GTK_WIDGET(gtk_builder_get_object(builder, "message_info"));

    GtkWidget *message_text = GTK_WIDGET(gtk_builder_get_object(builder, "message_text"));
    GtkWidget *message_login = GTK_WIDGET(gtk_builder_get_object(builder, "message_login"));
    GtkWidget *message_scroll = GTK_WIDGET(gtk_builder_get_object(builder, "message_scroll"));


    GtkWidget *message_size_body = GTK_WIDGET(gtk_builder_get_object(builder, "message_size_body"));
    GtkWidget *message_input = GTK_WIDGET(gtk_builder_get_object(builder, "message_input"));
    GtkTextBuffer *buffer_message_input = gtk_text_view_get_buffer (GTK_TEXT_VIEW(message_input));
    GtkWidget *message_input_scroll = GTK_WIDGET(gtk_builder_get_object(builder, "message_input_scroll"));
    
    g_signal_connect(G_OBJECT(buffer_message_input), "changed", G_CALLBACK(change_size_message_input), message_input_scroll);

    GtkWidget *pin_container = GTK_WIDGET(gtk_builder_get_object(builder, "pin_container"));
    GtkWidget *event_box_pin = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_pin"));
    GtkWidget *pin_img = GTK_WIDGET(gtk_builder_get_object(builder, "pin_img"));
    GtkWidget *send_container = GTK_WIDGET(gtk_builder_get_object(builder, "send_container"));
    GtkWidget *event_box_send = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_send"));
    GtkWidget *send_img = GTK_WIDGET(gtk_builder_get_object(builder, "send_img"));

   

    GtkWidget *arr[] = {message_info, message_input_scroll, contact_img_container, message_input, box_contacts, message_scroll, img_contact, contact_last_msg, contact_info,
                        grid_contacts, main_form, left_panel, event_box_lock, lock_img,
                        event_box_setting, setting_img, is_connection, con_img, event_box_profile,
                        profile_img, top_panel, search_entry, chat_name_lable, user_is_online_in_chat,
                        contacts_panel, contacts_container, event_box_contact, contact_container,
                        time_last_message, login_last_message, text_last_message, contact_name_lable, user_is_online, img_contact,
                        message_panel, contact_name_container, messages_container, message_line, event_box_message, message, message_time, message_text,
                        message_login, message_size_body, pin_container, event_box_pin, pin_img, send_container, event_box_send,
                        send_img, NULL};

    css_set(arr, "share/resources/css/main.css");
    gtk_container_add(GTK_CONTAINER(window), main_form);
    g_object_unref(builder);
}
