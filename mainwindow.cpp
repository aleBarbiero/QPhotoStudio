#include "mainwindow.h"
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

MainWindow::MainWindow(QWidget*):QWidget(),modello(new Model()),menu(new QMenuBar()),main(new QVBoxLayout(this)),file(":/qphotostudio.xml"),
    index(new Index(this)),add(new Add(this)),list(new Listino(this)),search(new Search(this)),det(new Details()){
    //window
    move(QApplication::desktop()->screen()->rect().center()-rect().center());
    setWindowTitle("QPhotoStudio");
    setWindowIcon(QIcon(":/icon/icon.png"));
    setFixedSize(QSize(1200,700));
    //elementi_menu_bar
    QMenu* fileM=new QMenu("File",menu);
    QAction* indexM=new QAction("Home", menu);
    QAction* addM=new QAction("Inserisci", menu);
    QAction* listM=new QAction("Listino",menu);
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
    menu->addAction(listM);
    menu->addAction(searchM);
    menu->addAction(alterM);
    //home
    main->setMenuBar(menu);
    main->addWidget(index);
    main->addWidget(add);
    main->addWidget(list);
    main->addWidget(search);
    indexSet();
    setLayout(main);
    //connect
    connect(saveM,SIGNAL(triggered()),this,SLOT(save()));
    connect(loadM,SIGNAL(triggered()),this,SLOT(load()));
    connect(indexM,SIGNAL(triggered()),this,SLOT(indexSet()));
    connect(addM,SIGNAL(triggered()),this,SLOT(addSet()));
    connect(searchM,SIGNAL(triggered()),this,SLOT(searchSet()));
    connect(add->getAdd(),SIGNAL(clicked()),this,SLOT(addEl()));
    connect(listM,SIGNAL(triggered()),this,SLOT(listSet()));
    connect(search->getDel(),SIGNAL(clicked()),this,SLOT(searchSet()));
    connect(search->getSearch(),SIGNAL(clicked()),this,SLOT(searchEl()));
    connect(search->getTab(),SIGNAL(cellDoubleClicked(int,int)),this,SLOT(showDet(int,int)));
}//MainWindow

void MainWindow::indexSet() const{
    main->setAlignment(Qt::AlignCenter);
    add->hide();
    list->hide();
    search->hide();
    index->show();
}//indexSet

void MainWindow::addSet() const{
    main->setAlignment(Qt::AlignCenter);
    index->hide();
    list->hide();
    search->hide();
    add->show();
}//addSet

void MainWindow::listSet() const{
    main->setAlignment(Qt::AlignCenter);
    index->hide();
    add->hide();
    search->hide();
    list->show();
    list->fullTab(modello);
    list->refTab(modello);
    list->accTab(modello);
    list->lensTab(modello);
}//listSet

void MainWindow::searchSet() const{
    main->setAlignment(Qt::AlignCenter);
    index->hide();
    add->hide();
    list->hide();
    search->show();
    search->goBack(modello);
}

void MainWindow::load(){
    file=(QFileDialog::getOpenFileName(this,"Carica","","Documento XML (*.xml);;All Files (*)"));
    modello->loadF(file);
    list->fullTab(modello);
    list->refTab(modello);
    list->accTab(modello);
    list->lensTab(modello);
    search->goBack(modello);
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
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        return;
    }//if
    if(type=="Reflex" && (add->getPX()<=0 || add->getISOMax()<=0 || add->getISOMin()<=0)){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Reflex" && add->getISOMin()>add->getISOMax()){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Reflex" && (!add->getISOMin() || !add->getISOMax() || !add->getPX())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        return;
    }
    if(type=="Accessorio" && (add->getComp()=="")){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        return;
    }//if
    if(type=="Obiettivo" && (add->getFMin()<=0 || add->getAngMin()<=0 || add->getDiam()<=0 || add->getLungMin()<=0)){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Obiettivo" && (!add->getFMin() || !add->getAngMin() || !add->getDiam() || !add->getLungMin())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        return;
    }
    if(type=="Obiettivo" && add->getComp()==""){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        return;
    }//if
    if(type=="Obiettivo" && add->getTipoOb()!="Focale fissa" && add->getFMax()<=0){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Obiettivo" && add->getTipoOb()!="Focale fissa" && add->getFMin()>=add->getFMax()){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Obiettivo" && add->getTipoOb()!="Focale fissa" && !add->getFMax()){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        return;
    }//if
    if(type=="Obiettivo" && add->getTipoOb()=="Focale fissa" && (add->getLungMax()<=0 || add->getAngMax()<=0)){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Obiettivo" && add->getTipoOb()=="Focale fissa" && (add->getLungMax()<=add->getLungMin() || add->getAngMax()<=add->getAngMin())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        return;
    }else if(type=="Obiettivo" && add->getTipoOb()=="Focale fissa" && (!add->getLungMax() || !add->getAngMax())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
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
    list->fullTab(modello);
    list->refTab(modello);
    list->accTab(modello);
    list->lensTab(modello);
    search->goBack(modello);
}//addEl

void MainWindow::searchEl() const{
    search->find(modello);
}//searchEl

void MainWindow::showDet(int row,int column) const{
    QList<int> temp;
    temp.append(row);
    if(search->getS())
        det->setDet(modello,row,search->getIndex());
    else
        det->setDet(modello,0,temp);
    det->show();
}//showDet)
