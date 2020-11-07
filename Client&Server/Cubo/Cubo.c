#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 3333

int main(int rgc, char **argv)
{
    int cubo=0;
    char buffer[100];
    struct sockaddr_in server,client;
    socklen_t ClientLen;
    int sock1, check=1,sock2,retcode;


    if((sock1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("Error socket()\n");
        exit(1);
    }

    if((setsockopt(sock1,SOL_SOCKET,SO_REUSEADDR,&check,sizeof(check)))<0)
    {
        printf("Error setsocket()\n");
        exit(1);
    }

    memset(&server,0,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);
   
    if((bind(sock1,(struct sockaddr *)&server,sizeof(server)))<0)
    {
        printf("Error bind()\n");
        exit(1);
    }

    listen(sock1,1);

    ClientLen=sizeof(client);
    
    while(1)
    {
        if((sock2=accept(sock1,(struct sockaddr *)&client,&ClientLen))<0)
        {
          printf("Error accept()\n");
          exit(1);
        }

        printf("Il server e' pronto\n");

        if((retcode=read(sock2,&buffer,sizeof(buffer)))<0)
        {
            printf("Error read()\n");
            exit(-1);
        }
        
        buffer[retcode]='\0';

        printf("Ho ricevuto %s",buffer);

        cubo=atoi(buffer);
        cubo=cubo*cubo*cubo;
        memset(&buffer,0,sizeof(buffer));

        sprintf(buffer,"Ecco il cubo:%d\n",cubo);

        write(sock2,&buffer,sizeof(buffer));

        close(sock2);

        exit(1);

    }


   close(sock1);

}
