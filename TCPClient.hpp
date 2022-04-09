
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
		void SendClient(int sock); /*send to client*/
		void login(int sock); /*for login function*/


		char password[255];
		char username[255];
		char existUser[255];
		char existPass[255];
		char buff[255];

		void changePassword(int sock); /*change password function*/
		void Subscribe(int sock); /*subscribe function*/
		void unSubscribe(int sock); /*unsubscribe function*/
		void communicate(int sock);
		void printSub(int sock);
		void SendMssg(int sock);
		void LocationChoose(string l,int sock);
		void print2();

		vector<string> location;


		void test(int sock);
		void checkMssg(int sock);
	private:
		int sockFD, PortNo; 
		struct sockaddr_in serv_addr;
};

#endif
