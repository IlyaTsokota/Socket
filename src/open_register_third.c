#include "chat.h"

void open_register_third(GtkWidget *window)
{
    GtkBuilder *builder = glade_file_to_interface("share/register_three.glade");
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(builder, "registrationTwo"));
    GtkWidget *labelLogo = GTK_WIDGET(gtk_builder_get_object(builder, "loginTitle"));
    GtkWidget *labelText = GTK_WIDGET(gtk_builder_get_object(builder, "loginText"));
    GtkWidget *loginLable = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    GtkWidget *btnNext = GTK_WIDGET(gtk_builder_get_object(builder, "nextBtn"));
    GtkWidget *arr[] = {grid, labelLogo, labelText, loginLable, btnNext};
    g_signal_connect(G_OBJECT(btnNext), "clicked", G_CALLBACK(open_register_second_form), grid);
    css_set(arr, "share/resources/css/auth.css", 5);
    gtk_container_add(GTK_CONTAINER(window), grid);
    g_object_unref(builder);
}
