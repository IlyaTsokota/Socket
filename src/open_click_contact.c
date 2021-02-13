#include "chat.h"

gboolean open_click_contact(GtkWidget *widget)
{
    hide_gtk_widgets(main_form.right_content);
    char *id = (char *)gtk_widget_get_name(widget);
    show_open_contact(main_form.main_grid, id);
    contact_info_t *current_info = get_contact_info(id);
    gtk_label_set_text(GTK_LABEL(main_form.contact_info_name), current_info->u_login);
    // main.form.img_info_contact
    char *tmp_quote = strjoin(3, "\" ", current_info->u_status, " \"");
    gtk_label_set_text(GTK_LABEL(main_form.quote_text), tmp_quote);
    free(tmp_quote);
    gtk_label_set_text(GTK_LABEL(main_form.fullname_text), current_info->u_name);
    free_contact_info_s(current_info);
    gtk_widget_show_all(main_form.right_content[2]);

    return false;
}
