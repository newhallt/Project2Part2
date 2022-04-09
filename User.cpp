
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

void User::test(int sock)
{

	int choice;
//	int sock = *(int *)  ptr;
	char *mssg;
	mssg = "Entering choice:\n";
	write(sock, mssg, strlen(mssg));

	recv(sock,&choice,sizeof(int),0);
	printf("client's choice is: %d\n",choice);


}


void User::functServ(int sock)
{
//	char buf[255]; /*for buffer*/
	int i, choice;

	ifstream d("user.txt",ios::in);

	/*send choice to client*/
	/*change from newSockFD to sock*/
	i = send(sock, "Enter choice:\n1.Log in\n2.Log out\n3.Register\n", strlen("Enter choice:\n1.Log in\n2.Log out\n3.Register\n"), 0);
	if(i < 0)
		perror("Error entering choice");
	recv(sock, &choice, sizeof(int),0);
	printf("Client's choice is: %d\n", choice);


	if(choice == 1) /*if the choice is 1*/
{
	i = send(sock, "Enter username: ", strlen("Enter username: "),0); /*send to client*/
	if(i < 0)
		perror("Error entering username");
	bzero(username, 255);
	recv(sock, username, 255,0); /*read username from client*/
	printf("username: %s\n", username);

		

	/*find if this user is exits in user.txt*/
	while(strcmp(username, existUser)){
		d >> existUser;
		if(strcmp(username, existUser) == 0)
		{
			i = send(sock, "Enter password: ", strlen("Enter password: "),0);
			if(i < 0)
				perror("Error entering password");
	
			bzero(password, 255);	
			recv(sock, password, 255,0); //recieve password from client
		}

		else
		{
			choice = 3;
		//	recv(newSockFD, &choice, sizeof(int), 0);
		//	goto R;
		}

		//printf("password: %s\n", password); //for  checking to password
	}
		//checking as if password correct or incorrect
		d >> existPass;
		//printf("Exist Password: %s\n", existPass);


	while(strcmp(password, existPass) != 0)
	{
		//if it wasn't matched, repeat asking until it matched
		i = send(sock, "Enter password: ", strlen("Enter password: "),0);
		if( i < 0)
			perror("Error entering password");
		bzero(password, 255);
		recv(sock, password ,255,0);

	}

	printf("LOGIN SUCCESSFULLY\n\n");
	Info newClient(username,sock);
	data.push_back(newClient);

	//cout << data[0].getName() << endl;
	//cout << data[0].getSockNo() << endl;
	login(sock,username);
	
	
}

 
else if(choice == 3)
{
//R:
	//for register
	send(sock, "Welcome a new register\n", strlen("Welcome a new register\n"),0);
//	if( i < 0)
//		perror("Error");
	//ask for user name and password
	send(sock, "Enter username: ", strlen("Enter username: "),0);
//	if( i < 0)
//		perror("error entering username");
	bzero(username, 255);
	recv(sock, username, 255,0); //recieving username from client

	//ask for password
	i = send(sock, "Enter password: ", strlen("Enter password: "),0);
	if( i < 0)
		perror("error");
	bzero(password, 255);
	recv(sock, password, 255,0);

	//append username and password into file
	ofstream myfile("user.txt",ios_base::app);
	myfile << username << " " << password << endl;

}
	

//if user want to log out
	else if(choice == 2)
	{
	close(sock);
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


void User::login(int sock, char*name)
	
{	

	int choice;
	int i = 0;
	/*asking to client to choose a choice*/
	i = send(sock, "Enter choice:\n1.Subcribed\n2.Unscrubscribed\n3.Send a message to a location\n4.Send a private message\n5.See all the locations you are subscribed to\n6.See all the online users\n7.See last 10 messages\n8.change password\n0.Quit\n", strlen("Enter choice:\n1.Subscribed\n2.Unscribscribed\n3.Send a message to a location\n4.Send a private message\n5.See all the locations you are subdcribed to\n6. See all the online users\n7.See last 10 messages\n8.change password\n0.Quit\n"),0);

	if( i < 0)
		perror("error");
	recv(sock, &choice, sizeof(int),0);
	printf("Client's choice: %d\n", choice); /*recieved choice*/


	if(choice == 1)
	{
		Subscribe(sock,name);
		login(sock,name);

	}

	else if(choice == 2)
	{
		unSubscribe(sock,name);
		login(sock,name);
	
	}
	else if(choice == 3)
	{
		communicate(sock,name);
	//	login(sock);
	
	}
	else if(choice == 5)
	{
// 		send(sock, "WELCOME CHOICE FIVE", strlen("WELCOM CHOICE FIVE"),0);

		printSubList(sock,name);
//		print2();
//		login(sock);
	}

	else if(choice == 8)
	{
		changePassword(sock);
		login(sock,name);
	}
	
	
//	if(choice == 0)
//		break;
	

	

}

void User::changePassword(int sock)
{
	
	send(sock, "Enter old password: ", strlen("Enter old password: "),0);/*write question to change password*/
	bzero(oldPass, 255);
	recv(sock, oldPass, strlen(oldPass),0);	/*recieve old password*/

	send(sock, "Enter new password: ", strlen("Enter new password: "),0);/*ET newpassword*/
	bzero(newPass, 255);
	recv(sock, newPass, strlen(newPass),0);	/*reveice new password*/	
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

void User::Subscribe(int sock,char*name)
{

	int choice;
	//int n;
	/*print optioons of location*/

	send(sock,"Enter location:\n1.Pensacola\n2.Milton\n3.Pace\n4.STOP\n", strlen("Enter location:\n1.Pensacola\n2.Milton\n3.Pace\n4.STOP\n"),0);
	bzero(buff,255);
	recv(sock, &choice, sizeof(int),0);
	printf("client's choice: %d\n", choice);

//	int byteRead, byteWritten = 0;

	if(choice == 1) //pensacola
	{


		location.push_back("Pensacola");
		send(sock, "Subscribed to Pensacola\n",strlen("Sunscribed to Pensacola\n"),0);
		login(sock,name);

	}

	else if(choice == 2)//milton
	{
		
		location.push_back("Milton");
		send(sock, "Subscribed to Milton\n", strlen("Subscribed to Milton\n"),0);
//		communicate();
		login(sock,name);
	}

	else if(choice == 3)//pace
	{

		location.push_back("Pace");
		send(sock, "Subscribed to Pace\n", strlen("Subscribed to Pace\n"),0);
//		communicate();
		login(sock,name);

	}


}


void User::communicate(int sock, char* name)
{
	int choice;
	//char buff[256];
	print2(); /*print subscribed location*/
	send(sock, "Enter Choice: \n",strlen("Enter Choice: \n"), 0);
	
	bzero(buff,255);
	recv(sock, &choice, sizeof(int), 0); 
	
	string locateName;
	locateName = location.at(choice);
	LocationChoose(locateName,sock,name);

}

void User::LocationChoose(string l,int sock, char*name)
{
	if( l == "Pensacola")
	{
		SendMssg(sock,name);
	}
	else if(l == "Milton")
	{
		SendMssg(sock,name);
	}
	else if(l == "Pace")
	{
		SendMssg(sock,name);
	}

}
void User::SendMssg(int sock,char* name)
{
//	while(1)
//	{
	send(sock, "Enter Mssg: ", strlen("Enter Mssg: "),0);
	bzero(buff, 256);

	int len;
	while(( len = recv(sock, buff, 255, 0)) > 0 ){	// recieve from one socket

		//char tempName[255];
		//for(int i =0; i < 3; i++)
		//{

		//if(username == data[i].getName()){
		//printf("%s: %s\n", name, buff);
		printf("%s\n",buff);
		//}
	//	}
		
		buff[len] = '\0';
		SendToAll(buff, sock);
		//memset(buff,'\0',sizeof(buff);
		bzero(buff,256);

		//int i = strncmp("Exit", buff, 4);
		//if(i == 0)
		//
		//	break;
		//}

	}
//	close(newSockFD);
//	close(sock);
//	login(sock);

}

void User::SendToAll(char *mssg, int sock)
{

	for(int i = 0; i < 2; i++)
	{
		cout << "socket No: " << data[i].getSockNo() <<endl;
	}

	for(int i = 0; i < 2; i++)
	{
		if(data[i].getSockNo() != sock)
		{
			/*check if they subscribe in the same location*/
	//		if(data[i].getLocation() == location.at(i))
	//		{

			int newSock;
			newSock = data[i].getSockNo();		
			send(newSock, mssg, strlen(mssg),0);
	//		}

		}


	}


}
void User::unSubscribe(int sock,char*name)
{

	int choice;

	/*print option of location*/
	send(sock, "Enter location to unsubscribe\n1.Pensacola\n2.Milton\3.Milton\n", strlen("Enter location to unsubscribe\n1.Pensacola\n2.Milton\3.Pace\n"), 0);
	bzero(buff,255);
	recv(sock, &choice, sizeof(choice),0);
	printf("Client's choice: %d", choice);

	if(choice == 1)
	{
		/*deleate*/
		send(sock, "Unsubscribed: Pensacola", strlen("Unsubscribed: Pensacola"), 0);
	}

	else if(choice == 2)
	{
		send(sock, "Unsubscribed: Milton", strlen("Unsubscribed: MIlton"),0);

	}

	else if(choice == 3)
	{
		send(sock, "Unsubscribed: Pace", strlen("Unsubscribed: Pace"),0);

	}

	login(sock,name);


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

void User::printSubList(int sock,char*name)
{	
	print2();
	login(sock,name);

}

