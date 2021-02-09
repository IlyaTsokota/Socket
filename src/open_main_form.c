#include "chat.h"
void open_main_form(GtkWidget *window)
{
    init_do_once(true);
    init_interface();
    main_form.last_ms_id = get_last_mesage_id("messages.json");
    get_all_messages(data.user_id,  main_form.last_ms_id);
    free(main_form.last_ms_id);
    main_form.last_ms_id = get_last_mesage_id("messages.json");
    is_fullscreen(window);
    create_widget_messages();
    create_chat_widgets(data.user_id);
    //puts("want dead");

    GtkBuilder *builder = glade_file_to_interface("share/main.glade");
    main_form.app_form = GTK_WIDGET(gtk_builder_get_object(builder, "main_form"));

    main_form.main_grid = GTK_WIDGET(gtk_builder_get_object(builder, "main_grid"));
    GtkWidget *left_panel = GTK_WIDGET(gtk_builder_get_object(builder, "left_panel"));

    //memory leak
    left_panel_img_t *left_panel_img = malloc(sizeof(left_panel_img_t));
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
    main_form.top_panel_top_text = GTK_WIDGET(gtk_builder_get_object(builder, "chat_name_lable"));
    main_form.top_panel_bottom_text = GTK_WIDGET(gtk_builder_get_object(builder, "user_is_online_in_chat"));
    GtkWidget *box_contacts = GTK_WIDGET(gtk_builder_get_object(builder, "box_contacts"));
    
    //puts("I want to say pizdec");
    show_chats(main_form.main_grid);
    //puts("I want to say pizdec1");

    show_opened_chat(main_form.main_grid, chats_f.curr_chat);
  //puts("I want to say pizdec2");
    GtkWidget *arr[] = {box_contacts, main_form.app_form, left_panel, is_connection, con_img, top_panel, search_entry, main_form.top_panel_top_text, main_form.top_panel_bottom_text,
                        left_panel_img->contact, left_panel_img->chat, left_panel_img->setting, left_panel_img->lock, NULL};
    css_set(arr,  data.main_theme_path);

    edit_styles_for_widget(left_panel_img->chat, "* {background: #88c5ce;}");

    g_signal_connect(G_OBJECT(event_box_contact_view), "button-press-event", G_CALLBACK(open_contacts), left_panel_img);
    g_signal_connect(G_OBJECT(event_box_setting), "button-press-event", G_CALLBACK(open_setting), left_panel_img);
    g_signal_connect(G_OBJECT(event_box_chats), "button-press-event", G_CALLBACK(open_chats), left_panel_img);
    g_signal_connect(G_OBJECT(event_box_lock), "button-press-event", G_CALLBACK(block_app), main_form.app_form);
    
    gtk_container_add(GTK_CONTAINER(window), main_form.app_form);
    g_object_unref(builder);
    start_timer_in_other_thread();
}
