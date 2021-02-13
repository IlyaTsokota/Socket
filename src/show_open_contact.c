#include "chat.h"

void show_open_contact(GtkWidget *main_grid, char *id)
{
    if (!do_once.bshow_open_contact)
        return;
    do_once.bshow_open_contact = false;
    GtkBuilder *builder = glade_file_to_interface("share/contacts_right.glade");

    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_contact_info_panel")); // это грид который буду менять
    GtkWidget *contact_info_name_container = GTK_WIDGET(gtk_builder_get_object(builder, "contact_info_name_container"));
    main_form.contact_info_name = GTK_WIDGET(gtk_builder_get_object(builder, "contact_info_name"));

    // GtkWidget *user_info_is_online = GTK_WIDGET(gtk_builder_get_object(builder, "user_info_is_online"));
    // GtkWidget *user_info_is_online_round = GTK_WIDGET(gtk_builder_get_object(builder, "user_info_is_online_round"));
    main_form.img_info_contact = GTK_WIDGET(gtk_builder_get_object(builder, "img_info_contact"));
    GtkWidget *send_message = GTK_WIDGET(gtk_builder_get_object(builder, "send_message"));

    GtkWidget *add_contact = GTK_WIDGET(gtk_builder_get_object(builder, "add_contact"));

    GtkWidget *blcok_contact = GTK_WIDGET(gtk_builder_get_object(builder, "blcok_contact"));

    GtkWidget *quote = GTK_WIDGET(gtk_builder_get_object(builder, "quote"));
    main_form.quote_text = GTK_WIDGET(gtk_builder_get_object(builder, "quote_text"));


    GtkWidget *fullname = GTK_WIDGET(gtk_builder_get_object(builder, "fullname"));
    main_form.fullname_text = GTK_WIDGET(gtk_builder_get_object(builder, "fullname_text"));


    GtkWidget *is_admin = GTK_WIDGET(gtk_builder_get_object(builder, "is_admin"));
    GtkWidget *support_text = GTK_WIDGET(gtk_builder_get_object(builder, "support_text"));

    GtkWidget *arr[] = {main_form.right_content[2], contact_info_name_container, main_form.contact_info_name, send_message, add_contact, blcok_contact, main_form.img_info_contact, quote,  main_form.quote_text , fullname, main_form.fullname_text, is_admin, support_text, NULL};
    css_set(arr, data.main_theme_path);
    gtk_grid_attach(GTK_GRID(main_form.right_content[2]), child, 0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[2], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[2]);

    g_object_unref(builder);
}
