#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

pthread_mutex_t mutex;
pthread_cond_t condA,condB;
pthread_t tA,tB;

int n=0;
int turn=0;

void *t_A()
{
   while(1)
   {
      pthread_mutex_lock(&mutex);
      int r=rand()%10;

      if(r%2==0)
      {
        n+=r;

        if(turn ==1) turn--;
        
        printf("tA>> n=%d, turn=%d\n",n,turn);

        if(turn ==0)
        {
           if(n>1000)
            {  
                printf("-------<<tA io Esco>>-------\n");
                
                //Mando un'altra volta il segnale, perchè se finisce prima tA devo comunque risvegliare tB
                pthread_cond_signal(&condB);
                pthread_mutex_unlock(&mutex);

                pthread_exit(NULL);
                
            }

           printf("Tocca a tB\n"); 
           pthread_cond_signal(&condB);
           pthread_cond_wait(&condA,&mutex);
           
        } 
      }
    
       pthread_mutex_unlock(&mutex);
   }
}

void *t_B()
{
    
   while(1)
   {
      pthread_mutex_lock(&mutex);
      int r=rand()%10;

      if(r%3==0)
      {
        n+=r;
        turn++;
        
        printf("tB>> n=%d, turn=%d\n",n,turn);

        if(turn ==1)
        {
            if(n>1000)
            {
                 printf("-------<<tB io Esco>>-------\n");

                //Mando un'altra volta il segnale, perchè se finisce prima tB devo comunque risvegliare tA
                pthread_cond_signal(&condA);
                pthread_mutex_unlock(&mutex);

                pthread_exit(NULL);
            }

           printf("Tocca a tA\n");
           pthread_cond_signal(&condA);
           pthread_cond_wait(&condB,&mutex);
           
        } 
      }

       pthread_mutex_unlock(&mutex);
   }
}


int main(int argc, char **argv)
{
    srand(time(NULL));

    pthread_mutex_init(&mutex,NULL);

    //Condizione per il thread t_A
    pthread_cond_init(&condA,NULL);

    //Condizione per il thread t_B
    pthread_cond_init(&condB,NULL);

    pthread_create(&tA,NULL,&t_A,NULL);
    pthread_create(&tB,NULL,&t_B,NULL);

    pthread_join(tA,NULL);
    pthread_join(tB,NULL);

    printf("Abbiamo finito finalmente!!\n");
}
