CC = gcc
CFLAGS = -Wall

all: server client

server: Server.c
	$(CC) $(CFLAGS) Server.c -o server

client: Client.c
	$(CC) $(CFLAGS) Client.c -o client

clean:
	rm -f server client
