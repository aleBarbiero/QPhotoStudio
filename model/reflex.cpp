#include "reflex.h"
using namespace std;

Reflex::Reflex(string newM,string newNM,float newP,unsigned int min,unsigned int max,unsigned int pixel,tipo newType,bool newTrop):Product(newM,newNM,newP),ISOmin(min),ISOmax(max),px(pixel),formato(newType),tropicalizzazione(newTrop){
    if(min==0 || max==0)
        throw ErrValue("Valore non valido");
    if(min>=max)
        throw ErrBond("Errore: ISOmin maggiore di ISOmax");
}//Reflex

//accessori_e_modificatori
unsigned int Reflex::getISOmin() const{
    return ISOmin;
}//getISOmin

unsigned int Reflex::getISOmax() const{
    return ISOmax;
}//getISOmax

unsigned int Reflex::getPX() const{
    return px;
}//getPX

string Reflex::getFormato() const{
    switch(formato){
        case APSC:
            return "APS-C";
        case DSLR:
            return "DSLR";
        case FF:
            return "FullFrame";
        case ML:
            return "Mirrorless";
        case UND:
            return "No data";
    }//switch
    return "No data";
}//getFormato

bool Reflex::isTropicalizzato() const{
    return tropicalizzazione;
}//getTropicalizzazione

string Reflex::getType() const{
    return "Reflex";
}//getType

void Reflex::setISOmin(unsigned int min){
    if(min==0)
        throw ErrValue("Valore non valido");
    else if(min>=ISOmax)
        throw ErrBond("ISOmin maggiore di ISOmax");
    else
        ISOmin=min;
}//setISOmin

void Reflex::setISOmax(unsigned int max){
    if(max==0)
        throw ErrValue("Valore non valido");
    else if(ISOmin>=max)
        throw ErrBond("ISOmin maggiore di ISOmax");
    else
        ISOmax=max;
}//setISOmax

void Reflex::setPX(unsigned int p){
    if(p==0)
        throw ErrValue("Valore non valido");
    else
        px=p;
}//setPX

void Reflex::setFormato(string f){
    if(f=="DSLR")
        formato=DSLR;
    else if(f=="FullFrame")
        formato=FF;
    else if(f=="Mirrorless")
        formato=ML;
    else if(f=="APS-C")
        formato=APSC;
    else formato=UND;
}//setFormato

void Reflex::setFormato(tipo f){
    formato=f;
}//setFormato

void Reflex::setTropicalizzazione(bool t){
    tropicalizzazione=t;
}//setTropicalizzazione

Reflex* Reflex::clone() const{
    return new Reflex(*this);
}//clone

string Reflex::print() const{
    ostringstream os;
    string old=Product::print();
    os<<"Prodotto: Reflex\n";
    os<<"Formato: "<<getFormato()<<"\n"<<old;
    os<<"ISO min: "<<ISOmin<<"\n";
    os<<"ISO max: "<<ISOmax<<"\n";
    os<<"Pixel: "<<px<<"\n";
    os<<"Tropicalizzazione: ";
    if(isTropicalizzato())
        os<<"SI"<<"\n";
    else
        os<<"NO"<<"\n";
    return os.str();
}//print

string Reflex::CSV() const{
    return "Reflex," + Product::CSV() + "," + getFormato();
}//CSV

void Reflex::XML(QXmlStreamWriter& x) const{
    x.writeStartElement(QString::fromStdString("Reflex"));
        Product::XML(x);
        x.writeStartElement("Formato");
        x.writeCharacters(QString::fromStdString(getFormato()));
        x.writeEndElement();
        x.writeStartElement("ISOmin");
        x.writeCharacters(QString::number(ISOmin));
        x.writeEndElement();
        x.writeStartElement("ISOmax");
        x.writeCharacters(QString::number(ISOmax));
        x.writeEndElement();
        x.writeStartElement("Pixel");
        x.writeCharacters(QString::number(px));
        x.writeEndElement();
        x.writeStartElement("Tropicalizzazione");
        if(isTropicalizzato())
            x.writeCharacters(QString::fromStdString("SI"));
        else
            x.writeCharacters(QString::fromStdString("NO"));
        x.writeEndElement();
    x.writeEndElement();
}//XML

//ausiliario
tipo Reflex::fromStrToType(string s){
    if(s=="APS-C")
            return APSC;
    if(s=="FullFrame")
        return FF;
    if(s=="Mirrorless")
        return ML;
    if(s=="DSLR")
        return DSLR;
    return UND;
}//fromStrToType
