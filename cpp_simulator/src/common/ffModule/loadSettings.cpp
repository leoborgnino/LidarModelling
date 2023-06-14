#include "loadSettings.h"

using namespace std;

loadSettings::loadSettings (char *path_file){

	init(path_file);
}

loadSettings::~loadSettings(){}

/*!Parseo del archivo utilizando la libreria JsonCpp*/
void loadSettings::init(char *path_file){

	Json::Reader reader;

	ifstream file(path_file, ifstream::binary);
	if (!file)
		throw std::runtime_error(string("LoadSettings::Problemas para leer el archivo JSON."));
	else{	
		bool parsingSuccessful = reader.parse(file,val,false);
	
		if(not parsingSuccessful)
			throw std::runtime_error(std::string("LoadSettings::Fallo en el parse del archivo JSON."
			+reader.getFormatedErrorMessages()));	
	}
}

int loadSettings::getParamAsInt(string ruta){
	
	return readPath(ruta).asInt();
}

vector <int> * loadSettings::getParamAsIntVec(string ruta){

	return toIntVec(readPath(ruta)); //cambiar
}

float loadSettings::getParamAsFloat(string ruta){

	return readPath(ruta).asFloat();
}

vector<float> * loadSettings::getParamAsFloatVec(string ruta){

	return toFloatVec(readPath(ruta));
}

double loadSettings::getParamAsDouble(string ruta) {

	return readPath(ruta).asDouble();
}

vector <double> * loadSettings::getParamAsDoubleVec(string ruta) {

	return  toDoubleVec(readPath(ruta));
}

string loadSettings::getParamAsString(string ruta) {

	return readPath(ruta).asString();
}

vector <string> * loadSettings::getParamAsStringVec(string ruta) {

	return toStringVec(readPath(ruta));
}

unsigned long long int loadSettings::getParamAsULLInt(string ruta){

    return (unsigned long long int) readPath(ruta).asUInt64(); //asInt();
}

long long int loadSettings::getParamAsLLInt(string ruta){

	return (long long int) readPath(ruta).asInt();
}


Json::Value loadSettings::readPath(string ruta)
{
	Json::Value nn, aux;

	stringstream ss(ruta);
	string item;
	vector<string> elems;
	aux=val;

	//Se separan los elementos de la ruta en componentes de un tipo vector
	while (getline(ss,item,'.')) elems.push_back(item);
	    
	//Se itera a traves del documento con el objetivo de llegar a la ultima 
	//jerarquia y obtener el valor del parametro 
	for(unsigned int i=0;i<elems.size(); i++){
		if (aux.isMember(elems[i])==true) //Validacion de la existencia del parametro en el documento
			aux=aux.get(elems[i],nn);
		else{
			throw std::runtime_error(string("LoadSettings::El parametro ->"
			+elems[i]+"<- no esta en la ruta:\n"));
	   	}
	 }
	return aux;
}

//::Conversion al tipo vector de dato requerido:

vector <int> * loadSettings::toIntVec(Json::Value aux ){

	vector<int> * v_int=new vector<int>;
	for(unsigned int index=0; index<aux.size();index++) 
		v_int->push_back(aux[index].asInt());
	return v_int;
}

vector<float> * loadSettings::toFloatVec(Json::Value aux)
{
	vector<float> * v_float=new vector<float>;
	for(unsigned int index=0; index<aux.size();index++) 
		v_float->push_back(aux[index].asFloat());
	return v_float;
}

vector<double> * loadSettings::toDoubleVec(Json::Value aux)
{
	vector<double> * v_double=new vector<double>;
	for(unsigned int index=0; index<aux.size();index++) 
		v_double->push_back(aux[index].asDouble());
	return v_double;
}

vector<string> * loadSettings::toStringVec(Json::Value aux)
{
	vector<string> * v_string=new vector<string>;
	for(unsigned int index=0; index<aux.size();index++) 
		v_string->push_back(aux[index].asString());
	return v_string;
}


void loadSettings::exposeJson( ) 
{
  Json::FastWriter fastWriter;
  std::string output = fastWriter.write(val);
  cout << output;
}
