#include "convertible.h"

using namespace std;

int convertible::toInt(string &str){

	return atoi( str.c_str() );
}

//convert int to String
string convertible::toString(int &i){

	stringstream ss;
	ss << i;
	return ss.str();
}

double convertible::toDouble(string &str){

	return atof( str.c_str() );
}

//convert float to String
string convertible::toString(float &f){

	std::ostringstream buffer;
	buffer << f;
	return buffer.str();
}

//convert string to String
string convertible::toString(string &i){

	return i;
}

//Convierte a mayusculas cada elemento del string
string convertible::toUpper(string &str){

	for(unsigned i=0;i<str.size();i++)	
		str[i]=toupper(str[i]);
	
	return str;
}
