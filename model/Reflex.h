#ifndef REFLEX_H
#define REFLEX_H
#include "Product.h"
enum tipo{FF,DSLR,ML,UND};
using namespace std;

class Reflex:virtual public Product{
    private:
        unsigned int ISOmin;
        unsigned int ISOmax;
        unsigned int px;
        tipo formato;
        bool tropicalizzazione;
    public:
        //costruttore
        Reflex(string="No data",string="No data",float=0.0,unsigned int=100,unsigned int=150,unsigned int=3,tipo=UND,bool=false);
        //metodi_accessori_e_modificatori
        unsigned int getISOmin() const;
        void setISOmin(unsigned int);
        unsigned int getISOmax() const;
        void setISOmax(unsigned int);
        unsigned int getPX() const;
        void setPX(unsigned int);
        string getFormato() const;
        void setFormato(string);
        void setFormato(tipo);
        bool isTropicalizzato() const;
        void setTropicalizzazione(bool);
        //virtual
        Reflex* clone() const;
        string print() const;
        string getType() const;
        //ausiliari
        static tipo fromStrToType(string);
        //esportazione
        string CSV() const;
        void XML(QXmlStreamWriter&) const;
};

#endif
