#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;
pthread_t tA,tB;


#define PORT 3333
#define MAXBUF 1024
#define MSG "ciao" //In questa si farà il mirror
#define MSG2 "eCCOMI" //In questa si farà il metodo lunghezza 

void *t_A()
{
    while(1)
    {
      usleep(100000);
      pthread_mutex_lock(&mutex);

      char buffer[MAXBUF];
      struct sockaddr_in server;
      socklen_t ClientLen;
      int retcode,sock1;

    if((sock1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("tA>>Error socket()\n");
        exit(-1);
    }

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);


    if((connect(sock1,(struct sockaddr*)&server,sizeof(server)))<0)
    {
        printf("tA>>Error connect()\n");
        exit(-1);
    }

    
    printf("tA>>Client pronto\n");


    write(sock1,&MSG,sizeof(MSG));
    printf("tA>>Ho inviato il messaggio %s\n",MSG);

    read(sock1,&buffer,sizeof(buffer));


    printf("tA>>Messaggio ricevuto dal server:%s\n",buffer);

     pthread_mutex_unlock(&mutex);

      sleep(10);

   }
}

void *t_B()
{
     while(1)
    {
     
      pthread_mutex_lock(&mutex);

      char buffer[MAXBUF];
      struct sockaddr_in server;
      socklen_t ClientLen;
      int retcode,sock1;

    if((sock1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("tB>>Error socket()\n");
        exit(-1);
    }

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);


    if((connect(sock1,(struct sockaddr*)&server,sizeof(server)))<0)
    {
        printf("tB>>Error connect()\n");
        exit(-1);
    }

    
    printf("tB>>Client pronto\n");


    write(sock1,&MSG,sizeof(MSG));
    printf("tB>>Ho inviato il messaggio %s\n",MSG);

    read(sock1,&buffer,sizeof(buffer));


    printf("tB>>Messaggio ricevuto dal server:%s\n",buffer);

     pthread_mutex_unlock(&mutex);

      sleep(10);


        
    }
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
