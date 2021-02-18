#include "chat.h"

gboolean send_pinned_resource(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
  GtkWidget *dialog = gtk_file_chooser_dialog_new("Open file", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
                                                  "Cancel", GTK_RESPONSE_CANCEL,
                                                  "Open", GTK_RESPONSE_OK,
                                                  NULL);
 
  gint res = gtk_dialog_run(GTK_DIALOG(dialog));
 

  if (res == -5)
  {
    g_mutex_lock(&main_form.mutex);

    GtkFileChooser *chooser = GTK_FILE_CHOOSER(dialog);
    char *filename = gtk_file_chooser_get_filename(chooser);
    puts(filename);
    char *num_f = strdup("13");
    char *arr[] = {chats_f.curr_chat, data.user_id, "0", "0", "1", filename, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    puts(json);
    write(data.socket_desc, json, strlen(json));
    free(json);
    g_mutex_unlock(&main_form.mutex);

    send_image(data.socket_desc, filename);
    g_mutex_lock(&main_form.mutex);
    int stat;
    long size = 0;
    size_t packet_size = 1024, packet_count = 0, read_index = 0;
    char buff[1024];
    char *str;
    stat = 1025;
    read(data.socket_desc, (void *)&size, sizeof(long));
    size = ntohl(size);
    str = mx_strnew(size);
    do
    {
      if (size < packet_size)
      {
        packet_size = size;
      }
      stat = recv(data.socket_desc, buff, packet_size, 0);
      memcpy(&str[read_index], buff, packet_size);
      if (stat == -1)
      {
        break;
      }
      size -= stat;
      read_index += stat;
      str[read_index] = '\0';

    } while (size > 0);
    free(str);
    stat = read(data.socket_desc, buff, 1);
    //read(data.socket_desc, buff, 1);
    g_free(filename);
    g_mutex_unlock(&main_form.mutex);
  }

  gtk_widget_destroy(dialog);
  return false;
}
