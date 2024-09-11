// Client side implementation of UDP client-server model in C++
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
using namespace std;

#define PORT 8080
#define MAXLINE 1024



// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n;
    socklen_t len; // Corrected type from int to socklen_t

    string msg;
    cout << "Connection Succeeded!\nEnter 2 words seprated by space to check for anagram : "<< endl;
    getline(cin, msg); 

    sendto(sockfd, msg.c_str(), msg.length(), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    // cout << "Client Question Sent!" << endl;

    n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    cout << "Server Result: " << buffer << endl;

    close(sockfd);
    return 0;
}