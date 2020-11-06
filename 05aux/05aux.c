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
    struct sockaddr_in server,server2; //server2 e sock 2 servono per la seconda connessione
    int retcode,sock,sock2;
    int i=0; //Conto i byte che ricevo
    char invio[1024]; //Conservo i byte che voglio
    char s[1024]; //Messaggio che ricevo dal Server

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

    
    printf("----------------------------\n",s);
    printf("Connesso con il server: %s, sulla porta: %d\n",inet_ntoa(server.sin_addr),ntohs(server.sin_port));

    printf("Invio al Server la stringa: %s",MSG);

    //Invio il messaggio
    if((retcode=write(sock,&MSG,sizeof(MSG)))<0)
    {
        printf("Error write\n");
        exit(-1);
    }
   
    //Ricevo dati dal server
    int k=0;
    
    //Leggo e conservo solo i caratteri compresi tra  le parentesi []
    //K fa da flag per monitorare se leggo [ oppure ]
    while((retcode=read(sock,&buffer,sizeof(buffer)))>0)
    {
       int j=0;
       for(int i=0; i<retcode;i++)
       {
           if(buffer[i]=='[')
           k=1;
           
    
        
           if(buffer[i]==']')
           k=0;

        //Fare ATTENZIONE alla ricezione perchè il messaggio da leggere và accapo, quindi controllo che c'è \n
          if(k==1 && buffer[i]!='[' && buffer[i]!='\n')
            {
              
              invio[j]=buffer[i];
              j++;
            }
       }
    
       invio[j]='\r';  //Aggiungo \r\n perchè lo richiede http
       invio[j+1]='\n';
      
    }

    //Stampo quello che ricevo
    printf("----------------------------\n",s);
    printf("Ricevo dal server la stringa: %s",invio);
    printf("----------------------------\n",s);

     close(sock); //Mi disconnetto

 
     

    //Mi ricollego allo stesso Server
    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("error socket\n");
        exit(-1);
    }


    memset(&server2,0,sizeof(server2));
    server2.sin_family=AF_INET;
    inet_aton(IP,&server2.sin_addr);
    server2.sin_port=htons(PORT);

    if(connect(sock,(struct sockaddr *)&server2,sizeof(server2))<0)
    {
        printf("error connect 2\n");
        exit(-1);
    
    }
    
    printf("Riconnesso al server: IP:%s port:%d\n",inet_ntoa(server2.sin_addr),htons(server2.sin_port));
    
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
        printf("Ho inviato al server: %s",invio);
    }
    

    //Leggo il messaggio ricevuto dal Server
    if((retcode=read(sock,s,sizeof(s)))<0)
    {
        printf("Error read 2\n");
        exit(-1);
    }

    printf("----------------------------\n",s);
    printf("Ho letto: %d bytes dal Server nella seconda connessione \n",retcode);

    printf("Messaggio dal server: %s\n",s);
  
   
  
    close(sock); //Chiudo la seconda connessione
    
    

}
