#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 3333
#define MAXBUF 1024*8

char * list(char *s, char *h);

int main(int argc, char ** argv)
{
    char buffer[MAXBUF],history[]="";
    struct sockaddr_in server,client;
    socklen_t ClientLen;
    int sock1,sock2,retcode,check=1;

    if((sock1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("Error socket()\n");
        exit(-1);
    }

    if((setsockopt(sock1,SOL_SOCKET,SO_REUSEADDR,&check,sizeof(check)))<0)
    {
        printf("Error setsockopt()\n");
        exit(-1);
    }
    
    memset(&server,0,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);


    if((bind(sock1,(struct sockaddr*)&server,sizeof(server)))<0)
    { 
         printf("Error bind()\n");
        exit(-1);
    }

    listen(sock1,1);

    ClientLen=sizeof(client);

    while(1)
    {
       if((sock2=accept(sock1,(struct sockaddr*)&client,&ClientLen))<0)
       {
           printf("Error accept()\n");
           exit(-1);
       }


       printf("Server pronto\n");
       printf("-------------------\n");
       
       retcode=read(sock2,&buffer,sizeof(buffer)-1);
       
       buffer[retcode]='\0';
        
        printf("Ho ricevuto: %s",buffer);
         


        printf("-------------------\n");

        
        strcpy(buffer,list(buffer,history));
        
        write(sock2,buffer,strlen(buffer));

        printf("Ho inviato: %s",buffer);


        close(sock2);

    }


    close(sock1);

}

char *list(char *s,char *h)
{
    if(strcmp(s,"SHOW\r\n")!=0)
    {
       for(int i=dim;i<strlen(s);i++)
       h[i]=s[i];
       
       dim=strlen(s);

       h[dim+1]=';';

       printf("Stringa: %s",h);
       return "OK\n";
    }

    return h;
}
