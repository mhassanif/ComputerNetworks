#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// functions 
string countVowels(string s)
{
	int count = 0;
	for (char c : s)
	{
		char lower = tolower(c);
		if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u')
		{
			count++;
		}
	}
	return to_string(count); 
}

string spaceToUnderscore(string s)
{
	replace(s.begin(), s.end(), ' ', '_');
	return s;
}

string reverse(string s)
{
	reverse(s.begin(), s.end());
	return s;
}

void handleClient(int clientSocket)
{
	char buffer[1024];
	string received_string = "";

	// recieve string from client
	recv(clientSocket, buffer, sizeof(buffer), 0);
	received_string = buffer;
	cout << "Received : " << buffer << endl;

	string optns = "\n\nOptions:\n1.Count Vowels\n2.Space to Underscore\n3.Reverse\n";
	send(clientSocket, optns.c_str(), optns.length(), 0);

	recv(clientSocket, buffer, sizeof(buffer), 0);
	int choice = atoi(buffer);

	string response = "";
	switch (choice)
	{
	case 1:
		// count
		response = countVowels(received_string).c_str();
		break;
	case 2:
		response = spaceToUnderscore(received_string).c_str();
		break;
	case 3:
		response = reverse(received_string).c_str();
		break;
	default:
		response = "Invalid option.\n";
		break;
	}
	cout << "Sending Response : " << response << endl;

	// sending response to client
	send(clientSocket, response.c_str(), response.length(), 0);
	close(clientSocket);
}

int main()
{
	// creating socket
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	// specifying the address
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	// binding socket
	bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

	// listening to the assigned socket
	listen(serverSocket, 5);

	while (true)
	{
		// accept connections
		int clientSocket1 = accept(serverSocket, nullptr, nullptr);
		int clientSocket2 = accept(serverSocket, nullptr, nullptr);
		int clientSocket3 = accept(serverSocket, nullptr, nullptr);

		// create proceses for client 1
		pid_t pid1 = fork();

		if (pid1 == 0)
		{
			// child 1 ie client 1
			handleClient(clientSocket1);
		}
		else
		{
			// parent
			close(clientSocket1);

			pid_t pid2 = fork();
			if (pid2 == 0)
			{
				// child 2
				handleClient(clientSocket2);
			}
			else
			{
				// parent
				close(clientSocket2);

				pid_t pid3 = fork();
				if (pid3 == 0)
				{
					// child 3
					handleClient(clientSocket3);
				}
				else
				{
					// parent
					close(clientSocket3);
				}
			}
		}
	}

	close(serverSocket);

	return 0;
}