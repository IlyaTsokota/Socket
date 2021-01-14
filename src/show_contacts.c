#include "chat.h"

void show_contacts(GtkWidget *main_grid)
{
    GtkBuilder *builder = glade_file_to_interface("share/contacts_left.glade");
    main_form.left_content = GTK_WIDGET(gtk_builder_get_object(builder, "grid_contacts_info"));
    GtkWidget *contacts_info_panel = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_info_panel"));
    GtkWidget *box_contact = GTK_WIDGET(gtk_builder_get_object(builder, "box_contact"));
    GtkWidget *event_box_contact = GTK_WIDGET(gtk_builder_get_object(builder, "event_box_contact"));
    GtkWidget *contact_container = GTK_WIDGET(gtk_builder_get_object(builder, "contact_container"));
    GtkWidget *contact_info = GTK_WIDGET(gtk_builder_get_object(builder, "contact_info"));
    GtkWidget *contact_status = GTK_WIDGET(gtk_builder_get_object(builder, "contact_status"));
    GtkWidget *contact_status_lable = GTK_WIDGET(gtk_builder_get_object(builder, "contact_status_lable"));
    GtkWidget *contact_name_container = GTK_WIDGET(gtk_builder_get_object(builder, "contact_name_container"));
    GtkWidget *contact_name_lable = GTK_WIDGET(gtk_builder_get_object(builder, "contact_name_lable"));
    GtkWidget *user_is_online = GTK_WIDGET(gtk_builder_get_object(builder, "user_is_online"));
    GtkWidget *user_is_online_round = GTK_WIDGET(gtk_builder_get_object(builder, "user_is_online_round"));
    GtkWidget *grid_list_contact_img = GTK_WIDGET(gtk_builder_get_object(builder, "grid_list_contact_img"));
    GtkWidget *img_contact = GTK_WIDGET(gtk_builder_get_object(builder, "img_contact"));
    GtkWidget *box_add_new = GTK_WIDGET(gtk_builder_get_object(builder, "box_add_new"));
    GtkWidget *add_new_contact = GTK_WIDGET(gtk_builder_get_object(builder, "add_new_contact"));
    GtkWidget *arr[] = {main_form.left_content, contacts_info_panel,box_contact, event_box_contact,contact_container,contact_info,
    contact_status,contact_status_lable,contact_name_container,contact_name_lable,user_is_online,user_is_online_round,
    grid_list_contact_img,img_contact,box_add_new,add_new_contact,NULL};
    
    css_set(arr, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_grid), main_form.left_content, 0, 0, 1, 1);
    g_object_unref(builder);
}
