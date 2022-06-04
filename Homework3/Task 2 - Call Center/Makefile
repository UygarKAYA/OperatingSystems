CC=gcc
LIB=-pthread

make: call_center_server.c call_center_client.c
	$(CC) -o call_center_server $(LIB) call_center_server.c
	$(CC) -o call_center_client $(LIB) call_center_client.c

clean:
	rm -f call_center_server
	rm -f call_center_client