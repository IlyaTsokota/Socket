#include "chat.h"

void create_one_contact(int i, contact_t *contact)
{
    contacts_t.widgets = realloc(contacts_t.widgets, sizeof(contacts_widget_s *) * (i + 2));
    contacts_t.widgets[i] = malloc(sizeof(contacts_widget_s));

    contacts_t.widgets[i]->event_box_contact = gtk_event_box_new();
    gtk_widget_set_hexpand(contacts_t.widgets[i]->event_box_contact, true);
    gtk_widget_set_vexpand(contacts_t.widgets[i]->event_box_contact, false);
    gtk_widget_set_valign(contacts_t.widgets[i]->event_box_contact, GTK_ALIGN_START);
    gtk_widget_set_name(contacts_t.widgets[i]->event_box_contact, contact->c_id);
    gtk_widget_set_size_request(contacts_t.widgets[i]->event_box_contact, -1, 84);
    g_signal_connect(G_OBJECT(contacts_t.widgets[i]->event_box_contact), "button-press-event", G_CALLBACK(open_click_contact), NULL);

    contacts_t.widgets[i]->contact_container = gtk_grid_new();
    gtk_widget_set_hexpand(contacts_t.widgets[i]->contact_container, true);
    gtk_widget_set_vexpand(contacts_t.widgets[i]->contact_container, true);
    set_style_context(contacts_t.widgets[i]->contact_container, "contact-container");

    contacts_t.widgets[i]->contact_info = gtk_grid_new();
    gtk_widget_set_hexpand(contacts_t.widgets[i]->contact_info, true);
    gtk_widget_set_vexpand(contacts_t.widgets[i]->contact_info, true);
    set_style_context(contacts_t.widgets[i]->contact_info, "contact-body");

    contacts_t.widgets[i]->contact_status = gtk_grid_new();
    gtk_widget_set_hexpand(contacts_t.widgets[i]->contact_status, true);
    gtk_widget_set_vexpand(contacts_t.widgets[i]->contact_status, true);
    gtk_widget_set_valign(contacts_t.widgets[i]->contact_status, GTK_ALIGN_END);

    char *status = cut_str(contact->u_status, 25);

    contacts_t.widgets[i]->contact_status_lable = gtk_label_new(status);
    gtk_widget_set_halign(contacts_t.widgets[i]->contact_status_lable, GTK_ALIGN_START);
    gtk_widget_set_hexpand(contacts_t.widgets[i]->contact_status_lable, false);
    set_style_context(contacts_t.widgets[i]->contact_status_lable, "contact-lastmessage");
    free(status);

    contacts_t.widgets[i]->contact_name_container = gtk_grid_new();

    contacts_t.widgets[i]->contact_name_lable = gtk_label_new(contact->u_name);
    gtk_widget_set_margin_top(contacts_t.widgets[i]->contact_name_lable, 10);
    gtk_widget_set_halign(contacts_t.widgets[i]->contact_name_lable, GTK_ALIGN_START);
    set_style_context(contacts_t.widgets[i]->contact_name_lable, "contact-login");

    contacts_t.widgets[i]->grid_list_contact_img = gtk_grid_new();
    gtk_widget_set_size_request(contacts_t.widgets[i]->grid_list_contact_img, 57, 57);
    gtk_widget_set_hexpand(contacts_t.widgets[i]->grid_list_contact_img, false);
    gtk_widget_set_halign(contacts_t.widgets[i]->grid_list_contact_img, GTK_ALIGN_START);
    gtk_widget_set_valign(contacts_t.widgets[i]->grid_list_contact_img, GTK_ALIGN_CENTER);
    set_style_context(contacts_t.widgets[i]->contact_name_lable, "contact-img");

    contacts_t.widgets[i]->img_contact = gtk_image_new_from_file("share/resources/img/aa.png");
    gtk_widget_set_hexpand(contacts_t.widgets[i]->img_contact, true);
    gtk_widget_set_vexpand(contacts_t.widgets[i]->img_contact, true);
    gtk_widget_set_margin_start(contacts_t.widgets[i]->img_contact, 10);
    set_style_context(contacts_t.widgets[i]->img_contact, "contact-icon");

    css_set_for_one(contacts_t.widgets[i]->img_contact, data.main_theme_path);
    css_set_for_one(contacts_t.widgets[i]->grid_list_contact_img, data.main_theme_path);
    css_set_for_one(contacts_t.widgets[i]->contact_name_lable, data.main_theme_path);
    css_set_for_one(contacts_t.widgets[i]->contact_status_lable, data.main_theme_path);
    css_set_for_one(contacts_t.widgets[i]->contact_status, data.main_theme_path);
    css_set_for_one(contacts_t.widgets[i]->contact_container, data.main_theme_path);
    css_set_for_one(contacts_t.widgets[i]->contact_info, data.main_theme_path);

    gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_container), contacts_t.widgets[i]->contact_info, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_container), contacts_t.widgets[i]->grid_list_contact_img, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->grid_list_contact_img), contacts_t.widgets[i]->img_contact, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_info), contacts_t.widgets[i]->contact_status, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_info), contacts_t.widgets[i]->contact_name_container, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_name_container), contacts_t.widgets[i]->contact_name_lable, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_status), contacts_t.widgets[i]->contact_status_lable, 0, 0, 1, 1);

    gtk_container_add(GTK_CONTAINER(contacts_t.widgets[i]->event_box_contact), contacts_t.widgets[i]->contact_container);
    contacts_t.widgets[i + 1] = NULL;
    contacts_t.size = i + 1;

}
