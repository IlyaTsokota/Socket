#include "chat.h"

void show_setting(GtkWidget *main_grid)
{
    GtkBuilder *builder = glade_file_to_interface("share/left_panel_setting.glade");
    main_form.left_content = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_info"));
    GtkWidget *setting_info_panel = GTK_WIDGET(gtk_builder_get_object(builder, "setting_info_panel"));

        GtkWidget *info_container = GTK_WIDGET(gtk_builder_get_object(builder, "info_container"));
    GtkWidget *info_img = GTK_WIDGET(gtk_builder_get_object(builder, "info_img"));
    GtkWidget *info_login = GTK_WIDGET(gtk_builder_get_object(builder, "info_login"));
    GtkWidget *info_status = GTK_WIDGET(gtk_builder_get_object(builder, "info_status"));
    GtkWidget *socket_version = GTK_WIDGET(gtk_builder_get_object(builder, "socket_version"));
    GtkWidget *socket_platform = GTK_WIDGET(gtk_builder_get_object(builder, "socket_platform"));
    
    GtkWidget *event_edit_profile = GTK_WIDGET(gtk_builder_get_object(builder, "event_edit_profile"));
    GtkWidget *edit_profile_img = GTK_WIDGET(gtk_builder_get_object(builder, "edit_profile_img"));
    GtkWidget *edit_profile_text = GTK_WIDGET(gtk_builder_get_object(builder, "edit_profile_text"));

    GtkWidget *event_notifications = GTK_WIDGET(gtk_builder_get_object(builder, "event_notifications"));
    GtkWidget *notifications_img = GTK_WIDGET(gtk_builder_get_object(builder, "notifications_img"));
    GtkWidget *notifications_text = GTK_WIDGET(gtk_builder_get_object(builder, "notifications_text"));

     GtkWidget *event_privacy = GTK_WIDGET(gtk_builder_get_object(builder, "event_privacy"));
    GtkWidget *privacy_img = GTK_WIDGET(gtk_builder_get_object(builder, "privacy_img"));
    GtkWidget *privacy_text = GTK_WIDGET(gtk_builder_get_object(builder, "privacy_text"));

     GtkWidget *event_language = GTK_WIDGET(gtk_builder_get_object(builder, "event_language"));
    GtkWidget *language_img = GTK_WIDGET(gtk_builder_get_object(builder, "language_img"));
    GtkWidget *language_text = GTK_WIDGET(gtk_builder_get_object(builder, "language_text"));

 GtkWidget *event_theme = GTK_WIDGET(gtk_builder_get_object(builder, "event_theme"));
    GtkWidget *theme_img = GTK_WIDGET(gtk_builder_get_object(builder, "theme_img"));
    GtkWidget *theme_text = GTK_WIDGET(gtk_builder_get_object(builder, "theme_text"));

     GtkWidget *event_double_bottom = GTK_WIDGET(gtk_builder_get_object(builder, "event_double_bottom"));
    GtkWidget *double_bottom_img = GTK_WIDGET(gtk_builder_get_object(builder, "double_bottom_img"));
    GtkWidget *double_bottom_text = GTK_WIDGET(gtk_builder_get_object(builder, "double_bottom_text"));

    
    GtkWidget *arr[] = {main_form.left_content, setting_info_panel,info_container,info_img,info_login, info_status,
    socket_version,socket_platform,event_edit_profile,edit_profile_img,edit_profile_text,event_notifications,
     notifications_img,notifications_text,event_privacy,privacy_img,privacy_text,event_language,language_img,
     language_text,event_double_bottom,double_bottom_img,double_bottom_text,event_theme,theme_img,theme_text,NULL};
    css_set(arr, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_grid), main_form.left_content, 0, 0, 1, 1);
    g_object_unref(builder);
}
