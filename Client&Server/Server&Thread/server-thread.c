#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <stdio.h>

#define PORT 3333
#define MAXBUF 1024
#define IP "127.0.0.1"
#define G "[ciao]"
#define SB "[sbagloata"

pthread_mutex_t mutex;
pthread_t tA,tB;


void *t_A()
{

    pthread_mutex_lock(&mutex);
    printf("------------------------\n");

    char buffer[MAXBUF];
    struct sockaddr_in server;
    int sock,retcode;
    
   
    sprintf(buffer,G,sizeof(G));


    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    { 
        printf("t1>> Error socket\n");
        exit(-1);
    }

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(IP);
    server.sin_port=htons(PORT);

    if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0)
    {
        printf("t1>> Error connect\n");
        exit(-1);
    }

    printf("t1>> Sono connesso al server\n");

    printf("t1>> sto inviando al server:%s\n",buffer);

    write(sock,buffer,sizeof(G));


    retcode=read(sock,&buffer,sizeof(buffer));

    buffer[retcode]='\0';

    printf("t1>>Ho ricevuto: %s",buffer);
    printf("------------------------\n");

    pthread_mutex_unlock(&mutex);

}

void *t_B()
{


    pthread_mutex_lock(&mutex);
    printf("------------------------\n");

    char buffer[MAXBUF];
    struct sockaddr_in server;
    int sock,retcode;

    sprintf(buffer,"sbagliata]");

    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    { 
        printf("tB>> Error socket\n");
        exit(-1);
    }

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(IP);
    server.sin_port=htons(PORT);

    if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0)
    {
        printf("tB>> Error connect\n");
        exit(-1);
    }

    printf("Sono connesso al server\n");

    printf("Sto inviando al server: %s\n",buffer);


    write(sock,buffer,sizeof(SB));


    retcode=read(sock,&buffer,sizeof(buffer));

    buffer[retcode]='\0';

    printf("tB>> Ho ricevuto: %s",buffer);

    printf("------------------------\n");

    pthread_mutex_unlock(&mutex);

}
int main(int argc, char **argv)
{

     srand(time(NULL));


     pthread_mutex_init(&mutex,NULL);

     pthread_create(&tA,NULL,&t_A,NULL);
     pthread_create(&tB,NULL,&t_B,NULL);

     pthread_join(tA,NULL);
     pthread_join(tB,NULL);

     printf("Finito\n");
    
}
