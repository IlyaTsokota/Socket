#include "chat.h"
void open_main_form(GtkWidget *window)
{
    is_fullscreen(window);
    GtkBuilder *builder = glade_file_to_interface("share/main.glade");
    GtkWidget *main_forma = GTK_WIDGET(gtk_builder_get_object(builder, "main_form"));

    main_form.main_grid = GTK_WIDGET(gtk_builder_get_object(builder, "main_grid"));
    GtkWidget *left_panel = GTK_WIDGET(gtk_builder_get_object(builder, "left_panel"));

    //memory leak
    left_panel_img_t *left_panel_img =  malloc(sizeof(left_panel_img_t));
    GtkWidget *event_box_lock = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_lock"));
    left_panel_img->lock = GTK_WIDGET(gtk_builder_get_object(builder, "lock_img"));

    GtkWidget *event_box_chats = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_chats"));
    left_panel_img->chat = GTK_WIDGET(gtk_builder_get_object(builder, "chats_img"));
    
    GtkWidget *event_box_contact_view = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_contact_view"));
    left_panel_img->contact = GTK_WIDGET(gtk_builder_get_object(builder, "contact_view_img"));

    GtkWidget *event_box_setting = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_setting"));
    left_panel_img->setting = GTK_WIDGET(gtk_builder_get_object(builder, "setting_img"));

    GtkWidget *is_connection = GTK_WIDGET(gtk_builder_get_object(builder, "is_connection"));
    GtkWidget *con_img = GTK_WIDGET(gtk_builder_get_object(builder, "con_img"));

    GtkWidget *event_box_profile = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_profile"));
    GtkWidget *profile_img = GTK_WIDGET(gtk_builder_get_object(builder, "profile_img"));

    GtkWidget *top_panel = GTK_WIDGET(gtk_builder_get_object(builder, "top_panel"));
    GtkWidget *search_entry = GTK_WIDGET(gtk_builder_get_object(builder, "search_entry"));
    GtkWidget *chat_name_lable = GTK_WIDGET(gtk_builder_get_object(builder, "chat_name_lable"));
    GtkWidget *user_is_online_in_chat = GTK_WIDGET(gtk_builder_get_object(builder, "user_is_online_in_chat"));
    GtkWidget *box_contacts = GTK_WIDGET(gtk_builder_get_object(builder, "box_contacts"));
    show_chats(main_form.main_grid);
    show_opened_chat(main_form.main_grid, "1");
    GtkWidget *arr[] = {box_contacts, main_forma,  left_panel, is_connection, con_img, top_panel, search_entry, chat_name_lable, user_is_online_in_chat,
    left_panel_img->contact, left_panel_img->chat , left_panel_img->setting , left_panel_img->lock ,NULL};
    css_set(arr, "share/resources/css/main.css");

    edit_styles_for_widget(left_panel_img->chat, "* {background: #fff;}");

    g_signal_connect(G_OBJECT(event_box_contact_view), "button-press-event", G_CALLBACK(open_contacts), left_panel_img);
    g_signal_connect(G_OBJECT(event_box_setting), "button-press-event", G_CALLBACK(open_setting), left_panel_img);
    g_signal_connect(G_OBJECT(event_box_chats), "button-press-event", G_CALLBACK(open_chats), left_panel_img);
    g_signal_connect(G_OBJECT(event_box_lock), "button-press-event", G_CALLBACK(open_setting), left_panel_img);

    gtk_container_add(GTK_CONTAINER(window), main_forma);
    g_object_unref(builder);
}
