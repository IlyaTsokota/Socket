#include "chat.h"

char *get_profile_img(int socket, char *filename, char *ch_id, bool flag)
{
    char *num_f = strdup("26");
     ////puts(filename);
    char *arr[] = {filename, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    write(socket, json, strlen(json));
    free(json);
    char *path_folder;
    if (flag)
    {
        const char *path_parts[] = {"./share/resources/img/chat_info/", ch_id, NULL};
        path_folder = strjoins_arr(path_parts);
        int status = mkdir("./share/resources/img/chat_info", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        status = mkdir(path_folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    else
    {
        const char *path_parts[] = {"share/resources/img/profile", NULL};
        path_folder = strjoins_arr(path_parts);
        int status = mkdir("share/resources/img/profile", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }

    char *file_extension = get_filename_extension(filename);

    char *path_resource = strjoin(3, path_folder, "/icon", file_extension);
    remove(path_resource);
    free(path_folder);
    free(file_extension);

    recieve_image(socket, path_resource);

    return path_resource;
}

char *get_chat_img(int socket, char *ch_id, char *filename) //, char *chat_id, char *message_id)
{
    char *num_f = strdup("26");
    char *arr[] = {filename, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    write(socket, json, strlen(json));
    free(json);

    const char *path_parts[] = {"./share/resources/img/chat_info/", ch_id, NULL};
    char *path_folder = strjoins_arr(path_parts);

    int status = mkdir("./share/resources/img/chat_info", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    status = mkdir(path_folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    char *file_extension = get_filename_extension(filename);

    char *path_resource = strjoin(3, path_folder, "/icon", file_extension);
    remove(path_resource);
    free(path_folder);
    free(file_extension);

    recieve_image(socket, path_resource);

    return path_resource;
}


char *get_msg_img(int socket, char *ch_id, char*ms_id, char *filename) //, char *chat_id, char *message_id)
{
    char *num_f = strdup("26");
    char *arr[] = {filename, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    write(socket, json, strlen(json));
    free(json);

    const char *path_parts[] = {"./share/resources/img/chat_msg/", ch_id, NULL};
    char *path_folder = strjoins_arr(path_parts);

    int status = mkdir("./share/resources/img/chat_msg", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    status = mkdir(path_folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    char *file_extension = get_filename_extension(filename);

    char *path_resource = strjoin(4, path_folder, "/",ms_id , file_extension);
    remove(path_resource);
    free(path_folder);
    free(file_extension);

    recieve_image(socket, path_resource);

    return path_resource;
}