
#include<netinet/in.h>
#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>


/*Quien recibe conexiones (el servidor) enviar√° al cliente unmensaje de bienvenida, despu√©s del cual, el cliente deber√°enviar un mensaje, y el servidor deber√° recibir. Esteproceso terminar√° cuando en el servidor o en el cliente elusuario ingrese un mensaje con el texto /exit"#include<sys/socket.h>
*/




int c;
int s;
int main (int argc, char * argv[]){
	

		
	//1. CreaciÛn de direcciÛn
	struct sockaddr_in addr;
	
	int port;
	int valopc;
	socklen_t len;
	
	//dominio= IPv4, socket de flujo, protocolo por defecto
	if ( (s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}


	//inicializar puerto	
	port=0;
	if(argc > 1){ //Especificar un puerto
		port= atoi(argv[1]);
	}
	if(port <= 1023){
		fprintf(stderr, "Puerto %s invalido\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	
	
	//limpiar y configurar la direciÛn a enlazar 
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;	//Familia de direciones IPv4
	addr.sin_port = htons(port);// Puerto 1111 con los bytes en orden de red
	//TODO tomar la ip de los argumentos del main! 
	addr.sin_addr.s_addr = INADDR_ANY; //Asociar a la interfaz de red "activa", sin importar la IP Actual
	
	//2. Asociar el socket a una direcciÛn (IPv4)
	port=0;
	if (bind (s, (struct sockaddr *)& addr, sizeof(struct sockaddr_in)) != 0) {
		perror("bind");
		exit(EXIT_FAILURE);
		
	}
	//3. Informar al S.O que el socket esta configurado y listo para recibir conexiones "escuchando"
	if (listen(s, 10) != 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	printf("Socket listo, esperando conexiones\n");
	//4. Esperar a que un cliente se conecte
	c = accept(s, NULL, 0);
	if(c<0){
		perror("accept");
		exit(EXIT_FAILURE);
	}
	printf("ConexiÛn establecida\n");
	sleep(5);


	
	printf("ConexiÛn establecida\n");
	sleep(30);
	
	printf("Cerrando conexiÛn\n");
	close(c);
	close(s);
	exit(EXIT_SUCCESS);
			
}
	
	//TODO para permitir la conexion con multiples clientes,  elservidor debe crear // un hilo que atienda el socket c 
	
	


//TODO leer mensaje del cliente
			///TODO si el mensaje del cliente comienza por "/exit",
			//TODO leer texto por la entrada estandar
			//TODO enviar texto al cliente
			//TODO si el texto leido comienza por "/exit", terminar
			
