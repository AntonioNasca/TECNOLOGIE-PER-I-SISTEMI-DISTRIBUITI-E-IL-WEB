#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define MAXHLEN 128; 
#define MAXBUF 8*1024
#define FINGER 79

/* Per compilare:
Prima
cc -Wall -c -o mkaddr.o mkaddr.c
Poi
cc -Wall fingerc.c mkaddr.o -o fingerc */

int main(int argc, char * argv[])
{
	char buffer[MAXBUF];
	struct sockaddr_in addr; // server socket's address
    int s,retcode;	
    u_int16_t fport;
    
    
    
	
	printf("Benvenuto\n");
	
	//Importo l'indirizzo IP su mkaddr
	int mkaddr(struct sockaddr_in * skaddr, char * ipaddr, u_int16_t port);
	
	if(argc!=3 && argc!=4)
	{
		printf("Problema negli argomenti inseriti\n");
		printf("Prova a inserire ./fingerc directory.mit.edu smith\n");
		exit(1);
    }
    
    //Creo la socket
    if((s=socket(AF_INET, SOCK_STREAM,0))==-1)
    {
		printf("Problema nella socket\n");
		exit(-1);
	}
	 
	fport= argc==4 ? atoi(argv[3]) : FINGER;
	
	mkaddr(&addr, argv[1], fport);  // costruisce l'indirizzo del server (IP/nome in argv[1])
	
	
	//Mi connetto al server
	if(connect(s, (struct sockaddr *)&addr,sizeof(addr))==-1)
	{
		printf("Errore nella connessione\n");
		exit(-2);
	}
	
    //Preparo la stringa per il server "smith"
    sprintf(buffer,"%s\n",argv[2]);
    
    //Scrivo al server
    if(write(s,buffer,strlen(buffer))==-1)
    {
		printf("Errore nell'inviare il messaggio\n");
		exit(-3);
	}
	
	//Leggo il messaggio ricevuto dal server
	while((retcode=read(s,buffer,MAXBUF))!=0)
	{
		if(retcode==-1)
		{
			printf("Problemi sulla socket\n"); exit(4);
 	    }
 	    
 	   fprintf(stderr,"Numero di byte letti %d\n",retcode);
 	   write(STDOUT_FILENO,buffer,retcode);	
		
	}
	
	fprintf(stderr,"Uscita dalla connessione con il server\n");
	
	close(s); exit(0);
	
	
	
}
