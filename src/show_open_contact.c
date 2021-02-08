#include "chat.h"

void show_open_contact(GtkWidget *main_grid, char *id)
{
   if (!do_once.bshow_open_contact)
        return;
    do_once.bshow_open_contact = false;
    contact_info_t *current_info = get_contact_info(id);
    GtkBuilder *builder = glade_file_to_interface("share/contacts_right.glade");

   GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_contact_info_panel")); // это грид который буду менять
    GtkWidget *contact_info_name_container = GTK_WIDGET(gtk_builder_get_object(builder, "contact_info_name_container"));
    GtkWidget *contact_info_name = GTK_WIDGET(gtk_builder_get_object(builder, "contact_info_name"));
    gtk_label_set_text(GTK_LABEL(contact_info_name), current_info->u_login);

    // GtkWidget *user_info_is_online = GTK_WIDGET(gtk_builder_get_object(builder, "user_info_is_online"));
    // GtkWidget *user_info_is_online_round = GTK_WIDGET(gtk_builder_get_object(builder, "user_info_is_online_round"));
    GtkWidget *img_info_contact = GTK_WIDGET(gtk_builder_get_object(builder, "img_info_contact"));
    GtkWidget *send_message = GTK_WIDGET(gtk_builder_get_object(builder, "send_message"));
    
    GtkWidget *add_contact = GTK_WIDGET(gtk_builder_get_object(builder, "add_contact"));
    
    GtkWidget *blcok_contact = GTK_WIDGET(gtk_builder_get_object(builder, "blcok_contact"));

    GtkWidget *quote = GTK_WIDGET(gtk_builder_get_object(builder, "quote"));
    GtkWidget *quote_text = GTK_WIDGET(gtk_builder_get_object(builder, "quote_text"));
    char *tmp_quote = strjoin(3, "\" ",  current_info->u_status," \"");
    gtk_label_set_text(GTK_LABEL(quote_text),tmp_quote);
    free(tmp_quote);

    GtkWidget *fullname = GTK_WIDGET(gtk_builder_get_object(builder, "fullname"));
    GtkWidget *fullname_text = GTK_WIDGET(gtk_builder_get_object(builder, "fullname_text"));
    gtk_label_set_text(GTK_LABEL(fullname_text), current_info->u_name);

    GtkWidget *is_admin = GTK_WIDGET(gtk_builder_get_object(builder, "is_admin"));
    GtkWidget *support_text = GTK_WIDGET(gtk_builder_get_object(builder, "support_text"));

    free_contact_info_s(current_info);
    GtkWidget *arr[] = {main_form.right_content[2], contact_info_name_container, contact_info_name, send_message, add_contact, blcok_contact, img_info_contact, quote, quote_text, fullname, fullname_text, is_admin, support_text, NULL};
    css_set(arr, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_form.right_content[2]), child, 0, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[2], 1, 0, 1, 1);
            gtk_widget_show_all(main_form.right_content[2]);

    g_object_unref(builder);
}
