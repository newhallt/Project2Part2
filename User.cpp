
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
#include <stdio.h>

#include "User.hpp"
#include <fstream>
#include <cstring>

using namespace std;


void User::createSocket()
{
	/*for creating socket*/
	this->sockFD = socket(AF_INET,SOCK_STREAM, 0);
	if(this->sockFD < 0 )
	{
		perror("Error creating socket");
	}

	bzero((char *) &myaddr, sizeof(myaddr));
}

void User::bindSocket(int PortNo)
{
	/*for binding socket*/
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = INADDR_ANY;
	myaddr.sin_port = htons(PortNo);
	if(bind(this->sockFD, (struct sockaddr *) &myaddr, sizeof(myaddr)) < 0)
	{
		perror("Error binding");
		
	}

}


void User::listenSocket()
{
	/*for listenning socket*/
	int status = listen(sockFD, 16);
	if( status < 0)
	{
		perror("Error listening");
		
	}
	else
	{
		printf("server: waiting for connections ... \n\n");
	}
}


int User::acceptSocket()
{
	/*for accepting socket*/
	int addr_len = sizeof(cli_addr);
	this->newSockFD = accept(sockFD, (struct sockaddr *) &cli_addr, (socklen_t*) &addr_len);
	if( newSockFD < 0)
		perror("Error accpeting");

	return this->newSockFD;
}


void User::setNewSock(int newSock)
{
	this->newSockFD = newSock;
}


/*
void User::send(string msg)
{
	int status;
	status = send(sockFD, msg.c_str(). msg.size(), 0);

	if (status == -1)
		return -1;
}
*/


void User::functServ()
{
//	char buf[255]; /*for buffer*/
	int i, choice;

	ifstream d("user.txt",ios::in);
	/*choice
	 * 1) Log in
	 * 2) Log out
	 * 3) Register */

	/*send choice to client*/
	i = send(newSockFD, "Enter choice:\n1.Log in\n2.Log out\n3.Register\n", strlen("Enter choice:\n1.Log in\n2.Log out\n3.Register\n"), 0);
	if(i < 0)
		perror("Error entering choice");
	recv(newSockFD, &choice, sizeof(int),0);
	printf("Client's choice is: %d\n", choice);


	if(choice == 1) /*if the choice is 1*/
{
	i = send(newSockFD, "Enter username: ", strlen("Enter username: "),0); /*send to client*/
	if(i < 0)
		perror("Error entering username");
	bzero(username, 255);
	recv(newSockFD, username, 255,0); /*read username from client*/
	printf("username: %s\n", username);


	/*find if this user is exits in user.txt*/
	while(strcmp(username, existUser)){
		d >> existUser;
		if(strcmp(username, existUser) == 0)
		{
			i = send(newSockFD, "Enter password: ", strlen("Enter password: "),0);
			if(i < 0)
				perror("Error entering password");
	
			bzero(password, 255);	
			recv(newSockFD, password, 255,0); /*recieve password from client*/
		}

		else
		{
			//choice = 3;
		//	recv(newSockFD, &choice, sizeof(int), 0);
			goto R;
		}

		//printf("password: %s\n", password); /*for  checking to password*/
	}
		/*checking as if password correct or incorrect*/
		d >> existPass;
		//printf("Exist Password: %s\n", existPass);


	while(strcmp(password, existPass) != 0)
	{
		/*if it wasn't matched, repeat asking until it matched*/
		i = send(newSockFD, "Enter password: ", strlen("Enter password: "),0);
		if( i < 0)
			perror("Error entering password");
		bzero(password, 255);
		recv(newSockFD, password ,255,0);

	}

	printf("LOGIN SUCCESSFULLY\n\n");
	login();
	
	
}

 
else if(choice == 3)
{
R:
	/*for register*/
	send(newSockFD, "Welcome a new register\n", strlen("Welcome a new register\n"),0);
//	if( i < 0)
//		perror("Error");
	/*ask for user name and password*/
	send(newSockFD, "Enter username: ", strlen("Enter username: "),0);
//	if( i < 0)
//		perror("error entering username");
	bzero(username, 255);
	recv(newSockFD, username, 255,0); /*recieving username from client*/

	/*ask for password*/
	i = send(newSockFD, "Enter password: ", strlen("Enter password: "),0);
	if( i < 0)
		perror("error");
	bzero(password, 255);
	recv(newSockFD, password, 255,0);

	/*append username and password into file*/
	ofstream myfile("user.txt",ios_base::app);
	myfile << username << " " << password << endl;

}
	

/*if user want to log out*/
	else if(choice == 2)
	{
	close(newSockFD);
	close(sockFD);
	printf("\nLOG OUT SUCCESSFULLY\n");
	
	}
}

int User::getSocket(){

return this->sockFD;
}


int User::getNewSock()
{
	return this->newSockFD;
}

/*
char* User::getUsername()
{
	return this->username;
}*/


void User::login()
	
{	

	int choice;
	int i = 0;
	/*asking to client to choose a choice*/
	i = send(newSockFD, "Enter choice:\n1.Subcribed\n2.Unscrubscribed\n3.Send a message to a location\n4.Send a private message\n5.See all the locations you are subscribed to\n6.See all the online users\n7.See last 10 messages\n8.change password\n0.Quit\n", strlen("Enter choice:\n1.Subscribed\n2.Unscribscribed\n3.Send a message to a location\n4.Send a private message\n5.See all the locations you are subdcribed to\n6. See all the online users\n7.See last 10 messages\n8.change password\n0.Quit\n"),0);

	if( i < 0)
		perror("error");
	recv(newSockFD, &choice, sizeof(int),0);
	printf("Client's choice: %d\n", choice); /*recieved choice*/


	if(choice == 1)
	{
		Subscribe();

	}

	else if(choice == 2)
	{
		unSubscribe();
		login();
	
	}
	else if(choice == 3)
	{
		communicate();
		login();
	
	}
	else if(choice == 5)
	{
		printSubList();
//		login();
	}

	else if(choice == 8)
	{
		changePassword();
		login();
	}
	
	
//	if(choice == 0)
//		break;
	

	

}

void User::changePassword()
{
	
	send(newSockFD, "Enter old password: ", strlen("Enter old password: "),0);/*write question to change password*/
	bzero(oldPass, 255);
	recv(newSockFD, oldPass, strlen(oldPass),0);	/*recieve old password*/

	send(newSockFD, "Enter new password: ", strlen("Enter new password: "),0);/*ET newpassword*/
	bzero(newPass, 255);
	recv(newSockFD, newPass, strlen(newPass),0);	/*reveice new password*/	
	PassChangeFunc();


}


void User::PassChangeFunc()
{	

	/*change password process*/
	ifstream outFile("user.txt", ios_base::in);
	ofstream inFile("temp.txt", ios_base::out);

	string strPassNew, strPassOld;
	string line1, line2;

	line1 = "";
	line2 = "";
	

//	strUser = string(username);
	strPassOld = string(oldPass);
	strPassNew = string(newPass);
	//strPassCur = string(password);

	while(outFile >> line1 >> line2)
	{
		if(line2 == strPassOld)
		{
			line2 == strPassNew;
			
		}

		line2 += "\n";
		inFile << line1 << " " <<  line2;
	}

	printf("Successfully change password!\n\n");


	outFile.close();
	inFile.close();


}

void User::Subscribe()
{

	int choice;
	//int n;
	/*print optioons of location*/

	send(newSockFD,"Enter location:\n1.Pensacola\n2.Milton\n3.Pace\n4.STOP\n", strlen("Enter location:\n1.Pensacola\n2.Milton\n3.Pace\n4.STOP\n"),0);
	bzero(buff,255);
	recv(newSockFD, &choice, sizeof(choice),0);
	printf("client's choice: %d\n", choice);

//	int byteRead, byteWritten = 0;

	if(choice == 1) //pensacola
	{


		location.push_back("Pensacola");
		send(newSockFD, "Subscribed to Pensacola\n",strlen("Sunscribed to Pensacola\n"),0);
		login();

	}

	else if(choice == 2)//milton
	{
		
		location.push_back("Milton");
		send(newSockFD, "Subscribed to Milton\n", strlen("Subscribed to Milton\n"),0);
//		communicate();
		login();
	}

	else if(choice == 3)//pace
	{

		location.push_back("Pace");
		send(newSockFD, "Subscribed to Pace\n", strlen("Subscribed to Pace\n"),0);
//		communicate();
		login();

	}


}


void User::communicate()
{
	int choice;
	print2();
	send(newSockFD, "Enter Choice: \n",strlen("Enter Choice: \n"), 0);
	bzero(buff,255);
	recv(newSockFD, &choice, sizeof(choice), 0); 
	string locateName;
	locateName = location.at(choice);
	LocationChoose(locateName);

}

void User::LocationChoose(string l)
{
	if( l == "Pensacola")
	{
		SendMssg();
	}
	else if(l == "Milton")
	{
		SendMssg();
	}
	else if(l == "Pace")
	{
		SendMssg();
	}

}
void User::SendMssg()
{
	while(1)
	{
		send(newSockFD, "Enter: ", strlen("Enter: "),0);
		bzero(buff, 256);
		recv(newSockFD, buff, 255, 0);
		printf("%s: %s\n", username, buff);

		int i = strncmp("Exit", buff, 4);
		if(i == 0)
			break;

	}
	close(newSockFD);
	close(sockFD);

}
void User::unSubscribe()
{

	int choice;

	/*print option of location*/
	send(newSockFD, "Enter location to unsubscribe\n1.Pensacola\n2.Milton\3.Milton\n", strlen("Enter location to unsubscribe\n1.Pensacola\n2.Milton\3.Pace\n"), 0);
	bzero(buff,255);
	recv(newSockFD, &choice, sizeof(choice),0);
	printf("Client's choice: %d", choice);

	if(choice == 1)
	{
		/*deleate*/
		send(newSockFD, "Unsubscribed: Pensacola", strlen("Unsubscribed: Pensacola"), 0);
	}

	else if(choice == 2)
	{
		send(newSockFD, "Unsubscribed: Milton", strlen("Unsubscribed: MIlton"),0);

	}

	else if(choice == 3)
	{
		send(newSockFD, "Unsubscribed: Pace", strlen("Unsubscribed: Pace"),0);

	}


}


void User::printSubList()
{
	int s;
	s = location.size();
	for(int i = 0; i < s; i++)
	{
		cout << location.at(i) << endl;
	}

	
	login();
}

void User::print2()
{
	int s;
	s = location.size();
	for(int i = 0; i < s; i++)
	{
		cout << location.at(i) << endl;
	}
}

