#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>

char* reverseString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    return str;
}

char* UpperCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

char* LowerCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}


int main()
{
    char server_message[200] = "Enter choice :\n1)reversing\n2)uppercase\n3)lowercase\n4)Exit\n";
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
        strcpy(op_msg, "You Chose Reversing!\nEnter String:");
        send(client_socket, op_msg, sizeof(op_msg), 0);
        recv(client_socket, &buf, sizeof(buf), 0);
        // func
        strcpy(msg,"");
        strcpy(msg,reverseString(msg));
        send(client_socket, msg, strlen(msg), 0);
        break;
    case 2:
        strcpy(op_msg, "You Chose Upper Case!\nEnter string:");
        send(client_socket, op_msg, sizeof(op_msg), 0);
        recv(client_socket, &buf, sizeof(buf), 0);
        // func
        strcpy(msg,UpperCase(msg));
        send(client_socket, (msg), sizeof((msg)), 0);
        break;
    case 3:
        strcpy(op_msg, "You Chose lower case!\nEnter Number1:");
        send(client_socket, op_msg, sizeof(op_msg), 0);
        recv(client_socket, &buf, sizeof(buf), 0);
        // func
        send(client_socket, LowerCase(msg), sizeof(LowerCase(msg)), 0);
        break;
    case 4:
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
