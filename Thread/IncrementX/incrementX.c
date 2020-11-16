#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;
pthread_t tA,tB;

int x=0;

void *t_A()
{
  usleep(rand()%1000);
  int cnt=0;

  while(1)
  {
     pthread_mutex_lock(&mutex);
     cnt++;
     x++;
    
     if(x>=299)
     {
         printf("------------------------\n");
         printf("tA finito>> cnt=%d\n",cnt);
         pthread_mutex_unlock(&mutex);
         pthread_exit(NULL);
     }
     printf("tA>> cnt=%d\n",cnt);

     pthread_mutex_unlock(&mutex);
  }
    
}

void *t_B()
{
  usleep(rand()%1000);
  int cnt=0;

  while(1)
  {
     pthread_mutex_lock(&mutex);
     cnt++;
     x++;
   
     if(x>=299)
     {
         printf("------------------------\n");
         printf("tB finito>> cnt=%d\n",cnt);
         pthread_mutex_unlock(&mutex);
         pthread_exit(NULL);
     }

      printf("tB>> cnt=%d\n",cnt);

     pthread_mutex_unlock(&mutex);
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
}
