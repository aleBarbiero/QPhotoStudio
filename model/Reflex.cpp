#include "Reflex.h"
using namespace std;

Reflex::Reflex(string newM,string newNM,float newP,unsigned int min,unsigned int max,unsigned int pixel,tipo newType,bool newTrop):Product(newM,newNM,newP),ISOmin(min),ISOmax(max),px(pixel),formato(newType),tropicalizzazione(newTrop){
    if(ISOmax<ISOmin){
        setISOmax(min);
        setISOmin(max);}
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
    ISOmin=min;
}//setISOmin

void Reflex::setISOmax(unsigned int max){
    ISOmax=max;
}//setISOmax

void Reflex::setPX(unsigned int p){
    px=p;
}//setPX

void Reflex::setFormato(string f){
    if(f=="DSLR")
        formato=DSLR;
    else if(f=="FF")
        formato=FF;
    else if(f=="Mirrorless")
        formato=ML;
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

void Reflex::XML(QXmlStreamWriter& x) const{
    x.writeStartElement(QString::fromStdString("Reflex"));
        Product::XML(x);
        x.writeStartElement("Formato");
        x.writeCharacters(QString::fromStdString(getFormato()));
        x.writeEndElement();
        x.writeStartElement("ISO min");
        x.writeCharacters(QString::number(ISOmin));
        x.writeEndElement();
        x.writeStartElement("ISO max");
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
tipo Reflex::fromStrToType(string s) const{
    if(s=="FullFrame")
        return FF;
    if(s=="Mirrorless")
        return ML;
    if(s=="DSLR")
        return DSLR;
    return UND;
}//fromStrToType
