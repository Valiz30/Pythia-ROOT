#include <iostream>
#include <string>
#include "Pythia8/Pythia.h" //Acceso para los objetos de Pythia
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "salidaDatos.cc"
int main(){
    // ----------- Inicializacion -----------
    Pythia8::Pythia pythia; //Objeto de Pythia

    // ----------- Lectura de la configuracion -----------
    pythia.readString("Beams:idA = 2212"); //linea por linea
    pythia.readString("Beams:idB = 2212");
    pythia.readString("Beams:eCM = 900");
    pythia.readString("SoftQCD:all = on");
    pythia.readString("HardQCD:all = on");
    pythia.readString("ColourReconnection:reconnect = on");
    // pythia.readFile(cardfile.cmnd); ejemplo para la lectura de un archivo

    // ----------- Declaracion de variables locales, histogramas, enlaces externos, etc -----------
    int totalEventos = 100, id, tamano, numeroParticula, evento;
    double masa, px, py, pz;
    std::string salidaPtr = {};
    TFile *salida = new TFile("Actividad1.root", "recreate");
    TTree *arbol = new TTree("tree", "tree");
    pythia.init(); //INICIALIZACION

    arbol->Branch("evento", &evento, "evento/I");
    arbol->Branch("tamano", &tamano, "tamano/I");
    arbol->Branch("numeroParticula", &numeroParticula, "numeroParticula/I");
    arbol->Branch("id", &id, "id/I");
    arbol->Branch("masa", &masa, "masa/I");
    arbol->Branch("px", &px, "px/I");
    arbol->Branch("py", &py, "py/I");
    arbol->Branch("pz", &pz, "pz/I");

    // ----------- Bucle de eventos -----------
    for(int i = 0; i < totalEventos; i++){
        if(!pythia.next()) continue; //Importante - Evita el mal funcionamiento del programa
        int totalEntradas = pythia.event.size();
        std::cout << "Evento: " << i << std::endl;
        salidaPtr = salidaPtr + "Evento" + std::to_string(i) + " ";
        //std::cout << "Tamaño - Numero de particulas: " << tamano << std::endl;
        evento = i;
        tamano = totalEntradas;
        for(int j = 0; j < tamano; j++){//Por cada evento, recorre cada particula generada he imprime la informacion
            id = pythia.event[j].id(); //identificador de la particula
            salidaPtr = salidaPtr + std::to_string(id) + " ";
            masa = pythia.event[j].m(); //masa de la particula
            salidaPtr = salidaPtr + std::to_string(masa) + " ";
            px = pythia.event[j].px();
            salidaPtr = salidaPtr + std::to_string(px) + " ";
            py = pythia.event[j].py();
            salidaPtr = salidaPtr + std::to_string(py) + " ";
            pz = pythia.event[j].pz();
            salidaPtr = salidaPtr + std::to_string(pz);
            salidaDatos(salidaPtr);
            arbol->Fill();
            //std::cout << salidaPtr << std::endl;
            salidaPtr = {};
        }
        
    }
    salida->Write();
    salida->Close();
    return 0;
}