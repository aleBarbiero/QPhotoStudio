#include "Lens.h"
using namespace std;

//costruttore
Lens::Lens(string newM,string newNM,float newP,unsigned int newLung,float newF,string newComp,bool newStab,bool newAF,float newAng,unsigned int newDiam):Product(newM,newNM,newP),lung(newLung),focale(newF),compatibilita(newComp),stabilizzato(newStab),AF(newAF),angolo(newAng),diametro(newDiam){
    if(focale<0) setFocale(0.0);
    if(newAng<0) setAngolo(0.0);
}//Lens

//accessori_e_modificatori
unsigned int Lens::getLung() const{
    return lung;
}//getLung

float Lens::getFocale() const{
    return focale;
}//getFocale

string Lens::getComp() const{
    return compatibilita;
}//getComp

bool Lens::isStabilizzato() const{
    return stabilizzato;
}//isStabilizzato

bool Lens::isAF() const{
    return AF;
}//isAF

float Lens::getAngolo() const{
    return angolo;
}//getAngolo

unsigned int Lens::getDiametro() const{
    return diametro;
}//getDiametro

void Lens::setLung(unsigned int newL){
    lung=newL;
}//setLung

void Lens::setFocale(float newF){
    focale=newF;
}//setFocale

void Lens::setComp(string newComp){
    compatibilita=newComp;
}//setComp

void Lens::setStabilizzazione(bool newS){
    stabilizzato=newS;
}//setStabilizzazione

void Lens::setAF(bool newAF){
    AF=newAF;
}//setAF

void Lens::setAngolo(float newAng){
    angolo=newAng;
}//setAngolo

void Lens::setDiametro(unsigned int newDiam){
    diametro=newDiam;
}//setDiametro

//virtuali
Lens* Lens::clone() const{
    return new Lens(*this);
}//clone

string Lens::getType() const{
    return "Fisso";
}

string Lens::print() const{
    ostringstream os;
    string old=Product::print();
    os<<"Prodotto: Obiettivo fisso\n"<<old;
    os<<"Lunghezza focale: "<<lung<<"mm \n";
    os<<"Apertura: f/"<<focale<<"\n";
    os<<"Stabilizzazione: ";
    if(isStabilizzato())
        os<<"SI"<<"\n";
    else
        os<<"NO"<<"\n";
    os<<"AF: ";
    if(isAF())
        os<<"SI"<<"\n";
    else
        os<<"NO"<<"\n";
    os<<"Angolo: "<<angolo<<"°\n";
    os<<"Diametro: "<<diametro<<"mm\n";
    os<<"Compatibilita': "<<compatibilita<<"\n";
    return os.str();
}//print

string Lens::CSV() const{
    return "Obiettivo," + Product::CSV();
}//CSV

void Lens::XML(QXmlStreamWriter& x) const{
    x.writeStartElement(QString::fromStdString("ObiettivoFisso"));
        Product::XML(x);
        x.writeStartElement("Lunghezza");
        x.writeCharacters(QString::number(getLung()));
        x.writeEndElement();
        x.writeStartElement("Focale");
        x.writeCharacters(QString::number(static_cast<double>(getFocale())));
        x.writeEndElement();
        x.writeStartElement("Stabilizzazione");
        if(isStabilizzato())
            x.writeCharacters(QString::fromStdString("SI"));
        else
            x.writeCharacters(QString::fromStdString("NO"));
        x.writeEndElement();
        x.writeStartElement("AF");
        if(isAF())
            x.writeCharacters(QString::fromStdString("SI"));
        else
            x.writeCharacters(QString::fromStdString("NO"));
        x.writeEndElement();
        x.writeStartElement("Angolo");
        x.writeCharacters(QString::number(static_cast<double>(getAngolo())));
        x.writeEndElement();
        x.writeStartElement("Diametro");
        x.writeCharacters(QString::number(getDiametro()));
        x.writeEndElement();
        x.writeStartElement("Compatibilita");
        x.writeCharacters(QString::fromStdString(getComp()));
        x.writeEndElement();
    x.writeEndElement();
}//XML
