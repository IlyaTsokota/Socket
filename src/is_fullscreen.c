#include "chat.h"

void is_fullscreen(GtkWidget *window){
    int* new_width = (int *)malloc(sizeof(int)); 
    *new_width = 1300;
    int *new_height = (int *)malloc(sizeof(int)); 
    *new_height = 740;
    int height = 0;
    int width = 0;
    gtk_window_get_size(GTK_WINDOW(window), &width, &height);
    if (width < *new_width)
    {
        gtk_window_resize(GTK_WINDOW(window), *new_width, height);
    }
    gtk_window_get_size(GTK_WINDOW(window), &width, &height);
    if (height < *new_height)
    {
        gtk_window_resize(GTK_WINDOW(window), width, *new_height);
    }
    free(new_width);
    free(new_height);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
}