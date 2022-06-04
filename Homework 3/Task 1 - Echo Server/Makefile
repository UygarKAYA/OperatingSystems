CC=gcc
LIB=-pthread

make: echo_server.c echo_client.c
	$(CC) -o echo_server $(LIB) echo_server.c
	$(CC) -o echo_client $(LIB) echo_client.c

clean:
	rm -f echo_server
	rm -f echo_client