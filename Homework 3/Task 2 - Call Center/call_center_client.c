#include <stdio.h>	    //printf
#include <string.h>	    //strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>

int main(int argc , char *argv[])
{
	int socket_;
	struct sockaddr_in server_addr;
	char msg[1000], server_reply_msg[2000];
	
	//Create socket
	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_ == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8888);

	//Connect to remote server
	if(connect(socket_, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}

	puts("Connected\n");

	//keep communicating with server
	while(1)
	{
		printf("Please Enter a message: ");
		scanf("%s", msg);
		
		//Send some data
		if(send(socket_, msg, strlen(msg), 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if(recv(socket_, server_reply_msg, 2000, 0) < 0)
		{
			puts("recv failed");
			break;
		}

		if(recv(socket_, server_reply_msg, 2000, MSG_DONTWAIT) == 0) 
		{
			puts("Time is up, server is closed, please try again later.");
			break;
		}
		
		puts("Server reply: ");
		puts(server_reply_msg);
	}
	
	close(socket_);
	return 0;
}