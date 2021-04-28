/*
* @file servidor.c
* @date 28/04/21
*
* @title Laboratorio de Sistemas Operativos- Segundo Parcial (Chat clientes-servidor)
* 
* @author	Juan Carlos Ruales Caicedo <juancarcaicedo@unicauca.edu.co>104617011700
* @author	Hector Esteban coral ordo�ez <hectorcoral@unicauca.edu.co>104616011357
* @author	Eliana Andrea Camayo Ante <eacamyo@unicauca.edu.co>104616021725
*/

#include <semaphore.h>
#include <pthread.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define MSGSIZE 512

typedef int socket_t;

/**
 * Variables del semaforo
 * */
typedef sem_t semaphore;
semaphore mutex;

/**
 * Funciones y variables del server
 * */
int s;
socket_t * clients;
/**
* Numero de clientes
**/
int nclients=0;
/**
* Tama�o del bufer
**/
int size = BUFSIZ;
/**
 * @brief Bandera para indicar el fin del servidor
 * */
int finished;

/**
 * @brief  Hilo para un cliente
 * @param arg Argumento al hilo del cliente 
 * */
void *handle_connection(void *arg);

/**
 * Funciones para cliente
 * */
void *leer(void * arg);
void adicionar(int c);
int buscar(int c);
void eliminar(int c);
void imprimir();
void MySignal(int sig);
/**
 * Funciones del semaforo
 * */
void down(semaphore *s);
void up(semaphore *s);

typedef struct{
	int clientId ;
	char message[MSGSIZE];
}message;
	
	int main(int argc, char * argv[]) {
		
		int c;
		/**
		* Creaci�n de direcci�n
		* */
		struct sockaddr_in addr;
		
		int valopc;
		socklen_t len;
		pthread_t hilo;
		
		/**
		* Si el usuario no ingresa el puerto, se mostrar� por consola el mensaje respectivo
		* */
		if(argc != 2){
			fprintf(stderr,"Por favor especificar el puerto para el servidor, recuerde que debe ser mayor a 1023\n");
			exit(EXIT_FAILURE);
		}
		
		
		/**
		* Inicializar puerto
		* */
		int puerto = atoi(argv[1]);
		
		/**
		* Si el usuario ingresa un puerto invalido, se mostrar�  por consola el mensaje respectivo
		* */
		if(puerto <= 1023){
			fprintf(stderr, "El puerto  %s es invalido\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		/**
		* Dominio=IPv4, socket de flujo, protocolo por defecto
		* */
		if ( (s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
			perror("socket");
			exit(EXIT_FAILURE);
		}
		valopc=1;
		len = sizeof(valopc);
		setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (void *)&valopc,len);
		/**
		* Limpiar y configurar la direcci�n a enlazar
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
		* Asociar a la interfaz de red "activa", sin importar la IP actual
		* */
		addr.sin_addr.s_addr = INADDR_ANY;
		
		/**
		* Asociar el socket a un direcci�n (IPv4)
		* */
		if (bind (s, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != 0) {
			perror("bind");
			exit(EXIT_FAILURE);
		}
		/**
		* Informar al S.O que el socket está configurado y listo para recibir conexciones "escuchando" 
		* */
		if (listen(s, 10) != 0) {
			perror("listen");
			exit(EXIT_FAILURE);
		}
		
		printf("Socket listo! Esperando conexiones...\n");
		//Recibir la conexion del cliente
		clients = (socket_t*)malloc(size * sizeof(socket_t));
		sem_init(&mutex,0,1);
		
		while(1){
			/**
			* ESperar que un cliente se conecte
			* */
			c = accept(s,NULL,0);
			if(c<0){
				perror("accept");
				exit(EXIT_FAILURE);
			}
			
			
			printf("Notificacion:Se ha conectado el cliente %d !\n",c);
			
			down(&mutex); //bloquear
			adicionar(c);
			up(&mutex); //desbloquear
			/*
			* Atender cliente: crear un hilo
			* */
			pthread_create(&hilo,NULL,handle_connection,&clients[nclients-1]);
		}		
		
		close(s);
		exit(EXIT_SUCCESS); 
	}

void *handle_connection(void *arg) {
	char buf[MSGSIZE];
	int c = *(int*)arg;
	
	/**
	* Enviar al cliente un mensaje de bienvenida
	* */
	strcpy(buf, "Bienvenido al chat!, escriba un mensaje.");
	write(c, buf, MSGSIZE);
	pthread_t read_m;
	pthread_create(&read_m,NULL,leer,&c);
	pthread_join(read_m,NULL);
	
	printf("Notificacion: El cliente %d se desconecto!\n",c);

	close(c);
}
/**
* Leer mensajes 
**/
void *leer(void * arg){
	char buf[MSGSIZE];
	int c = *(int*)arg;
	finished = 0;
	message *men =(message*)malloc(sizeof (message));
	while(!finished){
		memset(buf,0,MSGSIZE);
		memset(men->message,0,MSGSIZE);
		if(read(c,men,sizeof(message)) <= 0){
			down(&mutex);//bloquear
			eliminar(c);
			up(&mutex);//desploquear
			continue;
			/**
			* Si el usuario ingresa "/exit" cierra la terminal
			**/
		}else if(strncmp(men->message,"/exit",5)==0){
			down(&mutex); //bloquear
			eliminar(c);
			up(&mutex); //desbloquear
			finished = 1;
			
			close(c);
			
		}
		/**
		* Replicar el mensaje a todos los clientes
		* */
		men->clientId = c;
		if(nclients!=0){
			for(int j = 0;j<nclients;j++){
				if(clients[j] != c){
					if(write(clients[j],men,sizeof(message))<0){
						continue;
					}
				}
			}
		}
	}
}
	/**
	* Adicionar clientes
	**/
void adicionar(int c){
	
	if(nclients < size){
		clients[nclients] = c;
		nclients++;
	}else{
		int new_size = (size * 3)/2;
		if(new_size <= 1){
			new_size = 2;
		}
		socket_t * new_clients = (socket_t*)malloc(new_size * sizeof(socket_t));
		for(int i = 0;i < size; i++){
			new_clients[i] = clients[i];
		}
		free(clients);
		clients[nclients] = c;
		nclients++;
	}
}
	/**
	* Buscar clientes 
	**/
int buscar(int c){
	int pos;
	for(int i=0;i<nclients;i++){
		if(clients[i]=c){
			pos=i;
			break;
		}
	}
	return pos;
}
	/**
	* Eliminar clientes 
	**/
void eliminar(int c){
	if(nclients == 1){
		clients[0]=0;
		nclients = nclients-1;
	}else{
		for(int i=0;i<nclients;i++){
			if(clients[i]==c){
				clients[i]=0;
				while(i<nclients){
					clients[i]=clients[i+1];
					i++;
				}
				nclients = nclients-1;
				break;
			}
		}
	}
}

void imprimir(){
		for(int i = 0;i<nclients;i++){
		printf("%d\n",clients[i]);
	}
}

void down(semaphore * s){
	sem_wait(s);
}

void up(semaphore * s){
	sem_post(s);
}
