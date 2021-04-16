all: servidor.o cliente.o
	gcc -o servidor servidor.o
	gcc -o cliente cliente.o

servidor.o: servidor.c
	gcc -c -o servidor.o servidor.c
cliente.o: cliente.c 
	gcc -c -o cliente.o cliente.c

clean:
	rm -f *.o servidor cliente

