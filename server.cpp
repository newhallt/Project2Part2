

/*Thitari Newhall*/
/*Project2 Part II*/

#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "User.hpp"
#include <cstring>
//#include "User.cpp"
//#define PORT 8080
#include <pthread.h>
using namespace std;

User s;

void * process(void *ptr);

int main(int argc, char *argv[])
//int main()
{
	int socket_desc, new_socket, c, *new_sock;
    	struct sockaddr_in server, client;
    	char *message;

	int PortNo;

	PortNo = atoi(argv[1]);
    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PortNo);

    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");

    // Listen
    listen(socket_desc, 100);

    // Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
    {
        puts("Connection accepted");

        // Reply to the client
	pthread_t sniffer_thread;
	
        new_sock = (int *)malloc(1 * sizeof(int));
        *new_sock = new_socket;

	
	 if (pthread_create(&sniffer_thread, NULL, process, (void *)new_sock) < 0)
        {
            perror("could not create thread");
            return 1;
        }

 	puts("Handler assigned");
        // pthread_join(sniffer_thread, NULL);
    }

    if (new_socket < 0)
    {
        perror("accept failed");
        return 1;
    }

}

void *process(void *ptr)
{
//	int choice;
	int sock = *(int *) ptr;
	s.functServ(sock);

/*	char *message , client_message[2000];
	message = "Greetings! I am your connection handler\n";
	write(sock , message , strlen(message));
*/
	/*try to recieve*/
/*	recv(sock, &choice, sizeof(int),0);
	printf("Client's choice is: %d\n", choice);
*/
//	s.test(sock);

	return 0;
}



