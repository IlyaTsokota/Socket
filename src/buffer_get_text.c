#include "chat.h"

char *buffer_get_text(GtkTextBuffer *buffer){
    GtkTextIter start ;
    GtkTextIter end  ;
    char *text = gtk_text_buffer_get_text (buffer,&start,&end,TRUE);
    return text;
}
