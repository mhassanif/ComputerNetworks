#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include<string.h>
#include <netinet/in.h>

int main() {

	char server_message[256] = "The String is Palindrome.";
	char server_message1[256] = "The String is NOT Palindrome.";
	char buf[200];
	// create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	
	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(3001);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	printf("Waiting for Connection\n");
	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	listen(server_socket, 5);
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);
	
	// send the message
	recv(client_socket, &buf, sizeof(buf), 0);
	int check=1;
	int j=strlen(buf)-1;
	for(int i=0;i<j;i++,j--)
	{
		if(buf[i]!=buf[j])
		{
			check=0;
			break;
		}
	}	

	
	if(check)
		send(client_socket, server_message, sizeof(server_message), 0);
	else
		send(client_socket, server_message1, sizeof(server_message1), 0);
	// close the socket
	close(server_socket);
	
	return 0;
}
