#ifndef APERTURE_H
#define APERTURE_H
#include "lens.h"
using namespace std;

class Aperture:virtual public Lens{
    private:
        unsigned int lungMax;
        float angoloMax;
    public:
        //costruttore
        Aperture(string="No data",string="No data",float=0.0,unsigned int=0,unsigned int=0,float=0.0,string="No data",bool=false,bool=false,float=0.0,float=0.0,unsigned int=0);
        //accessori_e_modificatori
        unsigned int getLungMax() const;
        void setLungMax(unsigned int);
        float getAngoloMax() const;
        void setAngoloMax(float);
        //virtual
        Aperture* clone() const;
        string print() const;
        string getType() const;
        //esportazione
        string CSV() const;
        void XML(QXmlStreamWriter&) const;
};

#endif
