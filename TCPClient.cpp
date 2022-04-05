
/*Thitari Newhall*/
/*Project2 Part I*/

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fstream>
#include <stdio.h>

#include "TCPClient.hpp"
using namespace std;



void TCPClient::createSocket(char* host)
{
	/*to creating socket*/
	this->sockFD = socket(AF_INET, SOCK_STREAM, 0);
	struct hostent *server;
	server = gethostbyname(host);
	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;

	bcopy((char*) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);

}

void TCPClient::connectSocket(int PortNo)
{
	/*tp connect to socket*/
	serv_addr.sin_port = htons(PortNo);
	if(connect(this->sockFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("connection failed");
	}



}



void TCPClient::SendClient()
{

	int i;
	int choice;

	ifstream d("user.txt", ios::in);
	
	/*reas choices from server*/
	bzero(buff, 255);
	i = recv(sockFD, buff, 255, 0);
	if( i < 0)
		perror("Error reading");
	printf("Server - %s\n" , buff);
	/*write choice*/
	scanf("%d", &choice);
	send(sockFD, &choice, sizeof(int),0);

	
if(choice == 1)
{
	bzero(buff, 255);
	i = recv(sockFD, buff, 255,0); /*recieving mssg friom server*/
	if( i < 0)
		perror("Eror reading");
	printf("Server - %s\n", buff);
	scanf("%s", username);
	send(sockFD, username, strlen(username),0); /*send username to server*/

	while(strcmp(username, existUser))
	{
		d >> existUser;

		if(strcmp(username, existUser) == 0) /*if user matched*/
		{
	
			bzero(buff, 255);
			i = recv(sockFD, buff, 255,0);
				if(i < 0)
					perror("Error reading");
			printf("Server - %s\n", buff);
			scanf("%s", password);
			send(sockFD, password, strlen(password),0); /*send password back to server*/
		}

		/*else: incorrect username, -> new register
		{
			choice = 3;
		}*/
		else
		{
			goto R;
			//send(sockFD, &choice, sizeof(int), 0);
		}
	}

		/*if it was matched password*/
		d >> existPass;
		while(strcmp(password, existPass) != 0)
		{
			/*if password didn't match, kept asking*/
			bzero(buff, 255);
			recv(sockFD, buff, 255,0);
			printf("Server - %s\n", buff);
			scanf("%s", password);
			send(sockFD, password, strlen(password),0);
		}

		/*goto login function*/
		login();

}


/*log out*/	
else if(choice == 2)
{
	printf("LOG OUT SUCCESSFULLY\n");
	close(sockFD);
}
 
else if(choice == 3)
{
R:
	/*read welcom*/
	bzero(buff, 255);
	i = recv(sockFD, buff, 255,0);
	if ( i < 0)
		perror("error...\n");
	printf("Server - %s\n", buff);

	/*ask for username and password*/
	bzero(buff, 255);
	i = recv(sockFD, buff, 255,0);
	printf("Server - %s\n", buff);

	/*answer username*/
	scanf("%s",username);
	send(sockFD, username, strlen(username),0);

	/*read for password*/
	bzero(buff, 255);
	i = recv(sockFD, buff, 255,0);
	printf("Server - %s\n", buff);
	/*answer password*/
	scanf("%s", password);
	send(sockFD, password, strlen(password),0);


}
}

void TCPClient::login()
{
	char buff[255];
	int choice;
	
	/*read choices*/
	bzero(buff, 255);
	recv(sockFD, buff, 255,0);
	printf("server - %s\n", buff);
	scanf("%d", &choice);
	send(sockFD, &choice, sizeof(int),0); /*send chose choice back*/

	if(choice == 1)
		Subscribe();
	else if(choice == 2)
		unSubscribe();
	else if(choice == 3)
		communicate();
	else if(choice == 5)
		printSub();
	else if(choice == 8)
		changePassword();
	
}

void TCPClient::changePassword()
{

	char temp[255];
	/*read Enter password:*/ /*asking for old password*/
	bzero(buff,255);
	recv(sockFD, buff, 255,0);
	printf("server - %s\n", buff);
	scanf("%s", password);
	send(sockFD, password, strlen(password),0); /*sending old password*/
	/*askiing for new password*/
	bzero(buff,255);
	recv(sockFD, buff, 255,0);
	printf("server - %s\n", buff);
	scanf("%s", temp);
	send(sockFD, temp, strlen(temp),0);


}

void TCPClient::Subscribe()
{
	
	int choice;
	/*read choice*/
	bzero(buff, 255);
	recv(sockFD, buff, 255,0);
	printf("server - %s\n", buff);
	scanf("%d",&choice);
	send(sockFD, &choice, sizeof(int),0);

	if(choice == 1)
	{
		bzero(buff,255);
		recv(sockFD,buff,255,0);
		printf("server - %s\n",buff);
//		communicate();
		location.push_back("Pensacola");
		login();
	}
	else if(choice == 2)
	{
		bzero(buff,255);
		recv(sockFD, buff, 255,0); /*subscribed to milton*/
		printf("server - %s\n", buff);
//		communicate();
		location.push_back("Milton");
		login();
	}

	else if(choice == 3)
	{
		bzero(buff, 255);
		recv(sockFD, buff, 255,0); /*subscribed to  pace*/
		printf("server - %s\n",buff);
		//communicate();
		location.push_back("Pace");
		login();
	}

//	if(choice == 0)
//		break;



}
void TCPClient::communicate()
{
	print2();
	int choice;
	bzero(buff,256);
	recv(sockFD,buff,255,0); //recieve "Enter: "
	printf("Server - %s\n", buff);
	scanf("%d", &choice);
	send(sockFD, &choice, sizeof(int), 0);	
	string l;
	l = location.at(choice);
	LocationChoose(l);
}
void TCPClient::LocationChoose(string l)
{
	if( l == "Pensacola")
		SendMssg();
	else if( l == "Milton")
		SendMssg();
	else if( l == "Pace")
		SendMssg();
}


void TCPClient::SendMssg()
{

	while(1)
	{

		bzero(buff,256);
		recv(sockFD, buff, 255, 0);
		fgets(buff,255,stdin);
		send(sockFD, buff, strlen(buff),0);

		int i = strncmp("Exit",buff, 4);
		if(i == 0)
			break;
	}
	close(sockFD);


}

void TCPClient::unSubscribe()
{

	/*read choices*/
	int choice;
	bzero(buff,255);
	recv(sockFD, buff, 255,0); /*read choice*/
	printf("server - %s\n", buff); /*print choice from server*/
	scanf("%d", &choice);
	send(sockFD, &choice, sizeof(int),0); /*answer choice*/


	if(choice == 1)
	{
		bzero(buff,255);
		recv(sockFD, buff, 255,0);
		printf("server - %s", buff);


	}

	else if(choice == 2)

	{
		bzero(buff,255);
		recv(sockFD,buff,255,0);
		printf("server - %s", buff);

	}

	else if(choice == 3)
	{
		bzero(buff,255);
		recv(sockFD, buff, 255,0);
		printf("server - %s", buff);

	}

}

void TCPClient::printSub()
{
	int s;
	s = location.size();
	for(int i = 0; i < s; i++)
	{
		cout << i << ": " << location.at(i) << endl;
	}

	login();	
}

void TCPClient::print2()
{
	int s;
	s = location.size();
	for(int i = 0; i < s; i++)
	{
		cout << i << ": " << location.at(i) << endl;
	}
}

