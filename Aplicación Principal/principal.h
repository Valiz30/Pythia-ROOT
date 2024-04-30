/*
Información de contacto:
Correo: valiz_30@hotmail.com
*/

#include <TQObject.h>
#include <RQ_OBJECT.h>
#include <TGTextEntry.h>
#include <fstream>  
#include <string>
#include <TGListBox.h>
#include <TList.h>
using namespace std;



class TGWindow;
class TGMainFrame;
class TRootEmbeddedCanvas;
class MyMainFrame {
RQ_OBJECT("MyMainFrame")
    private:
        TGMainFrame         *fMain;
        TGTextEntry         *enombreArchivo, *recorte1, *recorte2;
        ofstream            archivo;
        const TString       nombreArchivo;
        TGListBox           *fListBox;

    public:
        MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
        virtual ~MyMainFrame();
        void procesarArchivo();
        void histograma1();
        void histograma2();
        void histograma3();
        void histograma4();
        void grafico1();
};

