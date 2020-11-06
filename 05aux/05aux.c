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
    char buffer[1024];
    struct sockaddr_in server,server1;
    int retcode,sock,sock2;
    int i=0; //Conto quanti caratteri da conservare
    char invio[1024],s[1024];

    //Mi collego la prima volta
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

    //Invio il messaggio
    if((retcode=write(sock,&MSG,sizeof(MSG)))<0)
    {
        printf("Error write\n");
        exit(-1);
    }
   
    //Ricevo dati dal server
    int k=0;
    
    while((retcode=read(sock,&buffer,sizeof(buffer)))>0)
    {
       int j=0;
       for(int i=0; i<retcode;i++)
       {
           if(buffer[i]=='[')
           k=1;
           
    
        
           if(buffer[i]==']')
           k=0;

          if(k==1 && buffer[i]!='[' && buffer[i]!='\n')
            {
              
              invio[j]=buffer[i];
              j++;
            }
       }
    
       invio[j]='\r';
       invio[j+1]='\n';
      
    }

     printf("Ricevo dal server %s\n",invio);

     close(sock); //Mi disconnetto

 
     

    //Mi ricollego allo stesso Server
    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("error socket\n");
        exit(-1);
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
    
    printf("Riconnesso al server: IP:%s port:%d\n",inet_ntoa(server1.sin_addr),htons(server1.sin_port));
    
    if((strncmp(invio,"GET /pappalardo/prova/05b.aux\n",strlen(invio)))==0)
    {
        printf("OK\n");
    }
   
   
    //Invio il messaggio prelevato dal Server
    if((retcode=write(sock,invio,sizeof(invio)))<0)
    {
        printf("Error write 2\n");
        exit(-1);
    }
     

    else
    {
        printf("Ho inviato al server: %s   \n",invio);
    }
    

    //Leggo il messaggio ricevuto dal Server
    if((retcode=read(sock,s,sizeof(s)))<0)
    {
        printf("Error read 2\n");
        exit(-1);
    }

    printf("Ho letto: %d bytes \n",retcode);
    
    printf("----------------------------\n",s);
    printf("Messaggio dal server: \n%s",s);
  
   
  
    close(sock); //Chiudo la seconda connessione
    
    

}
