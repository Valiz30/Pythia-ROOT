void salidaDatos(string linea){
    ofstream archivo;
    archivo.open("datos.txt", ios:: app);
    archivo << linea << endl;
    archivo.close();   
}