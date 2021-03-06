#include "aperture.h"
using namespace std;

Aperture::Aperture(string newM,string newNM,float newP,unsigned int newLungMin,unsigned int newLungMax,float newF,string newComp,bool newStab,bool newAF,float newAngMin,float newAngMax,unsigned int newDiam):Product(newM,newNM,newP),Lens(newM,newNM,newP,newLungMin,newF,newComp,newStab,newAF,newAngMin,newDiam),
            lungMax(newLungMax),angoloMax(newAngMax){
    if(newLungMin==0 || newLungMax==0 || newAngMax<=0 || newAngMin<=0 || newDiam==0 || newF<=0)
        throw ErrValue("Valore errato");
    if(newLungMax<=newLungMin)
        throw ErrBond("Errore: lunghezza minima maggiore di lunghezza massima");
    if(newAngMax<=newAngMin)
        throw ErrBond("Errore: angolo minimo maggiore di angolo massimo");
}//Aperture

//accessori_e_modificatori
unsigned int Aperture::getLungMax() const{
    return lungMax;
}//getLungMax

float Aperture::getAngoloMax() const{
    return angoloMax;
}//getAngoloMax

void Aperture::setLungMax(unsigned int newL){
    if(newL==0)
        throw ErrValue("Valore non valido");
    else if(newL<=getLung())
        throw ErrBond("Errore: lunghezza minima maggiore di lunghezza massima");
    else
        lungMax=newL;
}//setLungMax

void Aperture::setAngoloMax(float newA){
    if(newA<=0)
        throw ErrValue("Valore non valido");
    if(newA<=getAngolo())
        throw ErrBond("Errore: angolo minimo maggiore di angolo massimo");
    else
        angoloMax=newA;
}//setAngoloMax

//virtual
Aperture* Aperture::clone() const{
    return new Aperture(*this);
}//clone

string Aperture::print() const{
    ostringstream os;
    string old=Product::print();
    os<<"Prodotto: Obiettivo focale fissa\n"<<old;
    os<<"Lunghezza focale: "<<Lens::getLung()<<"-"<<lungMax<<"mm \n";
    os<<"Apertura: f/"<<Lens::getFocale()<<"\n";
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
    os<<"Angolo: "<<Lens::getAngolo()<<"° - "<<angoloMax<<"°\n";
    os<<"Diametro: "<<Lens::getDiametro()<<"mm\n";
    os<<"Compatibilita': "<<Lens::getComp()<<"\n";
    return os.str();
}//print

string Aperture::getType() const{
    return "Focale fissa";
}//getType

//esportazione
string Aperture::CSV() const{
    return Lens::CSV() + ",Focale fissa";
}

void Aperture::XML(QXmlStreamWriter& x) const{
    x.writeStartElement(QString::fromStdString("ObiettivoFocaleFissa"));
        Lens::XML(x);
        x.writeStartElement("LunghezzaMax");
        x.writeCharacters(QString::number(lungMax));
        x.writeEndElement();
        x.writeStartElement("AngoloMax");
        x.writeCharacters(QString::number(static_cast<double>(angoloMax)));
        x.writeEndElement();
    x.writeEndElement();
}//XML

