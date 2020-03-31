#include "Product.h"
#include <cmath>
#include <limits>
#include <string.h>
using namespace std;

Product::Product(string newM,string newNM,float newP):marca(newM),nomeModello(newNM),prezzo(newP){
    if(prezzo<0.0f) setPrezzo(0.0f);
    else setPrezzo(roundf(prezzo*100)/100);
};

//operatori
bool Product::operator==(const Product& p){
    return (marca==p.getMarca() && nomeModello==p.getNomeModello());
}//==

bool Product::operator!=(const Product& p){
    return !(Product::operator==(p));
}//!=

bool Product::operator>(const Product& p){
    int result=strcmp(marca.c_str(),p.marca.c_str());
    if(result<0)
        return false;
    if(result>0)
        return true;
    result=strcmp(nomeModello.c_str(),p.nomeModello.c_str());
    if(result<0)
        return false;
    if(result>0)
        return true;
    return false;
}//>

bool Product::operator>=(const Product& p){
    int result=strcmp(marca.c_str(),p.marca.c_str());
    if(result<0)
        return false;
    if(result>0)
        return true;
    result=strcmp(nomeModello.c_str(),p.nomeModello.c_str());
    if(result<0)
        return false;
    if(result>0)
        return true;
    return true;
}//>=

bool Product::operator<(const Product& p){
    int result=strcmp(marca.c_str(),p.marca.c_str());
    if(result<0)
        return true;
    if(result>0)
        return false;
    result=strcmp(nomeModello.c_str(),p.nomeModello.c_str());
    if(result<0)
        return true;
    if(result>0)
        return false;
    return false;
}//<

bool Product::operator<=(const Product& p){
    int result=strcmp(marca.c_str(),p.marca.c_str());
    if(result<0)
        return true;
    if(result>0)
        return false;
    result=strcmp(nomeModello.c_str(),p.nomeModello.c_str());
    if(result<0)
        return true;
    if(result>0)
        return false;
    return true;
}//<=

string Product::getMarca() const{
    return marca;
}//getMarca

string Product::getNomeModello() const{
    return nomeModello;
}

float Product::getPrezzo() const{
    return prezzo;
}//getPrezzo

void Product::setMarca(string newM){
    marca=newM;
}//setMarca

void Product::setNomeModello(string newNM){
    nomeModello=newNM;
}//setNomeModello

void Product::setPrezzo(float newP){
    prezzo=newP;
}//setPrezzo

string Product::print() const{
    ostringstream os;
    os<<"Marca: "<<marca<<"\n";
    os<<"Modello: "<<nomeModello<<"\n";
    os<<"Prezzo: "<<prezzo<<"\n";
    return os.str();
}

void Product::XML(QXmlStreamWriter &x) const{
    x.writeStartElement("Marca");
    x.writeCharacters(QString::fromStdString(Product::getMarca()));
    x.writeEndElement();
    x.writeStartElement("Modello");
    x.writeCharacters(QString::fromStdString(Product::getNomeModello()));
    x.writeEndElement();
    x.writeStartElement("Prezzo");
    x.writeCharacters(QString::number((static_cast<double>(Product::getPrezzo()))));
    x.writeEndElement();
}//xml
