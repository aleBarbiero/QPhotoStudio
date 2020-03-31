#include "Zoom.h"

//costruttore
Zoom::Zoom(string newM,string newNM,float newP,unsigned int newLungMin,unsigned int newLungMax,float newFMin,float newFMax,string newComp,bool newStab,bool newAF,float newAngMin,float newAngMax,unsigned int newDiam,bool newMolt):
    Aperture(newM,newNM,newP,newLungMin,newLungMax,newFMin,newComp,newStab,newAF,newAngMin,newAngMax,newDiam),Length(newM,newNM,newP,newLungMin,newFMin,newFMax,newComp,newStab,newAF,newAngMin,newDiam),moltiplicatore(newMolt){
}//Zoom

bool Zoom::hasMoltiplicatore() const{
    return moltiplicatore;
}//hasMoltiplicatore

void Zoom::setMoltiplicatore(bool b){
    moltiplicatore=b;
}//setMoltiplicatore

//virtual
string Zoom::getType() const{
    return "Zoom";
}//getType

Zoom* Zoom::clone() const{
    return new Zoom(*this);
}//clone

string Zoom::print() const{
    ostringstream os;
    string old=Product::print();
    os<<"Prodotto: Obiettivo focale fissa\n"<<old;
    os<<"Lunghezza focale: "<<Aperture::getLung()<<"-"<<Aperture::getLungMax()<<"mm \n";
    os<<"Apertura minima: f/"<<Length::getFocale()<<"\n";
    os<<"Apertura massima: f/"<<Length::getFocaleMax()<<"\n";
    os<<"Stabilizzazione: ";
    if(Aperture::isStabilizzato())
        os<<"SI"<<"\n";
    else
        os<<"NO"<<"\n";
    os<<"AF: ";
    if(Aperture::isAF())
        os<<"SI"<<"\n";
    else
        os<<"NO"<<"\n";
    os<<"Angolo: "<<Aperture::getAngolo()<<"° - "<<Aperture::getAngoloMax()<<"°\n";
    os<<"Diametro: "<<Aperture::getDiametro()<<"mm\n";
    os<<"Moltiplicatore: ";
    if(Zoom::hasMoltiplicatore())
        os<<"SI"<<"\n";
    else
        os<<"NO"<<"\n";
    os<<"Compatibilita': "<<Aperture::getComp()<<"\n";
    return os.str();
}//print

//XML
void Zoom::XML(QXmlStreamWriter& x) const{
    x.writeStartElement(QString::fromStdString("ObiettivoZoom"));
        Aperture::XML(x);
        x.writeStartElement("FocaleMax");
        x.writeCharacters(QString::number(static_cast<double>(Length::getFocaleMax())));
        x.writeEndElement();
        if(Zoom::hasMoltiplicatore())
           x.writeCharacters(QString::fromStdString("SI"));
        else
            x.writeCharacters(QString::fromStdString("NO"));
    x.writeEndElement();
}//XML
