#include "chat.h"

void create_one_user_widget(int i, user_curr_chat_t *contact)
{
    users_in_chat.users = realloc( users_in_chat.users, sizeof(user_in_chat_t *) * (i + 2));
    users_in_chat.users[i] = malloc(sizeof(user_in_chat_t));

    users_in_chat.users[i]->users_item = gtk_grid_new();
    gtk_widget_set_hexpand(users_in_chat.users[i]->users_item, true);
    gtk_widget_set_vexpand(users_in_chat.users[i]->users_item, true);
    gtk_widget_set_valign(users_in_chat.users[i]->users_item, GTK_ALIGN_START);
    gtk_widget_set_halign(users_in_chat.users[i]->users_item, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(users_in_chat.users[i]->users_item, 15);
    gtk_widget_set_size_request(users_in_chat.users[i]->users_item, 350, 70);

    users_in_chat.users[i]->user_event_box = gtk_event_box_new();
    gtk_widget_set_name(users_in_chat.users[i]->user_event_box, contact->u_id);
    gtk_widget_set_hexpand(users_in_chat.users[i]->user_event_box, true);
    gtk_widget_set_halign(users_in_chat.users[i]->user_event_box, GTK_ALIGN_START);
    g_signal_connect(G_OBJECT(users_in_chat.users[i]->user_event_box), "button-press-event", G_CALLBACK(open_click_contact), NULL);

    users_in_chat.users[i]->body_user = gtk_grid_new();

    users_in_chat.users[i]->user_img = gtk_image_new_from_file("share/resources/img/ava2.png");

    users_in_chat.users[i]->user_name  = gtk_label_new(contact->u_login);
    gtk_widget_set_margin_start( users_in_chat.users[i]->user_name ,10);
    gtk_widget_set_margin_end( users_in_chat.users[i]->user_name, 10);
    set_style_context( users_in_chat.users[i]->user_name, "contact-login");
    
    users_in_chat.users[i]->delete_event_box = gtk_event_box_new();
    gtk_widget_set_name(users_in_chat.users[i]->delete_event_box, contact->u_id);
    gtk_widget_set_hexpand(users_in_chat.users[i]->delete_event_box, false);
    gtk_widget_set_halign(users_in_chat.users[i]->delete_event_box, GTK_ALIGN_END);

    users_in_chat.users[i]->remove_img = gtk_image_new_from_file("share/resources/img/delete.png");

    css_set_for_one(users_in_chat.users[i]->user_name, data.main_theme_path);

    gtk_grid_attach(GTK_GRID(users_in_chat.users[i]->body_user), users_in_chat.users[i]->user_img, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(users_in_chat.users[i]->body_user), users_in_chat.users[i]->user_name, 1, 0, 1, 1);
    gtk_container_add(GTK_CONTAINER(users_in_chat.users[i]->delete_event_box), users_in_chat.users[i]->remove_img);
    gtk_container_add(GTK_CONTAINER(users_in_chat.users[i]->user_event_box), users_in_chat.users[i]->body_user);

    gtk_grid_attach(GTK_GRID(users_in_chat.users[i]->users_item), users_in_chat.users[i]->delete_event_box, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(users_in_chat.users[i]->users_item), users_in_chat.users[i]->user_event_box, 0, 0, 1, 1);

    users_in_chat.users[i + 1] = NULL;
    users_in_chat.size = i + 1;
}
