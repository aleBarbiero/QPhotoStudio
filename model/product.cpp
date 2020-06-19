#include "product.h"
#include <cmath>
#include <limits>
#include <string.h>
#include <iomanip>
using namespace std;

Product::Product(string newM,string newNM,float newP):marca(newM),nomeModello(newNM),prezzo(newP){
    if(newP<=0)
        throw ErrValue("Valore non valido");
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
    else if(result>0)
        return true;
    else{
        result=strcmp(nomeModello.c_str(),p.nomeModello.c_str());
        if(result<0)
            return false;
        else if(result>0)
            return true;
    }//else
    return false;
}//>

bool Product::operator>=(const Product& p){
    int result=strcmp(marca.c_str(),p.marca.c_str());
    if(result<0)
        return false;
    else if(result>0)
        return true;
    else{
        result=strcmp(nomeModello.c_str(),p.nomeModello.c_str());
        if(result<0)
            return false;
        else if(result>0)
           return true;
    }//else
    return true;
}//>=

bool Product::operator<(const Product& p){
    int result=strcmp(marca.c_str(),p.marca.c_str());
    if(result<0)
        return true;
    else if(result>0)
        return false;
    else{
        result=strcmp(nomeModello.c_str(),p.nomeModello.c_str());
        if(result<0)
            return true;
        else if(result>0)
            return false;
    }//else
    return false;
}//<

bool Product::operator<=(const Product& p){
    int result=strcmp(marca.c_str(),p.marca.c_str());
    if(result<0)
        return true;
    else if(result>0)
        return false;
    else{
        result=strcmp(nomeModello.c_str(),p.nomeModello.c_str());
        if(result<0)
            return true;
        if(result>0)
            return false;
    }//else
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
    if(newM=="")
        throw ErrValue("Valore non valido");
    else
        marca=newM;
}//setMarca

void Product::setNomeModello(string newNM){
    if(newNM=="")
        throw ErrValue("Valore non valido");
    else
        nomeModello=newNM;
}//setNomeModello

void Product::setPrezzo(float newP){
    if(newP<=0)
        throw ErrValue("Valore non valido");
    else
        prezzo=newP;
}//setPrezzo

string Product::print() const{
    ostringstream os;
    os<<"Marca: "<<marca<<"\n";
    os<<"Modello: "<<nomeModello<<"\n";
    os<<"Prezzo: "<<prezzo<<"\n";
    return os.str();
}//print

string Product::CSV() const{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2)<<prezzo;
    std::string str = stream.str();
    return marca + "," + nomeModello + ","+ str +"€";
}//CSV

void Product::XML(QXmlStreamWriter &x) const{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2)<<prezzo;
    std::string str = stream.str();
    x.writeStartElement("Marca");
    x.writeCharacters(QString::fromStdString(Product::getMarca()));
    x.writeEndElement();
    x.writeStartElement("Modello");
    x.writeCharacters(QString::fromStdString(Product::getNomeModello()));
    x.writeEndElement();
    x.writeStartElement("Prezzo");
    x.writeCharacters(QString::fromStdString(str));
    x.writeEndElement();
}//xml
