#include <stdio.h> /*07:45*/
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>

#define PORT 3333

pthread_mutex_t mutex;
pthread_t tA,tB;

int fn(char *a,int r);
char *pari_dispari(int r);

void *t_A()
{
     pthread_mutex_lock(&mutex);
    char buffer[1024];
    struct sockaddr_in server,client;
    socklen_t ClientLen; 
    int retcode,sock1,sock2,check=1;

    if((sock1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("tA>>Error socket()\n");
        exit(-1);
    }

    if((setsockopt(sock1,SOL_SOCKET,SO_REUSEADDR, &check, sizeof(check))) < 0)
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

        printf("tA>>Connessione stabilita con l'indirizzo IP: %s\n",inet_ntoa(client.sin_addr));

        retcode=read(sock2,&buffer,sizeof(buffer));

        printf("tA>>Ho ricevuto dal client: %s\n",buffer);

        sprintf(buffer,"tA>>Somma dei caratteri:%d\n",fn(buffer,retcode));

         printf("tA>>Attendi...\n");
        sleep(7);
        
        printf("tA>>Ho inviato al client: %s\n",buffer);
      
        write(sock2,&buffer,retcode+22);

        close(sock2);
    

    close(sock1);

        pthread_mutex_unlock(&mutex);
}

void *t_B()
{
   pthread_mutex_lock(&mutex);
    char buffer[1024];
    struct sockaddr_in server,client;
    socklen_t ClientLen; 
    int retcode,sock1,sock2,check=1;

    if((sock1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("tB>>Error socket()\n");
        exit(-1);
    }

    if((setsockopt(sock1,SOL_SOCKET,SO_REUSEADDR, &check, sizeof(check))) < 0)
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

        printf("tB>>Connessione stabilita con l'indirizzo IP: %s\n",inet_ntoa(client.sin_addr));

        retcode=read(sock2,&buffer,sizeof(buffer));

        printf("tB>>Ho ricevuto dal client: %s\n",buffer);

        sprintf(buffer,pari_dispari(retcode));
        
        printf("tB>>Attendi...\n");
        sleep(5);
        
        printf("tB>>Ho inviato al client: %s\n",buffer);

        write(sock2,&buffer,100);

        close(sock2);
    

    close(sock1);

        pthread_mutex_unlock(&mutex);
}

int main(int argc,char **argv)
{

     if(argc<1)
    {
        printf("Errore di stampa, scrivere ./server\n");
        exit(-1);
    }

    pthread_mutex_init(&mutex,NULL);

    pthread_create(&tA,NULL,&t_A,NULL);
    pthread_create(&tB,NULL,&t_B,NULL);


    pthread_join(tA,NULL);
    pthread_join(tB,NULL);

    printf("Finito\n");

}

int fn(char *a,int r)
{
   char b[0];
   
   int n=0,sum=0;

   for(int i=0;i<r-2;i++)
   {
      n=(int)(a[i]);
      sum+=n;
   }

  
   return sum;
}

char * pari_dispari(int r)
{
    if(r%2==0)
    return "la tua stringa ha lunghezza Pari\n";

    else
    return "la tua stringa ha lunghezza Dispari\n";
    
}

