#ifndef LENS_H
#define LENS_H
#include "Product.h"
using namespace std;

class Lens:virtual public Product{
    private:
       unsigned int lung;
       float focale;
       string compatibilita;
       bool stabilizzato;
       bool AF;
       float angolo;
       unsigned int diametro;
    public:
       //costruttore
       Lens(string="No data",string="No data",double=0.0,unsigned int=0,float=0.0,string="No data",bool=false,bool=false,float=0.0,unsigned int=0);
       //accessori_e_modificatori
       unsigned int getLung() const;
       void setLung(unsigned int);
       float getFocale() const;
       void setFocale(float);
       string getComp() const;
       void setComp(string);
       bool isStabilizzato() const;
       void setStabilizzazione(bool);
       bool isAF() const;
       void setAF(bool);
       float getAngolo() const;
       void setAngolo(float);
       unsigned int getDiametro() const;
       void setDiametro(unsigned int);
       //virtual
       Lens* clone() const;
       string print() const;
       string getType() const;
       //XML
       void XML(QXmlStreamWriter&) const;
};

#endif
