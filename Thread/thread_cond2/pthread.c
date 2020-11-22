#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_t tA,tB;

int n=0;
int c=0;

void *t_A()
{
   while(1)
   {
       pthread_mutex_lock(&mutex);


       int r=rand()%100;

        c++;

        if(c>100)
       {
           printf("tA>>Esco\n");
           pthread_mutex_unlock(&mutex);
           pthread_exit(NULL);
       }

       if(r%2==0)
       {
           usleep(100000);
           n+=r;
           printf("tA>> n=%d, count=%d\n",n,c);
       }

       if(r%3==0 || (!&cond))
       {
           printf("tA>>Dormo\n");
           
           pthread_cond_wait(&cond,&mutex);
           
       }



       pthread_mutex_unlock(&mutex);
   }
}

void *t_B()
{  
    while(1)
    {
       pthread_mutex_lock(&mutex);

       if(c>100)
       {
            printf("tA>>Esco\n");
           pthread_mutex_unlock(&mutex);
           pthread_exit(NULL);
       }
        
        printf("tB>> Sveglio tA\n");

        pthread_cond_signal(&cond);
         
        pthread_mutex_unlock(&mutex);
          usleep(300000);
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_create(&tA,NULL,&t_A,NULL);
    pthread_create(&tB,NULL,&t_B,NULL);

    pthread_join(tA,NULL);
    pthread_join(tB,NULL);

    printf("Abbiamo finito\n");
}
