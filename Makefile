CC = g++
CFLAGS = -std=c++11

all: daytime_client.out

daytime_client.out: daytime_client.cpp
	$(CC) $(CFLAGS) -o daytime_client.out daytime_client.cpp

clean:
	rm -f daytime_client.out
