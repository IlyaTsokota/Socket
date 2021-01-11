#include "chat.h"

void change_size_message_input(GtkTextBuffer *buffer, GtkWidget *container)
{
    GtkTextIter start, end;
    int index = 0;
    int count_lines = gtk_text_buffer_get_line_count(buffer) - 1;
    int add_h = count_lines > 0 ? count_lines * 20 : 0;
    int height = 0;
    int default_size = 47;
    int max_height = 270;
    height = default_size + add_h;
    height = height > max_height ? max_height : height;
    while (index != height)
    {
        gtk_widget_set_size_request(container, -1, index++);
    }
    int width = gtk_widget_get_allocated_width(container) - 30;
    int size_one_sym = 9;
    int count_sym_in_line = (width / size_one_sym) - 2;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    char *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    int arr_size = 0;

    index = 0;
    char *text_tmp = text;
    char *new_text = mx_strnew(strlen(text));
    while (*text)
    {
        if (index % 2 == 0)
        {
            if (mx_isspace(*text))
            {
                new_text[index] = '\n';
            }
            else
            {
                while (1)
                {
                    if (!mx_isspace(*text))
                    {
                        new_text[index++] = '\n';
                        break;
                    }
                    --text;
                    new_text[index--] = '\0';
                }
                while (index % count_sym_in_line != 0)
                {
                    new_text[index++] = *text;
                    ++text;
                }
            }
        }
        new_text[index++] = *text;
        g_print("%d -- index\n", index);
        ++text;
    }
    text = new_text;
    g_print("%s -- pzdc\n", new_text);
    // gtk_text_buffer_set_text (buffer, new_text, strlen(new_text));
    // while (*arr_str)
    // {
    //     g_print("%s\n ----str\n", *arr_str);
    //     arr_str++;
    // }

    // while (*arr_str)
    // {
    //     g_print("%s\n - item-arr", *arr_str);
    //     arr_str++;
    // }

    g_print("%d -- arr-s\n", arr_size);
}
