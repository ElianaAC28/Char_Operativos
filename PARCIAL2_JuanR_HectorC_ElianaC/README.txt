ELABORADO POR: Juan Carlos Ruales Caicedo <juancarcaicedo@unicauca.edu.co>
  					 : 	Hector Esteban coral ordoñez <hectorcoral@unicauca.edu.co>
						 :  Eliana Andrea Camayo Ante <eacamyo@unicauca.edu.co>
Implementacion: de chat entre un servidor y multiples clientes 

uso Servidor  :

./servidor [puerto]

inicia el servidor en el puerto especificado si el usuario
no especifica el puerto se toma 
por defecto el puerto numero 50000

Nota el servidor debe ejecutarse primer, de forma que los clientes
puedan conectarse 

posiblemente el servidor debera ser instalado como un servicio del sistema
que es arrancado automaticamente cuando inicia el sistema 

uso cliente

./cliente IP_SERVIDOR [PUERTO]

inicia una conexion de chat al servidor ubicado en la direccion IP_SERVIDOR,en el puerto especificado. si no se especifica, la conexion se realizara en
el puerto 50000
