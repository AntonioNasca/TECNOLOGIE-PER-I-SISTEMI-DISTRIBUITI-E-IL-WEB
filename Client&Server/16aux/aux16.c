#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>

#define IP "90.147.166.230"
#define PORT 8080
#define MSG "GET /prova/16.aux\r\n"
#define MAXBUF 1024

int main(int argc, char **argv)
{
    char buffer[MAXBUF],risposta[MAXBUF], s[1024];
    struct sockaddr_in server,server2;
    int retcode, sock,sock2;

    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("Error socket()\n");
        exit(-1);
    }

    memset(&server,0,sizeof(server));
    server.sin_family=AF_INET;
    inet_aton(IP,&server.sin_addr);
    server.sin_port=htons(PORT);
    

    if((connect(sock,(struct sockaddr*)&server,sizeof(server)))<0)
    {
        printf("Error connect()\n");
        exit(-1);
    }

    printf("Okay siamo connessi invio la stringa:%s\n",MSG);

    write(sock,&MSG,sizeof(MSG));

    int z=0;

    while((retcode=read(sock,&buffer,sizeof(buffer)))>0)
    {
        for(int i=0;i<retcode;i++)
        {
            if(buffer[i]!='x')
            {
                
              if((buffer[i]>='A' && buffer[i]<='Z') ||(buffer[i]>='a' && buffer[i]<='z')|| buffer[i]=='/' || buffer[i]=='.' || (buffer[i]>='0' && buffer[i]<='9') || buffer[i]==' ' )
                   {
                       s[z]=buffer[i];
                       z++;
                   }
        
            }
        }
    }

   s[z]='x';
   s[z+1]='\r';
   s[z+2]='\n';
   s[z+3]='\0';

   close(sock);
   
   //Nuova connessione

   if((sock2=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("Error socket()\n");
        exit(-1);
    }

    memset(&server2,0,sizeof(server2));
    server2.sin_family=AF_INET;
    inet_aton(IP,&server2.sin_addr);
    server2.sin_port=htons(PORT);
    

    if((connect(sock2,(struct sockaddr*)&server2,sizeof(server2)))<0)
    {
        printf("Error connect()\n");
        exit(-1);
    }

    printf("Okay siamo connessi di nuovo, invio la stringa:%s\n",s);

    write(sock2,&s,sizeof(s));

    if(strcmp(s,"GET /prova/16b.aux\r\n")==0)
    {
        printf("La stringa è corretta\n");
    }
    read(sock2,&s,sizeof(s));

    printf("Ho ricevuto dal server: %s",s);
          

   



}
