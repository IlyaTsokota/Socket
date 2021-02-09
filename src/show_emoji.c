#include "chat.h"
gboolean show_emoji(GtkWidget *widget, GdkEventButton *event, GtkTextView *text_view)
{
    g_signal_emit_by_name(text_view, "insert-emoji", text_view);
    return false;
}
