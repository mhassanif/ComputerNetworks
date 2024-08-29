#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main() {

	int sum=0;
	int buf[5];
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
	
	for(int i=0;i<5;i++)
	{
		sum+=buf[i];
	}
	printf("%d",sum);
	
	send(client_socket, &sum, sizeof(sum), 0);

	// close the socket
	close(server_socket);
	
	return 0;
}
