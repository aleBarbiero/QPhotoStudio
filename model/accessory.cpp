#include "accessory.h"
using namespace std;

//costruttore
Accessory::Accessory(string newM,string newNM,float newP,tipoA newT,string newComp,string newInfo):Product(newM,newNM,newP),tipologia(newT),compatibilita(newComp),info(newInfo){
    if(newComp=="")
        throw ErrValue("Valore non valido");
}//Accessory

//accessori_e_modificatori
string Accessory::getTipologia() const{
    switch(tipologia){
        case MC:
            return "MemoryCard";
        case TREP:
            return "Treppiedi";
        case ZA:
            return "Zaini e borse";
        case FIL:
            return "Filtri";
        case FL:
            return "Flash";
        case ALTRO:
            return "Altro";
    }//switch
    return "No data";
}//getTipologia

string Accessory::getCompatibilita() const{
    return compatibilita;
}//getCompatibilita

string Accessory::getInfo() const{
    return info;
}//getInfo

void Accessory::setTipologia(string t){
    if(t=="MemoryCard")
        tipologia=MC;
    else if(t=="Flash")
        tipologia=FL;
    else if(t=="Zaini e borse")
        tipologia=ZA;
    else if(t=="Treppiedi")
        tipologia=TREP;
    else if(t=="Filtri")
        tipologia=FIL;
    else tipologia=ALTRO;
}//setTipologia

void Accessory::setTipologia(tipoA t){
    tipologia=t;
}//setTipologia

void Accessory::setCompatibilita(string c){
    if(c=="")
        throw ErrValue("Valore non valido");
    else
        compatibilita=c;
}//set

void Accessory::setInfo(string i){
    info=i;
}//setInfo

//virtual
Accessory* Accessory::clone() const{
    return new Accessory(*this);
}//clone

string Accessory::getType() const{
    return "Accessorio";
}//getType

string Accessory::print() const{
    ostringstream os;
    string old=Product::print();
    os<<"Prodotto: Accessorio\n";
    os<<"Tipologia: "<<getTipologia()<<"\n"<<old;
    os<<"Compatibilita': "<<compatibilita<<"\n";
    os<<"Note: "<<info<<"\n";
    return os.str();
}//print

string Accessory::CSV() const{
    return "Accessorio," + Product::CSV() + "," + getTipologia();
}//CSV

//XML
void Accessory::XML(QXmlStreamWriter& x) const{
    x.writeStartElement(QString::fromStdString("Accessorio"));
        Product::XML(x);
        x.writeStartElement("Tipo");
        x.writeCharacters(QString::fromStdString(getTipologia()));
        x.writeEndElement();
        x.writeStartElement("Compatibilita");
        x.writeCharacters(QString::fromStdString(compatibilita));
        x.writeEndElement();
        x.writeStartElement("Note");
        x.writeCharacters(QString::fromStdString(info));
        x.writeEndElement();
    x.writeEndElement();
}//XML

//ausiliari
tipoA Accessory::fromStrToType(string s){
    if(s=="MemoryCard")
        return MC;
    if(s=="Zaini e borse")
        return ZA;
    if(s=="Filtri")
        return FIL;
    if(s=="Treppiedi")
        return TREP;
    if(s=="Flash")
        return FL;
    else return ALTRO;
}//fromStrToType
