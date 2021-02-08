#include "chat.h"

void get_contacts_from_db(GtkWidget *container, char *user_id)
{
    
    char *num_f = strdup("21");
    char *arr[] = {user_id, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    char *response = request_on_server(data.socket_desc,json);
    free(json);
    ////puts(response);
    json_object *jobj;
    jobj = json_tokener_parse(response);
    if (jobj == NULL) { return;}
    free(jobj);

    contact_t **contacts = get_contacts(response);
    free(response);
  
    if (contacts != NULL)
    {
        contacts_t.was_free = false;
        int size = 0;
        for (size_t i = 0; contacts[i]; i++)
        {
            size++;
        }

        contacts_t.widgets = malloc(sizeof(contacts_widget_s *) * (size + 1));
        contacts_t.widgets[size] = NULL;

        for (size_t i = 0; i < size; i++)
        {
       
            contacts_t.widgets[i] = malloc(sizeof(contacts_widget_s));

            contacts_t.widgets[i]->event_box_contact = gtk_event_box_new();
            gtk_widget_set_hexpand(contacts_t.widgets[i]->event_box_contact, true);
            gtk_widget_set_vexpand(contacts_t.widgets[i]->event_box_contact, false);
            gtk_widget_set_valign(contacts_t.widgets[i]->event_box_contact, GTK_ALIGN_START);
            gtk_widget_set_name(contacts_t.widgets[i]->event_box_contact, contacts[i]->c_id);
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
          
            char *status = cut_str(contacts[i]->u_status, 25);
        
            contacts_t.widgets[i]->contact_status_lable = gtk_label_new(status);
            gtk_widget_set_halign(contacts_t.widgets[i]->contact_status_lable, GTK_ALIGN_START);
            gtk_widget_set_hexpand(contacts_t.widgets[i]->contact_status_lable, false);
            set_style_context(contacts_t.widgets[i]->contact_status_lable, "contact-lastmessage");
            free(status);
        
            contacts_t.widgets[i]->contact_name_container = gtk_grid_new();

            contacts_t.widgets[i]->contact_name_lable = gtk_label_new(contacts[i]->u_name);
            gtk_widget_set_margin_top( contacts_t.widgets[i]->contact_name_lable, 10);
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
            gtk_widget_set_margin_start( contacts_t.widgets[i]->img_contact, 10);
            set_style_context(contacts_t.widgets[i]->img_contact, "contact-icon");
         
            css_set_for_one(contacts_t.widgets[i]->img_contact, "share/resources/css/main.css");
            css_set_for_one(contacts_t.widgets[i]->grid_list_contact_img, "share/resources/css/main.css");
            css_set_for_one(contacts_t.widgets[i]->contact_name_lable, "share/resources/css/main.css");
            css_set_for_one(contacts_t.widgets[i]->contact_status_lable, "share/resources/css/main.css");
            css_set_for_one(contacts_t.widgets[i]->contact_status, "share/resources/css/main.css");
            css_set_for_one(contacts_t.widgets[i]->contact_container, "share/resources/css/main.css");
            css_set_for_one(contacts_t.widgets[i]->contact_info, "share/resources/css/main.css");

            gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_container), contacts_t.widgets[i]->contact_info, 1, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_container), contacts_t.widgets[i]->grid_list_contact_img, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->grid_list_contact_img), contacts_t.widgets[i]->img_contact, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_info), contacts_t.widgets[i]->contact_status, 0, 1, 1, 1);
            gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_info), contacts_t.widgets[i]->contact_name_container, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_name_container), contacts_t.widgets[i]->contact_name_lable, 0, 0, 1, 1);
            gtk_grid_attach(GTK_GRID(contacts_t.widgets[i]->contact_status), contacts_t.widgets[i]->contact_status_lable, 0, 0, 1, 1);

            gtk_container_add(GTK_CONTAINER(contacts_t.widgets[i]->event_box_contact), contacts_t.widgets[i]->contact_container);
            gtk_box_pack_start (GTK_BOX(container), contacts_t.widgets[i]->event_box_contact, false, true, 0);
        }
        gtk_widget_show_all(container);
        free_contacts_s(contacts);

    }
}
