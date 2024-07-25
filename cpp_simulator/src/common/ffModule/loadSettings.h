#ifndef LOADSETTINGS_H
#define LOADSETTINGS_H

#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string>
#include <string.h>
#include "json/json.h"
#include <stdexcept> 

using namespace std;
//Declaracion de la clase loadSettings 

/*!Clase loadSettings. 
*  Clase encargada de cargar los parametros al simulador a partir de un archivo .json
*/
class loadSettings
{
  public: 

	loadSettings (char *path_file);
	~loadSettings(); 

	int getParamAsInt(string ruta);
	vector <int>* getParamAsIntVec(string ruta);
	float getParamAsFloat(string ruta);
	vector <float> * getParamAsFloatVec(string ruta);
	double getParamAsDouble(string ruta);
	vector <double> * getParamAsDoubleVec(string ruta);
	string getParamAsString(string ruta);
	vector <string> * getParamAsStringVec(string ruta);
	unsigned long long int  getParamAsULLInt(string ruta);
        long long int getParamAsLLInt(string ruta);
        void exposeJson();
        void printIndentedJSON(const std::string& jsonString, int indent);
  
	private:
	void init(char *path_file);
	Json::Value readPath(string ruta);

	//:::Metodos de conversion de dato:
	inline vector<int>* toIntVec(Json::Value aux);
	inline vector<float> * toFloatVec(Json::Value aux);
	inline vector <string> * toStringVec(Json::Value aux);
	inline vector <double> *   toDoubleVec(Json::Value aux);	
	
	//Variables
	char path_file;
	Json::Value val;
};
#endif
