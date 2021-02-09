#include "chat.h"

gboolean send_pinned_resource(GtkWidget *widget){
GtkWidget *dialog = gtk_file_chooser_dialog_new ("Open File",
                                      GTK_WINDOW(data.win),
                                      GTK_FILE_CHOOSER_ACTION_OPEN,
                                        "OPEN",
                                        GTK_RESPONSE_CANCEL,
                                        "CLOSE",
                                    //    GTK_RESPONSE_ACCEPT,
                                      NULL);
gint res = gtk_dialog_run (GTK_DIALOG (dialog));
if (res == GTK_RESPONSE_ACCEPT)
  {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    char *filename = gtk_file_chooser_get_filename (chooser);
    send_source(data.socket_desc, filename);
    g_free (filename);
  }

gtk_widget_destroy (dialog);
return false;
}
