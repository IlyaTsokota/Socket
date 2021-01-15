#include "server.h"

MYSQL *connection_try()
{
    MYSQL *con = mysql_init(NULL);

    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, "remotemysql.com", "F7PtEuRzNu", "w17IurRRy7",
                           "F7PtEuRzNu", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    return con;
}

void *connection_handler(void *socket_desc)
{
    int sock = *(int *)socket_desc;
    int read_size;
    char client_message[2000];
    char *server_answer_message;

    // message = "Hi! I am your conection handlerr\n";
    //write(sock, message, strlen(message));

    while ((read_size = recv(sock, client_message, 2000, 0)) > 0)
    {
        client_message[read_size] = '\0';
        // write(sock, client_message, strlen(client_message));
        // memset(client_message,0,2000);

        MYSQL *handler_con = connection_try();
        //Тут нужно получить номер запроса и вызвать по нему нужную функцию

        // server_answer_message= password_check(handler_con, "1111", "itsokota");

        array_t query = json_to_data(client_message);
        puts("<-------------[Processing the request]------------->");
        
        server_answer_message = queries_handler(handler_con, query.arr, sock);
        puts("<-------------[Waiting for next query]------------->");
        array_clear(&query);
        //password_check(handler_con, "1111", "itsokota");

        write(sock, server_answer_message, strlen(server_answer_message));
        memset(client_message, 0, 2000);

        if (read_size == 0)
        {
            puts("Client off");
        }
        else if (read_size == -1)
        {
            puts("Сбой при recv");
        }
    }

    return 0;
}

int main()
{
    //char *locale;
    //locale = setlocale(LC_ALL, "");

    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;

    //Creating socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
        printf("Error while socket creating");
    puts("Socket created");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3762);

    //Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind failed. Error");
        return 1;
    }
    puts("bind sucess");

    //Listening
    listen(socket_desc, 3); //second parametr set max_clients;

    puts("Waiting for new connections...");
    c = sizeof(struct sockaddr_in);
    pthread_t thread_id;

    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
    {
        puts("Connection created");

        if (pthread_create(&thread_id, NULL, connection_handler, (void *)&client_sock) < 0)
        {
            perror("Error while creating thread\n");
            exit(1);
        }
        puts("Handler was set");
    }

    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
}
