#include "Listino.h"
#include <QFormLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QGroupBox>

Listino::Listino(QWidget* q):QWidget(q),ref(new QPushButton("Reflex",this)),lens(new QPushButton("Obiettivi",this)),acc(new QPushButton("Accessori",this)){
        QVBoxLayout* mainL=new QVBoxLayout(this);
        list=new QVBoxLayout();
        //tabella
        QGroupBox* gbx=new QGroupBox("Filtra per tipologia");
        QHBoxLayout* buttonL=new QHBoxLayout();
        buttonL->addWidget(ref);
        buttonL->addWidget(lens);
        buttonL->addWidget(acc);
        gbx->setLayout(buttonL);
        //listino_generico
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
        list->setAlignment(Qt::AlignTop);
        //listino_reflex
        reftab=new QTableWidget(0,8,this);
        QStringList datiRef("Marca");
        datiRef.append("Modello");
        datiRef.append("Prezzo(€)");
        datiRef.append("ISOmin");
        datiRef.append("ISOmax");
        datiRef.append("Pixel");
        datiRef.append("Formato");
        datiRef.append("Trop.");
        reftab->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        reftab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        reftab->setEditTriggers(QAbstractItemView::NoEditTriggers);
        reftab->setHorizontalHeaderLabels(datiRef);
        reftab->verticalHeader()->setVisible(false);
        reftab->setSelectionBehavior(QAbstractItemView::SelectRows);
        reftab->setSelectionMode(QAbstractItemView::SingleSelection);
        list->setAlignment(Qt::AlignTop);
        //listino_accessori
        acctab=new QTableWidget(0,6,this);
        QStringList datiAcc("Marca");
        datiAcc.append("Modello");
        datiAcc.append("Prezzo(€)");
        datiAcc.append("Tipologia");
        datiAcc.append("Compat.");
        datiAcc.append("Info");
        acctab->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        acctab->horizontalHeader()->setStretchLastSection(true);
        acctab->setEditTriggers(QAbstractItemView::NoEditTriggers);
        acctab->setHorizontalHeaderLabels(datiAcc);
        acctab->verticalHeader()->setVisible(false);
        acctab->setSelectionBehavior(QAbstractItemView::SelectRows);
        acctab->setSelectionMode(QAbstractItemView::SingleSelection);
        list->setAlignment(Qt::AlignTop);
        //listino_obiettivi
        lenstab=new QTableWidget(0,15,this);
        QStringList datiLens("Marca");
        datiLens.append("Modello");
        datiLens.append("Prezzo(€)");
        datiLens.append("Tipologia");
        datiLens.append("Compat.");
        datiLens.append("mm(min)");
        datiLens.append("mm(max)");
        datiLens.append("f/(min)");
        datiLens.append("f/(max)");
        datiLens.append("Stab.");
        datiLens.append("AF");
        datiLens.append("Diametro");
        datiLens.append("°(min)");
        datiLens.append("°(max)");
        datiLens.append("Molt.");
        lenstab->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        lenstab->setEditTriggers(QAbstractItemView::NoEditTriggers);
        lenstab->setHorizontalHeaderLabels(datiLens);
        lenstab->verticalHeader()->setVisible(false);
        lenstab->setSelectionBehavior(QAbstractItemView::SelectRows);
        lenstab->setSelectionMode(QAbstractItemView::SingleSelection);
        list->setAlignment(Qt::AlignTop);
        //widget
        list->addWidget(tab);
        list->addWidget(reftab);
        list->addWidget(acctab);
        list->addWidget(lenstab);
        //layout
        mainL->addWidget(gbx);
        mainL->addLayout(list);
        //connect
        connect(ref,SIGNAL(clicked(bool)),this,SLOT(setRefTab()));
        connect(acc,SIGNAL(clicked(bool)),this,SLOT(setAccTab()));
        connect(lens,SIGNAL(clicked(bool)),this,SLOT(setLensTab()));
}//remove

void Listino::fullTab(Model* modello){
    list->removeWidget(reftab);
    reftab->setVisible(false);
    list->removeWidget(acctab);
    acctab->setVisible(false);
    list->removeWidget(lenstab);
    lenstab->setVisible(false);
    list->addWidget(tab);
    tab->setVisible(true);
    tab->setRowCount(0);
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
}//fullTab

void Listino::refTab(Model* modello){
    reftab->setRowCount(0);
    int j=0;
    for(int i=0;i<modello->count();++i){
        if(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getType()))=="Reflex"){
            QTableWidgetItem* marca=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getMarca())));
            QTableWidgetItem* mod=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getNomeModello())));
            QTableWidgetItem* prezzo=new QTableWidgetItem(QString(QString::number((((*modello).getQ().begin()+i))->getT().getPrezzo())));
            QTableWidgetItem* ISOmin=new QTableWidgetItem(QString(QString::number((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+i)->getT())))->getISOmin())));
            QTableWidgetItem* ISOmax=new QTableWidgetItem(QString(QString::number((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+i)->getT())))->getISOmax())));
            QTableWidgetItem* px=new QTableWidgetItem(QString(QString::number((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+i)->getT())))->getPX())));
            QTableWidgetItem* formato=new QTableWidgetItem(QString(QString::fromStdString((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+i)->getT())))->getFormato())));
            reftab->insertRow(j);
            reftab->setItem(j,0,marca);
            reftab->setItem(j,1,mod);
            reftab->setItem(j,2,prezzo);
            reftab->setItem(j,3,ISOmin);
            reftab->setItem(j,4,ISOmax);
            reftab->setItem(j,5,px);
            reftab->setItem(j,6,formato);
            if((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+i)->getT())))->isTropicalizzato())
                reftab->setItem(j,7,new QTableWidgetItem(QString(QString::fromStdString("SI"))));
            else
                reftab->setItem(j,7,new QTableWidgetItem(QString(QString::fromStdString("NO"))));
            ++j;
        }//if
    }//for
}//refTab

void Listino::accTab(Model* modello){
    int j=0;
    acctab->setRowCount(0);
    for(int i=0;i<modello->count();++i){
        if(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getType()))=="Accessorio"){
            QTableWidgetItem* marca=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getMarca())));
            QTableWidgetItem* mod=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getNomeModello())));
            QTableWidgetItem* prezzo=new QTableWidgetItem(QString(QString::number((((*modello).getQ().begin()+i))->getT().getPrezzo())));
            QTableWidgetItem* tipo=new QTableWidgetItem(QString(QString::fromStdString((dynamic_cast<Accessory*>(&(((*modello).getQ().begin()+i)->getT())))->getTipologia())));
            QTableWidgetItem* comp=new QTableWidgetItem(QString(QString::fromStdString((dynamic_cast<Accessory*>(&(((*modello).getQ().begin()+i)->getT())))->getCompatibilita())));
            QTableWidgetItem* info=new QTableWidgetItem(QString(QString::fromStdString((dynamic_cast<Accessory*>(&(((*modello).getQ().begin()+i)->getT())))->getInfo())));
            acctab->insertRow(j);
            acctab->setItem(j,0,marca);
            acctab->setItem(j,1,mod);
            acctab->setItem(j,2,prezzo);
            acctab->setItem(j,3,tipo);
            acctab->setItem(j,4,comp);
            if((dynamic_cast<Accessory*>(&(((*modello).getQ().begin()+i)->getT())))->getInfo()=="")
                acctab->setItem(j,5,new QTableWidgetItem(QString(QString::fromStdString("Nessuna info"))));
            else
                acctab->setItem(j,5,info);
            ++j;
        }//if
    }//for
}//accTab

void Listino::lensTab(Model* modello){
    int j=0;
    lenstab->setRowCount(0);
    QString type;
    for(int i=0;i<modello->count();++i){
        type=QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getType()));
        if(type=="Zoom" || type=="Focale fissa"){
            QTableWidgetItem* marca=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getMarca())));
            QTableWidgetItem* mod=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getNomeModello())));
            QTableWidgetItem* prezzo=new QTableWidgetItem(QString(QString::number((((*modello).getQ().begin()+i))->getT().getPrezzo())));
            QTableWidgetItem* comp=new QTableWidgetItem(QString(QString::fromStdString(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+i))->getT())->getComp())));
            QTableWidgetItem* lmin=new QTableWidgetItem(QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+i))->getT())->getLung())));
            lenstab->insertRow(j);
            lenstab->setItem(j,0,marca);
            lenstab->setItem(j,1,mod);
            lenstab->setItem(j,2,prezzo);
            lenstab->setItem(j,3,new QTableWidgetItem(type));
            lenstab->setItem(j,4,comp);
            lenstab->setItem(j,5,lmin);
            QTableWidgetItem* lmax=new QTableWidgetItem(QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+i))->getT())->getLungMax())));
            lenstab->setItem(j,6,lmax);
            QTableWidgetItem* fmin=new QTableWidgetItem(QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+i))->getT())->getFocale())));
            lenstab->setItem(j,7,fmin);
            if(type=="Zoom"){
                 QTableWidgetItem* fmax=new QTableWidgetItem(QString(QString::number(dynamic_cast<Zoom*>(&(((*modello).getQ().begin()+i))->getT())->getAngoloMax())));
                 lenstab->setItem(j,8,fmax);
            }else
            lenstab->setItem(j,8,new QTableWidgetItem(QString(QString::fromStdString("/"))));
            QTableWidgetItem* stab;
            if((dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+i))->getT())->isStabilizzato()))
                stab=new QTableWidgetItem(QString(QString::fromStdString("SI")));
            else
                stab=new QTableWidgetItem(QString(QString::fromStdString("NO")));
            QTableWidgetItem* diam=new QTableWidgetItem(QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+i))->getT())->getDiametro())));
            QTableWidgetItem* angmin=new QTableWidgetItem(QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+i))->getT())->getAngolo())));
            QTableWidgetItem* af;
            if((dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+i))->getT())->isAF()))
                af=new QTableWidgetItem(QString(QString::fromStdString("SI")));
            else
                af=new QTableWidgetItem(QString(QString::fromStdString("NO")));
            lenstab->setItem(j,9,stab);
            lenstab->setItem(j,10,af);
            lenstab->setItem(j,11,diam);
            lenstab->setItem(j,12,angmin);
            if(type=="Zoom" || type=="Focale fissa"){
                 QTableWidgetItem* angmax=new QTableWidgetItem(QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+i))->getT())->getAngoloMax())));
                 lenstab->setItem(j,13,angmax);
            }else
                lenstab->setItem(j,13,new QTableWidgetItem(QString(QString::fromStdString("/"))));
            if(type=="Zoom"){
                QTableWidgetItem* molt;
                if((dynamic_cast<Zoom*>(&(((*modello).getQ().begin()+i))->getT())->hasMoltiplicatore()))
                    molt=new QTableWidgetItem(QString(QString::fromStdString("SI")));
                else
                    molt=new QTableWidgetItem(QString(QString::fromStdString("NO")));
                lenstab->setItem(j,14,molt);
            }else
                lenstab->setItem(j,14,new QTableWidgetItem(QString(QString::fromStdString("/"))));
            ++j;
        }else if(type=="Zoom" || type=="Lunghezza fissa"){
            QTableWidgetItem* marca=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getMarca())));
            QTableWidgetItem* mod=new QTableWidgetItem(QString(QString::fromStdString((((*modello).getQ().begin()+i))->getT().getNomeModello())));
            QTableWidgetItem* prezzo=new QTableWidgetItem(QString(QString::number((((*modello).getQ().begin()+i))->getT().getPrezzo())));
            QTableWidgetItem* comp=new QTableWidgetItem(QString(QString::fromStdString(dynamic_cast<Length*>(&(((*modello).getQ().begin()+i))->getT())->getComp())));
            QTableWidgetItem* lmin=new QTableWidgetItem(QString(QString::number(dynamic_cast<Length*>(&(((*modello).getQ().begin()+i))->getT())->getLung())));
            lenstab->insertRow(j);
            lenstab->setItem(j,0,marca);
            lenstab->setItem(j,1,mod);
            lenstab->setItem(j,2,prezzo);
            lenstab->setItem(j,3,new QTableWidgetItem(type));
            lenstab->setItem(j,4,comp);
            lenstab->setItem(j,5,lmin);
            lenstab->setItem(j,6,new QTableWidgetItem(QString(QString::fromStdString("/"))));
            QTableWidgetItem* fmin=new QTableWidgetItem(QString(QString::number(dynamic_cast<Length*>(&(((*modello).getQ().begin()+i))->getT())->getFocale())));
            lenstab->setItem(j,7,fmin);
            QTableWidgetItem* fmax=new QTableWidgetItem(QString(QString::number(dynamic_cast<Length*>(&(((*modello).getQ().begin()+i))->getT())->getFocaleMax())));
            lenstab->setItem(j,8,fmax);
            QTableWidgetItem* stab;
            if((dynamic_cast<Length*>(&(((*modello).getQ().begin()+i))->getT())->isStabilizzato()))
                stab=new QTableWidgetItem(QString(QString::fromStdString("SI")));
            else
                stab=new QTableWidgetItem(QString(QString::fromStdString("NO")));
            QTableWidgetItem* diam=new QTableWidgetItem(QString(QString::number(dynamic_cast<Length*>(&(((*modello).getQ().begin()+i))->getT())->getDiametro())));
            QTableWidgetItem* angmin=new QTableWidgetItem(QString(QString::number(dynamic_cast<Length*>(&(((*modello).getQ().begin()+i))->getT())->getAngolo())));
            QTableWidgetItem* af;
            if((dynamic_cast<Length*>(&(((*modello).getQ().begin()+i))->getT())->isAF()))
                af=new QTableWidgetItem(QString(QString::fromStdString("SI")));
            else
                af=new QTableWidgetItem(QString(QString::fromStdString("NO")));
            lenstab->setItem(j,9,stab);
            lenstab->setItem(j,10,af);
            lenstab->setItem(j,11,diam);
            lenstab->setItem(j,12,angmin);
            if(type=="Zoom"){
                 QTableWidgetItem* angmax=new QTableWidgetItem(QString(QString::number(dynamic_cast<Zoom*>(&(((*modello).getQ().begin()+i))->getT())->getAngoloMax())));
                 lenstab->setItem(j,13,angmax);
            }else
                lenstab->setItem(j,13,new QTableWidgetItem(QString(QString::fromStdString("/"))));
            if(type=="Zoom"){
                QTableWidgetItem* molt;
                if((dynamic_cast<Zoom*>(&(((*modello).getQ().begin()+i))->getT())->hasMoltiplicatore()))
                    molt=new QTableWidgetItem(QString(QString::fromStdString("SI")));
                else
                    molt=new QTableWidgetItem(QString(QString::fromStdString("NO")));
                lenstab->setItem(j,14,molt);
            }else
                lenstab->setItem(j,14,new QTableWidgetItem(QString(QString::fromStdString("/"))));
            ++j;
        }//if
    }//for
}//lensTab

void Listino::setRefTab(){
    list->removeWidget(tab);
    tab->setVisible(false);
    list->removeWidget(acctab);
    acctab->setVisible(false);
    list->removeWidget(lenstab);
    lenstab->setVisible(false);
    list->addWidget(reftab);
    reftab->setVisible(true);
}//setRefTab

void Listino::setAccTab(){
    list->removeWidget(tab);
    tab->setVisible(false);
    list->removeWidget(reftab);
    reftab->setVisible(false);
    list->removeWidget(lenstab);
    lenstab->setVisible(false);
    list->addWidget(acctab);
    acctab->setVisible(true);
}//setAccTab

void Listino::setLensTab(){
    list->removeWidget(tab);
    tab->setVisible(false);
    list->removeWidget(reftab);
    reftab->setVisible(false);
    list->removeWidget(acctab);
    acctab->setVisible(false);
    list->addWidget(lenstab);
    lenstab->setVisible(true);
}//setAccTab

QPushButton* Listino::getRef() const{
    return ref;
}//getRef

QPushButton* Listino::getLens() const{
    return lens;
}//getRef

QPushButton* Listino::getAcc() const{
    return acc;
}//getRef

QTableWidget* Listino::getTable() const{
    return tab;
}//getTable
