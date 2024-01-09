
#include "Api.h"



int establishing_Connection(int socket, char *serverIp);
void sendFileName(FileData file, char *server_message, int client_socket);

int main(int argc, char const *argv[])
{
    char server_message[BUFFER_SIZE] = {0};
    FileData file;

    int client_socket = new_Socket();

    if(argc != 3)
    {
        fprintf(stderr,"Usage: %s <server_ip> <file>\n",argv[0]);
        return -1;
    }
    printf("Usage: %s <server_ip> <file>\n",argv[0]);

    file = bindFile(argv[2]);

    establishing_Connection(client_socket, argv[1]);
    FILE *fp = open_File(argv[2],"rb",client_socket);

    safeStrCopy(server_message, file.name, sizeof(server_message));
    send(client_socket, server_message, sizeof(server_message), 0);
    memset(server_message,0, sizeof(server_message));
    safeStrCopy(server_message, file.type, sizeof(server_message));
    send(client_socket, server_message, sizeof(server_message), 0);   
    memset(server_message,0, sizeof(server_message));

    size_t bytesRead;
    while((bytesRead = fread(server_message, 1, sizeof(server_message), fp)) > 0){
        ssize_t bytes_sent = send(client_socket, &server_message, sizeof(server_message), 0);
        if (bytes_sent == -1)
        {
            perror("Error sending data");
            close(client_socket);
            return -1;
        } 
         memset(server_message,0, sizeof(server_message));
    }
    printf("Data sent successfully\n");

    close(client_socket);

    return 0;
}

int establishing_Connection(int socket, char * serverIp)
{
    struct sockaddr_in server_side;
    server_side.sin_family = AF_INET;
    server_side.sin_port = htons(PORT);
    server_side.sin_addr.s_addr = inet_addr(serverIp);

    int con = connect(socket, (struct sockaddr_in*)&server_side, sizeof(server_side));
    if (con == -1)
    {
        perror("Error establishing connection");
        return -1;
    }else{
        fprintf(stdout,"Connection Established...\n");

    }
    return con;
}

void sendFileName(FileData file, char *server_message, int client_socket){ // Find Bug
    safeStrCopy(server_message, file.name, sizeof(server_message));
    send(client_socket, server_message, sizeof(server_message), 0);
    memset(server_message,0, sizeof(server_message));
    safeStrCopy(server_message, file.type, sizeof(server_message));
    send(client_socket, server_message, sizeof(server_message), 0);   
    memset(server_message,0, sizeof(server_message));
}






