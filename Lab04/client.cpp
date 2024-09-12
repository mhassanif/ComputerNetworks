#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main()
{
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // try to connect
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    int choice;
    string input;
    char buffer[1024] = {0};

    // input string
    cout << "Server Connected!\nEnter String: " << endl;
    getline(cin, input);

    // send input to server
    send(clientSocket, input.c_str(), input.length(), 0);

    memset(buffer, 0, sizeof(buffer)); //clear buffer

    // receiving choices from the server
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << buffer << endl;

    cin >> choice;

    // send choice
    string choiceStr = to_string(choice);
    send(clientSocket, choiceStr.c_str(), choiceStr.length(), 0);

    // receiving and outputting the result
    memset(buffer, 0, sizeof(buffer)); // clear buffer

    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << buffer << endl;

    close(clientSocket);

    return 0;
}
