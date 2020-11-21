#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 3333
#define MAXBUF 1024


int main(int argc, char **argv)
{
     char buffer[MAXBUF],risposta[18];
     struct sockaddr_in server,client;
     socklen_t Clientlen;
     int retcode,sock1,sock2,check=1;


     if((sock1=socket(AF_INET,SOCK_STREAM,0))<0)
     {
         printf("Error socket()\n");
         exit(-1);
     }

     if((setsockopt(sock1,SOL_SOCKET,SO_REUSEADDR,&check,sizeof(check)))<0)
     {
         printf("Error setsockopt\n");
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

     printf("Server pronto\n");

     listen(sock1,1);

     Clientlen=sizeof(client);

     while(1)
     {
         if((sock2=accept(sock1,(struct sockaddr*)&client,&Clientlen))<0)
         {
             printf("Error accept()\n");
             exit(-1);
         }

         printf("Connesso all'indirizzo IP %s\n",inet_ntoa(client.sin_addr));

         if((retcode=read(sock2,&buffer,sizeof(buffer)))<0)
         {
             printf("Error read\n");
             exit(-1);
         }
         
         printf("Lunghezza stringa:%d\n",retcode);
         buffer[retcode]='\0';

         printf("Ho ricevuto %s\n",buffer);


         if(buffer[0]=='[' && buffer[retcode-2]==']')
         {
             sprintf(risposta,"Risposta corretta\n");
             write(sock2,&risposta,sizeof(risposta));
         }

         else
         {
             sprintf(risposta,"Risposta errata\n");
             write(sock2,&risposta,sizeof(risposta));
         }

       close(sock2);

     }

     close(sock1);


}
