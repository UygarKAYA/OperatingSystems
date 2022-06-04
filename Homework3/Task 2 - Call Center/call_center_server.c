#include<stdio.h>
#include<string.h>	  //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>	  //write
#include<pthread.h>   //for threading
#include<stdlib.h>

int size = 0;
pthread_t thread_;
pthread_mutex_t mutex_;
void *server_handler(void *p_desc);

int main(int argc , char *argv[])
{
	pthread_mutex_init(&mutex_, NULL); //initialize mutex

	int desc, sock, client_thr, count, *socket_;
	struct sockaddr_in server, client;
	
	//Create socket
	desc = socket(AF_INET, SOCK_STREAM, 0);
	if(desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);
	
	//Bind
	if(bind(desc, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(desc, 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	count = sizeof(struct sockaddr_in);
	
	//accept connection from an incoming client
	while(size < 4 && (sock = accept(desc, (struct sockaddr *)&client, (socklen_t*)&count))) 
	{
		pthread_mutex_lock(&mutex_);
		puts("Connection accepted");

		socket_ = malloc(1);
		*socket_ = sock;
		
		client_thr = pthread_create(&thread_, NULL, server_handler, (void*) socket_) < 0;
		if(client_thr)
        {
            puts("Sorry, thread couldn't be created");
            return 1;
        }

		size++;
	}

	if(sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	
	return 0;
}

void *server_handler(void *p_desc) 
{
	time_t ticks = 10;
	time_t start_time = time(NULL);
	time_t end_time = start_time + ticks;

	int socket = *(int*)p_desc;
	int read_size;
	char client_message[2000];

	while(start_time < end_time && (read_size = recv(socket, client_message, 2000, 0)) > 0)
	{
		//Send the message back to client
		write(socket, client_message, strlen(client_message));
		start_time = time(NULL);
	}

    write(socket, "Out of Time.\n", strlen("Out of Time.\n"));
    shutdown(socket, 2);
    close(socket);

    pthread_mutex_unlock(&mutex_);
    size--;
	
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}

	return 0;
}