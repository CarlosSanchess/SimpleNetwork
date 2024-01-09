#include "Api.h"

//Create Socket 
//Bind() Socket to that port
//Put the socket to listen()
//Accept() connection



void bind_Socket(int socket);
int establishing_Connection(int socket);
FILE* getFilePointer(int client);

int main()
{   int socket = new_Socket();
    char buffer[BUFFER_SIZE] = {0};
    size_t dataReceived = 0;
    FILE *fp;


    bind_Socket(socket);

    listen(socket,1);
    int client = establishing_Connection(socket);

    fp = getFilePointer(client);
    while(dataReceived = recv(client,buffer,sizeof(buffer),0) > 0){ 
       fwrite(buffer, 1, strlen(buffer), fp); //Prevents from writting Null data of buffer
       memset(buffer, 0, sizeof(buffer));
    }

    printf("[+]Data received successfully.\n");
    close(socket);
    return 0;
}


void bind_Socket(int socket)
{   
     struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(PORT);
        addr.sin_addr.s_addr = INADDR_ANY;

    int b = bind(socket,(struct sockaddr_in *)&addr,sizeof(addr));
    if(b == -1)
    {
        perror("[-]Error binding socket");
        exit(EXIT_FAILURE);
    }
}

int establishing_Connection(int socket)
{
    struct sockaddr_in client;
    socklen_t client_len = sizeof(client);
    int con_Handler = (int)accept(socket, (struct sockaddr_in*)&client, &client_len); // We can get the information from the client 
    if(con_Handler == -1){
        perror("[-]Error establishing connection");
        exit(EXIT_FAILURE);
    }else{
        printf("[+]Connection established with %s\n",inet_ntoa(client.sin_addr));
    }
    return con_Handler;
}
FILE* getFilePointer(int client){
    FILE *fp;
    size_t dataReceived;
    int aux = 0;
    char buffer[BUFFER_SIZE] = {0};
    char *fileName = NULL;



   while ((dataReceived = recv(client, buffer, sizeof(buffer), 0)) > 0) { 
        if(aux == 0){
            fileName = (char*)malloc(sizeof(char) * (strlen(buffer) * strlen("_clone"))); // +1
            if(!fileName){
                perror("Error Malloc Memory");
                exit(EXIT_FAILURE);
            }
            //fileName[0] = '\0'; //STRCAT needs '\0' make sure of this 
            strcat(buffer,"_clone");
            strcat(fileName, buffer);
        }else if(aux == 1){
                fileName = (char*)realloc(fileName,sizeof(fileName) + strlen(buffer)); 
                strcat(fileName,buffer);    
                fp = open_File(fileName,"wb", client);
                memset(buffer, 0, sizeof(buffer));
                break;
            }
        memset(buffer, 0, sizeof(buffer));
        aux++;
    }
    return fp;
}
