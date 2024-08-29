#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
int main() {
	
	int number[256];
	int buf=0;
	
	printf("Enter 5 numbers: \n");
	for(int i=0;i<5;i++)
		scanf("%1d",&number[i]);
	
	// create the socket
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	
	//setup an address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(3001);

	connect(sock, (struct sockaddr *) &server_address, sizeof(server_address));
	
	send(sock, number, sizeof(number), 0);
	recv(sock, &buf, sizeof(buf), 0);
	printf("Your Sum is:");
	printf("\n %d \n", buf);
	
	
	close(sock);

	return 0;
}

