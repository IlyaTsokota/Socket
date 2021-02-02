#include "chat.h"

void update_profile(GtkWidget *button)
{
    char *quote = (char *)gtk_entry_get_text(GTK_ENTRY(profile_s.quote));
    char *name = (char *)gtk_entry_get_text(GTK_ENTRY(profile_s.name));
    char *surname = (char *)gtk_entry_get_text(GTK_ENTRY(profile_s.surname));
    
    update_user_data(data.user_id, name, surname, quote);
}