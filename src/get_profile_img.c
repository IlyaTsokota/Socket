#include "chat.h"

char *get_profile_img(int socket, char *filename) //, char *chat_id, char *message_id)
{
    char *num_f = strdup("26");
    puts(filename);
    char *arr[] = {filename, NULL};
    char *json = write_to_json(num_f, arr);
    free(num_f);
    write(socket, json, strlen(json));
    free(json);

    const char *path_parts[] = {"./share/resources/img/profile", NULL};
    char *path_folder = strjoins_arr(path_parts);

    int status = mkdir("./share/resources/img/profile", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    char *file_extension = get_filename_extension(filename);

    char *path_resource = strjoin(3, path_folder, "/icon", file_extension);
    remove(path_resource);
    free(path_folder);
    free(file_extension);

    recieve_image(socket, path_resource);

    return path_resource;
}