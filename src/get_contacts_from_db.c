#include "chat.h"

void get_contacts_from_db(GtkWidget *container, char *user_id)
{
    char *num_f = strdup("21");
    char *arr[] = {user_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(json);
    free(json);
    puts(response);
    contact_t **contacts = get_contacts(response);
    free(response);
    if (contacts != NULL)
    {
        int size = 0;
        for (size_t i = 0; contacts[i]; i++)
        {
            size++;
        }

        contacts_widget_s **widgets = (contacts_widget_s **)malloc(sizeof(contacts_widget_s *) * (size + 1));
        widgets[size] = NULL;

        for (size_t i = 0; i < size; i++)
        {
            widgets[i] = (contacts_widget_s *)malloc(sizeof(contacts_widget_s));

            widgets[i]->event_box_contact = gtk_event_box_new();
            gtk_widget_set_hexpand(widgets[i]->event_box_contact, true);
            gtk_widget_set_vexpand(widgets[i]->event_box_contact, false);
            gtk_widget_set_valign(widgets[i]->event_box_contact, GTK_ALIGN_START);
            gtk_widget_set_name(widgets[i]->event_box_contact, contacts[i]->c_id);
            gtk_widget_set_size_request(widgets[i]->event_box_contact, -1, 84);

            widgets[i]->contact_container = gtk_grid_new();
            gtk_widget_set_hexpand(widgets[i]->contact_container, true);
            gtk_widget_set_vexpand(widgets[i]->contact_container, true);
            set_style_context(widgets[i]->contact_container, "contact-container");

            widgets[i]->contact_info = gtk_grid_new();
            gtk_widget_set_hexpand(widgets[i]->contact_info, true);
            gtk_widget_set_vexpand(widgets[i]->contact_info, true);
            set_style_context(widgets[i]->contact_info, "contact-body");

            widgets[i]->contact_status = gtk_grid_new();
            gtk_widget_set_hexpand(widgets[i]->contact_status, true);
            gtk_widget_set_vexpand(widgets[i]->contact_status, true);
            gtk_widget_set_valign(widgets[i]->contact_status, GTK_ALIGN_END);

            char status[30];
            strncpy(status, contacts[i]->u_status, 25);
            strcpy(&status[25], "...\0");

            widgets[i]->contact_status_lable = gtk_label_new(status);
            gtk_widget_set_halign(widgets[i]->contact_status_lable, GTK_ALIGN_START);
            gtk_widget_set_hexpand(widgets[i]->contact_status_lable, false);
            set_style_context(widgets[i]->contact_status_lable, "contact-lastmessage");

            widgets[i]->contact_name_container = gtk_grid_new();
           

            widgets[i]->contact_name_lable = gtk_label_new(contacts[i]->u_name);
              gtk_widget_set_margin_top( widgets[i]->contact_name_lable, 10);
            gtk_widget_set_halign(widgets[i]->contact_name_lable, GTK_ALIGN_START);
            set_style_context(widgets[i]->contact_name_lable, "contact-login");

            widgets[i]->grid_list_contact_img = gtk_grid_new();
            gtk_widget_set_size_request(widgets[i]->grid_list_contact_img, 57, 57);
            gtk_widget_set_hexpand(widgets[i]->grid_list_contact_img, false);
            gtk_widget_set_vexpand(widgets[i]->grid_list_contact_img, false);
            gtk_widget_set_halign(widgets[i]->grid_list_contact_img, GTK_ALIGN_START);
            gtk_widget_set_valign(widgets[i]->grid_list_contact_img, GTK_ALIGN_CENTER);
            set_style_context(widgets[i]->contact_name_lable, "contact-img");

            widgets[i]->img_contact = gtk_image_new_from_file("share/resources/img/aa.png");
            gtk_widget_set_hexpand(widgets[i]->img_contact, true);
            gtk_widget_set_vexpand(widgets[i]->img_contact, true);
             gtk_widget_set_margin_start( widgets[i]->img_contact, 10);
            set_style_context(widgets[i]->img_contact, "contact-icon");

            css_set_for_one(widgets[i]->img_contact, "share/resources/css/main.css");
            css_set_for_one(widgets[i]->grid_list_contact_img, "share/resources/css/main.css");
            css_set_for_one(widgets[i]->contact_name_lable, "share/resources/css/main.css");
            css_set_for_one(widgets[i]->contact_status_lable, "share/resources/css/main.css");
            css_set_for_one(widgets[i]->contact_status, "share/resources/css/main.css");
            css_set_for_one(widgets[i]->contact_container, "share/resources/css/main.css");
            css_set_for_one(widgets[i]->contact_info, "share/resources/css/main.css");

            gtk_grid_attach(GTK_GRID(widgets[i]->contact_container), widgets[i]->contact_info, 1, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(widgets[i]->contact_container), widgets[i]->grid_list_contact_img, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(widgets[i]->grid_list_contact_img), widgets[i]->img_contact, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(widgets[i]->contact_info), widgets[i]->contact_status, 0, 1, 1, 1);
            gtk_grid_attach(GTK_GRID(widgets[i]->contact_info), widgets[i]->contact_name_container, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(widgets[i]->contact_name_container), widgets[i]->contact_name_lable, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(widgets[i]->contact_status), widgets[i]->contact_status_lable, 0, 0, 1, 1);

            gtk_container_add(GTK_CONTAINER(widgets[i]->event_box_contact), widgets[i]->contact_container);
            gtk_box_pack_start (GTK_BOX(container), widgets[i]->event_box_contact, false, true, 0);
        }
        gtk_widget_show_all(container);
        free_contacts_s(contacts);
    }
}
