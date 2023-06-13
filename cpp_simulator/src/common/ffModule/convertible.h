#ifndef CONVERTIBLE_H
#define CONVERTIBLE_H

#include <string>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include <iostream>

using namespace std;

namespace convertible{

	//From string
	int toInt(string &str);
	double toDouble(string &str);
	string toUpper(string &str);


	//To string
	string toString(string &str);		
	string toString(int &i);
	string toString(float &f);

}
#endif
