#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAXBUF 1024
#define IP "90.147.166.230"
#define PORT 8080
#define RISPOSTA "GET /prova/07.aux\r\n"

int main(int argc, char **argv)
{
    char buffer[MAXBUF], risposta[MAXBUF];
    struct sockaddr_in server1,server2;
    int sock1,sock2,retcode,check=0;

    if((sock1=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("Error socket1()\n");
        exit(-1);
    }

    server1.sin_family=AF_INET;
    server1.sin_addr.s_addr=inet_addr(IP);
    server1.sin_port=htons(PORT);

    if((connect(sock1,(struct sockaddr*)&server1,sizeof(server1)))<0)
    {
        printf("Error connect1()\n");
        exit(-1);
    }


    


    write(sock1,&RISPOSTA,sizeof(RISPOSTA));

    printf("Ho inviato al server %s:%s",IP,RISPOSTA);

    int j=0;
    int supp=0;
    while((retcode=read(sock1,&buffer,sizeof(buffer)))>0)
    {
    
        for(int i=0;i<=retcode;i++)
        {
             int byte=0;

             if(buffer[i]=='-' && check==0)
             {
                byte=i;

                //Memorizzo fino a 32 byte
                for(int j=0;j<=32;j++)
                {
                     risposta[j]=buffer[byte];
                     byte++;

                     if(j==32)
                      {
                          risposta[j+1]='\r';
                          risposta[j+2]='\n';
                          risposta[j+3]='\0';
                      }
                }

                check=1;
                   
            }
                
            
        }
                
        
         
    }
     
    printf("%s",risposta);
    close(sock1);
}
