#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int factorial(unsigned int N)
{
    int fact = 1, i;
    for (i = 1; i <= N; i++)
    {
        fact *= i;
    }
    return fact;
}

int main()
{
    char server_message[200] = "Enter choice :\n1)Addition\n2)subtraction\n3)Average\n4)Factorial\n5)Exit\n";
    char buf[200];
    // create the server socket
    int server_socket;

    // sock stream --> TCP
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server socket
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(3001);
    server_adress.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to out specified IP & port
    bind(server_socket, (struct sockaddr *)&server_adress, sizeof(server_adress));
    listen(server_socket, 5);
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // menu
    send(client_socket, server_message, sizeof(server_message), 0);
    // recive choice
    recv(client_socket, &buf, sizeof(buf), 0);

    char op_msg[200] = "";
    char msg[200] = "Enter Number2:";

    int num1 = 0;
    int num2 = 0;

    switch (atoi(buf))
    {
    case 1:
        strcpy(op_msg, "You Chose Addition!\nEnter Number1:");
        send(client_socket, op_msg, sizeof(op_msg), 0);
        recv(client_socket, &buf, sizeof(buf), 0);
        num1 = atoi(buf);
        send(client_socket, msg, sizeof(msg), 0);
        recv(client_socket, &buf, sizeof(buf), 0);
        num2 = atoi(buf);
        sprintf(msg, "%d", num1 + num2);
        send(client_socket, msg, sizeof(msg), 0);
        break;
    case 2:
        strcpy(op_msg, "You Chose Subtraction!\nEnter Number1:");
        send(client_socket, op_msg, sizeof(op_msg), 0);
        recv(client_socket, &buf, sizeof(buf), 0);
        num1 = atoi(buf);
        send(client_socket, msg, sizeof(msg), 0);
        recv(client_socket, &buf, sizeof(buf), 0);
        num2 = atoi(buf);
        sprintf(msg, "%d", num1 - num2);
        send(client_socket, msg, sizeof(msg), 0);

        break;
    case 3:
        strcpy(op_msg, "You Chose Average!\nEnter Number1:");
        send(client_socket, op_msg, sizeof(op_msg), 0);
        recv(client_socket, &buf, sizeof(buf), 0);
        num1 = atoi(buf);
        send(client_socket, msg, sizeof(msg), 0);
        recv(client_socket, &buf, sizeof(buf), 0);
        num2 = atoi(buf);
        sprintf(msg, "%d", ((num1 + num2) / 2));
        send(client_socket, msg, sizeof(msg), 0);
        break;
    case 4:
        strcpy(op_msg, "You Chose Factorial!\nEnter Number1:");
        send(client_socket, op_msg, sizeof(op_msg), 0);
        recv(client_socket, &buf, sizeof(buf), 0);
        num1 = atoi(buf);
        send(client_socket, msg, sizeof(msg), 0);
        recv(client_socket, &buf, sizeof(buf), 0);
        num2 = atoi(buf);
        sprintf(msg, "%d", (factorial(num1)));
        send(client_socket, msg, sizeof(msg), 0);

        break;
    case 5:
        strcpy(op_msg, "Bye!");
        send(client_socket, op_msg, sizeof(op_msg), 0);
        break;
    default:
        strcpy(op_msg, "Invalid Choice!");
        send(client_socket, op_msg, sizeof(op_msg), 0);

        break;
    }
    // close the socket
    close(server_socket);

    return 0;
}
