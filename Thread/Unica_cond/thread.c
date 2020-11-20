#include <stdio.h>  //orario 07:25
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_t t1,t2;

void *fun_1()
{
    while(1)
    {
        pthread_mutex_lock(&mutex);

        int m=rand()%100;
   
       
        if((m%3==0) || (!&cond))
        {
          printf("t1>>Attendo..\n");
          pthread_cond_wait(&cond,&mutex);
        }
     

         if(m%2==0)
        {
            usleep(300000);
            printf("t1>> m=%d\n",m);
            pthread_mutex_unlock(&mutex);
        }

        pthread_mutex_unlock(&mutex);
     

        
    }
}

void *fun_2()
{
    while(1)
    {
        
        pthread_mutex_lock(&mutex);
        printf("t2>>> Sveglio t1\n");
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(8);
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_create(&t1,NULL,&fun_1,NULL);
    pthread_create(&t2,NULL,&fun_2,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    printf("Ho finito\n");
    
}
