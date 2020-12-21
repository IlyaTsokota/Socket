#include "chat.h"

void change_event_pin(GtkWidget *entry, int *min)
{
     is_input_success(is_pin, &entry, min);
}