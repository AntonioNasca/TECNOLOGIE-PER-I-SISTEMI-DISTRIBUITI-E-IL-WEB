#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int n=0;
pthread_mutex_t mutex;
pthread_t tO,tE;
int counter1=0, counter2=0;
//gcc -o thread thread.c -lpthread


void *t_E()
{ 
    
    while(1)
    {
      usleep(200000);
      counter1++; 

      int c=(rand()%100);

      if(c%2==0)
      {
         pthread_mutex_lock(&mutex);
         n+=c;
         pthread_mutex_unlock(&mutex);
      }

      printf("tE: counter=%d, random_number=%d, n=%d\n",counter1,c,n);
      if ( counter1 >= 10 && n%2== 0 || counter1 >= 1000 )
        {
          printf("tE: sono stato terminato\n");
          pthread_exit(NULL);
        }
    } 

    
 
}

void *t_O()
{ 
    
    while(1)
    {
      usleep(200000);
      counter2++; 

      int c=(rand()%100);

      if(c%3==0)
      {
         pthread_mutex_lock(&mutex);
         n+=c;
         pthread_mutex_unlock(&mutex);
      }

      
      printf("t0: counter=%d, random_number=%d, n=%d\n",counter2,c,n);
      if ( counter2 >= 10 && n%3== 0 || counter2 >= 1000 )
        {
            printf("t0: sono stato terminato\n");
            pthread_exit(NULL);
        }

    } 

    
 
}


int main(int argc, char **argv)
{
     srand(time(NULL));
     printf("Inziamo\n");
     pthread_mutex_init(&mutex,NULL);

     pthread_create(&tO,NULL,&t_O,NULL);
     pthread_create(&tE,NULL,&t_E,NULL);

     pthread_join(tO,NULL);
     pthread_join(tE,NULL);

     printf("Finito\n");
}
