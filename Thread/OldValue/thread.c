#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

pthread_mutex_t mutex;
pthread_t tA,tB,tC;
int sample=50;

void *t_A()
{
    int c,ra;
    while(1)
    {
         pthread_mutex_lock(&mutex);
         ra=rand()%90;
         
         if(ra>=10 && ra<=90)
        {
          //Notare che metto unlock dentro l'if perchè se la variabile ra=sample, 
          //deve dare la possiblità ad altri thread di utilizzare ra,c e sample
          //Stessa cosa se ra non è compresa tra 10 e 90.

          if(ra==sample)
          {
            sample=c; printf("t_A Sono uscito\n");  pthread_mutex_unlock(&mutex);   pthread_exit(NULL);
          }

          c=ra;
          printf("Sono il thread t_A, sample valeva %d, adesso vale %d\n",sample,c);
        }

         pthread_mutex_unlock(&mutex);
    }
}

void *t_B()
{
    int c,ra;
    while(1)
    {
         pthread_mutex_lock(&mutex);
         ra=rand()%90;
         
         if(ra>=10 && ra<=90)
        {
          if(ra==sample)
          {
            sample=c; printf("t_B Sono uscito\n");  pthread_mutex_unlock(&mutex);   pthread_exit(NULL);
          }

          c=ra;
          printf("Sono il thread t_B, sample valeva %d, adesso vale %d\n",sample,c);
        }

         pthread_mutex_unlock(&mutex);
    }
}



void *t_C()
{
    int c,ra;

    while(1)
    {
         pthread_mutex_lock(&mutex);
         ra=rand()%90;
         
         if(ra>=10 && ra<=90)
        {
          if(ra==sample)
          {
             sample=c; printf("t_C Sono uscito\n");  pthread_mutex_unlock(&mutex);   pthread_exit(NULL);
          }

          c=ra;
          printf("Sono il thread t_C, sample valeva %d, adesso vale %d\n",sample,c);
          
          
        }
    pthread_mutex_unlock(&mutex);


    }
}



int main(int argc, char **argv)
{
    printf("Iniziamo\n");

    srand(time(NULL));

    pthread_mutex_init(&mutex,NULL);

    pthread_create(&tA,NULL,&t_A,NULL);
    pthread_create(&tB,NULL,&t_B,NULL);
    pthread_create(&tC,NULL,&t_C,NULL);

    pthread_join(tA,NULL);
    pthread_join(tB,NULL);
    pthread_join(tC,NULL);


    printf("Okay abbiamo finito ecco il valore finale di sample %d\n",sample);
    return 0;

}


