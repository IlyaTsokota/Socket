#include "chat.h"

gboolean open_add_chat(GtkWidget *widget, GdkEventButton *event)
{
    hide_gtk_widgets(main_form.right_content);
    show_add_chat(main_form.main_grid);
    gtk_widget_show_all(main_form.right_content[9]);
    return false;
}

void show_add_chat(GtkWidget *main_grid)
{
    if (!do_once.bshow_add_chat)
        return;
    do_once.bshow_add_chat = false;
    GtkBuilder *builder = glade_file_to_interface("share/add_chat.glade");
    GtkWidget *child = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *pinLable = GTK_WIDGET(gtk_builder_get_object(builder, "pinLable"));
    GtkWidget *fail_name = GTK_WIDGET(gtk_builder_get_object(builder, "fail_pin"));

    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
      int *minSize = (int *)malloc(sizeof(int));
    *minSize = 1;
    GtkWidget *chat_name = create_input(builder, "pinInput", maxSize);

    GtkWidget *add_chat = GTK_WIDGET(gtk_builder_get_object(builder, "add_chat"));
   GtkWidget *widgets[] = {chat_name,fail_name };
    //free(maxSize);
    GtkWidget *arr[] = {main_form.right_content[9], setting_form, fail_name, text_info, add_chat,  pinLable, chat_name, NULL};
    
    css_set(arr,  data.main_theme_path);
    g_signal_connect(G_OBJECT(chat_name), "changed", G_CALLBACK(change_event_login_or_password), minSize);
    g_signal_connect(G_OBJECT(add_chat), "clicked", G_CALLBACK(add_new_chat), chat_name);
    gtk_grid_attach(GTK_GRID(main_form.right_content[9]), child, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content[9], 1, 0, 1, 1);
    gtk_widget_show_all(main_form.right_content[9]);

    g_object_unref(builder);
}
