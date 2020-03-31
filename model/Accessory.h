#ifndef ACCESSORY_H
#define ACCESSORY_H
#include "Product.h"
using namespace std;

enum tipoA{MC,TREP,ZA,FIL,ALTRO};

class Accessory:virtual public Product{
    private:
        tipoA tipologia;
        string compatibilita;
        string info;
    public:
        //costruttore
        Accessory(string="No data",string="No data",float=0.0,tipoA=ALTRO,string="No data",string="");
        //accessori_e_modificatori
        string getTipologia() const;
        void setTipologia(string);
        void setTipologia(tipoA);
        string getCompatibilita() const;
        void setCompatibilita(string);
        string getInfo() const;
        void setInfo(string);
        //virtual
        Accessory* clone() const;
        string print() const;
        string getType() const;
        //XML
        void XML(QXmlStreamWriter&) const;
        //ausiliario
        tipoA fromStrToType(string) const;
};

#endif
