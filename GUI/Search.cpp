#include "Search.h"
#include <QHeaderView>

Search::Search(QWidget* q):QWidget(q),searchL(new QHBoxLayout()),tabL(new QVBoxLayout()),searchValue(new QLineEdit(this)), filter(new QComboBox(this)),
        search(new QPushButton("Cerca")),del(new QPushButton("Ripristina")),s(false){
    QVBoxLayout* mainL=new QVBoxLayout(this);
    //tabella_risultati
    tab=new QTableWidget(0,4,this);
    QStringList dati("Prodotto");
    dati.append("Marca");
    dati.append("Modello");
    dati.append("Prezzo(€)");
    tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tab->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tab->setHorizontalHeaderLabels(dati);
    tab->verticalHeader()->setVisible(false);
    tab->setSelectionBehavior(QAbstractItemView::SelectRows);
    tab->setSelectionMode(QAbstractItemView::SingleSelection);
    tabL->addWidget(tab);
    tabL->addWidget(del);
    //barra_ricerca
    filter->addItem("Marca");
    filter->addItem("Modello");
    searchL->setAlignment(Qt::AlignTop);
    searchL->addWidget(filter);
    searchL->addWidget(searchValue);
    searchL->addWidget(search);
    //layout
    mainL->addLayout(searchL);
    mainL->addLayout(tabL);
}//Search

void Search::goBack(Model* modello){
    tab->setRowCount(0);
    s=false;
    for(int i=0;i<modello->count();i++){
        QTableWidgetItem* marca=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getMarca())));
        QTableWidgetItem* type=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getType())));
        QTableWidgetItem* mod=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getNomeModello())));
        QTableWidgetItem* prezzo=new QTableWidgetItem(QString(QString::number((((*modello).getQ().begin()+i))->getT().getPrezzo())));
        tab->insertRow(i);
        tab->setItem(i,0,type);
        tab->setItem(i,1,marca);
        tab->setItem(i,2,mod);
        tab->setItem(i,3,prezzo);
    }//for
}//goBack

QTableWidget* Search::getTab() const{
    return tab;
}//getTab

QPushButton* Search::getDel() const{
    return del;
}//getDel

QPushButton* Search::getSearch() const{
    return search;
}//getSearch

bool Search::getS() const{
    return s;
}//getS

QList<int> Search::getIndex() const{
    return index;
}//getIndex

void Search::find(Model* modello){
    tab->setRowCount(0);
    index.clear();
    s=true;
    if(filter->currentText()=="Marca"){
        QString* marca=new QString(searchValue->text());
        int j=0;
        for(int i=0;i<modello->count();++i){
            QString marca_el=QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getMarca()));
            if(marca_el.contains(marca,Qt::CaseInsensitive)){
                QTableWidgetItem* tipo_el=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getType())));
                QTableWidgetItem* mod_el=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getNomeModello())));
                QTableWidgetItem* prezzo_el=new QTableWidgetItem(QString(QString::number((((*modello).getQ().begin()+i))->getT().getPrezzo())));
                tab->insertRow(j);
                tab->setItem(j,0,tipo_el);
                tab->setItem(j,1,new QTableWidgetItem(marca_el));
                tab->setItem(j,2,mod_el);
                tab->setItem(j,3,prezzo_el);
                index.append(i);
                ++j;
            }
        }//for

    }else{
        QString* mod=new QString(searchValue->text());
        int j=0;
        for(int i=0;i<modello->count();++i){
            QString mod_el=QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getNomeModello()));
            if(mod_el.contains(mod,Qt::CaseInsensitive)){
                QTableWidgetItem* tipo_el=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getType())));
                QTableWidgetItem* marca_el=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getMarca())));
                QTableWidgetItem* prezzo_el=new QTableWidgetItem(QString(QString::number((((*modello).getQ().begin()+i))->getT().getPrezzo())));
                tab->insertRow(j);
                tab->setItem(j,0,tipo_el);
                tab->setItem(j,1,marca_el);
                tab->setItem(j,2,new QTableWidgetItem(mod_el));
                tab->setItem(j,3,prezzo_el);
                index.append(i);
                ++j;
            }
        }//for
    }//if_else
}//find


