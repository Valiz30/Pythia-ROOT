/*
Información de contacto:
Correo: valiz_30@hotmail.com
*/

#include <TApplication.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TGButton.h>
#include <TRandom.h>
#include <TRootEmbeddedCanvas.h>
#include "principal.h"
#include "Pythia8/Pythia.h"
#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TGLabel.h>
#include <TGTextEntry.h>
#include <fstream>  
#include <TString.h>
#include <TGListBox.h>
#include <TH1.h>
#include <TH2.h>
#include <TGTextEdit.h>
#include <TSystem.h>
#include <TGraph.h>
#include<cmath>
#include <vector>
using std::string;
using std::vector;
Pythia8::Pythia     pythia;
int totalEventos = 0, xMaxNC = 0, xMaxC = 0, yMaxP = 0, xMaxEF = 0;
TH1F *HParticulasCargadas = new TH1F("histograma1","Particulas Cargadas; Particulas Cargadas; Eventos",1001,-1,1000);
TH1F *HParticulasNoCargadas = new TH1F("histograma2","Particulas no Cargadas; Particulas no Cargadas; Eventos",1001,-1,5000);
TH1F *HParticulasEstadoFinal = new TH1F("histograma6","Particulas en Estado Final; Particulas en Estado Final; Eventos",1001,-1,5000);
TH1F *HMomentoTransverso = new TH1F("histograma3","Momento Transverso; Momento Transverso; Eventos", 120, 0, 60);
TH1F *HPseudorapidity = new TH1F("histograma4","Pseudorapidity; n; Particulas", 200, -20, 20);
TH2F *HPromedio = new TH2F("histograma5","<pT>; Particulas Cargadas; <pT>", 100, 0, 1000, 100, 0, 10);
TFile *salida = new TFile("Salida.root", "recreate");
TTree *tree1 = new TTree("tree1", "tree1");
TTree *tree2 = new TTree("tree2", "tree2");
vector<float> promediopT;
vector<float> pcargadas;

MyMainFrame::MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h) {
    // Create a main frame
    fMain = new TGMainFrame(p,w,h);
    

    TGHorizontalFrame *hframe = new TGHorizontalFrame(fMain,200,40);
    TGLabel *label = new TGLabel(hframe, "Nombre del Archivo: ");
    hframe->AddFrame(label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));

    enombreArchivo = new TGTextEntry(fMain, "", 0);
    hframe->AddFrame(enombreArchivo, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
    TGTextButton *cargar = new TGTextButton(hframe,"&Cargar Archivo");
    cargar->Connect("Clicked()","MyMainFrame",this,"procesarArchivo()");
    hframe->AddFrame(cargar, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    fMain->AddFrame(hframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));


    // Set a name to the main frame
    fMain->SetWindowName("Principal");
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
void MyMainFrame::procesarArchivo(){

    int totalNoCargadas = 0, cargadas = 0, estadoFinal = 0;
    float pT = 0, promedio = 0, sumatoriapT = 0;
    double px = 0, py = 0, pseudorapidity = 0;
    bool cargada = false, final = false; 
    const char *infoEvento; 
    
    pythia.readFile(enombreArchivo->GetText());

    string totalEventosCadena = pythia.settings.output("Main:numberOfEvents", false);
    totalEventos = stoi(totalEventosCadena);
    string eventosInformacion[totalEventos+1];
    eventosInformacion[0] = "Evento     #Particulas     #P. Cargadas     #P. No Cargadas     #P. Estado Final";

    tree1->Branch("cargadas", &cargadas, "cargadas/I");
    tree1->Branch("totalNoCargadas", &totalNoCargadas, "totalNoCargadas/I");
    tree1->Branch("estadoFinal", &estadoFinal, "estadoFinal/I");
    tree2->Branch("pT", &pT, "pT/F");
    tree2->Branch("pseudorapidity", &pseudorapidity, "pseudorapidity/D");

    pythia.init();    
    
    for(int i = 0; i < totalEventos; i++){
        if(!pythia.next()) continue; 
        int tParticulasEvento = pythia.event.size();
        
        for(int j = 0; j < tParticulasEvento; j++){
            cargada = pythia.event[j].isCharged(); 
            px = pythia.event[j].px();
            py = pythia.event[j].py();
            final = pythia.event[j].isFinal();
            if(cargada){
                cargadas++;
            }
            if(final){
                estadoFinal++;
            }
            
            pT = sqrt(pow(px, 2) + pow(py, 2));
            HMomentoTransverso->Fill(pT);

            pseudorapidity = log(tan(pythia.event[j].theta()/2)) * -1;
            HPseudorapidity->Fill(pseudorapidity);

            tree2->Fill();
            sumatoriapT = sumatoriapT + pT;
        }
        eventosInformacion[i+1] = to_string(i+1) + "                    \t" + to_string(tParticulasEvento) + "                    \t" + to_string(cargadas) + "                    \t" + to_string(tParticulasEvento - cargadas) + "                    \t" + to_string(estadoFinal);
        
        if(yMaxP < tParticulasEvento){
            yMaxP = tParticulasEvento;
        }

        if(xMaxC < cargadas){
            xMaxC = cargadas;
        }
        if(xMaxEF < estadoFinal){
            xMaxEF = estadoFinal;
        }
        HParticulasCargadas->Fill(cargadas);

        totalNoCargadas = tParticulasEvento - cargadas;
        if(xMaxNC < totalNoCargadas){
            xMaxNC = totalNoCargadas;
        }
        HParticulasNoCargadas->Fill(totalNoCargadas);

        HParticulasEstadoFinal->Fill(estadoFinal);
        
        tree1->Fill();

        promedio = sumatoriapT / cargadas;

        HPromedio->Fill(cargadas, promedio);

        cargadas = 0;
        estadoFinal = 0;
        sumatoriapT = 0;

    }
    
    salida->Write();
    salida->Close();

    fListBox = new TGListBox(fMain);
    for (int i = 0; i < totalEventos+1; ++i) {
        infoEvento = const_cast<char*>(eventosInformacion[i].c_str());
        fListBox->AddEntry(infoEvento, i);
    }
    fListBox->Resize(100,150);
    fMain->AddFrame(fListBox, new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY,5, 5, 5, 5));

    TGHorizontalFrame *gframe = new TGHorizontalFrame(fMain,200,40);
    TGTextButton *Histograma1 = new TGTextButton(gframe,"&Particulas Cargadas");
    Histograma1->Connect("Clicked()","MyMainFrame",this,"histograma1()");
    gframe->AddFrame(Histograma1, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    TGTextButton *Histograma2 = new TGTextButton(gframe,"&Particulas No Cargadas");
    Histograma2->Connect("Clicked()","MyMainFrame",this,"histograma2()");
    gframe->AddFrame(Histograma2, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    TGTextButton *Histograma6 = new TGTextButton(gframe,"&Particulas en Estado Final");
    Histograma6->Connect("Clicked()","MyMainFrame",this,"histograma6()");
    gframe->AddFrame(Histograma6, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    fMain->AddFrame(gframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

    TGHorizontalFrame *kframe = new TGHorizontalFrame(fMain,200,40);
    TGTextButton *Histograma3 = new TGTextButton(kframe,"&Momento Transverso");
    Histograma3->Connect("Clicked()","MyMainFrame",this,"histograma3()");
    kframe->AddFrame(Histograma3, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    TGLabel *label = new TGLabel(kframe, "Recorte: De");
    kframe->AddFrame(label, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
    recorte1 = new TGTextEntry(kframe, "", 0);
    recorte1->Insert("0");
    kframe->AddFrame(recorte1, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
    TGLabel *label2 = new TGLabel(kframe, " a ");
    kframe->AddFrame(label2, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
    recorte2 = new TGTextEntry(kframe, "", 1);
    recorte2->Insert("60");
    kframe->AddFrame(recorte2, new TGLayoutHints(kLHintsLeft | kLHintsCenterY));
    fMain->AddFrame(kframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

    TGHorizontalFrame *lframe = new TGHorizontalFrame(fMain,200,40);
    TGTextButton *Grafico1 = new TGTextButton(lframe,"&Promedio pT");
    Grafico1->Connect("Clicked()","MyMainFrame",this,"histograma5()");
    lframe->AddFrame(Grafico1, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    TGTextButton *Histograma4 = new TGTextButton(lframe,"&Pseudorapidity");
    Histograma4->Connect("Clicked()","MyMainFrame",this,"histograma4()");
    lframe->AddFrame(Histograma4, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    fMain->AddFrame(lframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

    TGHorizontalFrame *jframe = new TGHorizontalFrame(fMain,200,40);
    TGTextButton *salir = new TGTextButton(jframe,"&Salir","gApplication->Terminate(0)");
    jframe->AddFrame(salir, new TGLayoutHints(kLHintsCenterX,5,5,3,4));
    fMain->AddFrame(jframe, new TGLayoutHints(kLHintsCenterX,2,2,2,2));

    // Set a name to the main frame
    fMain->SetWindowName("Principal");
    // Map all subwindows of main frame
    fMain->MapSubwindows();
    // Initialize the layout algorithm
    fMain->Resize(fMain->GetDefaultSize());
    // Map main frame
    fMain->MapWindow();
    
}
void MyMainFrame::histograma1(){
    TCanvas *c1=new TCanvas("1");
    HParticulasCargadas->SetAxisRange(0, xMaxC/2, "X");//xMaxC
    HParticulasCargadas->Fit("expo");
    //HParticulasCargadas->GetYaxis()->SetRangeUser(0,totalEventos);
    HParticulasCargadas->Draw();
}

void MyMainFrame::histograma2(){
    TCanvas *c2=new TCanvas("2");
    HParticulasNoCargadas->SetAxisRange(0, xMaxNC/2, "X");
    HParticulasNoCargadas->Fit("gaus");
    HParticulasNoCargadas->Draw();
}

void MyMainFrame::histograma3(){
    TCanvas *c3=new TCanvas("3");
    string s(recorte1->GetText()), s2(recorte2->GetText());;
    HMomentoTransverso->SetAxisRange(stoi(s),stoi(s2),"X");
    HMomentoTransverso->Fit("expo");
    HMomentoTransverso->Draw();
}
void MyMainFrame::histograma4(){
    TCanvas *c5=new TCanvas("5");
    HPseudorapidity->SetAxisRange(0, yMaxP/2, "Y");
    HPseudorapidity->Fit("gaus");
    HPseudorapidity->Draw();
}

void MyMainFrame::histograma5(){
    TCanvas *c4=new TCanvas("4");
    HPromedio->SetAxisRange(0, xMaxC/2, "X");
    HPromedio->Fit("gaus");
    HPromedio->Draw();
    
}
void MyMainFrame::histograma6(){
    TCanvas *c6=new TCanvas("6");
    HParticulasEstadoFinal->SetAxisRange(0, xMaxEF/2, "X");
    HParticulasEstadoFinal->Fit("gaus");
    HParticulasEstadoFinal->Draw();
}

void crearVentana() {
    new MyMainFrame(gClient->GetRoot(),500,500);
 }

int main(int argc, char **argv) {

    TApplication theApp("App",&argc,argv);
    crearVentana();
    theApp.Run();
    return 0;
}
