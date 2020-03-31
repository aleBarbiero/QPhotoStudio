#include "Length.h"
using namespace std;

//costruttore
Length::Length(string newM,string newNM,float newP,unsigned int newLung,float newFMin,float newFMax,string newComp,bool newStab,bool newAF,float newAng,unsigned int newDiam):Lens(newM,newNM,newP,newLung,newFMin,newComp,newStab,newAF,newAng,newDiam),
    focaleMax(newFMax){
    if(newFMax<newFMin){
        focaleMax=newFMin;
        Lens::setFocale(newFMax);
    }//controllo_focale
}//Length

//accessori_e_modifcatori
float Length::getFocaleMax() const{
    return focaleMax;
}//getFocelMax

void Length::setFocaleMax(float fm){
    focaleMax=fm;
}//setFocaleMax

//virtual
Length* Length::clone() const{
    return new Length(*this);
}//clone

string Length::print() const{
    ostringstream os;
    string old=Product::print();
    os<<"Prodotto: Obiettivo lunghezza fissa\n"<<old;
    os<<"Lunghezza focale: "<<Lens::getLung()<<"mm\n";
    os<<"Apertura minima: f/"<<Lens::getFocale()<<"\n";
    os<<"Apertura massima: f/"<<focaleMax<<"\n";
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
    os<<"Angolo: "<<Lens::getAngolo()<<"°\n";
    os<<"Diametro: "<<Lens::getDiametro()<<"mm\n";
    os<<"Compatibilita': "<<Lens::getComp()<<"\n";
    return os.str();
}//print

string Length::getType() const{
    return "Lunghezza fissa";
}//getType

//XML
void Length::XML(QXmlStreamWriter& x) const{
    x.writeStartElement(QString::fromStdString("ObiettivoLunghezzaFissa"));
        Lens::XML(x);
        x.writeStartElement("FocaleMax");
        x.writeCharacters(QString::number(static_cast<double>(focaleMax)));
        x.writeEndElement();
    x.writeEndElement();
}//XML
