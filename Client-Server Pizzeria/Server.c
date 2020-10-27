#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 39999
#define MAXBUF 2048

#include  "Prenotazioni.h"

void Answer(char *, char *, int);
int Checkstring(char *);

int main(int argc, char **argv)
{
    char msg[MAXBUF];
    char answer[50];
    struct sockaddr_in client,server;
    socklen_t clientLen;
    int retcode,s, check=1,sock,connectsock;
    char * NomePizza;
    int quantita;


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

       //Leggo
       if((retcode=read(connectsock,&msg,MAXBUF))<0)
       {
           printf("Problema read()\n");
           exit(-1);
       }

       msg[retcode]='\0';

       if(Checkstring(msg)==1)
       {
           NomePizza=strtok(msg,",");
           quantita=atoi(strtok(NULL,","));
       }

       else
       {
         printf("Problema sulla ricezione del messaggio\n");
         close(connectsock);
         continue;
       }

       printf("Ho ricevuto: %s %d\n",NomePizza, quantita);

       Answer(answer,NomePizza,quantita);

       if((retcode=write(connectsock,&answer,strlen(answer)))<0)
       {
           printf("Problema write()\n");
           exit(-1);
       }

       printf("Invio messaggio-- %d bytes Messaggio:%s\n",retcode,answer);

       close(connectsock);


    }

    close(sock);


}

void Answer(char * answer, char *nomep, int q)
{
    switch (getDisponibilita(nomep,q))
    {

    case 0: sprintf(answer,"Non ho travato l'ordine mi dispiace\n"); break;

    case 1: sprintf(answer,"Trovato l'ordine stanno per arrivare le pizze\n"); break;

    default: sprintf(answer,"Prova a scrivere bene il tuo ordinwe, perche' non l'abbiamo trovato\n"); break;
    
    }
    
}
int Checkstring(char * s)
{
    printf("Controllo la stringa\n");

    for(int i=0;i<strlen(s);i++)
    {
        if(s[i]==',' && s[i+1]>='0' && s[i+1]<='9')
        return 1;
        
    }

    return 0;
}