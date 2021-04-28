ELABORADO POR: 

Juan Carlos Ruales Caicedo <juancarcaicedo@unicauca.edu.co>104617011700
Hector Esteban coral ordoñez <hectorcoral@unicauca.edu.co>104616011357
Eliana Andrea Camayo Ante <eacamayo@unicauca.edu.co>104616021725
   
#Implementacion de chat entre un servidor y multiples clientes, como proyecto de segundo corte del curso Sistema Operativos 2021.1

#Planteamiento del problema

Se deberá desarrollar dos programas en C que implementen la funcionalidad de un chat simple entre dos 
sistemas conectados a la red, usando sockets.
Uno de los extermos actuará como cliente, y el otro como servidor. Quien recibeconexiones (el servidor) enviará al cliente un mensaje 
de bienvenida, después del cual, el cliente deberá enviar un mensaje, y el servidor deberá recibir. Este proceso terminará cuando en 
en el cliente el usuario ingrese un mensaje con el texto /exit".
Se debe permitir la comunicación entre un servidor y múltiples clientes clientes. Además, los clientes también podrán comunicarse entre sí, a través
del servidor.

#Codigo base
Se tomo de referencia algunos fragmentos de codigo dados en clase y material expuesto por el docente.

#Compilación y ejecución del programa

Paso (1): Ejecutar el servidor con el comando ./servidor seguido del puerto deseado, recuerde que debe ser mayor a 1023. p.ej: ./servidor 1235
		(-) Si el usuario no ingresa un servidor valido, el sistema le notificará el mensaje respectivo.
          	(+) Si el usuario ingresa un servidor valido, el sistema mostrará un mensaje "¡Sockect lsito! Esperando conexiones" indicando que al usuario
		que ya puede conectar un cliente.
Paso (2): Conectar un cliente con el comando ./cliente seguido del puerto y la dirección ipv4. p.ej: ./cliente 1235 127.0.0.1, este comando debe ejecutarse en una 
          terminal diferente, tenga en cuenta que el puerto debe ser el mismo que instancio en el servidor para que se puedan conectar.
		(-) Si el usuario no ingresa correctamente el comando, el sismema le notificará el mensaje respectivo.
		(+) Si el usuario ingresa el comando correctamente, el sistema mostrará un mensaje "Mensaje del servidor ¡Bienvenido al chat! Escriba un mensaje" 
		en la terminal del cliente indicandole al usuario que ya puede enviar un mensaje al chat. Adicionalmente en la terminal del servidor también se
		notificará que un cliente se conecto con el siguiente mensaje: "El cliente [#] se ha conectado".
Paso (3): Desconectar un cliente con el comando /exit: 
	  Si el usuario desea desconectar un cliente, deberá situarse en la terminal respectiva y como mensaje escribir "/exit", así se desconectará el cliente del
	  servidor y será notificado, se mostrará el mensaje "El cliente [#] se desconecto". 

#Salida del programa

Para observar la interacción de este programa, se deben conectar varios clientes como se indica en el paso (2), en la terminal de cada cliente se pueden enviar mensajes entre ellos, el usuario deberá situarse en un cliente en particular donde enviará un mensaje de prueba y este le llegara de manera simultanea a los demas clientes, este proceso se puede probar en cualquiera de los clientes que esten conectados.
  
 

   
 








 
