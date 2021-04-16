#include <netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>

/*Quien recibe conexiones (el servidor) enviará al cliente unmensaje de bienvenida, después del cual, el cliente deberáenviar un mensaje, y el servidor deberá recibir. Esteproceso terminará cuando en el servidor o en el cliente elusuario ingrese un mensaje con el texto /exit"#include<sys/socket.h>
*/


#define MSGSIZE 512
void handle_connection(int c);

int main (int argc, char * argv[]){

	int s ;
	int c;
	struct sockaddr_in addr;
	int valopc;
	socklen_t len;
  if ( (s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	valopc=1;
	len=sizeof(valopc);
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (void*)&valopc,len);
	memset(&addr, 0, sizeof(struct sockaddr_in));
		memset(&addr, 0, sizeof(struct sockaddr_in));

		 addr.sin_family = AF_INET;	
		 addr.sin_port = htons(50000);//TODO argumento del main!
	 //TODO tomar la ip de los argumentos del main! 
	   addr.sin_addr.s_addr = INADDR_ANY;
		 if (bind (s, (struct sockaddr *)& addr, sizeof(struct sockaddr_in)) != 0) {
		 		perror("bind");
				exit(EXIT_FAILURE);

		 }
		 if (listen(s, 10) != 0) {
			 perror("bind");
	   	exit(EXIT_FAILURE);
		 }
//Recibir la conexion del cliente
		c = accept(s, NULL, 0);

//TODO para permitir la conexion con multiples clientes,  elservidor debe crear // un hilo que atienda el socket c 
//
//atender la conexion 
		handle_connection(c);
		close(s);
		exit(EXIT_SUCCESS);
}
void handle_connection(int c) {
	char buf [MSGSIZE];
	int finished;
	//Enviar al cliente un mensaje de bienvenida
	strcpy(buf, "Hello!");
	write(c, buf, MSGSIZE);
	finished = 0;
	while (!finished) {
		//TODO leer mensaje del cliente
		///TODO si el mensaje del cliente comienza por "/exit",
		//TODO leer texto por la entrada estandar
		//TODO enviar texto al cliente
		//TODO si el texto leido comienza por "/exit", terminar
	}
	close(c);
}

