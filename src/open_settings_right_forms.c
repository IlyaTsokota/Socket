#include "chat.h"

gboolean open_edit_profile(GtkWidget *widget, GdkEventButton *event)
{
    
    set_active_setting_item(setting_elements.edit_profile_text, setting_elements.edit_profile_img,
                            "./share/resources/img/info_a.png", show_edit_profile, 8);
    return false;
}

void set_active_setting_item(GtkWidget *text, GtkWidget *img, char *path_img, void (*f)(GtkWidget *grid), int index)
{
    hide_gtk_widgets(main_form.right_content);
    clear_styles_from_setting_elements();
    edit_styles_for_widget(text, "* {color: #88c5ce;}");
    GdkPixbuf *active_img = gdk_pixbuf_new_from_file(path_img, NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(img), active_img);
    f(main_form.main_grid);
    gtk_widget_show_all(main_form.right_content[index]);
}

void show_edit_profile(GtkWidget *main_grid)
{
    if (!do_once.bshow_edit_profile)
        return;
    do_once.bshow_edit_profile = false;
    GtkBuilder *builder = glade_file_to_interface( localization_s.edit_profile);
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
    int *maxSizeQuote = (int *)malloc(sizeof(int));
    *maxSizeQuote = 50;
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));

    user_t *user = get_profile_info();

    GtkWidget *nameLable = GTK_WIDGET(gtk_builder_get_object(builder, "nameLable"));
    profile_s.name = create_input(builder, "nameInput", maxSize);
    gtk_entry_set_text(GTK_ENTRY(profile_s.name), user->u_name);
    g_signal_connect(G_OBJECT(profile_s.name), "changed", G_CALLBACK(change_event_entry_only_aplha), minSize);

    GtkWidget *surnameLable = GTK_WIDGET(gtk_builder_get_object(builder, "surnameLable"));
    profile_s.surname = create_input(builder, "surnameInput", maxSize);
    gtk_entry_set_text(GTK_ENTRY(profile_s.surname), user->u_surname);
    g_signal_connect(G_OBJECT(profile_s.surname), "changed", G_CALLBACK(change_event_entry_only_aplha), minSize);

    GtkWidget *quoteLable = GTK_WIDGET(gtk_builder_get_object(builder, "quoteLable"));
    profile_s.quote = create_input(builder, "quoteInput", maxSizeQuote);
    gtk_entry_set_text(GTK_ENTRY(profile_s.quote), user->u_status);
    g_signal_connect(G_OBJECT(profile_s.quote), "changed", G_CALLBACK(change_event_entry_only_aplha), minSize);

    GtkWidget *apply_btn = GTK_WIDGET(gtk_builder_get_object(builder, "apply_btn"));
    GtkWidget *delete_acc = GTK_WIDGET(gtk_builder_get_object(builder, "delete_acc"));
    GtkWidget *just = GTK_WIDGET(gtk_builder_get_object(builder, "just"));
    GtkWidget *curr_img = GTK_WIDGET(gtk_builder_get_object(builder, "curr_img"));
    GtkWidget *select_img = GTK_WIDGET(gtk_builder_get_object(builder, "select_img"));
    GtkWidget *login_edit = GTK_WIDGET(gtk_builder_get_object(builder, "login_edit"));
    free_user_s(user);
    GtkWidget *arr[] = {main_form.right_content[8], setting_form, nameLable, profile_s.name,
                        surnameLable, profile_s.surname, quoteLable, profile_s.quote, apply_btn, delete_acc, just, curr_img,
                        select_img, login_edit, NULL};

    g_signal_connect(G_OBJECT(apply_btn), "clicked", G_CALLBACK(update_profile), NULL);
    css_set(arr,  data.main_theme_path);
    gtk_grid_attach(GTK_GRID(main_form.right_content[8]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[8], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[8]);

    g_object_unref(builder);

    
}

gboolean open_language(GtkWidget *widget, GdkEventButton *event)
{

    set_active_setting_item(setting_elements.language_text, setting_elements.language_img,
                            "./share/resources/img/language-a.png", show_language, 7);
    return false;
}

void show_language(GtkWidget *main_grid)
{

        if (!do_once.bshow_language)
        return;
    do_once.bshow_language = false;
    GtkBuilder *builder = glade_file_to_interface( localization_s.language);

    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *languageLable = GTK_WIDGET(gtk_builder_get_object(builder, "languageLable"));
    GtkWidget *language_combobox = GTK_WIDGET(gtk_builder_get_object(builder, "language_combobox"));
    GtkWidget *arr[] = {main_form.right_content[7], setting_form, text_info, languageLable, language_combobox, NULL};
    css_set(arr,  data.main_theme_path);
    gtk_grid_attach(GTK_GRID(main_form.right_content[7]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[7], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[7]);

    g_object_unref(builder);
}

gboolean open_privacy(GtkWidget *widget, GdkEventButton *event)
{
    set_active_setting_item(setting_elements.privacy_text, setting_elements.privacy_img,
                            "./share/resources/img/shield-a.png", show_privacy, 6);
    return false;
}

void show_privacy(GtkWidget *main_grid)
{

    if (!do_once.bshow_privacy)
        return;
    do_once.bshow_privacy = false;
    GtkBuilder *builder = glade_file_to_interface( localization_s.privacy);
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *change_password = GTK_WIDGET(gtk_builder_get_object(builder, "change_password"));
    GtkWidget *change_pin = GTK_WIDGET(gtk_builder_get_object(builder, "change_pin"));
    GtkWidget *vpn_btn = GTK_WIDGET(gtk_builder_get_object(builder, "vpn_btn"));

    GtkWidget *arr[] = {main_form.right_content[6], setting_form, text_info, change_password, change_pin, vpn_btn, NULL};
    css_set(arr,  data.main_theme_path);
    gtk_grid_attach(GTK_GRID(main_form.right_content[6]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[6], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[6]);

    g_object_unref(builder);
}

gboolean open_double_bottom(GtkWidget *widget, GdkEventButton *event)
{
    set_active_setting_item(setting_elements.double_bottom_text, setting_elements.double_bottom_img,
                            "./share/resources/img/privacy-a.png", show_double_bottom, 5);
    return false;
}

void show_double_bottom(GtkWidget *main_grid)
{
    if (!do_once.bshow_double_bottom)
        return;
    do_once.bshow_double_bottom = false;
    GtkBuilder *builder = glade_file_to_interface( localization_s.double_bottom);
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *pinLable = GTK_WIDGET(gtk_builder_get_object(builder, "pinLable"));
    db_data * data_pin = malloc(sizeof(db_data));
    data_pin->fail_pin = GTK_WIDGET(gtk_builder_get_object(builder, "fail_pin"));

    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 4;
    data_pin->pin = create_input(builder, "pinInput", maxSize);
    g_signal_connect(G_OBJECT(data_pin->pin), "changed", G_CALLBACK(change_event_pin), maxSize);

    GtkWidget *create_db = GTK_WIDGET(gtk_builder_get_object(builder, "create_db"));
    g_signal_connect(G_OBJECT(create_db), "clicked", G_CALLBACK(create_db_acc), data_pin);
    //free(maxSize);
    GtkWidget *arr[] = {main_form.right_content[5], setting_form, data_pin->fail_pin, text_info, create_db,  pinLable, data_pin->pin, NULL};
    css_set(arr,  data.main_theme_path);
    gtk_grid_attach(GTK_GRID(main_form.right_content[5]), child, 0, 0, 1, 1);


    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[5], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[5]);

    g_object_unref(builder);
}

gboolean open_notification(GtkWidget *widget, GdkEventButton *event)
{
    set_active_setting_item(setting_elements.notifications_text, setting_elements.notifications_img,
                            "./share/resources/img/bell-a.png", show_notification, 4);
    return false;
}

void show_notification(GtkWidget *main_grid)
{
    if (!do_once.bshow_notification)
        return;
    do_once.bshow_notification = false;
    GtkBuilder *builder = glade_file_to_interface( localization_s.notifications);
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *notificationsLable = GTK_WIDGET(gtk_builder_get_object(builder, "notificationsLable"));
    GtkWidget *is_notification = GTK_WIDGET(gtk_builder_get_object(builder, "is_notification"));

    GtkWidget *arr[] = {main_form.right_content[4], setting_form, text_info, notificationsLable, is_notification, NULL};
    css_set(arr,  data.main_theme_path);
    gtk_grid_attach(GTK_GRID(main_form.right_content[4]), child, 0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[4], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[4]);

    g_object_unref(builder);
}

gboolean open_appereance(GtkWidget *widget, GdkEventButton *event)
{

    set_active_setting_item(setting_elements.theme_text, setting_elements.theme_img,
                            "./share/resources/img/theme-a.png", show_appereance, 3);
    return false;
}

void show_appereance(GtkWidget *main_grid)
{
    if (!do_once.bshow_appereance)
        return;
    do_once.bshow_appereance = false;
    GtkBuilder *builder = glade_file_to_interface( localization_s.appereance);
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *themeLable = GTK_WIDGET(gtk_builder_get_object(builder, "themeLable"));
    GtkWidget *theme = GTK_WIDGET(gtk_builder_get_object(builder, "theme")); 
    bool is_active = strcmp(data.theme, "Dark") != 0 ? true : false;    
    gtk_switch_set_active (GTK_SWITCH(theme), is_active);

    g_signal_connect(G_OBJECT(theme), "state-set", G_CALLBACK(switch_theme), NULL);

    GtkWidget *arr[] = {main_form.right_content[3], setting_form, text_info, themeLable, theme, NULL};
    css_set(arr,  data.main_theme_path);
    gtk_grid_attach(GTK_GRID(main_form.right_content[3]), child, 0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[3], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[3]);

    g_object_unref(builder);
}
