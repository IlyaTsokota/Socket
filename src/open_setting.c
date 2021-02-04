#include "chat.h"

gboolean open_setting(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img)
{
    
    if (main_form.current_panel_id != 1 && main_form.is_allow_access_next_panel)
    {
        puts("KAKOVO HYIA");
        main_form.is_allow_access_next_panel = false;
        main_form.current_panel_id = 1;
        free_chat_items(chats_f.chat_items);
        free_contact_widgets(contacts_t.widgets);
        // free_all_children_in_container(main_form.main_grid);
         puts("KAKOVO HYIA X2");
        gtk_widget_destroy(main_form.right_content);
        gtk_widget_destroy(main_form.left_content);
        clear_styles_from_left_panel(left_panel_img);
        edit_styles_for_widget(left_panel_img->setting, "* {background: #88c5ce;}");
        puts("KAKOVO HYIA X3");
        show_setting(main_form.main_grid);
         puts("KAKOVO HYIA X7");
        show_right_panel_is_clear(main_form.main_grid);
        main_form.is_allow_access_next_panel = true;
        puts("KAKOVO HYIA X4");

    }
    return false;
}
