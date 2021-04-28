/*
* @file cliente.c
* @date 28/04/21
*
* @title Laboratorio de Sistemas Operativos- Segundo Parcial (Chat clientes-servidor)
* 
* @author	Juan Carlos Ruales Caicedo <juancarcaicedo@unicauca.edu.co>104617011700
* @author	Hector Esteban coral ordoñez <hectorcoral@unicauca.edu.co>104616011357
* @author	Eliana Andrea Camayo Ante <eacamyo@unicauca.edu.co>104616021725
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
	
	/**
	* Dominio=IPv4, socket de flujo, protocolo por defecto
	* */
	if ( (s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	/**
	* Limpiar y configurar la direcciÃ³n 
	* */
	memset(&addr, 0, sizeof(struct sockaddr_in));
	/**
	* Familia de direcciones IPv4
	* */
	addr.sin_family = AF_INET;
	/**
	* Puerto ingresado por el usuario con los bytes en orden de red
	* */
	addr.sin_port = htons(puerto);
	/**
	* Tomar la IP
	* */
	if (inet_aton(ip,&addr.sin_addr) == 0) {
		fprintf(stderr, "Error! Dirección invalida!\n");
		exit(EXIT_FAILURE);
	}
	/**
	* Conectar al servidor
	* */
	if (connect (s, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != 0) {
		perror("connect");
		exit(EXIT_FAILURE);
	}
	pthread_t read_m;
	/**
	* Creación del hilo
	**/
	pthread_create(&read_m,NULL,leer,&s);
	handle_connection(s);
	close(s);
	exit(EXIT_SUCCESS);
}

void handle_connection(int s) {
	char buf[MSGSIZE];
	int finished;
	message *men=(message*)malloc(sizeof(message));
	/**
	* Limpiar 
	**/
	memset(buf, 0, MSGSIZE);
	memset(men->message,0,MSGSIZE);
	read(s, men->message, MSGSIZE);
	printf("Mensaje del servidor: %s\n", men->message);
	finished = 0;
	
	while (!finished) {
		/**
		* Leer texto por la entrada estandar
		**/
		memset(buf, 0, MSGSIZE);
		memset(men->message,0,MSGSIZE);
		fgets(men->message,MSGSIZE,stdin);
		/**
		* Enviar texto al servidor
		**/
		if(write(s,men,sizeof(message))<0){
			continue;
		}
		/**
		* Si el usuario ingresa "/exit" cierra la terminal
		**/
		if(strncmp(men->message,"/exit",5) == 0){
			finished = 1;
		} 
	}
	close(s);
}
/**
* Leer 
**/
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
				/**
				* Si el usuario ingresa "/exit" cierra la terminal
				**/
				if(strncmp(men->message,"/exit",5)==0){
					exit(EXIT_SUCCESS);
					finished = 1;	
				}
			}
		}
		if(men->clientId == -1){
			/**
			* Mensaje que se muestra cuando el servidor da la bienvenida al chat
			**/
			printf("Mensaje del servidor: %s \n",men->message);
		}else{
			/**
			* Mensaje que se muestra cuando un cliente envia un mensaje, se especifica que cliente está enviando el mensaje
			**/
			printf("El cliente %d envia:  %s",men->clientId,men->message);
		}
		
	}
}
	
	
	
	
	
