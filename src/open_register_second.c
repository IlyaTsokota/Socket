#include "chat.h"

void open_register_second(GtkWidget *window)
{
     int* minSize = (int*)malloc(sizeof(int));
    *minSize = 4;
    int* maxSize = (int*)malloc(sizeof(int));
    *maxSize = 16;
    GtkBuilder *builder = glade_file_to_interface("share/register_two.glade");
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(builder, "registrationTwo"));
    GtkWidget *labelLogo = GTK_WIDGET(gtk_builder_get_object(builder, "loginTitle"));
    GtkWidget *labelText = GTK_WIDGET(gtk_builder_get_object(builder, "loginText"));
    GtkWidget *passwordLable = GTK_WIDGET(gtk_builder_get_object(builder, "passwordLable"));
    GtkWidget *passwordInput = create_input(builder, "passwordInput", maxSize);
     g_signal_connect(G_OBJECT(passwordInput), "changed", G_CALLBACK(change_event_login_or_password), minSize);
    GtkWidget *pinLable = GTK_WIDGET(gtk_builder_get_object(builder, "pinLable"));
    GtkWidget *pinInput = create_input(builder, "pinInput", minSize);
    g_signal_connect(G_OBJECT(pinInput), "changed", G_CALLBACK(change_event_pin), minSize);
    GtkWidget *signInLabel = GTK_WIDGET(gtk_builder_get_object(builder, "signInLabel"));
    GtkWidget *btnNext = GTK_WIDGET(gtk_builder_get_object(builder, "nextBtn"));
    GtkWidget *arr[] = {grid, labelLogo, labelText, passwordLable, passwordInput, pinLable, pinInput, signInLabel, btnNext};
    g_signal_connect(G_OBJECT(signInLabel), "clicked", G_CALLBACK(open_login_form), grid);
    g_signal_connect(G_OBJECT(btnNext), "clicked", G_CALLBACK(open_register_third_form), grid);
    css_set(arr, "share/resources/css/auth.css", 9);
    gtk_container_add(GTK_CONTAINER(window), grid);
    g_object_unref(builder);
}
