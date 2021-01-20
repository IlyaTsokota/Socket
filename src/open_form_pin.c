#include "chat.h"

void open_form_pin(GtkWidget *window, bool is_start_app)
{
    if(is_start_app){
        is_fullscreen(window);
    }
    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 4;
    pin_t *pin_struct = (pin_t*)malloc(sizeof(pin_t));
    GtkBuilder *builder = glade_file_to_interface("share/pin_code.glade");
    pin_struct->pin_form = GTK_WIDGET(gtk_builder_get_object(builder, "pin_form"));
    GtkWidget *labelTitle = GTK_WIDGET(gtk_builder_get_object(builder, "loginTitle"));
    GtkWidget *labelText = GTK_WIDGET(gtk_builder_get_object(builder, "loginText"));
    GtkWidget *pinLable = GTK_WIDGET(gtk_builder_get_object(builder, "pinLable"));
    pin_struct->pin = create_input(builder, "pinInput", maxSize);
    g_signal_connect(G_OBJECT(pin_struct->pin), "changed", G_CALLBACK(change_event_pin_on_pin_form), maxSize);
     g_signal_connect(G_OBJECT( pin_struct->pin), "activate", G_CALLBACK(autorization_click_pin),  pin_struct);
    GtkWidget *btnNext = GTK_WIDGET(gtk_builder_get_object(builder, "nextBtn"));
    GtkWidget *logoutnBtn = GTK_WIDGET(gtk_builder_get_object(builder, "logout"));
    pin_struct->fail_pin = GTK_WIDGET(gtk_builder_get_object(builder, "fail_pin"));
    g_signal_connect(G_OBJECT(btnNext), "clicked", G_CALLBACK(autorization_click_pin), pin_struct);
    g_signal_connect(G_OBJECT(logoutnBtn), "clicked", G_CALLBACK(open_login_form), pin_struct->pin_form);
    GtkWidget *arrWidgetForStyled[] = {pin_struct->pin_form, labelTitle, labelText, pinLable, pin_struct->pin, btnNext, logoutnBtn, pin_struct->fail_pin, NULL};
    css_set(arrWidgetForStyled, "share/resources/css/auth.css");
    gtk_container_add(GTK_CONTAINER(window), pin_struct->pin_form);
    g_object_unref(builder);
}
