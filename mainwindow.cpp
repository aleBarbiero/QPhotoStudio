#include "mainwindow.h"
#include "model/Product.h"
#include "model/Reflex.h"
#include "model/Accessory.h"
#include "model/Lens.h"
#include "model/Aperture.h"
#include "model/Length.h"
#include "model/Zoom.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QString>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QApplication>
#include <QCloseEvent>
#include <QLayout>
#include <QGuiApplication>

MainWindow::MainWindow(QWidget*):QWidget(),modello(new Model()),menu(new QMenuBar()),main(new QVBoxLayout(this)),file(":/qphotostudio.xml"),index(new Index(this)),add(new Add(this)){
    //window
    move(QApplication::desktop()->screen()->rect().center()-rect().center());
    setWindowTitle("QPhotoStudio");
    setWindowIcon(QIcon(":/icon/icon.png"));
    setFixedSize(QSize(1200,700));
    //elementi_menu_bar
    QMenu* fileM=new QMenu("File",menu);
    QAction* indexM=new QAction("Home", menu);
    QAction* addM=new QAction("Inserisci", menu);
    QAction* searchM=new QAction("Ricerca",menu);
    QAction* alterM=new QAction("Modifica/Rimuovi",menu);
    QAction* saveM=new QAction("Salva", fileM);
    QAction* loadM=new QAction("Carica", fileM);
    //azioni_menu_bar
    fileM->addAction(saveM);
    fileM->addAction(loadM);
    menu->addMenu(fileM);
    menu->addAction(indexM);
    menu->addAction(addM);
    menu->addAction(searchM);
    menu->addAction(alterM);
    //home
    main->setMenuBar(menu);
    main->addWidget(index);
    main->addWidget(add);
    indexSet();
    setLayout(main);
    //connect
    connect(saveM,SIGNAL(triggered()),this,SLOT(save()));
    connect(loadM,SIGNAL(triggered()),this,SLOT(load()));
    connect(indexM,SIGNAL(triggered()),this,SLOT(indexSet()));
    connect(addM,SIGNAL(triggered()),this,SLOT(addSet()));
    connect(add->getAdd(),SIGNAL(clicked()),this,SLOT(addEl()));
    /*connect(search->getFindB(),SIGNAL(clicked()),this,SLOT(searchEl()));
    connect(list->getDelB(),SIGNAL(clicked()),this,SLOT(delEl()));*/
}//MainWindow

void MainWindow::indexSet() const{
    main->setAlignment(Qt::AlignCenter);
    add->hide();
    index->show();
}//indexSet

void MainWindow::addSet() const{
    main->setAlignment(Qt::AlignCenter);
    index->hide();
    add->show();
}//addSet

void MainWindow::load(){
    file=(QFileDialog::getOpenFileName(this,"Carica","","Documento XML (*.xml);;All Files (*)"));
    modello->loadF(file);
    //mancano i refresh dei listini
}//load

void MainWindow::save(){
    file=QFileDialog::getSaveFileName(this,"Seleziona un file .xml","","XML (*.xml)");
    modello->saveF(file);
}//save

void MainWindow::closeEvent(QCloseEvent* x){
    QMessageBox::StandardButton exit=QMessageBox::question(this,"QPhotoStudio","Salvare le modifiche prima di uscire?",QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,QMessageBox::Yes);
    if(exit==QMessageBox::No)
        x->accept();
    else if(exit==QMessageBox::Cancel)
            x->ignore();
         else{
            MainWindow::save();
            x->accept();
    }//if_else
}//close

void MainWindow::addEl(){
    string type=add->getTipoProd();
    if(add->getMarca()=="" || add->getModello()=="" || !add->getPrezzo()){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi 1");
        msg.setFixedSize(500,200);
        return;
    }//if
    if(type=="Reflex" && (add->getPX()<=0 || add->getISOMax()<=0 || add->getISOMin()<=0)){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Inserisci solo valori positivi 2");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Reflex" && add->getISOMin()>add->getISOMax()){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici 3");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Reflex" && (!add->getISOMin() || !add->getISOMax() || !add->getPX())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi 4");
        msg.setFixedSize(500,200);
        return;
    }
    if(type=="Accessorio" && (add->getComp()=="")){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi 5");
        msg.setFixedSize(500,200);
        return;
    }//if
    if(type=="Obiettivo" && (add->getFMin()<=0 || add->getAngMin()<=0 || add->getDiam()<=0 || add->getLungMin()<=0)){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Inserisci solo valori positivi 6");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Obiettivo" && (!add->getFMin() || !add->getAngMin() || !add->getDiam() || !add->getLungMin())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi 7");
        msg.setFixedSize(500,200);
        return;
    }
    if(type=="Obiettivo" && add->getComp()==""){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi 8");
        msg.setFixedSize(500,200);
        return;
    }//if
    if(type=="Obiettivo" && add->getTipoOb()!="Focale fissa" && add->getFMax()<=0){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Inserisci solo valori positivi 9");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Obiettivo" && add->getTipoOb()!="Focale fissa" && add->getFMin()>=add->getFMax()){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici 10");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Obiettivo" && add->getTipoOb()!="Focale fissa" && !add->getFMax()){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi 11");
        msg.setFixedSize(500,200);
        return;
    }//if
    if(type=="Obiettivo" && add->getTipoOb()=="Focale fissa" && (add->getLungMax()<=0 || add->getAngMax()<=0)){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Inserisci solo valori positivi 12");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Obiettivo" && add->getTipoOb()=="Focale fissa" && (add->getLungMax()<=add->getLungMin() || add->getAngMax()<=add->getAngMin())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici 13");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Obiettivo" && add->getTipoOb()=="Focale fissa" && (!add->getLungMax() || !add->getAngMax())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi 14");
        msg.setFixedSize(500,200);
        return;
    }//if
    string marca=add->getMarca();
    string mod=add->getModello();
    float prezzo=add->getPrezzo();
    if(type=="Reflex")
        modello->insert(new Reflex(marca,mod,prezzo,add->getISOMin(),add->getISOMax(),add->getPX(),Reflex::fromStrToType(add->getFormato()),add->getTrop()));
    if(type=="Accessorio")
        modello->insert(new Accessory(marca,mod,prezzo,Accessory::fromStrToType(add->getTipoAcc()),add->getComp(),add->getInfo()));
    if(type=="Obiettivo" && add->getTipoOb()=="Zoom variabile")
        modello->insert(new Zoom(marca,mod,prezzo,add->getLungMin(),add->getLungMax(),add->getFMin(),add->getFMax(),add->getComp(),add->getStab(),add->getAF(),add->getAngMin(),add->getAngMax(),add->getDiam(),add->getMolt()));
    if(type=="Obiettivo" && add->getTipoOb()=="Focale fissa")
        modello->insert(new Aperture(marca,mod,prezzo,add->getLungMin(),add->getLungMax(),add->getFMin(),add->getComp(),add->getStab(),add->getAF(),add->getAngMin(),add->getAngMax(),add->getDiam()));
    if(type=="Obiettivo" && add->getTipoOb()=="Lunghezza fissa")
         modello->insert(new Length(marca,mod,prezzo,add->getLungMin(),add->getFMin(),add->getFMax(),add->getComp(),add->getStab(),add->getAF(),add->getAngMin(),add->getDiam()));
    add->delElement();
    /*list->fullTab(modello);   REFRESH SULLE TABELLE
    search->fullTab(modello);
    search->setIndex(modello);*/
}//addEl
