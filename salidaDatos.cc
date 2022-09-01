#include <iostream>
#include <string>
#include <fstream>
using namespace std;
void salidaDatos(std::string linea){
    ofstream archivo;
    archivo.open("datos.txt", ios:: app);
    archivo << linea << endl;
    archivo.close();   
}