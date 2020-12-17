#include "chat.h"

void open_register(GtkWidget *window)
{
    GtkBuilder *builder = glade_file_to_interface("share/register_one.glade");
    GtkWidget *regOne = GTK_WIDGET(gtk_builder_get_object(builder, "registrationOne"));
   
    GtkWidget *labelLogo = GTK_WIDGET(gtk_builder_get_object(builder, "loginTitle"));
    GtkWidget *labelText = GTK_WIDGET(gtk_builder_get_object(builder, "loginText"));
    GtkWidget *loginLable = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    GtkWidget *loginInput = create_input(builder, "loginInput", 16);
    GtkWidget *nameLable = GTK_WIDGET(gtk_builder_get_object(builder, "nameLable"));
    GtkWidget *nameInput = create_input(builder, "nameInput", 16);
    GtkWidget *surnameLable = GTK_WIDGET(gtk_builder_get_object(builder, "surnameLable"));
    GtkWidget *surnameInput = create_input(builder, "surnameInput", 16);
    GtkWidget *signInLabel = GTK_WIDGET(gtk_builder_get_object(builder, "signInLabel"));
    GtkWidget *btnNext = GTK_WIDGET(gtk_builder_get_object(builder, "nextBtn"));
    GtkWidget *arr[] = {regOne, labelLogo, labelText, loginLable, loginInput, nameLable, nameInput, surnameLable, surnameInput, signInLabel, btnNext};
    g_signal_connect(G_OBJECT(signInLabel), "clicked", G_CALLBACK(open_login_form), regOne);
    g_signal_connect(G_OBJECT(btnNext), "clicked", G_CALLBACK(open_register_second_form), regOne);
    css_set(arr, "share/resources/css/auth.css", 11);
    gtk_container_add(GTK_CONTAINER(window), regOne);
    g_object_unref(builder);
}
