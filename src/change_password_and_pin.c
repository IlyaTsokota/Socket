#include "chat.h"

gboolean open_change_password(GtkWidget *widget, GdkEventButton *event)
{
     // = true;
     // = -1;
    hide_gtk_widgets(main_form.right_content);
    show_change_password(main_form.main_grid);
    gtk_widget_show_all(main_form.right_content[14]);
    return false;
}

void show_change_password(GtkWidget *main_grid)
{
    if (!do_once.bshow_change_password)
        return;
    do_once.bshow_change_password = false;

    GtkBuilder *builder = glade_file_to_interface(localization_s.change_password);
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

    GtkWidget *arr[] = {main_form.right_content[14], child, setting_form, add_cont, info->input,
                        loginLable, login_edit, info->fail_lable, NULL};
    css_set(arr, data.main_theme_path);

    g_signal_connect(G_OBJECT(add_cont), "clicked", G_CALLBACK(change_password), info);

    gtk_grid_attach(GTK_GRID(main_form.right_content[14]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[14], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[14]);

    g_object_unref(builder);
}

void change_password(GtkWidget *button, data_input_t *info)
{
    //g_mutex_lock(&main_form.mutex);
    //g_mutex_lock(&main_form.mutex);
    char *password = (char *)gtk_entry_get_text(GTK_ENTRY(info->input));
    int flag = 0;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    is_valid_message_to_entry(is_login_or_password, password, minSize, &info->fail_lable, &info->input, "The field may containt only latin or numerals", &flag);
    free(minSize);
    if (flag == 1)
    {
        char *num_f = strdup("27");
        char *arr[] = {data.user_id, password, NULL};
        char *json = write_to_json(num_f, arr);
        free(num_f);
        if (request_to_server(json))
        {
            edit_styles_for_widget(info->fail_lable, "* {color: green;}");
            gtk_label_set_text(GTK_LABEL(info->fail_lable), "Successfully");
        }
        else
        {
            edit_styles_for_widget(info->fail_lable, "* {color: red;}");
            gtk_label_set_text(GTK_LABEL(info->fail_lable), "Fail");
        }
        free(json);
    }
    //g_mutex_unlock(&main_form.mutex);
}

gboolean open_change_pin(GtkWidget *widget, GdkEventButton *event)
{
     // = true;
     // = -1;
    hide_gtk_widgets(main_form.right_content);
    show_change_pin(main_form.main_grid);
    gtk_widget_show_all(main_form.right_content[15]);
    return false;
}

void show_change_pin(GtkWidget *main_grid)
{
    if (!do_once.bshow_change_pin)
        return;
    do_once.bshow_change_pin = false;

    GtkBuilder *builder = glade_file_to_interface(localization_s.change_pin);
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *loginLable = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    GtkWidget *login_edit = GTK_WIDGET(gtk_builder_get_object(builder, "login_edit"));
    data_input_t *info = malloc(sizeof(data_input_t));
    info->fail_lable = GTK_WIDGET(gtk_builder_get_object(builder, "fail_login"));

    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 4;
    info->input = create_input(builder, "loginInput", maxSize);

    GtkWidget *add_cont = GTK_WIDGET(gtk_builder_get_object(builder, "add_participants"));
    g_signal_connect(G_OBJECT(info->input), "changed", G_CALLBACK(change_event_pin_on_pin_form), maxSize);

    GtkWidget *arr[] = {main_form.right_content[15], child, setting_form, add_cont, info->input,
                        loginLable, login_edit, info->fail_lable, NULL};
    css_set(arr, data.main_theme_path);

    g_signal_connect(G_OBJECT(add_cont), "clicked", G_CALLBACK(change_pin), info);

    gtk_grid_attach(GTK_GRID(main_form.right_content[15]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[15], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[15]);

    g_object_unref(builder);
}

void change_pin(GtkWidget *button, data_input_t *info)
{
    //g_mutex_lock(&main_form.mutex);
    char *password = (char *)gtk_entry_get_text(GTK_ENTRY(info->input));
    int flag = 0;
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    is_valid_message_to_entry(is_pin, password, minSize, &info->fail_lable, &info->input, "The field may containt only numerals", &flag);
    free(minSize);
    if (flag == 1)
    {
        char *num_f = strdup("38");
        char *arr1[] = {data.user_id, password, NULL};
        char *json = write_to_json(num_f, arr1);
        free(num_f);
        if (!request_to_server(json))
        {
            free(json);
            num_f = strdup("28");
            char *arr[] = {data.user_id, password, NULL};
            json = write_to_json(num_f, arr);
            free(num_f);
            if (request_to_server(json))
            {
                edit_styles_for_widget(info->fail_lable, "* {color: green;}");
                gtk_label_set_text(GTK_LABEL(info->fail_lable), "Successfully");
            }
            else
            {
                edit_styles_for_widget(info->fail_lable, "* {color: red;}");
                gtk_label_set_text(GTK_LABEL(info->fail_lable), "Fail");
            }
            free(json);
        }
        else
        {
            edit_styles_for_widget(info->fail_lable, "* {color: red;}");
            gtk_label_set_text(GTK_LABEL(info->fail_lable), "You can't use this pin");
        }
    }
    //g_mutex_unlock(&main_form.mutex);
}
