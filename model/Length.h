#ifndef LENGTH_H
#define LENGTH_H
#include "Lens.h"
using namespace std;

class Length:public Lens{
    private:
        float focaleMax;
    public:
        //costruttore
        Length(string="No data",string="No data",float=0.0,unsigned int=0,float=0.0,float=0.0,string="No data",bool=false,bool=false,float=0.0,unsigned int=0);
        //accessori_e_modificatori
        float getFocaleMax() const;
        void setFocaleMax(float);
        //virtual
        virtual Length* clone() const;
        string print() const;
        string getType() const;
        //XML
        void XML(QXmlStreamWriter&) const;
};

#endif
