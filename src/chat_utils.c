#include "chat.h"

void set_chat_name_in_info_chat()
{
    char *chat_name_text = (char *)gtk_label_get_text(GTK_LABEL(main_form.top_panel_top_text));
    gtk_entry_set_text(GTK_ENTRY(main_form.chat_name_input), chat_name_text);
    gtk_label_set_text(GTK_LABEL(main_form.chat_name_title), chat_name_text);
}

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
                        nameLable, select_img, delete_chat, main_form.chat_name_title, main_form.chat_name_input, NULL};

    css_set(arr, data.main_theme_path);
    g_signal_connect(G_OBJECT(main_form.chat_name_input), "changed", G_CALLBACK(change_event_login_or_password), minSize);

    g_signal_connect(G_OBJECT(apply_btn), "clicked", G_CALLBACK(edit_name_chat), NULL);
    g_signal_connect(G_OBJECT(add_participants), "clicked", G_CALLBACK(open_add_participant), NULL);
    g_signal_connect(G_OBJECT(delete_participants), "clicked", G_CALLBACK(open_remove_participant), NULL);

    gtk_grid_attach(GTK_GRID(main_form.right_content[10]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[10], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[10]);

    g_object_unref(builder);
}

gboolean open_add_participant(GtkWidget *widget, GdkEventButton *event)
{
    main_form.is_allow_access_next_panel = true;
    main_form.current_panel_id = -1;
    hide_gtk_widgets(main_form.right_content);
    show_add_participant(main_form.main_grid);
    gtk_widget_show_all(main_form.right_content[11]);
    return false;
}

void show_add_participant(GtkWidget *main_grid)
{
    if (!do_once.bshow_add_participant)
        return;
    do_once.bshow_add_participant = false;

    GtkBuilder *builder = glade_file_to_interface("share/add_participant.glade");
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *loginLable = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    GtkWidget *login_edit = GTK_WIDGET(gtk_builder_get_object(builder, "login_edit"));
    data_input_t *info = malloc(sizeof(data_input_t));
    info->fail_lable = GTK_WIDGET(gtk_builder_get_object(builder, "fail_login"));

    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    info->input = create_input(builder, "loginInput", maxSize);

    GtkWidget *add_participants = GTK_WIDGET(gtk_builder_get_object(builder, "add_participants"));
    GtkWidget *back = GTK_WIDGET(gtk_builder_get_object(builder, "back"));
    g_signal_connect(G_OBJECT( info->input ), "changed", G_CALLBACK(change_event_login_or_password), minSize);
    g_signal_connect(G_OBJECT(back), "button-press-event", G_CALLBACK(open_chat_info), NULL);

    GtkWidget *arr[] = {main_form.right_content[11], child, setting_form, back, add_participants, info->input,
                        loginLable, login_edit, info->fail_lable, NULL};
    css_set(arr, data.main_theme_path);

    g_signal_connect(G_OBJECT(add_participants), "clicked", G_CALLBACK(add_participant), info);

    gtk_grid_attach(GTK_GRID(main_form.right_content[11]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[11], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[11]);

    g_object_unref(builder);
}

void add_participant(GtkWidget *button, data_input_t *info)
{
        //g_mutex_lock(&main_form.mutex);

    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(info->input));
    int flag = 0;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    is_valid_message_to_entry(is_login_or_password, login, minSize, &info->fail_lable, &info->input, "The field may containt only latin or numerals", &flag);
    free(minSize);
    if (flag == 1)
    {
        // на рефакторинг
        char *num_f = strdup("12");
        char *arr[] = {login, chats_f.curr_chat, NULL};
        char *json = write_to_json(num_f, arr);
        free(num_f);
        if(request_to_server(json)){
            edit_styles_for_widget(info->fail_lable, "* {color: green;}");
            gtk_label_set_text(GTK_LABEL(info->fail_lable), "");
        } else {
            gtk_label_set_text(GTK_LABEL(info->fail_lable), "User already exist in this chat");
        }
        free(json);
       
    }
        //g_mutex_unlock(&main_form.mutex);

}

gboolean open_remove_participant(GtkWidget *widget, GdkEventButton *event)
{
    main_form.is_allow_access_next_panel = true;
    main_form.current_panel_id = -1;
    hide_gtk_widgets(main_form.right_content);
    show_remove_participant(main_form.main_grid);
    gtk_widget_show_all(main_form.right_content[12]);
    return false;
}

void show_remove_participant(GtkWidget *main_grid)
{
    if (!do_once.bshow_remove_participant)
        return;
    do_once.bshow_remove_participant = false;

    GtkBuilder *builder = glade_file_to_interface("share/remove_participant.glade");
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *loginLable = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    GtkWidget *login_edit = GTK_WIDGET(gtk_builder_get_object(builder, "login_edit"));
    GtkWidget *fail_login = GTK_WIDGET(gtk_builder_get_object(builder, "fail_login"));

    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 1;
    GtkWidget *loginInput = create_input(builder, "loginInput", maxSize);

    GtkWidget *remove_participants = GTK_WIDGET(gtk_builder_get_object(builder, "add_participants"));
    GtkWidget *back = GTK_WIDGET(gtk_builder_get_object(builder, "back"));
    g_signal_connect(G_OBJECT(loginInput), "changed", G_CALLBACK(change_event_login_or_password), minSize);
    g_signal_connect(G_OBJECT(back), "button-press-event", G_CALLBACK(open_chat_info), NULL);

    GtkWidget *arr[] = {main_form.right_content[12], child, setting_form, back, remove_participants, loginInput,
                        loginLable, login_edit, fail_login, NULL};
    css_set(arr, data.main_theme_path);

    // g_signal_connect(G_OBJECT(add_participants), "clicked", G_CALLBACK(open_add_participant), NULL);

    gtk_grid_attach(GTK_GRID(main_form.right_content[12]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[12], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[12]);

    g_object_unref(builder);
}

gboolean open_add_contact(GtkWidget *widget, GdkEventButton *event)
{
    main_form.is_allow_access_next_panel = true;
    main_form.current_panel_id = -1;
    hide_gtk_widgets(main_form.right_content);
    show_add_contact(main_form.main_grid);
    gtk_widget_show_all(main_form.right_content[13]);
    return false;
}

void show_add_contact(GtkWidget *main_grid)
{
    if (!do_once.bshow_add_contact)
        return;
    do_once.bshow_add_contact = false;

    GtkBuilder *builder = glade_file_to_interface("share/add_contact.glade");
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *loginLable = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    GtkWidget *login_edit = GTK_WIDGET(gtk_builder_get_object(builder, "login_edit"));
     data_input_t *info = malloc(sizeof(data_input_t));
    info->fail_lable = GTK_WIDGET(gtk_builder_get_object(builder, "fail_login"));

    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    info->input = create_input(builder, "loginInput", maxSize);

    GtkWidget *add_cont= GTK_WIDGET(gtk_builder_get_object(builder, "add_participants"));
    g_signal_connect(G_OBJECT(info->input), "changed", G_CALLBACK(change_event_login_or_password), minSize);

    GtkWidget *arr[] = {main_form.right_content[13], child, setting_form, add_cont, info->input,
                        loginLable, login_edit, info->fail_lable, NULL};
    css_set(arr, data.main_theme_path);

    g_signal_connect(G_OBJECT(add_cont), "clicked", G_CALLBACK(add_contact), NULL);

    gtk_grid_attach(GTK_GRID(main_form.right_content[13]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[13], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[13]);

    g_object_unref(builder);
}


void add_contact(GtkWidget *button, data_input_t *info)
{
    //g_mutex_lock(&main_form.mutex);
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(info->input));
    int flag = 0;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    is_valid_message_to_entry(is_login_or_password, login, minSize, &info->fail_lable, &info->input, "The field may containt only latin or numerals", &flag);
    free(minSize);
    if (flag == 1)
    {
        char *num_f = strdup("29");
        char *arr[] = {chats_f.curr_chat, login, NULL};
        char *json = write_to_json(num_f, arr);
        free(num_f);
        request_to_server(json);
        free(json);
       
    }
        //g_mutex_unlock(&main_form.mutex);

}
