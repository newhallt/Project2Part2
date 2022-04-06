
/*Thitari Newhall*/
/*Project2 Part II*/


#include "TCPClient.hpp"
//#include "TCPClient.cpp"
#include <string>
using namespace std;


int main(int argc, char *argv[])
{


	TCPClient c;

	int PortNo = 60001;
	char* name;

	name = argv[1];
	PortNo = atoi(argv[2]);
	/*to create*/
	c.createSocket(name);
	/*to connect*/
	c.connectSocket(PortNo);
	/*to send*/
	c.SendClient();



}

