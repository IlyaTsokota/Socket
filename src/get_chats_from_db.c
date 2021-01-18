#include "chat.h"

void get_chats_from_db(GtkWidget *container_chats)
{
    char *num_f = mx_strnew(strlen("17"));
    strcpy(num_f, "17");
    char *arr[] = {"3", NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    chat_t **chats = request_get_chats(json);
    int size = 0;
    for (size_t i = 0; chats[i]; i++)
    {
        size++;
    }
    g_print("%d -- size\n", size);
    GtkBuilder *builder = glade_file_to_interface("share/chat_item.glade");
    chat_item_t **chat_items = (chat_item_t **)malloc(sizeof(chat_item_t *) * (size + 1));
    chat_items[size] = NULL;
    for (size_t i = 0; i < size; i++)
    {
        chat_items[i] = (chat_item_t *)malloc(sizeof(chat_item_t));
        chat_items[i]->event_box_contact = gtk_event_box_new();
        gtk_widget_set_name(chat_items[i]->event_box_contact, chats[i]->ch_id);
        chat_items[i]->contact_container = gtk_grid_new();
        chat_items[i]->time_last_message = gtk_label_new("11.05");
        chat_items[i]->contact_info = gtk_grid_new();

        chat_items[i]->contact_last_msg = gtk_grid_new();
        chat_items[i]->text_last_message =  gtk_label_new("text last");
        chat_items[i]->login_last_message = gtk_label_new("login last");
        

        chat_items[i]->contact_name_container = gtk_grid_new();
        chat_items[i]->contact_name_lable =  gtk_label_new(chats[i]->ch_name);
        chat_items[i]->user_is_online =  gtk_grid_new();

        chat_items[i]->contact_img_container = gtk_grid_new();
        chat_items[i]->img_contact = gtk_image_new();
    
        puts(chats[i]->ch_id);
        puts(chats[i]->ch_name);
        puts(chats[i]->ch_avatar);
        puts(chats[i]->u_login);
        puts(chats[i]->u_lastSeen);
        puts(chats[i]->u_avatar); 


        gtk_grid_attach(GTK_GRID(chat_items[i]->contact_container), chat_items[i]->contact_img_container, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(chat_items[i]->contact_img_container), chat_items[i]->img_contact, 0, 0, 1, 1);

        gtk_grid_attach(GTK_GRID(chat_items[i]->contact_container), chat_items[i]->contact_info, 1, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(chat_items[i]->contact_info), chat_items[i]->contact_last_msg, 0, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(chat_items[i]->contact_last_msg), chat_items[i]->login_last_message, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(chat_items[i]->contact_last_msg), chat_items[i]->text_last_message, 1, 0, 1, 1);


        gtk_grid_attach(GTK_GRID(chat_items[i]->contact_info), chat_items[i]->contact_name_container, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(chat_items[i]->contact_name_container), chat_items[i]->contact_name_lable, 0, 0, 1, 1);
        gtk_grid_attach(GTK_GRID(chat_items[i]->contact_name_container), chat_items[i]->user_is_online, 1, 0, 1, 1);


        gtk_grid_attach(GTK_GRID(chat_items[i]->contact_container), chat_items[i]->time_last_message, 2, 0, 1, 1);

        gtk_container_add (GTK_CONTAINER (chat_items[i]->event_box_contact), chat_items[i]->contact_container);
        
        gtk_grid_attach(GTK_GRID(container_chats), chat_items[i]->event_box_contact, 0, i, 1, 1);
        free(chat_items[i]);
    }

    puts("GG");
    g_object_unref(builder);
}