/*
	Programa cliente del chat
*/

#include <pthread.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


#define MSGSIZE 512
void handle_connection(int c);
void *leer(void * arg);

typedef struct{
	int clientId;
	char message[MSGSIZE];
}message;

int main(int argc, char * argv[]) {
	int s;
	int puerto;
	char *ip;
	
	if(argc != 3){
		fprintf(stderr,"Por favor especificar el puerto y el ip para le cliente\n");
		exit(EXIT_FAILURE);
	}

	puerto = atoi(argv[1]);
	ip = argv[2];
	struct sockaddr_in addr;
	
	if ( (s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(puerto);
	//tomar la IP 
	if (inet_aton(ip,&addr.sin_addr) == 0) {
		fprintf(stderr, "Invalid address!\n");
		exit(EXIT_FAILURE);
	}
	/**
	 * Conectar al servidor
	 * */
	if (connect (s, (struct sockaddr *)&addr, sizeof(struct
		sockaddr_in)) != 0) {
		perror("connect");
		exit(EXIT_FAILURE);
	}
	pthread_t read_m;
	pthread_create(&read_m,NULL,leer,&s);
	handle_connection(s);
	close(s);
	exit(EXIT_SUCCESS);
}

void handle_connection(int s) {
	char buf[MSGSIZE];
	int finished;
	message *men=(message*)malloc(sizeof(message));
	memset(buf, 0, MSGSIZE);
	memset(men->message,0,MSGSIZE);
	read(s, men->message, MSGSIZE);
	printf("Mensaje del servidor: %s\n", men->message);
	finished = 0;
	
	while (!finished) {
		//TODO leer texto por la entrada estandar
		memset(buf, 0, MSGSIZE);
		memset(men->message,0,MSGSIZE);
		fgets(men->message,MSGSIZE,stdin);
		//TODO enviar texto al servidor
		if(write(s,men,sizeof(message))<0){
			continue;
		}

		if(strncmp(men->message,"/exit",5) == 0){
			finished = 1;
		} 
	}
	close(s);
}

void *leer(void * arg){
	char buf[MSGSIZE];
	int finished;
	int s =*(int*)arg;
	finished = 0;
	message *men=(message*)malloc(sizeof(message));
	while(!finished){
		memset(buf,0,MSGSIZE);
		memset(men->message,0,MSGSIZE);
		if(read(s,men,sizeof(message)) <= 0){
			exit(EXIT_SUCCESS);
		}else{
			if(men->clientId == -1){
				if(strncmp(men->message,"/exit",5)==0){
					exit(EXIT_SUCCESS);
					finished = 1;	
				}
			}
		}
		if(men->clientId == -1){
			printf("Mensaje del servidor: %s \n",men->message);
		}else{
			printf("El cliente %d envia:  %s",men->clientId,men->message);
		}
		
	}
}





