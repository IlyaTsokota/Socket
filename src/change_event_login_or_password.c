#include "chat.h"

void change_event_login_or_password(GtkWidget *entry, int *min){
    is_input_success(is_login_or_password, &entry, min);
}
