#include "chat.h"

gboolean open_edit_profile(GtkWidget *widget, GdkEventButton *event)
{
    set_active_setting_item(setting_elements.edit_profile_text,setting_elements.edit_profile_img,
                            "./share/resources/img/info_a.png",show_edit_profile);
    return false;
}

void set_active_setting_item(GtkWidget *text, GtkWidget *img, char *path_img,void (*f)(GtkWidget *grid)){
    gtk_widget_destroy(main_form.right_content);
    clear_styles_from_setting_elements();
    edit_styles_for_widget(text, "* {color: #88c5ce;}");
    GdkPixbuf *active_img = gdk_pixbuf_new_from_file (path_img,NULL);
    gtk_image_set_from_pixbuf(GTK_IMAGE(img), active_img);
    f(main_form.main_grid);
}


void show_edit_profile(GtkWidget *main_grid)
{




    GtkBuilder *builder = glade_file_to_interface("share/edit_profile.glade");
    int *minSize = (int *)malloc(sizeof(int));
    *minSize = 4;
    int *maxSize = (int *)malloc(sizeof(int));
    *maxSize = 16;
    int *maxSizeQuote = (int *)malloc(sizeof(int));
    *maxSizeQuote = 50;
    main_form.right_content = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
   
    user_t *user = get_profile_info();

    GtkWidget *nameLable = GTK_WIDGET(gtk_builder_get_object(builder, "nameLable"));
    profile_s.name =  create_input(builder, "nameInput", maxSize);
    gtk_entry_set_text(GTK_ENTRY(profile_s.name),user->u_name);
    g_signal_connect(G_OBJECT( profile_s.name ), "changed", G_CALLBACK(change_event_entry_only_aplha), minSize);
   
    GtkWidget *surnameLable = GTK_WIDGET(gtk_builder_get_object(builder, "surnameLable"));
    profile_s.surname = create_input(builder, "surnameInput", maxSize);
    gtk_entry_set_text(GTK_ENTRY(profile_s.surname), user->u_surname);
    g_signal_connect(G_OBJECT( profile_s.surname), "changed", G_CALLBACK(change_event_entry_only_aplha), minSize);
    
    GtkWidget *quoteLable = GTK_WIDGET(gtk_builder_get_object(builder, "quoteLable"));
    profile_s.quote = create_input(builder, "quoteInput", maxSizeQuote);
    gtk_entry_set_text(GTK_ENTRY(profile_s.quote), user->u_status);
    g_signal_connect(G_OBJECT( profile_s.quote), "changed", G_CALLBACK(change_event_entry_only_aplha), minSize);
 
    

    GtkWidget *apply_btn = GTK_WIDGET(gtk_builder_get_object(builder, "apply_btn"));
    GtkWidget *delete_acc = GTK_WIDGET(gtk_builder_get_object(builder, "delete_acc"));
    GtkWidget *just = GTK_WIDGET(gtk_builder_get_object(builder, "just"));
    GtkWidget *curr_img = GTK_WIDGET(gtk_builder_get_object(builder, "curr_img"));
    GtkWidget *select_img = GTK_WIDGET(gtk_builder_get_object(builder, "select_img"));
    GtkWidget *login_edit = GTK_WIDGET(gtk_builder_get_object(builder, "login_edit"));
       free_user_s(user);
    GtkWidget *arr[] = {main_form.right_content, setting_form, nameLable,  profile_s.name,
                        surnameLable, profile_s.surname, quoteLable, profile_s.quote, apply_btn, delete_acc, just, curr_img,
                        select_img, login_edit, NULL};

    g_signal_connect(G_OBJECT(apply_btn), "clicked", G_CALLBACK(update_profile), NULL);
    css_set(arr, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content, 1, 0, 1, 1);
    g_object_unref(builder);
}


gboolean open_language(GtkWidget *widget, GdkEventButton *event)
{
    set_active_setting_item(setting_elements.language_text,setting_elements.language_img,
                            "./share/resources/img/language-a.png",show_language);
    return false;
}

void show_language(GtkWidget *main_grid)
{
    GtkBuilder *builder = glade_file_to_interface("share/language.glade");

    main_form.right_content = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *languageLable = GTK_WIDGET(gtk_builder_get_object(builder, "languageLable"));
    GtkWidget *language_combobox = GTK_WIDGET(gtk_builder_get_object(builder, "language_combobox"));
    GtkWidget *arr[] = {main_form.right_content, setting_form, text_info, languageLable, language_combobox, NULL};
    css_set(arr, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content, 1, 0, 1, 1);
    g_object_unref(builder);
}

gboolean open_privacy(GtkWidget *widget, GdkEventButton *event)
{
    set_active_setting_item(setting_elements.privacy_text,setting_elements.privacy_img,
                            "./share/resources/img/shield-a.png",show_privacy);
    return false;
}


void show_privacy(GtkWidget *main_grid)
{
    GtkBuilder *builder = glade_file_to_interface("share/privacy.glade");
    main_form.right_content = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *change_password = GTK_WIDGET(gtk_builder_get_object(builder, "change_password"));
    GtkWidget *change_pin = GTK_WIDGET(gtk_builder_get_object(builder, "change_pin"));
    GtkWidget *vpn_btn = GTK_WIDGET(gtk_builder_get_object(builder, "vpn_btn"));

    GtkWidget *arr[] = {main_form.right_content, setting_form, text_info, change_password, change_pin, vpn_btn, NULL};
    css_set(arr, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content, 1, 0, 1, 1);
    g_object_unref(builder);
}

gboolean open_double_bottom(GtkWidget *widget, GdkEventButton *event)
{
    set_active_setting_item(setting_elements.double_bottom_text,setting_elements.double_bottom_img,
                            "./share/resources/img/privacy-a.png",show_double_bottom);
    return false;
}

void show_double_bottom(GtkWidget *main_grid)
{
    GtkBuilder *builder = glade_file_to_interface("share/double_bottom.glade");
    main_form.right_content = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *loginLable = GTK_WIDGET(gtk_builder_get_object(builder, "loginLable"));
    GtkWidget *loginInput = GTK_WIDGET(gtk_builder_get_object(builder, "loginInput"));
    GtkWidget *create_db = GTK_WIDGET(gtk_builder_get_object(builder, "create_db"));
    GtkWidget *create_ac = GTK_WIDGET(gtk_builder_get_object(builder, "create_ac"));
    GtkWidget *pinLable = GTK_WIDGET(gtk_builder_get_object(builder, "pinLable"));
    GtkWidget *pinInput = GTK_WIDGET(gtk_builder_get_object(builder, "pinInput"));

    GtkWidget *arr[] = {main_form.right_content, setting_form, text_info, loginLable, loginInput, create_db, create_ac, pinLable, pinInput, NULL};
    css_set(arr, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content, 1, 0, 1, 1);
    g_object_unref(builder);
}


gboolean open_notification(GtkWidget *widget, GdkEventButton *event)
{
    set_active_setting_item(setting_elements.notifications_text,setting_elements.notifications_img,
                            "./share/resources/img/bell-a.png",show_notification);
    return false;
}

void show_notification(GtkWidget *main_grid)
{
    GtkBuilder *builder = glade_file_to_interface("share/notifications.glade");
    main_form.right_content = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *notificationsLable = GTK_WIDGET(gtk_builder_get_object(builder, "notificationsLable"));
    GtkWidget *is_notification = GTK_WIDGET(gtk_builder_get_object(builder, "is_notification"));


    GtkWidget *arr[] = {main_form.right_content, setting_form, text_info, notificationsLable, is_notification,  NULL};
    css_set(arr, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content, 1, 0, 1, 1);
    g_object_unref(builder);
}

gboolean open_appereance(GtkWidget *widget, GdkEventButton *event)
{
    set_active_setting_item(setting_elements.theme_text,setting_elements.theme_img,
                            "./share/resources/img/theme-a.png",show_appereance);
    return false;
}

void show_appereance(GtkWidget *main_grid)
{
    GtkBuilder *builder = glade_file_to_interface("share/appereance.glade");
    main_form.right_content = GTK_WIDGET(gtk_builder_get_object(builder, "grid_setting_panel")); // это грид который буду менять
    GtkWidget *setting_form = GTK_WIDGET(gtk_builder_get_object(builder, "setting_form"));
    GtkWidget *text_info = GTK_WIDGET(gtk_builder_get_object(builder, "text_info"));
    GtkWidget *notificationsLable = GTK_WIDGET(gtk_builder_get_object(builder, "notificationsLable"));
    GtkWidget *is_appereance = GTK_WIDGET(gtk_builder_get_object(builder, "is_notification"));

    GtkWidget *arr[] = {main_form.right_content, setting_form, text_info, notificationsLable, is_appereance,  NULL};
    css_set(arr, "share/resources/css/main.css");
    gtk_grid_attach(GTK_GRID(main_grid), main_form.right_content, 1, 0, 1, 1);
    g_object_unref(builder);
}
