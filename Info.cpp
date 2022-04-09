
#include "Info.hpp"
#include <string>
#include <iostream>

using namespace std;

Info::Info(){
	name = nullptr;
	sockNo = -1;

}
Info::Info(char* n, int s)
{
	name = n;
	sockNo = s;

}

char *Info::getName()
{
	return name;

}

int Info::getSockNo()
{
	return sockNo;
}


void Info::addLocation(string l){

	newLocation.push_back(l);
}

vector<string> Info::getLocation(){

	return newLocation; 

}
