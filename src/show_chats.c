#include "chat.h"

void show_chats(GtkWidget *main_grid)
{
    GtkBuilder *builder = glade_file_to_interface("share/chats.glade");
    main_form.left_content = GTK_WIDGET(gtk_builder_get_object(builder, "grid_contacts"));
    GtkWidget *contacts_panel = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_panel"));
    GtkWidget *contacts_container = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_container"));
    GtkWidget *event_box_contact = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_contact"));
    GtkWidget *contact_container = GTK_WIDGET(gtk_builder_get_object(builder, "contact_container"));
    GtkWidget *time_last_message = GTK_WIDGET(gtk_builder_get_object(builder, "time_last_message"));
    GtkWidget *login_last_message = GTK_WIDGET(gtk_builder_get_object(builder, "login_last_message"));
    GtkWidget *text_last_message = GTK_WIDGET(gtk_builder_get_object(builder, "text_last_message"));
    GtkWidget *contact_name_lable = GTK_WIDGET(gtk_builder_get_object(builder, "contact_name_lable"));
    GtkWidget *user_is_online = GTK_WIDGET(gtk_builder_get_object(builder, "user_is_online"));
    GtkWidget *contact_info = GTK_WIDGET(gtk_builder_get_object(builder, "contact_info"));
    GtkWidget *contact_last_msg = GTK_WIDGET(gtk_builder_get_object(builder, "contact_last_msg"));
    GtkWidget *contact_name_container = GTK_WIDGET(gtk_builder_get_object(builder, "contact_name_container"));
    GtkWidget *img_contact = GTK_WIDGET(gtk_builder_get_object(builder, "img_contact"));
    GtkWidget *contact_img_container = GTK_WIDGET(gtk_builder_get_object(builder, "contact_img_container"));
    GtkWidget *arr[] = {main_form.left_content, contacts_panel, contacts_container, event_box_contact, contact_container, time_last_message,
                        login_last_message, text_last_message, contact_name_lable, contact_name_lable, user_is_online, contact_info, contact_last_msg,
                        contact_name_container, img_contact, contact_img_container, NULL};
    css_set(arr, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_grid), main_form.left_content, 0, 0, 1, 1);
    g_object_unref(builder);
}
