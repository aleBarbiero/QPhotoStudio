#include "Model.h"
#include "container/Container.cpp"
#include "container/DeepPtr.cpp"
Model::Model(){}

Model::~Model(){
    Q.deleteAll();
}//~Model

//carica/salva
void Model::saveF(const QString& file) const{
    MyXml x;
    x.save(file,Q);
}//saveF

void Model::loadF(const QString& file){
    MyXml x;
    Q=x.load(file);
    Q.sortC();
}//load

void Model::exportCSV() const{
    MyCSV csv;
    csv.exportCSV(Q);
}

//metodi
void Model::insert(Product* el){
    Q.pushLast(el);
    Q.sortC();
}//insert

void Model::remove(Product* el){
    Q.deleteThis(el);
    Q.sortC();
}//remove

void Model::remove(int i){
    Q.deletePos(Q.begin() + i);
    Q.sortC();
}//remove

void Model::alter(int i, Product* el){
    Q.deletePos(Q.begin() + i);
    Q.pushLast(el);
    Q.sortC();
}//alter

int Model::count() const{
    return Q.getSize();
}//count

bool Model::search(int i,const QRegExp& r,const QString& s) const{
    if(s=="Marca")
        return (QString::fromStdString((*(Q.begin()+i))->getMarca()).contains(r));
    else if(s=="Modello")
        return (QString::fromStdString((*(Q.begin()+i))->getNomeModello()).contains(r));
    return false;
}//searchMarca

Container<DeepPtr<Product>> Model::getQ() const{
    return Q;
}//getQ
