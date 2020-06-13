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
    setWindowTitle("QPhotoStudio");
    setWindowIcon(QIcon(":/icon/icon.png"));
    setFixedSize(QSize(1200,700));
    //elementi_menu_bar
    QMenu* fileM=new QMenu("File",menu);
    QAction* indexM=new QAction("Home", menu);
    QAction* addM=new QAction("Inserisci", menu);
    QAction* listM=new QAction("Listino",menu);
    QAction* searchM=new QAction("Modifica/Rimuovi",menu);
    QAction* saveM=new QAction("Salva", fileM);
    QAction* loadM=new QAction("Carica", fileM);
    QAction* exportM=new QAction("Esporta (CSV)",fileM);
    //azioni_menu_bar
    fileM->addAction(saveM);
    fileM->addAction(loadM);
    fileM->addAction(exportM);
    menu->addMenu(fileM);
    menu->addAction(indexM);
    menu->addAction(addM);
    menu->addAction(listM);
    menu->addAction(searchM);
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
    connect(exportM,SIGNAL(triggered()),this,SLOT(exportCSV()));
    connect(indexM,SIGNAL(triggered()),this,SLOT(indexSet()));
    connect(addM,SIGNAL(triggered()),this,SLOT(addSet()));
    connect(searchM,SIGNAL(triggered()),this,SLOT(searchSet()));
    connect(add->getAdd(),SIGNAL(clicked()),this,SLOT(addEl()));
    connect(add->getDel(),SIGNAL(clicked()),this,SLOT(delForm()));
    connect(listM,SIGNAL(triggered()),this,SLOT(listSet()));
    connect(search->getDel(),SIGNAL(clicked()),this,SLOT(searchSet()));
    connect(search->getSearch(),SIGNAL(clicked()),this,SLOT(searchEl()));
    connect(search->getTab(),SIGNAL(cellDoubleClicked(int,int)),this,SLOT(showDet(int)));
    connect(det->getAlter(),SIGNAL(clicked()),this,SLOT(alterEl()));
    connect(det->getRemove(),SIGNAL(clicked()),this,SLOT(removeEl()));
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
    if(file!=nullptr && file!=""){
        modello->loadF(file);
        list->fullTab(modello);
        list->refTab(modello);
        list->accTab(modello);
        list->lensTab(modello);
        search->goBack(modello);
        QMessageBox msg;
        msg.setWindowIcon(QIcon(":/icon/icon.png"));
        msg.setText("Listino caricato con successo");
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        msg.exec();
    }else{
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Nessun file selezionato.");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
    }
}//load

bool MainWindow::save(){
    file=QFileDialog::getSaveFileName(this,"Seleziona un file .xml","","XML (*.xml)");
    if(file!=nullptr && file!=""){
        modello->saveF(file);
        QMessageBox msg;
        msg.setWindowIcon(QIcon(":/icon/icon.png"));
        msg.setText("Listino salvato in formato XML");
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        msg.exec();
        return true;
    }else{
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Nessun file selezionato.");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        return false;
    }
}//save

void MainWindow::exportCSV(){
    modello->exportCSV();
    QMessageBox msg;
    msg.setWindowIcon(QIcon(":/icon/icon.png"));
    msg.setText("Listino esportato in: /output/QPhotoStudio.csv");
    msg.setWindowFlags(Qt::WindowStaysOnTopHint);
    msg.exec();
}

void MainWindow::closeEvent(QCloseEvent* x){
    QMessageBox exit;
    exit.setWindowIcon(QIcon(":/icon/icon.png"));
    exit.setText("Vuoi salvare le modifiche prima di uscire?");
    QAbstractButton* yes=exit.addButton("Si",QMessageBox::YesRole);
    QAbstractButton* no=exit.addButton("No",QMessageBox::NoRole);
    QAbstractButton* canc=exit.addButton("Annulla",QMessageBox::NoRole);
    exit.setWindowFlags(Qt::WindowStaysOnTopHint);
    exit.exec();
    if(exit.clickedButton()==no)
       x->accept();
    else if(exit.clickedButton()==canc)
       x->ignore();
    else if(exit.clickedButton()==yes){
       if(MainWindow::save())
           x->accept();
       else
           x->ignore();
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
    if(type=="Obiettivo" && add->getTipoOb()=="Zoom")
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

void MainWindow::showDet(int row){
    pos=row;
    QList<int> temp;
    temp.append(row);
    if(search->getS()){
        det->setDet(modello,row,search->getIndex());
        pos=(search->getIndex())[row];
    }else
        det->setDet(modello,0,temp);
    det->show();
}//showDet

void MainWindow::removeEl(){
    QMessageBox sure;
    sure.setWindowIcon(QIcon(":/icon/icon.png"));
    sure.setText("Vuoi veramente eliminare il prodotto selezionato?");
    QAbstractButton* si=sure.addButton("Conferma",QMessageBox::YesRole);
    sure.addButton("Annulla",QMessageBox::NoRole);
    sure.setWindowFlags(Qt::WindowStaysOnTopHint);
    sure.exec();
    if(sure.clickedButton()==si){
        modello->remove(pos);
        list->fullTab(modello);
        list->refTab(modello);
        list->accTab(modello);
        list->lensTab(modello);
        if(search->getS())
            search->find(modello);
        else
            search->goBack(modello);
        det->hide();
    }//if
}//removeEl

void MainWindow::alterEl(){
    det->hide();
    string type=det->getTipoProd();
    if(det->getMarca()=="" || det->getModello()=="" || !det->getPrezzo()){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }//if
    if(type=="Reflex" && (det->getPX()<=0 || det->getISOMax()<=0 || det->getISOMin()<=0)){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }else if(type=="Reflex" && det->getISOMin()>det->getISOMax()){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }else if(type=="Reflex" && (!det->getISOMin() || !det->getISOMax() || !det->getPX())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }
    if(type=="Accessorio" && (det->getComp()=="")){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }//if
    if(type=="Obiettivo" && (det->getFMin()<=0 || det->getAngMin()<=0 || det->getDiam()<=0 || det->getLungMin()<=0)){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }else if(type=="Obiettivo" && (!det->getFMin() || !det->getAngMin() || !det->getDiam() || !det->getLungMin())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }
    if(type=="Obiettivo" && det->getComp()==""){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }//if
    if(type=="Obiettivo" && det->getTipoOb()!="Focale fissa" && det->getFMax()<=0){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }else if(type=="Obiettivo" && det->getTipoOb()!="Focale fissa" && det->getFMin()>=add->getFMax()){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }else if(type=="Obiettivo" && det->getTipoOb()!="Focale fissa" && !det->getFMax()){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }//if
    if(type=="Obiettivo" && det->getTipoOb()=="Focale fissa" && (det->getLungMax()<=0 || det->getAngMax()<=0)){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }else if(type=="Obiettivo" && det->getTipoOb()=="Focale fissa" && (det->getLungMax()<=det->getLungMin() || det->getAngMax()<=det->getAngMin())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Controlla i valori numerici");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }else if(type=="Obiettivo" && det->getTipoOb()=="Focale fissa" && (!det->getLungMax() || !det->getAngMax())){
        QMessageBox msg;
        msg.critical(nullptr,"Errore","Compila tutti i campi");
        msg.setFixedSize(500,200);
        msg.setWindowFlags(Qt::WindowStaysOnTopHint);
        det->show();
        return;
    }//if
    if(type=="Reflex"){
        bool trop=false;
        if(det->getTrop()=="SI")
            trop=true;
        Reflex* el=new Reflex(det->getMarca(),det->getModello(),det->getPrezzo(),det->getISOMin(),det->getISOMax(),det->getPX(),Reflex::fromStrToType(det->getFormato()),trop);
        modello->alter(pos,el);
    }else if(type=="Accessorio"){
        Accessory* el=new Accessory(det->getMarca(),det->getModello(),det->getPrezzo(),Accessory::fromStrToType(det->getTipoAcc()),det->getComp(),det->getInfo());
        modello->alter(pos,el);
    }else if(type=="Obiettivo" && det->getTipoOb()=="Zoom"){
        bool stab=false,af=false,molt=false;
        if(det->getStab()=="SI")
            stab=true;
        if(det->getAF()=="SI")
            af=true;
        if(det->getMolt()=="SI")
            molt=true;
        Zoom* el=new Zoom(det->getMarca(),det->getModello(),det->getPrezzo(),det->getLungMin(),det->getLungMax(),det->getFMin(),det->getFMax(),det->getComp(),stab,af,det->getAngMin(),det->getAngMax(),det->getDiam(),molt);
        modello->alter(pos,el);
    }else if(type=="Obiettivo" && det->getTipoOb()=="Focale fissa"){
        bool stab=false,af=false;
        if(det->getStab()=="SI")
            stab=true;
        if(det->getAF()=="SI")
            af=true;
        Aperture* el=new Aperture(det->getMarca(),det->getModello(),det->getPrezzo(),det->getLungMin(),det->getLungMax(),det->getFMin(),det->getComp(),stab,af,det->getAngMin(),det->getAngMax(),det->getDiam());
        modello->alter(pos,el);
    }else if(type=="Obiettivo" && det->getTipoOb()=="Lunghezza fissa"){
        bool stab=false,af=false;
        if(det->getStab()=="SI")
            stab=true;
        if(det->getAF()=="SI")
            af=true;
        Length* el=new Length(det->getMarca(),det->getModello(),det->getPrezzo(),det->getLungMin(),det->getFMin(),det->getFMax(),det->getComp(),stab,af,det->getAngMin(),det->getDiam());
        modello->alter(pos,el);
    }//modifica
    list->fullTab(modello);
    list->refTab(modello);
    list->accTab(modello);
    list->lensTab(modello);
    search->goBack(modello);
    QMessageBox msg;
    msg.setWindowIcon(QIcon(":/icon/icon.png"));
    msg.setText("Modifica effettuata con successo");
    msg.setFixedSize(500,200);
    msg.setWindowFlags(Qt::WindowStaysOnTopHint);
    msg.exec();
}//alterEl

void MainWindow::delForm() const{
    add->delElement();
}
