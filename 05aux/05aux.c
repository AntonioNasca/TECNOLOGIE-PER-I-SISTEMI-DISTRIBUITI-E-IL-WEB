#include <unistd.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define IP "90.147.166.230"
#define PORT 8080
#define MSG "GET /pappalardo/prova/05.aux\r\n"

int main(int argc, char ** argv)
{
    char buffer;
    char s[1024];
    struct sockaddr_in server,server1;
    int retcode,sock,sock2;
    int i=0; //Conto quanti caratteri da conservare
    char invio[1024],supp[2914];

    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("error socket\n");
    }

    memset(&server,0,sizeof(server));
    server.sin_family=AF_INET;
    inet_aton(IP,&server.sin_addr);
    server.sin_port=htons(PORT);

    if(connect(sock,(struct sockaddr *)&server,sizeof(server))<0)
    {
        printf("error connect\n");
        exit(-1);
    }

    printf("Connesso con il server: %s, sulla porta: %d\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));

    printf("Invio: %s\n",MSG);

    if((retcode=write(sock,&MSG,sizeof(MSG)))<0)
    {
        printf("Error write\n");
        exit(-1);
    }
   
    
    int k=0;
    int boh=0;
    while((retcode=read(sock,&buffer,sizeof(buffer)))>0)
    {
      if(k==1)
      {
         sprintf(s,"%s",&buffer);
         invio[i]=*s;
         i++;

      }

      if(strncmp(&buffer,"[",strlen(&buffer))==0)
      k=1;
    
        
      if(strncmp(&buffer,"]",strlen(&buffer))==0)
      k=0;
    }

     close(sock);
    

     
    //Sistemo il messaggio
    for(int j=0;j<i-1;j++)
    supp[j]=invio[j];

    supp[i]='\r';
    supp[i+1]='\n';
    

    //Mi ricollego 
    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("error socket\n");
    }


    memset(&server1,0,sizeof(server1));
    server1.sin_family=AF_INET;
    inet_aton(IP,&server1.sin_addr);
    server1.sin_port=htons(PORT);

    if(connect(sock,(struct sockaddr *)&server1,sizeof(server1))<0)
    {
        printf("error connect 2\n");
        exit(-1);
    
    }
    
    printf("Riconnesso al server IP:%s port:%d\n",inet_ntoa(server1.sin_addr),htons(server1.sin_port));

   
    if((retcode=write(sock,&supp,sizeof(supp)))<0)
    {
        printf("Error write 2\n");
        exit(-1);
    }

    else
    {
        printf("Ho inviato al server: %s\n",&supp);
    }
    

    //Leggo
    if((retcode=read(sock,&s,sizeof(s)))<0)
    {
        printf("Error read 2\n");
        exit(-1);
    }

    printf("Ho letto: %d bytes \n",retcode);
    
    printf("----------------------------\n",s);
    printf("Messaggio dal server: \n%s",s);
  
   
  
    close(sock);
    
    

}
