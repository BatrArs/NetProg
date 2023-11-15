CC=g++
CFLAGS=-I.

all: echo_client

echo_client: echo_client.cpp
	$(CC) -o echo_client echo_client.cpp $(CFLAGS)

clean:
	rm -f *.o echo_client
