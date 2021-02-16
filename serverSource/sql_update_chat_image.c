#include "server.h"

char *sql_update_chat_image(MYSQL *con, int socket, char *ch_id, char *filename) //, char *chat_id, char *message_id)
{

    const char *path_parts[] = {"./chat_info/", ch_id, NULL};
    char *path_folder = strjoins_arr(path_parts);

    int status = mkdir("./chat_info", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    status = mkdir(path_folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    char *file_extension = get_filename_extension(filename);

    char *path_resource = strjoin(3, path_folder, "/icon", file_extension);
    remove(path_resource);
    free(path_folder);
    free(file_extension);

    recieve_image(socket, path_resource);
    //update
    const char *request_parts[] = {"update chat set ch_avatar = \"", path_resource, "\" where ch_id = \"", ch_id, "\";", NULL};
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


