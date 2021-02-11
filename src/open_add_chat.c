#include "chat.h"

gboolean open_add_chat(GtkWidget *widget, GdkEventButton *event)
{
    main_form.is_allow_access_next_panel = true;
    main_form.current_panel_id = -1;
    hide_gtk_widgets(main_form.right_content);
    show_add_chat(main_form.main_grid);
    gtk_widget_show_all(main_form.right_content[9]);
    return false;
}

void show_add_chat(GtkWidget *main_grid)
{
    if (!do_once.bshow_add_chat)
        return;
    do_once.bshow_add_chat = false;
    GtkBuilder *builder = glade_file_to_interface("share/add_chat.glade");
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *pinLable = GTK_WIDGET(gtk_builder_get_object(builder, "pinLable"));
    GtkWidget *fail_name = GTK_WIDGET(gtk_builder_get_object(builder, "fail_pin"));

    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 1;
    GtkWidget *chat_name = create_input(builder, "pinInput", maxSize);

    GtkWidget *add_chat = GTK_WIDGET(gtk_builder_get_object(builder, "add_chat"));
    GtkWidget *widgets[] = {chat_name, fail_name};
    //free(maxSize);
    GtkWidget *arr[] = {main_form.right_content[9], setting_form, fail_name, text_info, add_chat, pinLable, chat_name, NULL};

    css_set(arr, data.main_theme_path);
    g_signal_connect(G_OBJECT(chat_name), "changed", G_CALLBACK(change_event_login_or_password), minSize);
    g_signal_connect(G_OBJECT(add_chat), "clicked", G_CALLBACK(add_new_chat), chat_name);
    gtk_grid_attach(GTK_GRID(main_form.right_content[9]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[9], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[9]);

    g_object_unref(builder);
}

gboolean open_chat_info(GtkWidget *widget, GdkEventButton *event)
{
    main_form.is_allow_access_next_panel = true;
    main_form.current_panel_id = -1;
    hide_gtk_widgets(main_form.right_content);
    show_chat_info(main_form.main_grid);
    set_chat_name_in_info_chat();
    gtk_widget_show_all(main_form.right_content[10]);
    return false;
}

void show_chat_info(GtkWidget *main_grid)
{
    if (!do_once.bshow_chat_info)
        return;
    do_once.bshow_chat_info = false;
  
    
    GtkBuilder *builder = glade_file_to_interface("share/chat_info.glade");
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *nameLable = GTK_WIDGET(gtk_builder_get_object(builder, "nameLable"));
    main_form.chat_name_title = GTK_WIDGET(gtk_builder_get_object(builder, "login_edit"));
    GtkWidget *select_img = GTK_WIDGET(gtk_builder_get_object(builder, "select_img"));

    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 1;
    main_form.chat_name_input = create_input(builder, "nameInput", maxSize);

    GtkWidget *apply_btn = GTK_WIDGET(gtk_builder_get_object(builder, "apply_btn"));
    GtkWidget *add_participants = GTK_WIDGET(gtk_builder_get_object(builder, "add_participants"));
    GtkWidget *delete_participants = GTK_WIDGET(gtk_builder_get_object(builder, "delete_participants"));
    GtkWidget *delete_chat = GTK_WIDGET(gtk_builder_get_object(builder, "delete_chat"));
   set_chat_name_in_info_chat();

    //free(maxSize);
    GtkWidget *arr[] = {main_form.right_content[10], child, setting_form, apply_btn, add_participants, delete_participants,
                        nameLable,select_img,delete_chat,main_form.chat_name_title, main_form.chat_name_input, NULL};

    css_set(arr, data.main_theme_path);
    g_signal_connect(G_OBJECT(main_form.chat_name_input), "changed", G_CALLBACK(change_event_login_or_password), minSize);

    // g_signal_connect(G_OBJECT(add_chat), "clicked", G_CALLBACK(edit_name_chat), chat_name);
    gtk_grid_attach(GTK_GRID(main_form.right_content[10]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[10], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[10]);

    g_object_unref(builder);
}


void set_chat_name_in_info_chat(){
    char *chat_name_text = (char *)gtk_label_get_text(GTK_LABEL(main_form.top_panel_top_text));
    gtk_entry_set_text(GTK_ENTRY(main_form.chat_name_input), chat_name_text);
    gtk_label_set_text(GTK_LABEL( main_form.chat_name_title),chat_name_text);
}