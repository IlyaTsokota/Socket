#include "chat.h"

char *get_text_of_textview(GtkTextView *text_view)
{
  GtkTextIter start, end;
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
  if (buffer == NULL)
  {
    return NULL;
  }
  gtk_text_buffer_get_bounds(buffer, &start, &end);
  // gtk_text_buffer_get_start_iter();
  // gtk_text_buffer_get_end_iter(buffer, );
  char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
  return text;
}

void clear_text__buffer(GtkTextView *text_view)
{
  GtkTextIter start, end;

  GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
  gtk_text_buffer_get_start_iter(buffer, &start);
  gtk_text_buffer_get_end_iter(buffer, &end);
  gtk_text_buffer_delete(buffer, &start, &end);
}
void insert_text(GtkTextBuffer *buffer, GtkTextIter *location, gchar *text, gint len, gpointer user_data)
{

  GThread *thread = g_thread_new("max_size", limit_size_msg_text, location);
}

gpointer limit_size_msg_text(gpointer location)
{
  GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(main_form.text_view));
  gint count = gtk_text_buffer_get_char_count(buffer);
  if (count > 300)
  {
    GtkTextIter offset, end;
    gtk_text_buffer_get_iter_at_offset(buffer, &offset, 300);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_delete(buffer, &offset, &end);
    // gtk_text_iter_assign((GtkTextIter *)location, &offset);
  }
  return NULL;
}

void change_size_message_input(GtkWidget *widget, msg_t *msg_entry)
{
  GtkTextIter iter;
  int n_display_lines = 0;
  gtk_text_buffer_get_start_iter(msg_entry->buffer, &iter);
  while (gtk_text_view_forward_display_line(GTK_TEXT_VIEW(msg_entry->text_view), &iter))
  {
    n_display_lines++;
  }
  int index = 0;
  int height_line = 12;
  int add_h = n_display_lines > 0 ? n_display_lines * 12 : 0;
  int height = 0;
  int default_size = 47;
  int max_height = height_line * 10;
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
  g_timeout_add(50, change_insert_to_message, msg_entry->container);
}
