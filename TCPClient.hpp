
/*Thitari Newhall*/
/*Project2 PartI*/
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>

#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

using namespace std;

class TCPClient
{
	public:
		void createSocket(char* host); /*for creating socket*/
		void connectSocket(int PortNo); /*connecting socket*/
		void SendClient(); /*send to client*/
		void login(); /*for login function*/


		char password[255];
		char username[255];
		char existUser[255];
		char existPass[255];
		char buff[255];

		void changePassword(); /*change password function*/
		void Subscribe(); /*subscribe function*/
		void unSubscribe(); /*unsubscribe function*/
		void communicate();
		void printSub();
		void SendMssg();
		void LocationChoose(string l);
		void print2();

		vector<string> location;


	private:
		int sockFD, PortNo; 
		struct sockaddr_in serv_addr;
};

#endif
