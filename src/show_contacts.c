#include "chat.h"

void show_contacts(GtkWidget *main_grid)
{
    static bool do_once = true;
    if (!do_once)
        return;
    GtkBuilder *builder = glade_file_to_interface("share/contacts_left.glade");
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_contacts_info"));

    GtkWidget *contacts_info_panel = GTK_WIDGET(gtk_builder_get_object(builder, "contacts_info_panel"));
    GtkWidget *box_contact = GTK_WIDGET(gtk_builder_get_object(builder, "box_contact"));

    GtkWidget *box_add_new = GTK_WIDGET(gtk_builder_get_object(builder, "box_add_new"));
    GtkWidget *add_new_contact = GTK_WIDGET(gtk_builder_get_object(builder, "add_new_contact"));
    GtkWidget *arr[] = {main_form.left_content[1], contacts_info_panel,box_contact, box_add_new,add_new_contact,NULL};
    gtk_label_set_text(GTK_LABEL(main_form.top_panel_top_text), "Contacts"); 
    gtk_label_set_text(GTK_LABEL(main_form.top_panel_bottom_text), "Some contacts can affect your life"); 
    css_set(arr, "share/resources/css/main.css");
    get_contacts_from_db(box_contact, data.user_id);
     gtk_grid_attach(GTK_GRID( main_form.left_content[1]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.left_content[1], 0, 0, 1, 1);
    gtk_widget_show_all(main_form.left_content[1]);
    g_object_unref(builder);
    do_once = false;
}
