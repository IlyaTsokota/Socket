#include "chat.h"

void open_register_third(GtkWidget *window)
{
    GtkBuilder *builder = glade_file_to_interface(localization_s.register_three);
    GtkWidget *grid = GTK_WIDGET(gtk_builder_get_object(builder, "registrationTwo"));
    GtkWidget *labelLogo = GTK_WIDGET(gtk_builder_get_object(builder, "loginTitle"));
    GtkWidget *labelText = GTK_WIDGET(gtk_builder_get_object(builder, "loginText"));
    GtkWidget *loginLable = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    gtk_label_set_text(GTK_LABEL(loginLable), registration.login_text);
    GtkWidget *btnNext = GTK_WIDGET(gtk_builder_get_object(builder, "nextBtn"));
    GtkWidget *arr[] = {grid, labelLogo, labelText, loginLable, btnNext, NULL};
    g_signal_connect(G_OBJECT(btnNext), "clicked", G_CALLBACK(open_main_form_after_register), grid);
    css_set(arr,   data.auth_theme_path);
    gtk_container_add(GTK_CONTAINER(window), grid);
    g_object_unref(builder);
}
