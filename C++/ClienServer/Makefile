CFLAGS = -O 
CC = g++ 

all: server client

server: server.o 
	$(CC) $(CFLAGS) -o server server.o 
client: client.o 
	$(CC) $(CFLAGS) -o client client.o  
server.o: server.cpp 
	$(CC) $(CFLAGS) -c server.cpp 
client.o: client.cpp 
	$(CC) $(CFLAGS) -c client.cpp 
clean: 
	rm -f client server *.o *~


