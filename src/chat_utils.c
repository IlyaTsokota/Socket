#include "chat.h"

void set_chat_name_in_info_chat()
{
    char *chat_name_text = (char *)gtk_label_get_text(GTK_LABEL(main_form.top_panel_top_text));
    gtk_entry_set_text(GTK_ENTRY(main_form.chat_name_input), chat_name_text);
    gtk_label_set_text(GTK_LABEL(main_form.chat_name_title), chat_name_text);
}

gboolean open_add_chat(GtkWidget *widget, GdkEventButton *event)
{
     // = true;
     // = -1;
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
    GtkBuilder *builder = glade_file_to_interface(localization_s.add_chat);
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
    
    char *num_f = strdup("32");
    char *arr[] = {chats_f.curr_chat, data.user_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    main_form.is_admin_by_chat = request_to_server(json);
    hide_gtk_widgets(main_form.right_content);
    show_chat_info(main_form.main_grid);
    set_chat_name_in_info_chat();
    if (main_form.is_admin_by_chat)
    {
        g_signal_handlers_disconnect_by_func(main_form.delete_chat, remove_chat, NULL);
        g_signal_handlers_disconnect_by_func(main_form.delete_chat, exit_from_chat, NULL);
        gtk_button_set_label(GTK_BUTTON(main_form.delete_chat), "Remove chat");
        g_signal_connect(G_OBJECT(main_form.delete_chat), "clicked", G_CALLBACK(remove_chat), NULL);
    }
    else
    {
        g_signal_handlers_disconnect_by_func(main_form.delete_chat, remove_chat, NULL);
        g_signal_handlers_disconnect_by_func(main_form.delete_chat, exit_from_chat, NULL);
        gtk_button_set_label(GTK_BUTTON(main_form.delete_chat), "Leave from chat");
        g_signal_connect(G_OBJECT(main_form.delete_chat), "clicked", G_CALLBACK(exit_from_chat), NULL);
    }

    gtk_widget_show_all(main_form.right_content[10]);
    return false;
}

void show_chat_info(GtkWidget *main_grid)
{
    if (!do_once.bshow_chat_info)
        return;
    do_once.bshow_chat_info = false;

    GtkBuilder *builder = glade_file_to_interface(localization_s.chat_info);
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *nameLable = GTK_WIDGET(gtk_builder_get_object(builder, "nameLable"));

    main_form.chat_name_title = GTK_WIDGET(gtk_builder_get_object(builder, "login_edit"));
    main_form.curr_chat_img = GTK_WIDGET(gtk_builder_get_object(builder, "curr_img"));
    
    GtkWidget *select_img = GTK_WIDGET(gtk_builder_get_object(builder, "select_img"));
    gtk_file_chooser_set_local_only(GTK_FILE_CHOOSER(select_img), false);
    GtkFileFilter *filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter, "*.jpeg");
    gtk_file_filter_add_pattern(filter, "*.jpg");
    gtk_file_filter_add_pattern(filter, "*.png");
    gtk_file_filter_add_pattern(filter, "*.webp");

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(select_img), filter);
    g_signal_connect(G_OBJECT(select_img), "selection-changed", G_CALLBACK(update_img_in_chat), main_form.curr_chat_img);

    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 1;
    main_form.chat_name_input = create_input(builder, "nameInput", maxSize);

    GtkWidget *apply_btn = GTK_WIDGET(gtk_builder_get_object(builder, "apply_btn"));
    GtkWidget *add_participants = GTK_WIDGET(gtk_builder_get_object(builder, "add_participants"));
    GtkWidget *delete_participants = GTK_WIDGET(gtk_builder_get_object(builder, "delete_participants"));
    main_form.delete_chat = GTK_WIDGET(gtk_builder_get_object(builder, "delete_chat"));
    set_chat_name_in_info_chat();

    //free(maxSize);
    GtkWidget *arr[] = {main_form.right_content[10], child, setting_form, apply_btn, add_participants, delete_participants,
                        nameLable, select_img, main_form.delete_chat, main_form.chat_name_title, main_form.chat_name_input, NULL};

    css_set(arr, data.main_theme_path);
    g_signal_connect(G_OBJECT(main_form.chat_name_input), "changed", G_CALLBACK(change_event_entry_only_aplha), minSize);

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

    GtkBuilder *builder = glade_file_to_interface(localization_s.add_participant);
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
    g_signal_connect(G_OBJECT(info->input), "changed", G_CALLBACK(change_event_login_or_password), minSize);
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
        if (request_to_server(json))
        {
            edit_styles_for_widget(info->fail_lable, "* {color: green;}");
            gtk_label_set_text(GTK_LABEL(info->fail_lable), "User added successfully");
        }
        else
        {
            gtk_label_set_text(GTK_LABEL(info->fail_lable), "User already exist in this chat");
        }
        free(json);
    }
    //g_mutex_unlock(&main_form.mutex);
}

gboolean open_remove_participant(GtkWidget *widget, GdkEventButton *event)
{
    hide_gtk_widgets(main_form.right_content);
    show_remove_participant(main_form.main_grid);
    refresh_users_by_chat();
    gtk_widget_show_all(main_form.right_content[12]);
    return false;
}

void refresh_users_by_chat()
{
    free_user_widgets(users_in_chat.users);
    user_curr_chat_t **users = take_users_by_chat(data.socket_desc);
    if (users != NULL)
    {
        for (size_t i = 0; users[i]; i++)
        {
            create_one_user_widget(i, users[i]);
        }
        free_user_curr_chat_t_s(users);

        for (size_t i = 0; users_in_chat.users[i]; i++)
        {
            gtk_grid_attach(GTK_GRID(main_form.users_container), users_in_chat.users[i]->users_item, 0, i, 1, 1);
        }
        gtk_widget_show_all(main_form.users_container);
    }
}

void show_remove_participant(GtkWidget *main_grid)
{
    if (!do_once.bshow_remove_participant)
        return;
    do_once.bshow_remove_participant = false;

    GtkBuilder *builder = glade_file_to_interface(localization_s.remove_participant);
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *login_edit = GTK_WIDGET(gtk_builder_get_object(builder, "login_edit"));
    GtkWidget *scroll_by_users = GTK_WIDGET(gtk_builder_get_object(builder, "scroll_by_users"));
    main_form.users_container = GTK_WIDGET(gtk_builder_get_object(builder, "users_container"));

    GtkWidget *back = GTK_WIDGET(gtk_builder_get_object(builder, "back"));
    g_signal_connect(G_OBJECT(back), "button-press-event", G_CALLBACK(open_chat_info), NULL);

    GtkWidget *arr[] = {main_form.right_content[12], child, setting_form, back, scroll_by_users,
                        login_edit, NULL};
    css_set(arr, data.main_theme_path);

    // g_signal_connect(G_OBJECT(add_participants), "clicked", G_CALLBACK(open_add_participant), NULL);

    gtk_grid_attach(GTK_GRID(main_form.right_content[12]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[12], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[12]);

    g_object_unref(builder);
}

gboolean open_add_contact(GtkWidget *widget, GdkEventButton *event)
{
     // = true;
     // = -1;
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

    GtkBuilder *builder = glade_file_to_interface(localization_s.add_contact);
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

    GtkWidget *add_cont = GTK_WIDGET(gtk_builder_get_object(builder, "add_participants"));
    g_signal_connect(G_OBJECT(info->input), "changed", G_CALLBACK(change_event_login_or_password), minSize);

    GtkWidget *arr[] = {main_form.right_content[13], child, setting_form, add_cont, info->input,
                        loginLable, login_edit, info->fail_lable, NULL};
    css_set(arr, data.main_theme_path);

    g_signal_connect(G_OBJECT(add_cont), "clicked", G_CALLBACK(add_contact), info);

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
        char *num_f = strdup("35");
        char *arr[] = {login, data.user_id, NULL};
        char *json = write_to_json(num_f, arr);
        free(num_f);
        char *request = request_on_server(data.socket_desc, json);
         //puts(request);
        free(json);
        if (strcmp(request, "1") == 0)
        {
            gtk_label_set_text(GTK_LABEL(info->fail_lable), "User already in contacts ");
        }
        else if (strcmp(request, "2") == 0)
        {
            gtk_label_set_text(GTK_LABEL(info->fail_lable), "User doesn't exist");
        }
        else
        {
            char *num_f = strdup("36");
            char *arr[] = {login, NULL};
            char *json = write_to_json(num_f, arr);
            free(num_f);
            char *response = request_on_server(data.socket_desc, json);
            free(json);
            contact_t **contacts = get_contacts(response);
            free(response);
            create_one_contact(contacts_t.size, contacts[0]);
            free_contacts_s(contacts);
            gtk_box_pack_start(GTK_BOX(main_form.box_contact), contacts_t.widgets[contacts_t.size - 1]->event_box_contact, false, true, 0);
            gtk_widget_show_all(main_form.box_contact);
            edit_styles_for_widget(info->fail_lable, "* {color: green;}");
            gtk_label_set_text(GTK_LABEL(info->fail_lable), "User added successfully to contacts");
        }
        free(request);
    }
    //g_mutex_unlock(&main_form.mutex);
}

gboolean remove_user_from_chat(GtkWidget *widget)
{
    char *num_f = strdup("31");
    char *user_id = (char *)gtk_widget_get_name(widget);
    char *arr[] = {user_id, chats_f.curr_chat, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    request_to_server(json);
    free(json);
    refresh_users_by_chat();

    return false;
}

gboolean remove_chat(GtkWidget *widget)
{
    char *num_f = strdup("10");
    char *arr[] = {chats_f.curr_chat, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    request_to_server(json);
    free(json);

    free_chat_widgets(chats_f.chat_items);
    create_chat_widgets(data.user_id, data.socket_desc);
    show_chats_widgets();
    show_right_panel_is_clear(main_form.main_grid);
    hide_gtk_widgets(main_form.right_content);
    gtk_widget_show_all(main_form.right_content[1]);
    // update_chats_after_delete();
    return false;
}

gboolean exit_from_chat(GtkWidget *widget)
{
    char *num_f = strdup("31");
    char *arr[] = {data.user_id, chats_f.curr_chat, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    request_to_server(json);
    free(json);
    free_chat_widgets(chats_f.chat_items);
    create_chat_widgets(data.user_id, data.socket_desc);
    show_chats_widgets();
    show_right_panel_is_clear(main_form.main_grid);
    hide_gtk_widgets(main_form.right_content);
    gtk_widget_show_all(main_form.right_content[1]);
    return false;
}

void update_chats_after_delete()
{
     //g_print("%d -- prev\n", chats_f.size);

    chat_item_t **temp_arr = malloc(sizeof(chat_item_t) * chats_f.size);
    temp_arr[chats_f.size - 1] = NULL;
    int j = 0;
    for (size_t i = 0; chats_f.chat_items[i]; i++)
    {
        char *curr_id = (char *)gtk_widget_get_name(chats_f.chat_items[i]->event_box_contact);
        if (strcmp(curr_id, chats_f.curr_chat) != 0)
        {
            temp_arr[j] = malloc(sizeof(chat_item_t));
            temp_arr[j] = chats_f.chat_items[i];
            j++;
        }
    }
     //puts("Fuck");
    free_chat_widgets(chats_f.chat_items);

    chats_f.size = j;
     //g_print("%d -- next\n", chats_f.size);
    chats_f.chat_items = malloc(sizeof(chat_item_t) * (chats_f.size + 1));
    chats_f.chat_items[chats_f.size] = NULL;

    for (size_t i = 0; i < chats_f.size; i++)
    {
        chats_f.chat_items[i] = malloc(sizeof(chat_item_t));
        chats_f.chat_items[i] = temp_arr[i];
    }
    for (size_t i = 0; i < chats_f.size; i++)
    {
        if (temp_arr[i] != NULL)
        {
            free(temp_arr[i]);
            temp_arr[i] = NULL;
        }
    }
    if (temp_arr != NULL)
    {
        free(temp_arr);
        temp_arr = NULL;
    }

    for (int i = 0; i < chats_f.size; i++)
    {
        gtk_grid_attach(GTK_GRID(main_form.chats_grid), chats_f.chat_items[i]->event_box_contact, 0, i, 1, 1);
    }
    gtk_widget_show_all(main_form.chats_grid);
}