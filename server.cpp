

/*Thitari Newhall*/
/*Project2 Part II*/

#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "User.hpp"
//#include "User.cpp"
//#define PORT 8080
using namespace std;

User s;

void * process(void *ptr)
{

	s.functServ();
	return 0;
}

//int main(int argc, char *argv[])
int main()
{

//	User s;
	/*create socket*/

	s.createSocket();
	
	/*bind*/

	int PortNo = 60020;
	//PortNo = atoi(argv[1]);
	s.bindSocket(PortNo);

	/*listen*/

	s.listenSocket();
	printf("Server listening...\n");

	/*accept*/
	//int newSockFD;
	//while(newSockFD = s.acceptSocket()){

	s.acceptSocket();
//	pthread_t t;
//	pthread_create(&t, NULL, process,  NULL);  //(void *) newSockFD));
	//}
	s.functServ();

	return 0;

}

