#include "length.h"
using namespace std;

//costruttore
Length::Length(string newM,string newNM,float newP,unsigned int newLung,float newFMin,float newFMax,string newComp,bool newStab,bool newAF,float newAng,unsigned int newDiam):Product(newM,newNM,newP),Lens(newM,newNM,newP,newLung,newFMin,newComp,newStab,newAF,newAng,newDiam),
    focaleMax(newFMax){
    if(newFMax<=0 || newFMin<=0)
        throw ErrValue("Valore non valido");
    if(newFMax<=newFMin)
        throw ErrBond("Errore: focale minima maggiore di focale massima");
}//Length

//accessori_e_modifcatori
float Length::getFocaleMax() const{
    return focaleMax;
}//getFocelMax

void Length::setFocaleMax(float fm){
    if(fm<=0)
        throw ErrValue("Valore non valido");
    else
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

//esportazione
string Length::CSV() const{
    return Lens::CSV() + ",Lunghezza fissa";
}

void Length::XML(QXmlStreamWriter& x) const{
    x.writeStartElement(QString::fromStdString("ObiettivoLunghezzaFissa"));
        Lens::XML(x);
        x.writeStartElement("FocaleMax");
        x.writeCharacters(QString::number(static_cast<double>(focaleMax)));
        x.writeEndElement();
    x.writeEndElement();
}//XML
