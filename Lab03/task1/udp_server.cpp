// Server side implementation of UDP client-server model in C++
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sstream>
using namespace std;

#define PORT     8080
#define MAXLINE 1024

float performOperation(const string& expression) {
    float num1, num2;
    char op;
    stringstream iss(expression);
    iss >> num1 >> op >> num2;

    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 == 0) {
                //division by zero
                return -1; 
            }
            return num1 / num2;
    }
}

// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        // SOCK_DGRAM means UDP
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int n;
    socklen_t len;
    len = sizeof(cliaddr); 
    string msg = "Message from server";

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
    buffer[n] = '\0';
    cout << "Client Question: " << buffer <<  endl;
    
    msg = to_string(performOperation(buffer));
    cout << "Result : "<<msg<<endl;

    sendto(sockfd, msg.c_str(), msg.length(), 0, (const struct sockaddr *)&cliaddr, len);
     cout << "Result Returned to Client!" <<  endl;

    return 0;
}