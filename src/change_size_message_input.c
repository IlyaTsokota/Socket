#include "chat.h"

 static int timeout = 0;

void change_size_message_input(GtkWidget *widget, msg_t *msg_entry)
{
   g_print("Here111\n");
    GtkTextIter iter;
    int n_display_lines = 0;
    gtk_text_buffer_get_start_iter(msg_entry->buffer, &iter);
    while (gtk_text_view_forward_display_line(GTK_TEXT_VIEW(msg_entry->text_view), &iter))
    {
        n_display_lines++;
    }
    int index = 0;
    int add_h = n_display_lines > 0 ? n_display_lines * 18 : 0;
    int height = 0;
    int default_size = 47;
    int max_height = 270;
    height = default_size + add_h;
    height = height > max_height ? max_height : height;
  
    
    gtk_widget_set_size_request(msg_entry->container, -1, height);
    if (height < max_height)
    {
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(msg_entry->container), GTK_POLICY_NEVER, GTK_POLICY_NEVER);
    }
    else
    {
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(msg_entry->container), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
    }
    timeout = g_timeout_add(50, change_insert_to_message, msg_entry->container);

    //g_source_remove(timeout);
    
    // g_source_remove(timeout);
    // GtkAdjustment *adjustment = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(msg_entry->container));
    // gtk_adjustment_set_value(adjustment, gtk_adjustment_get_upper(adjustment));
}
