#include "server.h"

char *receive_img_to_profile(MYSQL *con, int socket, char *u_id, char *filename) //, char *chat_id, char *message_id)
{

    const char *path_parts[] = {"./user_info/", u_id, NULL};
    char *path_folder = strjoins_arr(path_parts);

    int status = mkdir("./user_info", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    status = mkdir(path_folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    char *file_extension = get_filename_extension(filename);

    char *path_resource = strjoin(3, path_folder, "/icon", file_extension);
    remove(path_resource);

    FILE *image = fopen(path_resource, "w");
    free(path_folder);
    free(file_extension);
    if (image == NULL)
    {
        printf("Error has occurred. Image file could not be opened\n");
        return strdup("0");
    }

    printf("Reading Picture Size\n");
    int size;
    read(socket, &size, sizeof(size));

    //Read Picture Byte Array
    printf("Reading Picture Byte Array\n");
    char p_array[1024];
    while (size > 0)
    {
        read(socket, p_array, 1024);
        fwrite(p_array, 1, sizeof(p_array), image);
        size -= 1024;
    }

    fclose(image);

    //update
    const char *request_parts[] = {"update user set u_avatar = \"", path_resource, "\" where u_id = \"", u_id, "\";", NULL};
    char *bdrequest = strjoins_arr(request_parts);
    puts(bdrequest); //Вывод запроса в консоль

    if (mysql_query(con, bdrequest))
    {
        finish_with_error(con);
    }
    free(bdrequest);
    free(path_resource);
    mysql_close(con);

    printf("Image successfully Received!\n");
    return strdup("1");
}
