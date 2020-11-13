#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define PORT 8080 
#define IP "90.147.166.230"
#define MSG "GET /prova/14.aux\r\n"
#define MAXBUF 1024

char * validate(char *s);

int main(int argc, char ** argv)
{
    char buffer[MAXBUF];
    char riga1[MAXBUF],riga2[MAXBUF],riga3[MAXBUF],riga4[MAXBUF],riga5[MAXBUF],riga6[MAXBUF],riga7[MAXBUF],riga8[MAXBUF],riga9[MAXBUF];
    struct sockaddr_in server;
    int sock,retcode;
    
    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("Error socket()\n");
        exit(-1);
    }

    memset(&server,0,sizeof(server));
    server.sin_family=AF_INET,
    inet_aton(IP,&server.sin_addr);
    server.sin_port=htons(PORT);
    

    if((connect(sock,(struct sockaddr*)&server,sizeof(server))<0))
    {
        printf("Error connect()\n");
        exit(-1);
    }

    printf("Server pronto\n");

    printf("\nInvio al server:%s",MSG);
    write(sock,&MSG,sizeof(MSG));
    
    int z=0;
    int county=1; //Utilizzo county per passare da un char riga ad un altro fino a riga9

    while((retcode=read(sock,&buffer,sizeof(buffer)))>0)
    {
      for(int i=0;i<retcode;i++)
      {
         
        if((buffer[i]>='0' && buffer[i]<='9'))
        {
          //Stesso passaggio per 9 righe
          if(county==1 && z<8)
          {
              riga1[z]=buffer[i]; z++;

              if(z==8)
              {
                  z=0; county++;
              }
              
          }

          if(county==2 && z<8)
          {
              riga2[z]=buffer[i]; z++;

              if(z==8)
              {
                  z=0; county++;
              }
              
          }

          if(county==3 && z<8)
          {
              riga3[z]=buffer[i]; z++;

              if(z==8)
              {
                  z=0; county++;
              }
              
          }

          if(county==4 && z<8)
          {
              riga4[z]=buffer[i]; z++;

              if(z==8)
              {
                  z=0; county++;
              }
              
          }

          if(county==5 && z<8)
          {
              riga5[z]=buffer[i]; z++;

              if(z==8)
              {
                  z=0; county++;
              }
              
          }

          if(county==6 && z<8)
          {
              riga6[z]=buffer[i]; z++;

              if(z==8)
              {
                  z=0; county++;
              }
              
          }

          if(county==7 && z<8)
          {
              riga7[z]=buffer[i]; z++;

              if(z==8)
              {
                  z=0; county++;
              }
              
          }

          if(county==8 && z<8)
          {
              riga8[z]=buffer[i]; z++;

              if(z==8)
              {
                  z=0; county++;
              }
              
          }

          if(county==9 && z<8)
          {
              riga9[z]=buffer[i]; z++;

              if(z==8)
              {
                  z=0; county++;
              }
              
          }

          
        
        }
        
      }
    }

    riga1[8]='\0';
    
    //Richiamo il metodo validate() per ogni riga
    
    printf("\nVedo che cosa accade alle stringhe..\n");

    printf("---------------------------------\n");
    printf("Riga1: %s\n",validate(riga1));

    printf("---------------------------------\n");
    printf("Riga2: %s\n",validate(riga2));

    printf("---------------------------------\n");
    printf("Riga3: %s\n",validate(riga3));

    printf("---------------------------------\n");
    printf("Riga4: %s\n",validate(riga4));

    printf("---------------------------------\n");
    printf("Riga5: %s\n",validate(riga5));

    printf("---------------------------------\n");
    printf("Riga6: %s\n",validate(riga6));

    printf("---------------------------------\n");
    printf("Riga7: %s\n",validate(riga7));

    printf("---------------------------------\n");
    printf("Riga8: %s\n",validate(riga8));

    printf("---------------------------------\n");
    printf("Riga9: %s\n",validate(riga9));

    printf("---------------------------------\n");

    close(sock);

}

char * validate(char * s)
{

    int x,y;
    char suppx[10],suppy[20];
    int i=0,j=7;
    
    while(i<8)
    {
        suppx[0]=s[i];
        suppy[0]=s[j];

        x=atoi(suppx);
        y=atoi(suppy);

        i++;
        j--;

        if(x==y)s="La stringa non è permutabile";
    }

    
    return s;    
    
}
