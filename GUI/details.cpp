#include "details.h"
#include <QApplication>
#include <QDesktopWidget>

Details::Details(QWidget* q):QWidget(q),qgb(new QGroupBox()),qfl(new QFormLayout()),marcaL(new QLabel("Marca")),modelloL(new QLabel("Modello")),tipoProdL(new QLabel("Tipologia prodotto")),compL(new QLabel("Compatibilità")),
        prezzoL(new QLabel("Prezzo")),ISOminL(new QLabel("ISO(min)")),ISOmaxL(new QLabel("ISO(max)")),pxL(new QLabel("Megapixels")),formatoL(new QLabel("Formato")),tropL(new QLabel("Tropicalizzazione")),tipoAccL(new QLabel("Tipologia accessorio")),infoL(new QLabel("Note(opzionali)")),tipoObL(new QLabel("Tipologia obiettivo")),
        lungMinL(new QLabel("Lunghezza focale")),lungMaxL(new QLabel("Lunghezza focale(max)")),fMinL(new QLabel("f/")),fMaxL(new QLabel("f/(max)")),stabL(new QLabel("Stabilizzazione")),AFL(new QLabel("Automatic focus")),angMinL(new QLabel("Angolo")),angMaxL(new QLabel("Angolo(max)")),
        diamL(new QLabel("Diametro lente(mm)")),moltL(new QLabel("Compatibilità moltiplicatore")),marcaValue(new QLabel("")),modelloValue(new QLabel("")),tipoProdValue(new QLabel("")),compValue(new QLineEdit(this)),prezzoValue(new QLineEdit(this)),ISOminValue(new QLineEdit(this)),ISOmaxValue(new QLineEdit(this)),
        pxValue(new QLineEdit(this)),formatoValue(new QLabel("")),tropValue(new QCheckBox(this)),tipoAccValue(new QLabel("")),infoValue(new QLineEdit(this)),tipoObValue(new QLabel("")),lungMinValue(new QLineEdit(this)),lungMaxValue(new QLineEdit(this)),
        fMinValue(new QLineEdit(this)),fMaxValue(new QLineEdit(this)),stabValue(new QCheckBox(this)),AFValue(new QCheckBox(this)),angMinValue(new QLineEdit(this)),angMaxValue(new QLineEdit(this)),diamValue(new QLineEdit(this)),
        moltValue(new QCheckBox(this)),alter(new QPushButton("Modifica")),remove(new QPushButton("Rimuovi")){
    //controlli_input
    prezzoValue->setValidator(new QDoubleValidator(1.00,15000.00,2,this));
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
    setWindowTitle("QPhotoStudio - Dettagli");
    setWindowIcon(QIcon(":/icon/icon.png"));
    qfl->addRow(marcaL,marcaValue);
    qfl->addRow(modelloL,modelloValue);
    qfl->addRow(tipoProdL,tipoProdValue);
    qfl->addRow(prezzoL,prezzoValue);
    tipoProdL->setVisible(true);
    tipoProdValue->setVisible(true);
    marcaL->setVisible(true);
    marcaValue->setVisible(true);
    prezzoL->setVisible(true);
    prezzoValue->setVisible(true);
    qgb->setLayout(qfl);
    //main_layout
    QVBoxLayout* mainLayout=new QVBoxLayout(this);
    QHBoxLayout* buttonL=new QHBoxLayout();
    buttonL->addWidget(alter);
    buttonL->addWidget(remove);
    mainLayout->addWidget(qgb);
    mainLayout->addLayout(buttonL);
}//Details

void Details::setDet(Model* modello,int pos,QList<int> list){
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
    this->delDet();
    int row=list[pos];
    QString type=QString(QString::fromStdString((((*modello).getQ().begin()+row))->getT().getType()));
    QString marca=QString(QString::fromStdString((((*modello).getQ().begin()+row))->getT().getMarca()));
    QString mod=QString(QString::fromStdString((((*modello).getQ().begin()+row))->getT().getNomeModello()));
    QString prezzo=QString(QString::number((((*modello).getQ().begin()+row))->getT().getPrezzo()));
    QString title=marca+" - "+mod;
    qgb->setTitle(title);
    tipoProdValue->setText(type);
    marcaValue->setText(marca);
    modelloValue->setText(mod);
    prezzoValue->setText(prezzo);
    if(type=="Reflex"){
        QString ISOmin=QString(QString::number((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+row)->getT())))->getISOmin()));
        QString ISOmax=QString(QString::number((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+row)->getT())))->getISOmax()));
        QString px=QString(QString::number((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+row)->getT())))->getPX()));
        QString formato=QString(QString::fromStdString((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+row)->getT())))->getFormato()));
        QString trop;
        if((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+row))->getT())->isTropicalizzato()))
            tropValue->setChecked(true);
        else
            tropValue->setChecked(false);
        qfl->addRow(ISOminL,ISOminValue);
        qfl->addRow(ISOmaxL,ISOmaxValue);
        qfl->addRow(pxL,pxValue);
        qfl->addRow(formatoL,formatoValue);
        qfl->addRow(tropL,tropValue);
        ISOminValue->setText(ISOmin);
        ISOmaxValue->setText(ISOmax);
        pxValue->setText(px);
        formatoValue->setText(formato);
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
    }else if(type=="Accessorio"){
        QString tipo=QString(QString::fromStdString((dynamic_cast<Accessory*>(&(((*modello).getQ().begin()+row)->getT())))->getTipologia()));
        QString comp=QString(QString::fromStdString((dynamic_cast<Accessory*>(&(((*modello).getQ().begin()+row)->getT())))->getCompatibilita()));
        QString info=QString(QString::fromStdString((dynamic_cast<Accessory*>(&(((*modello).getQ().begin()+row)->getT())))->getInfo()));
        qfl->addRow(tipoAccL,tipoAccValue);
        qfl->addRow(compL,compValue);
        qfl->addRow(infoL,infoValue);
        tipoAccValue->setText(tipo);
        compValue->setText(comp);
        infoValue->setText(info);
        tipoAccL->setVisible(true);
        tipoAccValue->setVisible(true);
        compL->setVisible(true);
        compValue->setVisible(true);
        infoL->setVisible(true);
        infoValue->setVisible(true);
    }else{
        //tipoProdValue->setText("Obiettivo - "+tipoProdValue->text());
        qfl->addRow(compL,compValue);
        qfl->addRow(lungMinL,lungMinValue);
        qfl->addRow(lungMaxL,lungMaxValue);
        qfl->addRow(fMinL,fMinValue);
        qfl->addRow(fMaxL,fMaxValue);
        qfl->addRow(stabL,stabValue);
        qfl->addRow(diamL,diamValue);
        qfl->addRow(angMinL,angMinValue);
        qfl->addRow(angMaxL,angMaxValue);
        qfl->addRow(AFL,AFValue);
        qfl->addRow(moltL,moltValue);
        compL->setVisible(true);
        compValue->setVisible(true);
        lungMinL->setVisible(true);
        lungMinValue->setVisible(true);
        fMinL->setVisible(true);
        fMinValue->setVisible(true);
        stabL->setVisible(true);
        stabValue->setVisible(true);
        diamL->setVisible(true);
        diamValue->setVisible(true);
        angMinL->setVisible(true);
        angMinValue->setVisible(true);
        AFL->setVisible(true);
        AFValue->setVisible(true);
        QString comp=QString(QString::fromStdString((dynamic_cast<Lens*>(&(((*modello).getQ().begin()+row)->getT())))->getComp()));
        QString lmin=QString(QString::number(dynamic_cast<Lens*>(&(((*modello).getQ().begin()+row))->getT())->getLung()));
        QString fmin=QString(QString::number(dynamic_cast<Lens*>(&(((*modello).getQ().begin()+row))->getT())->getFocale()));
        QString diam=QString(QString::number(dynamic_cast<Lens*>(&(((*modello).getQ().begin()+row))->getT())->getDiametro()));
        QString angmin=QString(QString::number(dynamic_cast<Lens*>(&(((*modello).getQ().begin()+row))->getT())->getAngolo()));
        QString stab;
        QString af;
        if((dynamic_cast<Lens*>(&(((*modello).getQ().begin()+row))->getT())->isStabilizzato()))
            stabValue->setChecked(true);
        else
            stabValue->setChecked(false);
        if((dynamic_cast<Lens*>(&(((*modello).getQ().begin()+row))->getT())->isAF()))
            AFValue->setChecked(true);
        else
            AFValue->setChecked(false);
        compValue->setText(comp);
        lungMinValue->setText(lmin);
        fMinValue->setText(fmin);
        stabValue->setText(stab);
        diamValue->setText(diam);
        angMinValue->setText(angmin);
        AFValue->setText(af);
        if(type=="Fisso"){
            fMinL->setText("f/");
            lungMinL->setText("Lunghezza focale");
            angMinL->setText("Angolo");
        }else if(type=="Lunghezza fissa"){
            QString fmax=QString(QString::number(dynamic_cast<Length*>(&(((*modello).getQ().begin()+row))->getT())->getFocaleMax()));
            fMaxValue->setText(fmax);
            fMaxL->setVisible(true);
            fMaxValue->setVisible(true);
            fMinL->setText("f/ (min)");
        }else if(type=="Focale fissa"){
            QString lmax=QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+row))->getT())->getLungMax()));
            QString angmax=QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+row))->getT())->getAngoloMax()));
            lungMaxValue->setText(lmax);
            angMaxValue->setText(angmax);
            angMaxL->setVisible(true);
            angMaxValue->setVisible(true);
            lungMaxL->setVisible(true);
            lungMaxValue->setVisible(true);
            lungMinL->setText("Lunghezza focale (min)");
            angMinL->setText("Angolo (min)");
        }else if(type=="Zoom"){
            QString fmax=QString(QString::number(dynamic_cast<Zoom*>(&(((*modello).getQ().begin()+row))->getT())->getFocaleMax()));
            QString lmax=QString(QString::number(dynamic_cast<Zoom*>(&(((*modello).getQ().begin()+row))->getT())->getLungMax()));
            QString angmax=QString(QString::number(dynamic_cast<Zoom*>(&(((*modello).getQ().begin()+row))->getT())->getAngoloMax()));
            if((dynamic_cast<Zoom*>(&(((*modello).getQ().begin()+row))->getT())->hasMoltiplicatore()))
                moltValue->setChecked(true);
            else
                moltValue->setChecked(false);
            fMaxValue->setText(fmax);
            fMaxL->setVisible(true);
            fMaxValue->setVisible(true);
            fMinL->setText("f/ (min)");
            angMaxValue->setText(angmax);
            angMaxL->setVisible(true);
            angMaxValue->setVisible(true);
            angMinL->setText("Angolo (min)");
            lungMaxValue->setText(lmax);
            lungMaxL->setVisible(true);
            lungMaxValue->setVisible(true);
            lungMinL->setText("Lunghezza focale (min)");
            moltL->setVisible(true);
            moltValue->setVisible(true); 
        }//zoom
    }//if_else
}//setDet

void Details::delDet() const{
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
    tipoObValue->setVisible(false);
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
    tipoObValue->setText("");
    compValue->setText("");
    ISOminValue->setText("");
    ISOmaxValue->setText("");
    pxValue->setText("");
    formatoValue->setText("");
    tropValue->setText("");
    tipoAccValue->setText("");
    infoValue->setText("");
    lungMinValue->setText("");
    lungMaxValue->setText("");
    fMinValue->setText("");
    fMaxValue->setText("");
    stabValue->setText("");
    AFValue->setText("");
    angMinValue->setText("");
    angMaxValue->setText("");
    diamValue->setText("");
    moltValue->setText("");
}//delDet

//accessori
QPushButton* Details::getAlter() const{
    return alter;
}//getAlter

QPushButton* Details::getRemove() const{
    return remove;
}//getRemove

float Details::getPrezzo() const{
    return prezzoValue->text().toFloat();
}//getPrezzo

string Details::getMarca() const{
     return marcaValue->text().toStdString();
}//getMarca

string Details::getModello() const{
     return modelloValue->text().toStdString();
}//getModello

string Details::getTipoProd() const{
    return tipoProdValue->text().toStdString();
}//getTipoProdotto

string Details::getComp() const{
     return compValue->text().toStdString();
}//getComp

unsigned int Details::getISOMin() const{
    return static_cast<unsigned int>(ISOminValue->text().toInt());
}//getISOMin

unsigned int Details::getISOMax() const{
    return static_cast<unsigned int>(ISOmaxValue->text().toInt());
}//getISOMax

unsigned int Details::getPX() const{
    return static_cast<unsigned int>(pxValue->text().toInt());
}//getPx

string Details::getFormato() const{
    return formatoValue->text().toStdString();
}//getFormato

bool Details::getTrop() const{
    return tropValue->isChecked();
}//getTrop

string Details::getTipoAcc() const{
    return tipoAccValue->text().toStdString();
}//getTipoAcc

string Details::getInfo() const{
     return infoValue->text().toStdString();
}//getInfo

string Details::getTipoOb() const{
    return tipoObValue->text().toStdString();
}//getTipoOb

unsigned int Details::getLungMin() const{
    return static_cast<unsigned int>(lungMinValue->text().toInt());
}//getLungMin

unsigned int Details::getLungMax() const{
    return static_cast<unsigned int>(lungMaxValue->text().toInt());
}//getLungMax

float Details::getFMin() const{
    return fMinValue->text().toFloat();
}//getFMin

float Details::getFMax() const{
    return fMaxValue->text().toFloat();
}//getFMax

bool Details::getStab() const{
    return stabValue->isChecked();
}//getStab

bool Details::getAF() const{
    return AFValue->isChecked();
}//getAF

float Details::getAngMin() const{
    return angMinValue->text().toFloat();
}//getAngMin

float Details::getAngMax() const{
    return angMaxValue->text().toFloat();
}//getAngMax

unsigned int Details::getDiam() const{
    return static_cast<unsigned int>(diamValue->text().toInt());
}//getDiam

bool Details::getMolt() const{
    return moltValue->isChecked();
}//getMolt

