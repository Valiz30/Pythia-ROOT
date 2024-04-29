#include <TApplication.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TGButton.h>
#include <TList.h>
#include <TRootEmbeddedCanvas.h>
#include "ficha.h"
#include <iostream>
#include <TGLabel.h>
#include <TGTextEntry.h>
#include <fstream>  
#include <TString.h>
#include <string>
#include <TGListBox.h>
#include <TList.h>
using std::string;

string arregloC[1882];

MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h) {
    // Create a main frame
    fMain = new TGMainFrame(p,w,h);
    // Create canvas widget
    //fEcanvas = new TRootEmbeddedCanvas("Ecanvas",fMain,200,200);
    //fMain->AddFrame(fEcanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 10,10,10,1));
    TGHorizontalFrame *hframe = new TGHorizontalFrame(fMain,200,40);
    TGLabel *label = new TGLabel(hframe, "Nombre del Archivo: ");
    hframe->AddFrame(label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));



    enombreArchivo = new TGTextEntry(fMain, "", 0);
    hframe->AddFrame(enombreArchivo, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
    TGTextButton *siguiente = new TGTextButton(hframe,"&Siguiente");
    siguiente->Connect("Clicked()","MyMainFrame",this,"siguiente()");
    hframe->AddFrame(siguiente, new TGLayoutHints(kLHintsCenterX,5,5,3,4));

    TGTextButton *salir = new TGTextButton(hframe,"&Salir","gApplication->Terminate(0)");
    hframe->AddFrame(salir, new TGLayoutHints(kLHintsCenterX,5,5,3,4));

    fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
    // Set a name to the main frame
    fMain->SetWindowName("Ficha");
    // Map all subwindows of main frame
    fMain->MapSubwindows();
    // Initialize the layout algorithm
    fMain->Resize(fMain->GetDefaultSize());
    // Map main frame
    fMain->MapWindow();
}
MyMainFrame::~MyMainFrame() {
    // Clean up used widgets: frames, buttons, layout hints
    fMain->Cleanup();
    archivo.close();
    delete fMain;
}
void MyMainFrame::siguiente(){
    const char *c; 
    TGString *tmp;
    //Creacion del archivo
    archivo.open(enombreArchivo->GetText());

    fListBox = new TGListBox(fMain, 89);
    fSelected = new TList;
    for (int i = 0; i < 1882; ++i) {
        c = const_cast<char*>(arregloC[i].c_str());
        fListBox->AddEntry(c, i);
    }
    fListBox->Resize(100,150);
    fMain->AddFrame(fListBox, new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY,5, 5, 5, 5));
    TGHorizontalFrame *hframe = new TGHorizontalFrame(fMain,200,40);
    TGLabel *label = new TGLabel(hframe, "Valor: ");
    hframe->AddFrame(label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));

    fValor = new TGTextEntry(hframe, "", 0);
    hframe->AddFrame(fValor, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
    TGTextButton *agregar = new TGTextButton(hframe,"&Agregar");
    agregar->Connect("Clicked()","MyMainFrame",this,"aniadir()");
    hframe->AddFrame(agregar, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    TGTextButton *salir = new TGTextButton(hframe,"&Salir","gApplication->Terminate(0)");
    hframe->AddFrame(salir, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));
    // Set a name to the main frame
    fMain->SetWindowName("Ficha");
    // Map all subwindows of main frame
    fMain->MapSubwindows();
    // Initialize the layout algorithm
    fMain->Resize(fMain->GetDefaultSize());
    // Map main frame
    fMain->MapWindow();
}
void MyMainFrame::aniadir(){ //Funcion de la clase principal que se encarga de almacenar la configuracion seleccionada
    archivo << arregloC[fListBox->GetSelected()] << " = " << fValor->GetText() << endl;    
    fMain->Resize(fMain->GetDefaultSize());
    fMain->MapSubwindows();
}
void crearVentana() {
    new MyMainFrame(gClient->GetRoot(),500,500);
 }
void leerArchivo(string arregloC[]){ //Funcion que se encarga de leer el archivo donde se encuentran todas las configuraciones de Pythia.
    ifstream archivoC;  // objeto de la clase ofstream
    int cont = 0;
    string linea;

    archivoC.open("Configuracion.txt");
    if(archivoC.fail())
    cerr << "Error al abrir el archivo " << endl;
    else
    while(!archivoC.eof()){
        getline(archivoC, linea);
        arregloC[cont] = linea;
        cont++;
    }
    archivoC.close();
}
int main(int argc, char **argv) {
    
    leerArchivo(arregloC);
    TApplication aplicacion("App",&argc,argv);
    crearVentana();
    aplicacion.Run();
    return 0;
}