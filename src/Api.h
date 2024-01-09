#include <stdio.h>
#include <sys/socket.h> //C socket API
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#define SIZE 50
#define BUFFER_SIZE 1024
#define PORT 4444


struct{
    char name[SIZE];
    char type[SIZE];
}typedef FileData;

int new_Socket(){
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    return s;
}
FILE *open_File(char *file, char *mode, int socket)
{
    FILE *fp = fopen(file, mode);
    if (fp == NULL)
    {
        perror("Error opening file");
        close(socket);
        exit(EXIT_FAILURE);
    }
    return fp;
}

FileData bindFile(const char *fileName){
    FileData file;
    int aux = 0;
    for(int i = 0; i < sizeof(fileName); i++){ //TODO NULL TERMINATE THE STRING
        if(fileName[i] != '.' && aux == 0){
            file.name[i] = fileName[i];
        }else{
            file.type[aux] = fileName[i];
            aux++;
        }
    
    }
    return file;
}

void safeStrCopy(char *dest, char *from, size_t destSize){
    if(destSize <  strlen(from) + 1){
        perror("Buffer Overflow...");
        exit(EXIT_FAILURE);
    }else{
        strcpy(dest, from);
    }
}

