all: servidor.o cliente.o
	gcc -o servidor servidor.o -pthread
	gcc -o cliente cliente.o -pthread

servidor.o: servidor.c
	gcc -c -o servidor.o servidor.c

cliente.o: cliente.c
	gcc -c -o cliente.o cliente.c

clean:
	rm -f servidor cliente *.o
