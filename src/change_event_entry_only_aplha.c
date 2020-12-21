#include "chat.h"

void change_event_entry_only_aplha(GtkWidget *entry, int *min)
{
     is_input_success(is_only_alpha, &entry, min);
}