#ifndef ZOOM_H
#define ZOOM_H
#include "aperture.h"
#include "length.h"
using namespace std;

class Zoom:public Aperture, public Length{
    private:
        bool moltiplicatore;
    public:
        //costruttore
        Zoom(string="No data",string="No data",float=0.0,unsigned int=0,unsigned int=0,float=0.0,float=0.0,string="No data",bool=false,bool=false,float=0.0,float=0.0,unsigned int=0,bool=false);
        //accessori_e_modificatori
        bool hasMoltiplicatore() const;
        void setMoltiplicatore(bool);
        //virtual
        Zoom* clone() const;
        string getType() const;
        string print() const;
        //esportazione
        string CSV() const;
        void XML(QXmlStreamWriter&) const;
};

#endif
