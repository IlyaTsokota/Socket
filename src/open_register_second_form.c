#include "chat.h"

void open_register_second_form(GtkWidget *button, GtkWidget *widget)
{   
    char *login = (char *)gtk_entry_get_text(GTK_ENTRY(reg_one.login));
    char *name = (char *)gtk_entry_get_text(GTK_ENTRY(reg_one.name));
    char *surname = (char *)gtk_entry_get_text(GTK_ENTRY(reg_one.surname));
    int flag = 0;
    
    if (strlen(login) < 4) {
        // label все хуево давай по новой
    } else {++flag;}
    
    if(strlen(name) < 4 || !is_alpha_string(name)){
        // label все хуево давай по новой
    } else {++flag;}

    if(strlen(surname) < 4 || !is_alpha_string(surname)){
        // label все хуево давай по новой
    }  else {++flag;}
    
    if(flag == 3){
        gtk_widget_destroy(widget);
        open_register_second(data.win);
    }
}
