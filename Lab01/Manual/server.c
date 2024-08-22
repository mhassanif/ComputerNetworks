#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    char server_message[256] = "Hi, yes you have reached the server!";
    char buf[200];
    //create the server socket
    int server_socket;

    //sock stream --> TCP
    server_socket = socket(AF_INET,SOCK_STREAM,0);

    //define the server socket
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(3001);
    server_adress.sin_addr.s_addr = INADDR_ANY;


    // bind the socket to out specified IP & port
    bind(server_socket,(struct sockaddr*)&server_adress,sizeof(server_adress));
    listen(server_socket,5);
    int client_socket;
    client_socket = accept(server_socket,NULL,NULL);

    //send the message
    recv(client_socket,&buf,sizeof(buf),0);
    printf("\n %s \n",buf);
    send(client_socket,server_message,sizeof(server_message),0);

    //close the socket
    close(server_socket);

    return 0;
}
