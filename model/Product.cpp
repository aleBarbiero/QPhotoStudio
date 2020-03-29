#include "Product.h"
#include <cmath>
#include <limits>
using namespace std;

Product::Product(string newM,string newNM,double newP):marca(newM),nomeModello(newNM),prezzo(newP){
    if(prezzo<0.0) setPrezzo(0.0);
    else setPrezzo(round(prezzo*100)/100);
};

//operatori
bool Product::operator==(const Product& p){
    return (marca==p.getMarca() && nomeModello==p.getNomeModello() && (fabs(prezzo - p.getPrezzo()) < numeric_limits<double>::epsilon()));
}//==

bool Product::operator!=(const Product& p){
    return !(*this==p);
}//!=

bool Product::operator>(const Product& p){
    return prezzo>p.getPrezzo();
}//>

bool Product::operator>=(const Product& p){
    return prezzo>=p.getPrezzo();
}//>=

bool Product::operator<(const Product& p){
    return prezzo<p.getPrezzo();
}//<

bool Product::operator<=(const Product& p){
    return prezzo<=p.getPrezzo();
}//<=

string Product::getMarca() const{
    return marca;
}//getMarca

string Product::getNomeModello() const{
    return nomeModello;
}

double Product::getPrezzo() const{
    return prezzo;
}//getPrezzo

void Product::setMarca(string newM){
    marca=newM;
}//setMarca

void Product::setNomeModello(string newNM){
    nomeModello=newNM;
}//setNomeModello

void Product::setPrezzo(double newP){
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
    x.writeCharacters(QString::number(Product::getPrezzo()));
    x.writeEndElement();
}//xml
