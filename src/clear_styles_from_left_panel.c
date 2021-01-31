#include "chat.h"

void clear_styles_from_left_panel(left_panel_img_t *left_panel_img)
{
    edit_styles_for_widget(left_panel_img->chat, "* {background: #b787ff;}");
    edit_styles_for_widget(left_panel_img->setting, "* {background: #b787ff;}");
    edit_styles_for_widget(left_panel_img->contact, "* {background: #b787ff;}");
    edit_styles_for_widget(left_panel_img->lock, "* {background: #b787ff;}");
}

void clear_styles_from_setting_elements()
{
    edit_styles_for_widget(setting_elements.theme_text, "* {color: #c5c5c5;}");
    GdkPixbuf *theme_img = gdk_pixbuf_new_from_file("./share/resources/img/theme.png", NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.theme_img), theme_img);

    edit_styles_for_widget(setting_elements.privacy_text, "* {color: #c5c5c5;}");
    GdkPixbuf *privacy_img = gdk_pixbuf_new_from_file("./share/resources/img/shield.png", NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.privacy_img), privacy_img);

    edit_styles_for_widget(setting_elements.notifications_text, "* {color: #c5c5c5;}");
    GdkPixbuf *notification_img = gdk_pixbuf_new_from_file("./share/resources/img/bell.png", NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.notifications_img), notification_img);
   
    edit_styles_for_widget(setting_elements.language_text, "* {color: #c5c5c5;}");
    GdkPixbuf *language_img = gdk_pixbuf_new_from_file ("./share/resources/img/language.png",NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.language_img), language_img);
    
    edit_styles_for_widget(setting_elements.edit_profile_text, "* {color: #c5c5c5;}");
    GdkPixbuf *edit_profile_img = gdk_pixbuf_new_from_file ("./share/resources/img/info.png",NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.edit_profile_img), edit_profile_img);
    
    edit_styles_for_widget(setting_elements.double_bottom_text, "* {color: #c5c5c5;}");
    GdkPixbuf *double_bottom_img = gdk_pixbuf_new_from_file ("./share/resources/img/privacy.png",NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(setting_elements.double_bottom_img), double_bottom_img);
}
