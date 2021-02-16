#include "chat.h"

gboolean open_contacts(GtkWidget *widget, GdkEventButton *event, left_panel_img_t *left_panel_img)
{
 
        hide_gtk_widgets(main_form.left_content);
        hide_gtk_widgets(main_form.right_content);
        clear_styles_from_left_panel(left_panel_img);
        edit_styles_for_widget(left_panel_img->contact,  "* {background: #88c5ce;}");
        show_contacts(main_form.main_grid);
        show_right_panel_is_clear(main_form.main_grid);
        gtk_widget_show_all(main_form.left_content[1]);
        gtk_widget_show_all(main_form.right_content[1]);

        gtk_widget_hide(main_form.chat_info_event_box);

    
    return false;
}
