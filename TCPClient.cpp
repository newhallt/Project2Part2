
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

void TCPClient::test(int sock)
{
	int i;
	int choice;
	char buff[255];
	char username[255];

	bzero(buff, 255);
	i = recv(sock, buff, 255, 0);
	if( i < 0)
		perror("Error reading");
	printf("Server - %s\n" , buff);


	scanf("%d", &choice);
	send(sock, &choice, sizeof(int),0);

	if(choice == 1)
	{
	       	bzero(buff, 256);
		i = recv(sock, buff, 255,0);
		printf("Server - %s\n",buff);
	
		scanf("%s", username);
       		send(sock, username, strlen(username),0);
	}

	close(sock);


}



void TCPClient::SendClient(int sock)
{

	int i;
	int choice;

	ifstream d("user.txt", ios::in);
	
	/*reas choices from server*/
	//change fom sockFD to sock
	bzero(buff, 255);
	i = recv(sock, buff, 255, 0);
	if( i < 0)
		perror("Error reading");
	printf("Server - %s\n" , buff);
	/*write choice*/
	scanf("%d", &choice);
	send(sock, &choice, sizeof(int),0);

	
if(choice == 1)
{
	bzero(buff, 255);
	i = recv(sock, buff, 255,0); /*recieving mssg friom server*/
	if( i < 0)
		perror("Eror reading");
	printf("Server - %s\n", buff);
	scanf("%s", username);
	send(sock, username, strlen(username),0); /*send username to server*/

	while(strcmp(username, existUser))
	{
		d >> existUser;

		if(strcmp(username, existUser) == 0) 
		{
	
			bzero(buff, 255);
			i = recv(sock, buff, 255,0);
				if(i < 0)
					perror("Error reading");
			printf("Server - %s\n", buff);
			scanf("%s", password);
			send(sock, password, strlen(password),0); //send password back to serve
		}

		
		else
		{
			//goto R;
			//send(sockFD, &choice, sizeof(int), 0);
			choice = 3;
		}
	}

		/*if it was matched password*/
		d >> existPass;
		while(strcmp(password, existPass) != 0)
		{
			/*if password didn't match, kept asking*/
			bzero(buff, 255);
			recv(sock, buff, 255,0);
			printf("Server - %s\n", buff);
			scanf("%s", password);
			send(sock, password, strlen(password),0);
		}

		/*goto login function*/
		login(sock);

}


/*log out*/	
else if(choice == 2)
{
	printf("LOG OUT SUCCESSFULLY\n");
	close(sock);
	exit(1);
}
 
else if(choice == 3)
{
//R:
	/*read welcom*/
	bzero(buff, 255);
	i = recv(sock, buff, 255,0);
	if ( i < 0)
		perror("error...\n");
	printf("Server - %s\n", buff);

	/*ask for username and password*/
	bzero(buff, 255);
	i = recv(sock, buff, 255,0);
	printf("Server - %s\n", buff);

	/*answer username*/
	scanf("%s",username);
	send(sock, username, strlen(username),0);

	/*read for password*/
	bzero(buff, 255);
	i = recv(sock, buff, 255,0);
	printf("Server - %s\n", buff);
	/*answer password*/
	scanf("%s", password);
	send(sock, password, strlen(password),0);


}
}

void TCPClient::checkMssg(int sock)
{

	int len;
	char buff[255];
	while((len = recv(sock, buff, 255,0)) > 0)	{
		buff[len] = '\0';
		fputs(buff,stdout);
		bzero(buff,256);
	}


}

void TCPClient::login(int sock)
{
	char buff[255];
	int choice;
	int len;
	/*read choices*/
	bzero(buff, 255);
	recv(sock, buff, 255,0);

	//checkMssg(sock);
	/*while((len = recv(sock, buff, 255,0)) > 0){
		buff[len] = '\0';
		fputs(buff,stdout);
		bzero(buff,256);
	}*/
	printf("server - %s\n", buff);
	scanf("%d", &choice);
	send(sock, &choice, sizeof(int),0); /*send chose choice back*/

	if(choice == 1){
		Subscribe(sock);
		login(sock);
	}
	else if(choice == 2){
		unSubscribe(sock);
		login(sock);
	}
	else if(choice == 3){
		communicate(sock);
//		login(sock);
	}
	else if(choice == 5){
	//	bzero(buff,255);
	//	recv(sock, buff, 255,0);
	    //    printf("Server - %s\n", buff);

//		print2();
		printSub(sock);
		//login(sock);
	}
	else if(choice == 8){
		changePassword(sock);
		login(sock);
	}

	else if(choice == 0){
		exit(1);
	}
	
}

void TCPClient::changePassword(int sock)
{

	char temp[255];
	/*read Enter password:*/ /*asking for old password*/
	bzero(buff,255);
	recv(sock, buff, 255,0);
	printf("server - %s\n", buff);
	scanf("%s", password);
	send(sock, password, strlen(password),0); /*sending old password*/
	/*askiing for new password*/
	bzero(buff,255);
	recv(sock, buff, 255,0);
	printf("server - %s\n", buff);
	scanf("%s", temp);
	send(sock, temp, strlen(temp),0);


}

void TCPClient::Subscribe(int sock)
{
	
	int choice;
	/*read choice*/
	bzero(buff, 255);
	recv(sock, buff, 255,0);
	printf("server - %s\n", buff);
	scanf("%d",&choice);

	send(sock, &choice, sizeof(int),0);

	//cout << "Clinet choice for location: "<< choice << endl;

	if(choice == 1)
	{
		bzero(buff,255);
		recv(sock,buff,255,0);
		printf("server - %s\n",buff);
//		communicate();
		location.push_back("Pensacola");
		login(sock);
	}
	else if(choice == 2)
	{
		bzero(buff,255);
		recv(sock, buff, 255,0); /*subscribed to milton*/
		printf("server - %s\n", buff);
//		communicate();
		location.push_back("Milton");
		login(sock);
	}

	else if(choice == 3)
	{
		bzero(buff, 255);
		recv(sock, buff, 255,0); /*subscribed to  pace*/
		printf("server - %s\n",buff);
		//communicate();
		location.push_back("Pace");
		login(sock);
	}

//	if(choice == 0)
//		break;



}
void TCPClient::communicate(int sock)
{
	print2(); //print sucscribed location
	int choice;
	//:char buff[256];
	bzero(buff,256);
	recv(sock,buff,255,0); //recieve "Enter: "
	printf("Server - %s\n", buff);

	scanf("%d", &choice);
	send(sock, &choice, sizeof(int), 0);	

	string l;
	l = location.at(choice);
	LocationChoose(l,sock);
}
void TCPClient::LocationChoose(string l, int sock)
{
	if( l == "Pensacola")
		SendMssg(sock);
	else if( l == "Milton")
		SendMssg(sock);
	else if( l == "Pace")
		SendMssg(sock);
}


void TCPClient::SendMssg(int sock)
{

//	while(1)
//	{

		bzero(buff,256);
		recv(sock, buff, 255, 0);
		printf("Server -%s\n",buff); //read Enter Mssg:

		int len;
		char res[256];
		while(fgets(buff,255,stdin) > 0)
		{
	//		strcpy(res, username);
			strcat(res,":");
			strcat(res,buff);
			len = send(sock, buff, strlen(buff),0);

			if(len < 0){
				perror("message not send");
				exit(1);
			}
			bzero(buff,256);
			bzero(res,256);


//			int i = strncmp("Exit",buff, 4);
//			if(i == 0)
//				break;
		}

		while((len = recv(sock,buff, 255, 0)) > 0){
			buff[len] = '\0';
			fputs(buff,stdout);
			bzero(buff,256);
		}



		
//	close(sockFD);


}

void TCPClient::unSubscribe(int sock)
{

	/*read choices*/
	int choice;
	bzero(buff,255);
	recv(sock, buff, 255,0); /*read choice*/
	printf("server - %s\n", buff); /*print choice from server*/
	scanf("%d", &choice);
	send(sock, &choice, sizeof(int),0); /*answer choice*/


	if(choice == 1)
	{
		bzero(buff,255);
		recv(sock, buff, 255,0);
		printf("server - %s", buff);


	}

	else if(choice == 2)

	{
		bzero(buff,255);
		recv(sock,buff,255,0);
		printf("server - %s", buff);

	}

	else if(choice == 3)
	{
		bzero(buff,255);
		recv(sock, buff, 255,0);
		printf("server - %s", buff);

	}

}

void TCPClient::printSub(int sock)
{

	print2();
	login(sock);	
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

