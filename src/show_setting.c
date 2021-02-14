#include "chat.h"

void show_setting(GtkWidget *main_grid)
{
    gtk_label_set_text(GTK_LABEL(main_form.top_panel_top_text), "Settings");
    gtk_label_set_text(GTK_LABEL(main_form.top_panel_bottom_text), "Some settings can affect your life");
    if (!do_once.bshow_setting)
        return;
    do_once.bshow_setting = false;


    GtkBuilder *builder = glade_file_to_interface(localization_s.left_panel_setting);
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_info"));
    GtkWidget *setting_info_panel = GTK_WIDGET(gtk_builder_get_object(builder, "setting_info_panel"));

    GtkWidget *info_container = GTK_WIDGET(gtk_builder_get_object(builder, "info_container"));
    GtkWidget *info_img = GTK_WIDGET(gtk_builder_get_object(builder, "info_img"));

    main_form.setting_login = GTK_WIDGET(gtk_builder_get_object(builder, "info_login"));
    GtkWidget *info_status = GTK_WIDGET(gtk_builder_get_object(builder, "info_status"));
    GtkWidget *socket_version = GTK_WIDGET(gtk_builder_get_object(builder, "socket_version"));
    GtkWidget *socket_platform = GTK_WIDGET(gtk_builder_get_object(builder, "socket_platform"));

    GtkWidget *event_edit_profile = GTK_WIDGET(gtk_builder_get_object(builder, "event_edit_profile"));
    setting_elements.edit_profile_img = GTK_WIDGET(gtk_builder_get_object(builder, "edit_profile_img"));
    setting_elements.edit_profile_text = GTK_WIDGET(gtk_builder_get_object(builder, "edit_profile_text"));

    GtkWidget *event_notifications = GTK_WIDGET(gtk_builder_get_object(builder, "event_notifications"));
    setting_elements.notifications_img = GTK_WIDGET(gtk_builder_get_object(builder, "notifications_img"));
    setting_elements.notifications_text = GTK_WIDGET(gtk_builder_get_object(builder, "notifications_text"));

    GtkWidget *event_privacy = GTK_WIDGET(gtk_builder_get_object(builder, "event_privacy"));
    setting_elements.privacy_img = GTK_WIDGET(gtk_builder_get_object(builder, "privacy_img"));
    setting_elements.privacy_text = GTK_WIDGET(gtk_builder_get_object(builder, "privacy_text"));
    if (data.isBottomed)
    {
        gtk_widget_destroy(event_privacy);
    }
    GtkWidget *event_language = GTK_WIDGET(gtk_builder_get_object(builder, "event_language"));
    setting_elements.language_img = GTK_WIDGET(gtk_builder_get_object(builder, "language_img"));
    setting_elements.language_text = GTK_WIDGET(gtk_builder_get_object(builder, "language_text"));

    GtkWidget *event_theme = GTK_WIDGET(gtk_builder_get_object(builder, "event_theme"));
    setting_elements.theme_img = GTK_WIDGET(gtk_builder_get_object(builder, "theme_img"));
    setting_elements.theme_text = GTK_WIDGET(gtk_builder_get_object(builder, "theme_text"));

    GtkWidget *event_double_bottom = GTK_WIDGET(gtk_builder_get_object(builder, "event_double_bottom"));
    setting_elements.double_bottom_img = GTK_WIDGET(gtk_builder_get_object(builder, "double_bottom_img"));
    setting_elements.double_bottom_text = GTK_WIDGET(gtk_builder_get_object(builder, "double_bottom_text"));
    if (data.isBottomed)
    {
        gtk_widget_destroy(event_double_bottom);
    }

    GtkWidget *event_logout = GTK_WIDGET(gtk_builder_get_object(builder, "event_logout"));
    GtkWidget *logout_img = GTK_WIDGET(gtk_builder_get_object(builder, "logout_img"));
    GtkWidget *logout_text = GTK_WIDGET(gtk_builder_get_object(builder, "logout_text"));
    if (strcmp(data.theme, "Dark") != 0)
    {
        GdkPixbuf *theme_img = gdk_pixbuf_new_from_file("./share/resources/img/logout-l.png", NULL);
        gtk_image_set_from_pixbuf(GTK_IMAGE(logout_img), theme_img);
    }

    g_signal_connect(G_OBJECT(event_edit_profile), "button-press-event", G_CALLBACK(open_edit_profile), NULL);
    g_signal_connect(G_OBJECT(event_notifications), "button-press-event", G_CALLBACK(open_notification), NULL);
    g_signal_connect(G_OBJECT(event_privacy), "button-press-event", G_CALLBACK(open_privacy), NULL);
    g_signal_connect(G_OBJECT(event_language), "button-press-event", G_CALLBACK(open_language), NULL);
    g_signal_connect(G_OBJECT(event_theme), "button-press-event", G_CALLBACK(open_appereance), NULL);
    g_signal_connect(G_OBJECT(event_double_bottom), "button-press-event", G_CALLBACK(open_double_bottom), NULL);
    g_signal_connect(G_OBJECT(event_logout), "button-press-event", G_CALLBACK(logout), NULL);

    GtkWidget *arr[] = {main_form.left_content[2], setting_info_panel, info_container, info_img, main_form.setting_login, info_status,
                        socket_version, socket_platform, event_edit_profile, setting_elements.edit_profile_img, setting_elements.edit_profile_text, event_notifications,
                        setting_elements.notifications_img, setting_elements.notifications_text, event_privacy, setting_elements.privacy_img, setting_elements.privacy_text, event_language, setting_elements.language_img,
                        setting_elements.language_text, event_logout, logout_img, logout_text, event_double_bottom, setting_elements.double_bottom_img, setting_elements.double_bottom_text, event_theme, setting_elements.theme_img, setting_elements.theme_text, NULL};
    css_set(arr, data.main_theme_path);
    gtk_grid_attach(GTK_GRID(main_form.left_content[2]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.left_content[2], 0, 0, 1, 1);
    gtk_widget_show_all(main_form.left_content[2]);
    g_object_unref(builder);
}
