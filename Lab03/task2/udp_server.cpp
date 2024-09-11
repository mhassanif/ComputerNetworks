// Server side implementation of UDP client-server model in C++
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
using namespace std;

#define PORT     8080
#define MAXLINE 1024

string sortString(const string& str) {
    string sortedStr = str;
    sort(sortedStr.begin(), sortedStr.end());
    return sortedStr;
}

string checkAnagram(const string& expression) {
    string word1, word2;
    stringstream iss(expression);
    iss >> word1>> word2 ;

    // length dont match
    if(word1.length() != word2.length())
        return "No";

    // sort words
    sort(word1.begin(), word1.end());
    sort(word2.begin(), word2.end());

    // if sorted is same then anagram
    if(word1 == word2)
        return "Yes";
    else return "No";
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
    cout << "Words Received: " << buffer <<  endl;
    
    msg = checkAnagram(buffer);
    cout<<"Anagram : "<<msg<<endl;

    sendto(sockfd, msg.c_str(), msg.length(), 0, (const struct sockaddr *)&cliaddr, len);
     cout << "Result Returned" <<  endl;

    return 0;
}