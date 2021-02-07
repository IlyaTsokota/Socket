#include "chat.h"

gboolean change_placeholder_msg_in_focus(GtkTextView *text_view, GdkEvent *event, char *placeholder)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    char *text = buffer_get_text(buffer);
    //g_print("%s\n",text);
    if (strcmp(text, placeholder) == 0)
    {
        gtk_text_buffer_set_text(buffer, "", strlen(""));
    }
    return false;
}

gboolean change_placeholder_msg_out_focus(GtkTextView *text_view, GdkEvent *event, char *placeholder)
{
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    char *text = buffer_get_text(buffer);
    if (strcmp(text, "") == 0)
    {
        gtk_text_buffer_set_text(buffer, placeholder, strlen(placeholder));
    }
    return false;
}
