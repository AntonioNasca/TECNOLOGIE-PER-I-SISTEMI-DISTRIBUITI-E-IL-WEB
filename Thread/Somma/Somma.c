#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;
pthread_t tA,tB;
int sum=0;
int p=0,d=0;

void * t_A()
{
   usleep(20000);
   int count=0;
 while(1)
 {  
   pthread_mutex_lock(&mutex);
   count++;
   int r=rand()%10;
   if(r%2==0)
   {
       p++;
       sum+=r;
   }
   
   printf("t_A>> r=%d, count=%d,sum=%d\n",r,count,sum);
   if(count>=1000 && sum%2==0 || sum>=3000)
   {
       pthread_mutex_unlock(&mutex);
       pthread_exit(NULL);
   }

   pthread_mutex_unlock(&mutex);
 }

}

void * t_B()
{
   usleep(20000);
   int count2=0;
 while(1)
 {  
   pthread_mutex_lock(&mutex);
   count2++;
   int r=rand()%10;
   if(r%3==0)
   {
       d++;
       sum+=r;
   }
   
   printf("t_B>> r=%d, count=%d,sum=%d\n",r,count2,sum);
   if((count2>=1000 && sum%3==0 || sum>=3000))
   {
       pthread_mutex_unlock(&mutex);
       pthread_exit(NULL);
   }

   pthread_mutex_unlock(&mutex);
 }

}


int main(int argc, char ** argv)
{
  printf("Iniziamo\n");
  srand(time(NULL));


  pthread_mutex_init(&mutex,NULL);

  pthread_create(&tA,NULL,&t_A,NULL);
  pthread_create(&tB,NULL,&t_B,NULL);

  pthread_join(tA,NULL);
  pthread_join(tB,NULL);

  printf("-----------------------------------\n",sum);


  printf("Finito l'ultima somma è: %d\n",sum);
  printf("I numeri Random pari sono: [%d]\nI numeri Random dispari sono: [%d]\n",p,d);



}
