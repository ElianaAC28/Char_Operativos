#include <arpa/inet.h>
#include <netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<unistd.h>

/*Quien recibe conexiones (el servidor) enviará al cliente unmensaje de bienvenida, después del cual, el cliente deberáenviar un mensaje, y el servidor deberá recibir. Esteproceso terminará cuando en el servidor o en el cliente elusuario ingrese un mensaje con el texto /exit".
*/

#define MSGSIZE 512
void handle_connection(int c);

int main (int argc, char * argv[]){
	int s;
	int port;
	struct sockaddr_in addr;
	
	//Crear el socket
	//dominio=IPv4, socket de flujo, protocolo por defecto
	s= socket(PF_INET, SOCK_STREAM, 0);
	if ( s < 0) {
	perror("socket");
		exit(EXIT_FAILURE);
}
	//2. Asociar el socket a una direcci�n (IPv4)
	port=0;
	if(argc =3){
		port = atoi(argv[2]);
	}
	if(port<=0){
		fprintf(stderr, "Puerto %s invalido\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	//limpiar y configurar la direci�n a enlazar 
	memset(&addr, 0, sizeof(struct sockaddr_in));
	
	addr.sin_family = AF_INET;	//Familia de direciones IPv4
	addr.sin_port = htons(port);// Puerto 1111 con los bytes en orden de red
	//TODO tomar la IP de los argumentos del main!
	if (inet_aton("127.0.0.1",&addr.sin_addr) == 0) {
		fprintf(stderr, "Invalid address!\n");
		exit(EXIT_FAILURE);
	}
	//Conectar el servidor
if (connect (s, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) != 0) {
	perror("connect");
	exit(EXIT_FAILURE);
}
	handle_connection(s);
	close(s);
	exit(EXIT_SUCCESS);
	
	}

	void handle_connection(int s) {
	char buf[MSGSIZE];
	int finished;
//Recibir mensaje de bienvenida del servidor
	memset(buf, 0, MSGSIZE);
	read(s, buf, MSGSIZE);
	printf("Server sent: %s\n", buf);
	finished = 0;  
	while (!finished) {
//TODO leer texto por la entrada estandar
//TODO enviar texto al servidor
///TODO si el texto leido comienza por "/exit", terminar.
///TODO leer mensaje del servidor
//TODO si el mensaje del cliente comienza por "/exit",terminar.

	}
	close (s);
	}
