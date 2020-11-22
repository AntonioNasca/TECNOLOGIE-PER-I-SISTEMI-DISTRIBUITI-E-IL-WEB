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

char * mirror(char *a,int r);
char *lunghezza(char *a,int r);

void *t_A()
{
    pthread_mutex_lock(&mutex);
    char buffer[MAXBUF];
    struct sockaddr_in client,server;
    socklen_t ClientLen;
    int retcode,check=1,sock1,sock2;

    if((sock1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("tA>>Error socket()\n");
        exit(-1);
    }

    if((setsockopt(sock1,SOL_SOCKET,SO_REUSEADDR,&check,sizeof(check)))<0)
    {
        printf("tA>>Error setsockopt()\n");
        exit(-1);
    }

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);

    if((bind(sock1,(struct sockaddr*)&server,sizeof(server)))<0)
    {
        printf("tA>>Error bind()\n");
        exit(-1);
    }

    printf("tA>>Server pronto\n");

    listen(sock1,1);

    ClientLen=sizeof(client);

   
        if((sock2=accept(sock1,(struct sockaddr*)&client,&ClientLen))<0)
        {
          printf("tA>>Error accept()\n");
          exit(-1);
        }

        printf("tA>>Okay sono connesso con l'indirizzo IP : %s\n",inet_ntoa(client.sin_addr));

        retcode=read(sock2,&buffer,sizeof(buffer));

        buffer[retcode]='\0';


        printf("tA>>Ho ricevuto dal client: %s \n",buffer);

        sprintf(buffer,mirror(buffer,retcode));

        write(sock2,&buffer,retcode);

        close(sock2);

       close(sock1);

       pthread_mutex_unlock(&mutex);

       sleep(4);
}

void *t_B()
{
    pthread_mutex_lock(&mutex);
    char buffer[MAXBUF];
    struct sockaddr_in client,server;
    socklen_t ClientLen;
    int retcode,check=1,sock1,sock2;

    if((sock1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("tB>>Error socket()\n");
        exit(-1);
    }

    if((setsockopt(sock1,SOL_SOCKET,SO_REUSEADDR,&check,sizeof(check)))<0)
    {
        printf("tB>>Error setsockopt()\n");
        exit(-1);
    }

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(PORT);

    if((bind(sock1,(struct sockaddr*)&server,sizeof(server)))<0)
    {
        printf("tB>>Error bind()\n");
        exit(-1);
    }

    printf("tB>>Server pronto\n");

    listen(sock1,1);

    ClientLen=sizeof(client);

     if((sock2=accept(sock1,(struct sockaddr*)&client,&ClientLen))<0)
        {
          printf("tB>>Error accept()\n");
          exit(-1);
        }

        printf("tB>>Okay sono connesso con l'indirizzo IP : %s\n",inet_ntoa(client.sin_addr));

        retcode=read(sock2,&buffer,sizeof(buffer));

        buffer[retcode]='\0';


        printf("tB>>Ho ricevuto dal client: %s \n",buffer);

        sprintf(buffer,lunghezza(buffer,retcode));

        write(sock2,&buffer,retcode);

        close(sock2);

     close(sock1);

     pthread_mutex_unlock(&mutex);

     sleep(8);
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

char * mirror(char *a,int r)
{
     int l=r-2;

     char b[l];
     int z=0;

     for(int i=l;i!=-1;i--)
     {
         b[z]=a[i];
         z++;
     }

    strcpy(a,b);

     return a;
    
}

char *lunghezza(char *a,int r)
{
     int l=r-2;
     
     char b[l];
     int z=0;

     for(int i=0;i<l;i++)
     {
        b[z]='x';
        z++;
     }

     strncpy(a,b,l);

     return a;
}

