#include <stdio.h> /*07:45*/
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>

#define PORT 3333
#define IP "127.0.0.1"
#define MSG "ciaocomeva"
#define MSG2 "eccomi"

pthread_mutex_t mutex;
pthread_t tA,tB;

void *t_A()
{
     pthread_mutex_lock(&mutex);
    char buffer[1024];
    struct sockaddr_in server;
    int retcode,sock;


    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("tA>>Error socket()\n");
        exit(-1);
    }


    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(IP);
    server.sin_port=htons(PORT);

    if((connect(sock,(struct sockaddr*)&server,sizeof(server)))<0)
    {
        printf("tA>>Error connect()\n");
        exit(-1);
    }

   
    printf("tA>>Connessione stabilita con il server e l'indirizzo IP e': %s\n",inet_ntoa(server.sin_addr));
    
     printf("tA>>Ho inviato al server: %s\n",MSG);

     write(sock,&MSG,sizeof(MSG));

     retcode=read(sock,&buffer,sizeof(buffer));

      printf("tA>>Ho ricevuto dal server: %s\n",buffer);


        close(sock);

        pthread_mutex_unlock(&mutex);
}

void *t_B()
{
   pthread_mutex_lock(&mutex);
    char buffer[1024];
    struct sockaddr_in server;
    int retcode,sock;


    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("tB>>Error socket()\n");
        exit(-1);
    }


    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(IP);
    server.sin_port=htons(PORT);

    if((connect(sock,(struct sockaddr*)&server,sizeof(server)))<0)
    {
        printf("tB>>Error connect()\n");
        exit(-1);
    }

   
    printf("tB>>Connessione stabilita con il server e l'indirizzo IP e': %s\n",inet_ntoa(server.sin_addr));
    
     printf("tB>>Ho inviato al server: %s\n",MSG2);

     write(sock,&MSG2,sizeof(MSG2));

     retcode=read(sock,&buffer,sizeof(buffer));

      printf("tB>>Ho ricevuto dal server: %s\n",buffer);


        close(sock);

        pthread_mutex_unlock(&mutex);
}

int main(int argc,char **argv)
{

     if(argc<1)
    {
        printf("Errore di stampa, scrivere ./client\n");
        exit(-1);
    }

    pthread_mutex_init(&mutex,NULL);

    pthread_create(&tA,NULL,&t_A,NULL);
    pthread_create(&tB,NULL,&t_B,NULL);


    pthread_join(tA,NULL);
    pthread_join(tB,NULL);

    printf("Finito\n");

}

