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
    char message[256] = "";
    char buf[200];
    //create the server socket
    int sock;
    sock = socket(AF_INET,SOCK_STREAM,0);

    //setup an address
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(3001);
    server_adress.sin_addr.s_addr = INADDR_ANY;

    connect(sock,(struct sockaddr*)&server_adress,sizeof(server_adress));

    recv(sock,&buf,sizeof(buf),0);
    printf("\n %s \n",buf);
    scanf("%s",message);
    send(sock,message,sizeof(message),0);
    
    close(sock);

    return 0;
}
