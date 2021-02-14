#include "chat.h"

gboolean open_click_contact(GtkWidget *widget)
{
    hide_gtk_widgets(main_form.right_content);
    char *id = (char *)gtk_widget_get_name(widget);
    show_open_contact(main_form.main_grid, id);
    contact_info_t *current_info = get_contact_info(id);
    clear_style_all_contact_widgets();
    char *color = strcmp(data.theme, "Dark") == 0 ? strdup("* { background-color: #3c3c3c;}")
                                                  : strdup("* { background-color: #ebf3f7;}");
    edit_styles_for_widget(widget, color);
    free(color);
    if (contacts_t.curr_contact != NULL)
    {
        free(contacts_t.curr_contact);
        contacts_t.curr_contact = NULL;
    }
    contacts_t.curr_contact = strdup(id);
    puts(contacts_t.curr_contact);
    gtk_label_set_text(GTK_LABEL(main_form.contact_info_name), current_info->u_login);
    // main.form.img_info_contact
    char *tmp_quote = strjoin(3, "\" ", current_info->u_status, " \"");
    gtk_label_set_text(GTK_LABEL(main_form.quote_text), tmp_quote);
    free(tmp_quote);
    if (!current_info->is_my_contact)
    {
        g_signal_handlers_disconnect_by_func(main_form.add_contact, remove_from_contact, NULL);
        g_signal_handlers_disconnect_by_func(main_form.add_contact, add_to_contact, NULL);
        gtk_button_set_label(GTK_BUTTON(main_form.add_contact), "Remove contact");
        g_signal_connect(G_OBJECT(main_form.add_contact), "clicked", G_CALLBACK(remove_from_contact), NULL);
    }
    else
    {
        g_signal_handlers_disconnect_by_func(main_form.add_contact, remove_from_contact, NULL);
        g_signal_handlers_disconnect_by_func(main_form.add_contact, add_to_contact, NULL);
        gtk_button_set_label(GTK_BUTTON(main_form.add_contact), "Add contact");
        g_signal_connect(G_OBJECT(main_form.add_contact), "clicked", G_CALLBACK(add_to_contact), NULL);
    }
    gtk_label_set_text(GTK_LABEL(main_form.fullname_text), current_info->u_name);
    free_contact_info_s(current_info);
    gtk_widget_show_all(main_form.right_content[2]);

    return false;
}




void remove_from_contact(GtkWidget *button)
{
    char *num_f = strdup("5");
    char *arr[] = {data.user_id, contacts_t.curr_contact, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    request_to_server(json);
    free(json);
    free_contact_widgets(contacts_t.widgets);
    create_widget_contacts(data.user_id);
    if (contacts_t.widgets != NULL)
    {
        for (size_t i = 0; contacts_t.widgets[i]; i++)
        {
            gtk_box_pack_start(GTK_BOX(main_form.box_contact), contacts_t.widgets[i]->event_box_contact, false, true, 0);
        }
        gtk_widget_show_all(main_form.box_contact);
    }
    g_signal_handlers_disconnect_by_func(main_form.add_contact, remove_from_contact, NULL);
    g_signal_handlers_disconnect_by_func(main_form.add_contact, add_to_contact, NULL);
    gtk_button_set_label(GTK_BUTTON(main_form.add_contact), "Add contact");
    g_signal_connect(G_OBJECT(main_form.add_contact), "clicked", G_CALLBACK(add_to_contact), NULL);
}

void add_to_contact(GtkWidget *button)
{
    char *num_f = strdup("4");
    char *arr[] = {data.user_id, contacts_t.curr_contact, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    request_to_server(json);
    free(json);
    num_f = strdup("36");
    char *login = (char *)gtk_label_get_text(GTK_LABEL(main_form.contact_info_name));
    char *arr1[] = {login, NULL};
    json = write_to_json(num_f, arr1);
    free(num_f);
    char *response = request_on_server(data.socket_desc, json);
    free(json);
    contact_t **contacts = get_contacts(response);
    free(response);
    create_one_contact(contacts_t.size, contacts[0]);
    free_contacts_s(contacts);
    gtk_box_pack_start(GTK_BOX(main_form.box_contact), contacts_t.widgets[contacts_t.size - 1]->event_box_contact, false, true, 0);
    gtk_widget_show_all(main_form.box_contact);
    g_signal_handlers_disconnect_by_func(main_form.add_contact, remove_from_contact, NULL);
    g_signal_handlers_disconnect_by_func(main_form.add_contact, add_to_contact, NULL);
    gtk_button_set_label(GTK_BUTTON(main_form.add_contact), "Remove contact");
    g_signal_connect(G_OBJECT(main_form.add_contact), "clicked", G_CALLBACK(remove_from_contact), NULL);
}
