#include "chat.h"

void autorization_click_pin(GtkWidget *button, pin_t *pin_struct)
{
    char *pin = (char *)gtk_entry_get_text(GTK_ENTRY(pin_struct->pin));
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    if (strlen(pin) < 4)
    {
        gtk_label_set_text(GTK_LABEL(pin_struct->fail_pin), "The field can't be empty");
        valid_entry_border_pin(pin_struct->pin);
    }
    else if (!is_pin(strlen(pin), minSize, pin))
    {
        gtk_label_set_text(GTK_LABEL(pin_struct->fail_pin), "The field may containt only numerals");
    }
    else
    {
        if (is_pin_user(pin))
        {
            gtk_widget_destroy(pin_struct->pin_form);
             // =-1;
             // = true;
            open_main_form(data.win);
        }
        else
        {
             gtk_label_set_text(GTK_LABEL(pin_struct->fail_pin), "Invalid pin");
        }
    }
    free(minSize);
}
