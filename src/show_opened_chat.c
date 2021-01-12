#include "chat.h"

void show_opened_chat(GtkWidget *main_grid, char *id)
{
    GtkBuilder *builder = glade_file_to_interface("share/opened_chat.glade");

    main_form.right_content = GTK_WIDGET(gtk_builder_get_object(builder, "grid_message")); // это грид который буду менять
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
    
    msg_t *msg_entry = (msg_t *)malloc(sizeof(msg_t));
    GtkWidget *message_size_body = GTK_WIDGET(gtk_builder_get_object(builder, "message_size_body"));
    msg_entry->text_view  = GTK_WIDGET(gtk_builder_get_object(builder, "message_input"));
    msg_entry->buffer  = gtk_text_view_get_buffer(GTK_TEXT_VIEW( msg_entry->text_view));
    msg_entry->container = GTK_WIDGET(gtk_builder_get_object(builder, "message_input_scroll"));
    // char *placeholder_msg = "Write a message...";
    g_signal_connect(G_OBJECT(msg_entry->buffer), "changed", G_CALLBACK(change_size_message_input), msg_entry);
    // g_signal_connect(G_OBJECT(message_input), "focus-in-event", G_CALLBACK(change_placeholder_msg_in_focus), placeholder_msg);
    // g_signal_connect(G_OBJECT(message_input), "focus-out-event", G_CALLBACK(change_placeholder_msg_out_focus), placeholder_msg);
    
    GtkWidget *emoji_container = GTK_WIDGET(gtk_builder_get_object(builder, "emoji_container"));
    GtkWidget *event_box_emoji = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_emoji"));
    GtkWidget *pin_container = GTK_WIDGET(gtk_builder_get_object(builder, "pin_container"));
    GtkWidget *event_box_pin = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_pin"));
    GtkWidget *send_container = GTK_WIDGET(gtk_builder_get_object(builder, "send_container"));
    GtkWidget *event_box_send = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_send"));
    GtkWidget *arr[] = {main_form.right_content,message_panel,messages_container,message_line,event_box_message,
    message_time,message_time,message_info,message_info,message_text,message_login,message_scroll,message_size_body,
      msg_entry->text_view ,msg_entry->container,emoji_container,event_box_emoji,pin_container,send_container, event_box_send, message,NULL};
    css_set(arr, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content, 1, 0, 1, 1);
    g_object_unref(builder);
}