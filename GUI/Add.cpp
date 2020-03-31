#include "Add.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QIntValidator>
#include <QDoubleValidator>

Add::Add(QWidget* wid):QWidget(wid),qfl(new QFormLayout()),qgb(new QGroupBox("Aggiunta nuova prodotto")),img(new QHBoxLayout()),button(new QHBoxLayout()),marcaL(new QLabel("Marca")),modelloL(new QLabel("Modello")),tipoProdL(new QLabel("Tipologia prodotto")),compL(new QLabel("Compatibilità")),
    ISOminL(new QLabel("ISO (min)")),ISOmaxL(new QLabel("ISO (max)")),pxL(new QLabel("Pixel")),formatoL(new QLabel("Formato")),tropL(new QLabel("Tropicalizzazione")),
    tipoAccL(new QLabel("Tipologia accessorio")),infoL(new QLabel("Note")),tipoObL(new QLabel("Tipologia obiettivo")),lungMinL(new QLabel("Lunghezza focale")),lungMaxL(new QLabel("Lunghezza focale (max)")),
    fMinL(new QLabel("f/")),fMaxL(new QLabel("(max) f/")),stabL(new QLabel("Stabilizzazione")),AFL(new QLabel("Automatic focus")),angMinL(new QLabel("Angolo")),angMaxL(new QLabel("Angolo (max)")),
    diamL(new QLabel("Diametro lente")),moltL(new QLabel("Compatibilità moltiplicatore")),imgL(new QLabel(this)),add(new QPushButton("Aggiungi",this)),del(new QPushButton("Azzera form",this)){
    //controlli_input
    ISOminValue->setValidator(new QIntValidator(0,100000,this));
    ISOmaxValue->setValidator(new QIntValidator(0,100000,this));
    pxValue->setValidator(new QIntValidator(0,1000,this));
    lungMinValue->setValidator(new QIntValidator(5,2000,this));
    lungMaxValue->setValidator(new QIntValidator(5,2000,this));
    diamValue->setValidator(new QIntValidator(10,150,this));
    fMinValue->setValidator(new QDoubleValidator(0.3,50.0,2,this));
    fMaxValue->setValidator(new QDoubleValidator(0.3,50.0,2,this));
    angMinValue->setValidator(new QDoubleValidator(5.0,200.0,2,this));
    angMaxValue->setValidator(new QDoubleValidator(5.0,200.0,2,this));
    tipoProdValue->addItem("Reflex");
    tipoProdValue->addItem("Obiettivo");
    tipoProdValue->addItem("Accessorio");
    tipoObValue->addItem("Focale fissa");
    tipoObValue->addItem("Lunghezza fissa");
    tipoObValue->addItem("Zoom variabile");
    tipoAccValue->addItem("MemoryCard");
    tipoAccValue->addItem("Zaini e borse");
    tipoAccValue->addItem("Treppiedi");
    tipoAccValue->addItem("Filtri");
    tipoAccValue->addItem("Altro");
    formatoValue->addItem("DSLR");
    formatoValue->addItem("Fullframe");
    formatoValue->addItem("Mirrorless");
    //form_base
    qfl->addRow(marcaL,marcaValue);
    qfl->addRow(modelloL,modelloValue);
    qfl->addRow(tipoProdL,tipoProdValue);
    //main_layout
    QVBoxLayout* mainLayout=new QVBoxLayout(this);
    mainLayout->addWidget(qgb);
    mainLayout->addLayout(img);
    mainLayout->addWidget(del);
    mainLayout->addWidget(add);
    //connect
    connect(tipoProdValue,SIGNAL(currentTextChanged(QString)),this,SLOT(modify(QString)));
    connect(tipoObValue,SIGNAL(currentTextChanged(QString)),this,SLOT(modify(QString)));
    connect(del,SIGNAL(clicked()),this,SLOT(delElement()));
    //emit
    emit(tipoProdValue->currentTextChanged(tipoProdValue->currentText()));
}//Add

void Add::modify(QString type){
    if(type=="Reflex"){
        delForm();
        qfl->addRow(ISOminL,ISOminValue);
        qfl->addRow(ISOmaxL,ISOmaxValue);
        qfl->addRow(pxL,pxValue);
        qfl->addRow(formatoL,formatoValue);
        qfl->addRow(tropL,tropValue);
        ISOminL->setVisible(true);
        ISOminValue->setVisible(true);
        ISOmaxL->setVisible(true);
        ISOmaxValue->setVisible(true);
        pxL->setVisible(true);
        pxValue->setVisible(true);
        formatoL->setVisible(true);
        formatoValue->setVisible(true);
        tropL->setVisible(true);
        tropValue->setVisible(true);
        QPixmap imm=QPixmap(":/images/camera.png");
        imm=imm.scaled(imgL->size(),Qt::KeepAspectRatio);
        imgL->setPixmap(imm);
        img->addWidget(imgL);
    }else if(type=="Accessorio"){
        delForm();
        qfl->addRow(tipoAccL,tipoAccValue);
        qfl->addRow(compL,compValue);
        qfl->addRow(infoL,infoValue);
        tipoAccL->setVisible(true);
        tipoAccValue->setVisible(true);
        compL->setVisible(true);
        compValue->setVisible(true);
        infoL->setVisible(true);
        infoValue->setVisible(true);
        QPixmap imm=QPixmap(":/images/accessory.png");
        imm=imm.scaled(imgL->size(),Qt::KeepAspectRatio);
        imgL->setPixmap(imm);
        img->addWidget(imgL);
    }else{
        delForm();
        qfl->addRow(tipoObL,tipoObValue);
        tipoObL->setVisible(true);
        tipoObValue->setVisible(true);
        QPixmap imm=QPixmap(":/images/lens.png");
        imm=imm.scaled(imgL->size(),Qt::KeepAspectRatio);
        imgL->setPixmap(imm);
        img->addWidget(imgL);
    }
    if(type=="Focale fissa"){
        delForm();
        qfl->addRow(tipoObL,tipoObValue);
        qfl->addRow(lungMinL,lungMinValue);
        qfl->addRow(lungMaxL,lungMaxValue);
        qfl->addRow(fMinL,fMinValue);
        qfl->addRow(stabL,stabValue);
        qfl->addRow(AFL,AFValue);
        qfl->addRow(angMinL,angMinValue);
        qfl->addRow(angMaxL,angMaxValue);
        qfl->addRow(diamL,diamValue);
        tipoObL->setVisible(true);
        tipoObValue->setVisible(true);
        lungMinL->setVisible(true);
        lungMinValue->setVisible(true);
        lungMaxL->setVisible(true);
        lungMaxValue->setVisible(true);
        fMinL->setVisible(true);
        fMinValue->setVisible(true);
        stabL->setVisible(true);
        stabValue->setVisible(true);
        AFL->setVisible(true);
        AFValue->setVisible(true);
        angMinL->setVisible(true);
        angMinValue->setVisible(true);
        angMaxL->setVisible(true);
        angMaxValue->setVisible(true);
        diamL->setVisible(true);
        diamValue->setVisible(true);
        QPixmap imm=QPixmap(":/images/lens.png");
        imm=imm.scaled(imgL->size(),Qt::KeepAspectRatio);
        imgL->setPixmap(imm);
        img->addWidget(imgL);
    }else if(type=="Lunghezza fissa"){
        delForm();
        qfl->addRow(tipoObL,tipoObValue);
        qfl->addRow(lungMinL,lungMinValue);
        qfl->addRow(fMinL,fMinValue);
        qfl->addRow(fMaxL,fMaxValue);
        qfl->addRow(stabL,stabValue);
        qfl->addRow(AFL,AFValue);
        qfl->addRow(angMinL,angMinValue);
        qfl->addRow(diamL,diamValue);
        tipoObL->setVisible(true);
        tipoObValue->setVisible(true);
        lungMinL->setVisible(true);
        lungMinValue->setVisible(true);
        fMinL->setVisible(true);
        fMinValue->setVisible(true);
        fMaxL->setVisible(true);
        fMaxValue->setVisible(true);
        stabL->setVisible(true);
        stabValue->setVisible(true);
        AFL->setVisible(true);
        AFValue->setVisible(true);
        angMinL->setVisible(true);
        angMinValue->setVisible(true);
        diamL->setVisible(true);
        diamValue->setVisible(true);
        QPixmap imm=QPixmap(":/images/lens.png");
        imm=imm.scaled(imgL->size(),Qt::KeepAspectRatio);
        imgL->setPixmap(imm);
        img->addWidget(imgL);
    }else if(type=="Zoom variabile"){
        delForm();
        qfl->addRow(tipoObL,tipoObValue);
        qfl->addRow(lungMinL,lungMinValue);
        qfl->addRow(lungMaxL,lungMaxValue);
        qfl->addRow(fMinL,fMinValue);
        qfl->addRow(fMaxL,fMaxValue);
        qfl->addRow(stabL,stabValue);
        qfl->addRow(AFL,AFValue);
        qfl->addRow(angMinL,angMinValue);
        qfl->addRow(angMaxL,angMaxValue);
        qfl->addRow(diamL,diamValue);
        tipoObL->setVisible(true);
        tipoObValue->setVisible(true);
        lungMinL->setVisible(true);
        lungMinValue->setVisible(true);
        lungMaxL->setVisible(true);
        lungMaxValue->setVisible(true);
        fMinL->setVisible(true);
        fMinValue->setVisible(true);
        fMaxL->setVisible(true);
        fMaxValue->setVisible(true);
        stabL->setVisible(true);
        stabValue->setVisible(true);
        AFL->setVisible(true);
        AFValue->setVisible(true);
        angMinL->setVisible(true);
        angMinValue->setVisible(true);
        angMaxL->setVisible(true);
        angMaxValue->setVisible(true);
        diamL->setVisible(true);
        diamValue->setVisible(true);
        QPixmap imm=QPixmap(":/images/lens.png");
        imm=imm.scaled(imgL->size(),Qt::KeepAspectRatio);
        imgL->setPixmap(imm);
        img->addWidget(imgL);
    }
}//modify

void Add::delElement() const{
    marcaValue->clear();
    modelloValue->clear();
    tipoProdValue->clear();
    compValue->clear();
    //reflex
    ISOminValue->clear();
    ISOmaxValue->clear();
    pxValue->clear();
    formatoValue->clear();
    tropValue->setChecked(false);
    //accessori
    tipoAccValue->clear();
    infoValue->clear();
    //obiettivi
    tipoObValue->clear();
    lungMinValue->clear();
    lungMaxValue->clear();
    fMinValue->clear();
    fMaxValue->clear();
    stabValue->setChecked(false);
    AFValue->setChecked(false);
    angMinValue->clear();
    angMaxValue->clear();
    diamValue->clear();
    moltValue->setChecked(false);
}//delElement

void Add::delForm() const{
    qfl->removeWidget(compL);
    qfl->removeWidget(compValue);
    qfl->removeWidget(ISOminL);
    qfl->removeWidget(ISOminValue);
    qfl->removeWidget(ISOmaxL);
    qfl->removeWidget(ISOmaxValue);
    qfl->removeWidget(pxL);
    qfl->removeWidget(pxValue);
    qfl->removeWidget(formatoL);
    qfl->removeWidget(formatoValue);
    qfl->removeWidget(tropL);
    qfl->removeWidget(tropValue);
    qfl->removeWidget(tipoAccL);
    qfl->removeWidget(tipoAccValue);
    qfl->removeWidget(infoL);
    qfl->removeWidget(tipoObL);
    qfl->removeWidget(tipoObValue);
    qfl->removeWidget(infoValue);
    qfl->removeWidget(lungMaxL);
    qfl->removeWidget(lungMaxValue);
    qfl->removeWidget(lungMinL);
    qfl->removeWidget(lungMinValue);
    qfl->removeWidget(fMinL);
    qfl->removeWidget(fMinValue);
    qfl->removeWidget(fMaxL);
    qfl->removeWidget(fMaxValue);
    qfl->removeWidget(stabL);
    qfl->removeWidget(stabValue);
    qfl->removeWidget(AFL);
    qfl->removeWidget(AFValue);
    qfl->removeWidget(angMaxL);
    qfl->removeWidget(angMaxValue);
    qfl->removeWidget(angMinL);
    qfl->removeWidget(angMinValue);
    qfl->removeWidget(diamL);
    qfl->removeWidget(diamValue);
    qfl->removeWidget(moltL);
    qfl->removeWidget(moltValue);
    compL->setVisible(false);
    ISOminL->setVisible(false);
    ISOmaxL->setVisible(false);
    pxL->setVisible(false);
    formatoL->setVisible(false);
    tropL->setVisible(false);
    tipoAccL->setVisible(false);
    infoL->setVisible(false);
    tipoObL->setVisible(false);
    lungMinL->setVisible(false);
    lungMaxL->setVisible(false);
    fMinL->setVisible(false);
    fMaxL->setVisible(false);
    stabL->setVisible(false);
    AFL->setVisible(false);
    angMinL->setVisible(false);
    angMaxL->setVisible(false);
    diamL->setVisible(false);
    moltL->setVisible(false);
    compValue->setVisible(false);
    ISOminValue->setVisible(false);
    ISOmaxValue->setVisible(false);
    pxValue->setVisible(false);
    formatoValue->setVisible(false);
    tropValue->setVisible(false);
    tipoAccValue->setVisible(false);
    infoValue->setVisible(false);
    lungMinValue->setVisible(false);
    lungMaxValue->setVisible(false);
    fMinValue->setVisible(false);
    fMaxValue->setVisible(false);
    stabValue->setVisible(false);
    AFValue->setVisible(false);
    angMinValue->setVisible(false);
    angMaxValue->setVisible(false);
    diamValue->setVisible(false);
    moltValue->setVisible(false);
}//delForm

//modificatori
void Add::setAF(bool b){
    if(b)
        AFValue->setChecked(true);
    else
        AFValue->setChecked(false);
}//setAF

void Add::setPX(QString s){
    pxValue->setText(s);
}//setPX

void Add::setComp(QString s){
    compValue->setText(s);
}//setComp

void Add::setDiam(QString s){
    diamValue->setText(s);
}//setDiam

void Add::setFMax(QString s){
    fMaxValue->setText(s);
}//setFMax

void Add::setFMin(QString s){
    fMinValue->setText(s);
}//setFMax

void Add::setInfo(QString s){
    infoValue->setText(s);
}//setInfo

void Add::setMolt(bool b){
    if(b)
        moltValue->setChecked(true);
    else
        moltValue->setChecked(false);
}//setMolt

void Add::setStab(bool b){
    if(b)
        stabValue->setChecked(true);
    else
        stabValue->setChecked(false);
}//setStab

void Add::setTrop(bool b){
    if(b)
        tropValue->setChecked(true);
    else
        tropValue->setChecked(false);
}//setTrop

void Add::setMarca(QString s){
    marcaValue->setText(s);
}//setMarca

void Add::setAngMax(QString s){
    angMaxValue->setText(s);
}//setAngMax

void Add::setAngMin(QString s){
    angMinValue->setText(s);
}//setAngMin

void Add::setISOMax(QString s){
    ISOmaxValue->setText(s);
}//setISOMax

void Add::setISOMin(QString s){
    ISOminValue->setText(s);
}//setISOMin

void Add::setTipoOb(QString s){
    tipoObValue->setCurrentText(s);
}//setTipoOb

void Add::setFormato(QString s){
    formatoValue->setCurrentText(s);
}//setFormato

void Add::setLungMax(QString s){
    lungMaxValue->setText(s);
}//setLungMax

void Add::setLungMin(QString s){
    lungMinValue->setText(s);
}//setLungMin

void Add::setModello(QString s){
    modelloValue->setText(s);
}//setModello

void Add::setTipoAcc(QString s){
    tipoAccValue->setCurrentText(s);
}//setTipoAcc

void Add::setTipoProd(QString s){
    tipoProdValue->setCurrentText(s);
}//setTipoAcc

string Add::getMarca() const{
     return marcaValue->text().toStdString();
}//getMarca

string Add::getModello() const{
     return modelloValue->text().toStdString();
}//getModello

string Add::getTipoProd() const{
    return tipoProdValue->currentText().toStdString();
}//getTipoProdotto

string Add::getComp() const{
     return compValue->text().toStdString();
}//getComp

unsigned int Add::getISOMin() const{
    return static_cast<unsigned int>(ISOminValue->text().toInt());
}//getISOMin

unsigned int Add::getISOMax() const{
    return static_cast<unsigned int>(ISOmaxValue->text().toInt());
}//getISOMax

unsigned int Add::getPX() const{
    return static_cast<unsigned int>(pxValue->text().toInt());
}//getPx

string Add::getFormato() const{
    return formatoValue->currentText().toStdString();
}//getFormato

bool Add::getTrop() const{
    return tropValue->isChecked();
}//getTrop

string Add::getTipoAcc() const{
    return tipoAccValue->currentText().toStdString();
}//getTipoAcc

string Add::getInfo() const{
     return infoValue->text().toStdString();
}//getInfo

string Add::getTipoOb() const{
    return tipoObValue->currentText().toStdString();
}//getTipoOb

unsigned int Add::getLungMin() const{
    return static_cast<unsigned int>(lungMinValue->text().toInt());
}//getLungMin

unsigned int Add::getLungMax() const{
    return static_cast<unsigned int>(lungMinValue->text().toInt());
}//getLungMax

float Add::getFMin() const{
    return fMinValue->text().toFloat();
}//getFMin

float Add::getFMax() const{
    return fMaxValue->text().toFloat();
}//getFMax

bool Add::getStab() const{
    return stabValue->isChecked();
}//getStab

bool Add::getAF() const{
    return AFValue->isChecked();
}//getAF

float Add::getAngMin() const{
    return angMinValue->text().toFloat();
}//getAngMin

float Add::getAngMax() const{
    return angMaxValue->text().toFloat();
}//getAngMax

unsigned int Add::getDiam() const{
    return static_cast<unsigned int>(diamValue->text().toInt());
}//getDiam

bool Add::getMolt() const{
    return moltValue->isChecked();
}//getMolt

QPushButton* Add::getAdd() const{
    return add;
}//getAdd

QPushButton* Add::getDel() const{
    return del;
}//getDel
