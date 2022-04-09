
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef INFO_HPP
#define INFO_HPP

class Info {

	        private:
			char *name;
			int sockNo;
			vector<string> newLocation;
		public:
			Info();
			Info(char* n, int s);
			char *getName();
			int getSockNo();

			void addLocation(string l);
			vector<string> getLocation();

			
			

};
#endif
