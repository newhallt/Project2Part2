
/*Thitari Newhall*/
/*Project2 Part II*/


#include "TCPClient.hpp"
//#include "TCPClient.cpp"
#include <string.h>
using namespace std;
#include <pthread.h>

void *recvMssg(void *ptr);

int main(int argc, char *argv[])
{


	

	int PortNo;// = 60001;
	char* name;

	name = argv[1];
	PortNo = atoi(argv[2]);
	/*to create*/
//	c.createSocket(name);
	/*to connect*/
//	c.connectSocket(PortNo);
	/*to send*/
//	c.SendClient();
//
	int sockFD;
	struct sockaddr_in serv_addr;
	char buff[256];

	sockFD = socket(AF_INET,SOCK_STREAM,0);
	struct hostent *server;
	server = gethostbyname(name);
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char*) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);

	/*connect*/
	serv_addr.sin_port = htons(PortNo);
	 if(connect(sockFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
         {
		 perror("connection failed");
	 }

	 TCPClient c;

	 /*recv*/
	 int i;
	 int choice;
//	 pthread_t recvt;

//	 pthread_create(&recvt, NULL, recvMssg, &sockFD);

	 while (true) {
	/*	 bzero(buff, 255);
		
	 	 i = recv(sockFD, buff, 255, 0);

		 if( i < 0)
			 perror("Error reading");
		 printf("Server - %s\n" , buff);

		 //try sending
		 scanf("%d", &choice);
	         send(sockFD, &choice, sizeof(int),0);*/
		 c.SendClient(sockFD);
//		 c.checkMssg(sockFD);


	 }


}

/*
void *recvMssg(void *ptr){

	int sock = *((int *) ptr);
	char buff[500];
	int len;

	while((len = recv(sock,buff, 500, 0)) > 0){

		buff[len] = '\0';
		fputs(buff,stdout);
		bzero(buff,256);

	}

	return 0;

}
*/



