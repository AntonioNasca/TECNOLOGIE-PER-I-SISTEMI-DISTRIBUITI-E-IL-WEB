#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


#define PORT 3333

int n=0;

int Sommacifre(char *s);

int main(int argc, char **argv)
{
     char buffer[100],risposta[9];
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
         printf("Error setsock()\n");
         exit(-1);
     }

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

          printf("Server C connesso IP:%s, porta:3333\n",inet_ntoa(client.sin_addr));
          n++;
        

       if((retcode=read(sock2,&buffer,sizeof(buffer)))<0)
       {
           printf("Error read\n");
           exit(-1);
       }

        int x=Sommacifre(buffer);
        
        sprintf(risposta,"n:%d x:%d\n",n,x);
       
        write(sock2,&risposta,9);

        close(sock2);
     }

    close(sock1);



}

int Sommacifre(char * s)
{
    return 0;
}