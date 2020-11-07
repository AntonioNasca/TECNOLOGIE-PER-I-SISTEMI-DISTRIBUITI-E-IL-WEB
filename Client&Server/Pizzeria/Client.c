#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 39999
#define MAXBUF 1024

/*
   make Pclient
   make Prenotazioni.o
   make Pserver.o
   cc -o Pserver Pserver.c Prenotazioni.o
*/

int main(int argc, char ** argv)
{ 
   char * msg=argv[2];
   char answer[100];
   struct sockaddr_in sock;
   int retcode,s;

   if(argc!=3)
   {
       printf("Problema nella sintassi indicata\n");
       printf("Provare ./Client 127.0.0.1 'Margherita',5\n");
       exit(-1);
   }

   if((s=socket(AF_INET,SOCK_STREAM,0))<0)
   {
       printf("Problema sulla SOCKET()\n");
       exit(-1);
   }

   //Creo l'indirizzo
   memset(&sock,0,sizeof(s));
   sock.sin_family=AF_INET;
   sock.sin_addr.s_addr=inet_addr(argv[1]);
   sock.sin_port=htons(PORT);

   if((connect(s,(struct sockaddr  *)&sock, sizeof(sock)))<0)
   {
       printf("Problema sulla CONNECT()\n");
       exit(-1);
   }

   if((retcode=write(s,msg,strlen(msg)+1))<0)
   {
       printf("Problema sulla WRITE()\n");
       exit(-1);
   }

   printf("Invio il messaggio %s\n",msg);

   if((retcode=read(s,answer,100)<0))
   {
       printf("Problema sulla READ()\n");
       exit(-1);
   }

   printf("Ho ricevuto --%d bytes ---- R.Server: %s\n",retcode,answer);

   close(s);



}
