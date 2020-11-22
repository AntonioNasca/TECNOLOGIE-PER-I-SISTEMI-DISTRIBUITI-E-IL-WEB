#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

pthread_mutex_t mutex;
pthread_cond_t condA,condB;
pthread_t tA,tB;

int n=0;
int c1=0;
int c2=0;

void * t_A()
{
    while(1)
    {
        pthread_mutex_lock(&mutex);

        int r=rand()%100;
        
         n+=r;
         c1++;

        if(n%2==0)
        {
          usleep(100000);
          printf("tA>> PARI, n=%d\n",n);
        }

        if(n%3==0 || (!&condA))
        {
            printf("tA>> DORMO\n");
             pthread_cond_signal(&condB);
            pthread_cond_wait(&condA,&mutex);
        }

        if(n>1000)
        {
            printf("tA>> ESCO\n");
            pthread_mutex_unlock(&mutex);
            pthread_cond_signal(&condB);
            pthread_exit(NULL);
        }


         pthread_mutex_unlock(&mutex);
    }
}

void * t_B()
{
    while(1)
    {
        pthread_mutex_lock(&mutex);

        int r=rand()%100;
        
         n+=r;
         c2++;

        if(n%3==0)
        {
          printf("tB>> DISPARI, n=%d\n",n);
          sleep(2);
        }

        if(n%2==0 || (!&condB))
        {
            printf("tB>> DORMO\n");
             pthread_cond_signal(&condA);
            pthread_cond_wait(&condB,&mutex);
        }

        if(n>1000)
        {
            printf("tB>> ESCO\n");
            pthread_cond_signal(&condA);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }

      
         pthread_mutex_unlock(&mutex);
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    pthread_mutex_init(&mutex,NULL);

    pthread_cond_init(&condA,NULL);
    pthread_cond_init(&condB,NULL);

    pthread_create(&tA,NULL,&t_A,NULL);
    pthread_create(&tB,NULL,&t_B,NULL);

    pthread_join(tA,NULL);
    pthread_join(tB,NULL);

    printf("Finito\n");
}
