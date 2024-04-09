#include <TQObject.h>
#include <TGButton.h>
#include <TList.h>
#include <TGLabel.h>
#include <RQ_OBJECT.h>
#include <TGTextEntry.h>
#include <TGComboBox.h>
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
        TRootEmbeddedCanvas *fEcanvas;
        TList               *fSelected;
        TGTextEntry         *fValor, *enombreArchivo;
        ofstream            archivo;
        TGListBox           *fListBox;
    public:
        MyMainFrame(const TGWindow *p,UInt_t w,UInt_t h);
        virtual ~MyMainFrame();
        void aniadir();
        void siguiente();
};
