#include "chat.h"

gboolean open_chats(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img)
{
    if (main_form.current_panel_id != 2 && main_form.is_allow_access_next_panel)
    {
        main_form.is_allow_access_next_panel = false;
        main_form.current_panel_id = 2;
        free_contact_widgets(contacts_t.widgets);
        gtk_widget_destroy(main_form.right_content);
        gtk_widget_destroy(main_form.left_content);
        clear_styles_from_left_panel(left_panel_img);
        edit_styles_for_widget(left_panel_img->chat, "* {background: #88c5ce;}");
        show_chats(main_form.main_grid);
        show_opened_chat(main_form.main_grid, chats_f.curr_chat);
        main_form.is_allow_access_next_panel = true;
    }
    return false;
}
