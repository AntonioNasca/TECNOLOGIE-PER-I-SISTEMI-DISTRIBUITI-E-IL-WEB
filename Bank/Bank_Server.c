#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 7777
#define MAXBUF 2048

#include  "Informazioni.h"

/* Da ricordare che questo Server è stato sviluppato per Telnet.
Quindi manderà due carrateri in più per ogni messaggio
per questo sul metodo strlen(messaggio) tolgo -3 */

void Answer(char *, char *, int);
int Checkstring(char *);
char risposta[100];
int pronto=0;

int main(int argc, char **argv)
{
    char msg[MAXBUF];
    char answer[200];
    struct sockaddr_in client,server;
    socklen_t clientLen;
    int retcode,s, check=1,sock,connectsock;


    printf("Benvenuto\n");

    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("Problema socket()\n");
        exit(-1);
    }

    if((setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&check,sizeof(check)))<0)
    {
        printf("Problema setsockopt()\n");
        exit(-1);
    }

    memset(&server,0,sizeof(server));
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);

    if((bind(sock, (struct sockaddr *)&server,sizeof(server))<<0))
    {
        printf("Problema bind()\n");
        exit(-1);
    }

    printf("Il server è pronto a comunicare\n");
    printf("Comandi [Sxyz] estratto conto, accetta solo da 0 a 9\n");
    printf("Comandi [Uxyz] permettere operazioni sul conto digitato con [Sxyz]\n");
    printf("Comandi [Vxyz] oppure [Pxyz] per versare oppure prelevare sul conto\n");
    printf("Comandi [Qxyz] disconettersi dal server\n");
    printf("xyz con valori da 0 a 99\n");

    listen(sock,1);

    clientLen=sizeof(client);


    //Comincio ad ascoltare le richieste
    while(1)
    {
       if((connectsock=accept(sock,(struct sockaddr *)&client,&clientLen))<0)
       {
           printf("Problema sull'accept()\n");
           exit(-1);
       }

       printf("Connessione stabilita sull'indirizzo ip: %s, e porta :%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));

       //Leggo, se il comando e' Q chiudo la socket senno' continuo ad ascoltare
       do
       {

       if(pronto==1)
       {
          if((retcode=write(connectsock,&risposta,strlen(risposta)))<0)
          {
           printf("Problema write()\n");
           exit(-1);
          }
           printf("Invio messaggio-- %d bytes\n",retcode);
           printf("Messaggio inviato %s",risposta);

          
        }

        if((retcode=read(connectsock,&msg,MAXBUF))<0)
        {
           printf("Problema read()\n");
           exit(-1);
        }
           
        msg[retcode]='\0';
        //Ripulisco il char risposta
        for(int i=0;i<=100;i++)
        risposta[i]='\0';

          

       } while (Checkstring(msg));
       
       
      close(sock);
      close(connectsock);

    }

   
}



int Checkstring(char * s)
{
    int valorec,v;
    int check;
    char conto[10];
    char valore[10];
    

    printf("Controllo la stringa:%s\n",s);

    //[Uxyz] controllo se ci sono le parentesi e se la stringa e' del tipo [Ux]
    if(s[0]=='[' && s[1]=='S' && s[strlen(s)-3]==']')
    {
       check=0;
      //il numero del conto
      memcpy(&conto,&s[2],sizeof(s)-1);
      valorec=atoi(conto);
      
      if(valorec>=0 && valorec <=9)
      {
        sprintf(risposta,"Il tuo conto e' il numero:%d con saldo:%d Euro\n",get_Conto(valorec),get_Saldo(valorec));
        pronto=1;
        check=1;
      }
      
      
      else 
      {
        sprintf(risposta,"Conto non valido, inserisci un valore tra 0 e 9\n",get_Conto(valorec),get_Saldo(valorec));
        pronto=1;
      }

      return 1;
      
    }

   
     
    //[Uxyz] controllo se ci sono le parentesi e se la stringa e' del tipo [Uxyz]
    printf("Check=%d",check);
    if(s[0]=='[' && (s[1]=='U' || s[1]=='V' || s[1]=='P') && s[strlen(s)-3]==']' && check==1)
    {
       printf("Ho notato che vuoi prelevare o versare con il conto numero:%d\n",valorec); 
       memcpy(&valore,&s[2],sizeof(s)-1);
       v=atoi(valore);

             
       if(s[1]=='V')
       {
         sprintf(risposta,"Hai versato %d Euro, adesso il tuo conto ha un saldo di:%d Euro\n",v,set_Versare(valorec,v));
         pronto=1;
         return 1;   
       }
       
       
       if(s[1]=='P')
       {
         sprintf(risposta,"Hai prelevato %d Euro, adesso il tuo conto ha un saldo di:%d Euro\n",v,set_Prelievo(valorec,v));
         pronto=1;
         return 1;  
       }

       else
       {
         sprintf(risposta,"Devi digitare [Vxyz] oppure [Pxyz]\n");
         pronto=1;
         return 1;
       }
       
            
       
    }

    


    //Uscire dal conto
    if(s[0]=='[' && s[1]=='Q' && s[strlen(s)-3]==']')
    {
      printf("Il cliente si è disconesso\n");
      return 0;
    }

    else
    {
         sprintf(risposta,"Hai scritto male oppure dovevi scrivere prima [Sxyz] se vuoi operare sul conto\n");
         pronto=1;
        
    }

    



    return 1;
    
}
