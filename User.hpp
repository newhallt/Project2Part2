
/*Thitari Newhall*/
/*for Server*/

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include <vector>

#ifndef USER_HPP
#define USER_HPP

#include "Info.hpp"

using namespace std;
class User {

	public:
//		User();

		void createSocket(); /*creating socket*/
		void bindSocket(int PortNo); /*bind socket*/
		void listenSocket(); /*listen socket*/
		int  acceptSocket(); /*accept socket*/

		void functServ(int sock);
		void login(int sock, char*name); /*for login*/
		
		void changePassword(int sock); /*for changing password*/
		void Subscribe(int sock,char*name); /*for subscribe*/
		void unSubscribe(int sock,char*name); /*for unsubscribe*/
		void PassChangeFunc(); /*changing password function*/
		void printSubList(int sock,char*name); /*print subscribtiob lists*/
		void communicate(int sock, char*name);
		void SendMssg(int sock, char*name);
		void LocationChoose(string l,int sock,char*name);
		void print2();

		int getSocket();
		int getNewSock();
		void setNewSock(int newSockFD);

		char password[255];
		char username[255]; 
		char existUser[255]; /*exist usename in file*/
		char existPass[255]; /*exist password in file*/

		char buff[255]; /*fot printing/reading/sending choices*/

		char oldPass[255]; /*old password*/
		char newPass[255]; /*new password*/


		int SocketNo;
		char messages[255];
		vector<string> location;

		void test(int sock);

//		Info *infoCli = new Infio;
//		Info infoCli;
//
		vector<Info> data;

		void SendToAll(char *mssg, int sock);

	private:
		int sockFD;
		int newSockFD;
		sockaddr_in myaddr;
		sockaddr_in cli_addr;

		
};

#endif
