#include "chat.h"

void open_register(GtkWidget *window)
{
    GtkBuilder *builder = glade_file_to_interface("share/register_one.glade");
    GtkWidget *regOne = GTK_WIDGET(gtk_builder_get_object(builder, "registrationOne"));
  
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
  
    GtkWidget *labelLogo = GTK_WIDGET(gtk_builder_get_object(builder, "loginTitle"));
    GtkWidget *labelText = GTK_WIDGET(gtk_builder_get_object(builder, "loginText"));

    GtkWidget *loginLable = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    registration.login = create_input(builder, "loginInput", maxSize);
    g_signal_connect(G_OBJECT(registration.login), "changed", G_CALLBACK(change_event_login_or_password), minSize);
    
    GtkWidget *nameLable = GTK_WIDGET(gtk_builder_get_object(builder, "nameLable"));
    registration.name = create_input(builder, "nameInput", maxSize);
    g_signal_connect(G_OBJECT(registration.name), "changed", G_CALLBACK(change_event_entry_only_aplha), minSize);
    
    GtkWidget *surnameLable = GTK_WIDGET(gtk_builder_get_object(builder, "surnameLable"));
    registration.surname = create_input(builder, "surnameInput", maxSize);
    g_signal_connect(G_OBJECT(registration.surname), "changed", G_CALLBACK(change_event_entry_only_aplha), minSize);
    
    GtkWidget *signInLabel = GTK_WIDGET(gtk_builder_get_object(builder, "signInLabel"));
    GtkWidget *btnNext = GTK_WIDGET(gtk_builder_get_object(builder, "nextBtn"));
    
    GtkWidget *arr[] = {regOne, labelLogo, labelText, loginLable, registration.login, nameLable, registration.name, surnameLable, registration.surname, signInLabel, btnNext};
    g_signal_connect(G_OBJECT(signInLabel), "clicked", G_CALLBACK(open_login_form), regOne);
    g_signal_connect(G_OBJECT(btnNext), "clicked", G_CALLBACK(open_register_second_form), regOne);
    
    css_set(arr, "share/resources/css/auth.css", 11);
    
    gtk_container_add(GTK_CONTAINER(window), regOne);
    g_object_unref(builder);
}
