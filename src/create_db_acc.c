#include "chat.h"

void create_db_acc(GtkWidget *button, db_data *db_data)
{
    char *pin = (char *)gtk_entry_get_text(GTK_ENTRY(db_data->pin));
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    int flag = 0;
    is_valid_message_to_entry(is_pin, pin, minSize, &db_data->fail_pin, &db_data->pin, "The field may containt only numerals", &flag);
    free(minSize);
    if (flag == 1)
    {
        char *num_f = strdup("23");
        char *arr[] = {data.user_id, pin, NULL};
        char *json = write_to_json(num_f, arr);
        free(num_f);
        request_to_server(json);
        block_app(NULL, NULL, main_form.app_form);
    }
}
