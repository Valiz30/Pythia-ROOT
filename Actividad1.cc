#include <iostream>
#include "Pythia8/Pythia.h" //Acceso para los objetos de Pythia
#include "TFile.h"
int main(){
    // ----------- Inicializacion -----------
    Pythia8::Pythia pythia; //Objeto de Pythia

    // ----------- Lectura de la configuracion -----------
    pythia.readString("Beams:idA = 2212"); //linea por linea
    pythia.readString("Beams:idB = 2212");
    pythia.readString("Beams:eCM = 900");
    pythia.readString("SoftQCD:all = on");
    pythia.readString("HardQCD:all = on");
    // pythia.readFile(cardfile.cmnd); ejemplo para la lectura de un archivo

    // ----------- Declaracion de variables locales, histogramas, enlaces externos, etc -----------
    int totalEventos = 1000, id, size, no;
    double m, px, py, pz;
    TFile *salida = new TFile("Archivo.root", "recreate");
    pythia.init(); //INICIALIZACION

    // ----------- Bucle de eventos -----------
    for(int i = 0; i < totalEventos; i++){
        if(!pythia.next()) continue; //Importante - Evita el mal funcionamiento del programa
        int tamano = pythia.event.size();
        std::cout << "Evento: " << i << std::endl;
        std::cout << "Tamaño - Numero de particulas: " << tamano << std::endl;
        for(int j = 0; j < tamano; j++){//Por cada evento, recorre cada particula generada he imprime la informacion
            id = pythia.event[j].id(); //identificador de la particula
            m = pythia.event[j].m(); //masa de la particula

            std::cout << id << " " << m << " " << std::endl;
        }
    }
    salida->Write();
    salida->Close();
    return 0;
}