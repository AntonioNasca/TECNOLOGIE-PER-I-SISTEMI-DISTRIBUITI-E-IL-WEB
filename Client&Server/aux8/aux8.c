#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define IP "90.147.166.230"
#define PORT 8080
#define RISPOSTA "GET /prova/08.aux\r\n"
#define MAXBUF 1024
#define MIN 22016
#define MAX 22023

int main(int argc, char **argv)
{
     char buffer[MAXBUF], risposta[MAXBUF], num[MAXBUF],supp[MAXBUF],risposta2[MAXBUF];
     struct sockaddr_in server1;
     int sock1, retcode, check=0,check2=0,n=0;


     if((sock1=socket(AF_INET,SOCK_STREAM,0))<0)
     {
         printf("Error socket()\n");
         exit(-1);
     }

     server1.sin_family=AF_INET;
     server1.sin_addr.s_addr=inet_addr(IP);
     server1.sin_port=htons(PORT);

     if((connect(sock1,(struct sockaddr*)&server1,sizeof(server1)))<0)
     {
         printf("Error connect()\n");
         exit(-1);
     }

     printf("Siamo collegati\n");

    write(sock1,&RISPOSTA,sizeof(RISPOSTA));

    int j=0;
    int q=0;
    int z=0;
    int f=0;
    while((retcode=read(sock1,&buffer,sizeof(buffer)))>0)
    {
        for(int i=0;i<retcode;i++)
        {
             if(buffer[i]=='\n')
             {
               j++;   

               if(j>=MIN && j<=MAX)
               {
                  for(int i=0;i<retcode;i++)
                  {
                      if(buffer[i]!='x' && check==0)
                      {risposta[q]=buffer[i]; q++;}
                    
                  }

                  check=1;
               }
               

               if(j==MAX+3828)
               {
                   for(int i=0;i<retcode;i++)
                   {
                   if(buffer[i]!='x' && buffer[i]>='0')
                   {
                     num[z]=buffer[i];
                     z++;

                      //Prelevare il numero e convertirlo in INT
                   }

                   num[z+1]='\0';
                  
                   }
                   check2=1;

               }

            if(check2==1)
            {
                int n2=atoi(num);
                if(j>=n2 && j<=n2+8)
                {
                   for(int i=0;i<retcode;i++)
                  {
                      if(buffer[i]!='x' && check2==1)
                      {risposta2[f]=buffer[i]; f++;}
                    
                  }

                  check2=0;
                }
            }             

             }

            
        }
      
 
    }

    printf("%s",risposta);
    printf("%s",risposta2);
    close(sock1);


}
