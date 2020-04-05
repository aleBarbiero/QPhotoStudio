#include "Details.h"
#include <QApplication>
#include <QDesktopWidget>

Details::Details(QWidget* q):QWidget(q),qgb(new QGroupBox()),qfl(new QFormLayout()),marcaL(new QLabel("Marca")),modelloL(new QLabel("Modello")),tipoProdL(new QLabel("Tipologia prodotto")),compL(new QLabel("Compatibilità")),
        prezzoL(new QLabel("Prezzo")),ISOminL(new QLabel("ISO(min)")),ISOmaxL(new QLabel("ISO(max)")),pxL(new QLabel("Pixel")),formatoL(new QLabel("Formato")),tropL(new QLabel("Tropicalizzazione")),tipoAccL(new QLabel("Tipologia accessorio")),infoL(new QLabel("Note(opzionali)")),tipoObL(new QLabel("Tipologia obiettivo")),
        lungMinL(new QLabel("Lunghezza focale")),lungMaxL(new QLabel("Lunghezza focale(max)")),fMinL(new QLabel("Focale")),fMaxL(new QLabel("Focale(max)")),stabL(new QLabel("Stabilizzazione")),AFL(new QLabel("Automatic focus")),angMinL(new QLabel("Angolo")),angMaxL(new QLabel("Angolo(max)")),
        diamL(new QLabel("Diametro lente")),moltL(new QLabel("Compatibilità moltiplicatore")),marcaValue(new QLabel("")),modelloValue(new QLabel("")),tipoProdValue(new QLabel("")),compValue(new QLabel("")),prezzoValue(new QLabel("")),ISOminValue(new QLabel("")),ISOmaxValue(new QLabel("")),
        pxValue(new QLabel("")),formatoValue(new QLabel("")),tropValue(new QLabel("")),tipoAccValue(new QLabel("")),infoValue(new QLabel("")),tipoObValue(new QLabel("")),lungMinValue(new QLabel("")),lungMaxValue(new QLabel("")),
        fMinValue(new QLabel("")),fMaxValue(new QLabel("")),stabValue(new QLabel("")),AFValue(new QLabel("")),angMinValue(new QLabel("")),angMaxValue(new QLabel("")),diamValue(new QLabel("")),
        moltValue(new QLabel("")){
    move(QApplication::desktop()->screen()->rect().center()-rect().center());
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
    mainLayout->addWidget(qgb);
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
    prezzoValue->setText(prezzo+"€");
    if(type=="Reflex"){
        QString ISOmin=QString(QString::number((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+row)->getT())))->getISOmin()));
        QString ISOmax=QString(QString::number((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+row)->getT())))->getISOmax()));
        QString px=QString(QString::number((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+row)->getT())))->getPX()));
        QString formato=QString(QString::fromStdString((dynamic_cast<Reflex*>(&(((*modello).getQ().begin()+row)->getT())))->getFormato()));
        qfl->addRow(ISOminL,ISOminValue);
        qfl->addRow(ISOmaxL,ISOmaxValue);
        qfl->addRow(pxL,pxValue);
        qfl->addRow(formatoL,formatoValue);
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
        if(type=="Lunghezza fissa" || type=="Zoom"){
            QString comp=QString(QString::fromStdString((dynamic_cast<Length*>(&(((*modello).getQ().begin()+row)->getT())))->getComp()));
            QString lmin=QString(QString::number(dynamic_cast<Length*>(&(((*modello).getQ().begin()+row))->getT())->getLung()));
            QString fmin=QString(QString::number(dynamic_cast<Length*>(&(((*modello).getQ().begin()+row))->getT())->getFocale()));
            QString fmax=QString(QString::number(dynamic_cast<Length*>(&(((*modello).getQ().begin()+row))->getT())->getFocaleMax()));
            QString stab;
            if((dynamic_cast<Length*>(&(((*modello).getQ().begin()+row))->getT())->isStabilizzato()))
                stab=QString(QString::fromStdString("SI"));
            else
                stab=QString(QString::fromStdString("NO"));
            QString diam=QString(QString::number(dynamic_cast<Length*>(&(((*modello).getQ().begin()+row))->getT())->getDiametro()));
            QString angmin=QString(QString::number(dynamic_cast<Length*>(&(((*modello).getQ().begin()+row))->getT())->getAngolo()));
            QString af;
            if((dynamic_cast<Length*>(&(((*modello).getQ().begin()+row))->getT())->isAF()))
                af=QString(QString::fromStdString("SI"));
            else
                af=QString(QString::fromStdString("NO"));
            compValue->setText(comp);
            lungMinValue->setText(lmin+"mm");
            fMinValue->setText("f/"+fmin);
            fMaxValue->setText("f/"+fmax);
            stabValue->setText(stab);
            diamValue->setText(diam+"mm");
            angMinValue->setText(angmin+"°");
            AFValue->setText(af);
            fMaxL->setVisible(true);
            fMaxValue->setVisible(true);
        }//length
        if(type=="Zoom"){
            QString lmax=QString(QString::number(dynamic_cast<Zoom*>(&(((*modello).getQ().begin()+row))->getT())->getLungMax()));
            QString angmax=QString(QString::number(dynamic_cast<Zoom*>(&(((*modello).getQ().begin()+row))->getT())->getAngoloMax()));
            QString molt;
            if((dynamic_cast<Zoom*>(&(((*modello).getQ().begin()+row))->getT())->hasMoltiplicatore()))
                molt=QString(QString::fromStdString("SI"));
            else
                molt=QString(QString::fromStdString("NO"));
            angMaxValue->setText(angmax+"°");
            angMaxL->setVisible(true);
            angMaxValue->setVisible(true);
            moltValue->setText(molt);
            moltL->setVisible(true);
            moltValue->setVisible(true);
            lungMaxValue->setText(lmax+"mm");
            lungMaxL->setVisible(true);
            lungMaxValue->setVisible(true);
        }//zoom
        if(type=="Focale fissa"){
            QString comp=QString(QString::fromStdString((dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+row)->getT())))->getComp()));
            QString lmin=QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+row))->getT())->getLung()));
            QString fmin=QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+row))->getT())->getFocale()));
            QString lmax=QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+row))->getT())->getLungMax()));
            QString angmax=QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+row))->getT())->getAngoloMax()));
            QString stab;
            if((dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+row))->getT())->isStabilizzato()))
                stab=QString(QString::fromStdString("SI"));
            else
                stab=QString(QString::fromStdString("NO"));
            QString diam=QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+row))->getT())->getDiametro()));
            QString angmin=QString(QString::number(dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+row))->getT())->getAngolo()));
            QString af;
            if((dynamic_cast<Aperture*>(&(((*modello).getQ().begin()+row))->getT())->isAF()))
                af=QString(QString::fromStdString("SI"));
            else
                af=QString(QString::fromStdString("NO"));
            compValue->setText(comp);
            lungMinValue->setText(lmin+"mm");
            lungMaxValue->setText(lmax+"mm");
            fMinValue->setText("f/"+fmin);
            stabValue->setText(stab);
            diamValue->setText(diam+"mm");
            angMinValue->setText(angmin+"°");
            angMaxValue->setText(angmax+"°");
            AFValue->setText(af);
            angMaxL->setVisible(true);
            angMaxValue->setVisible(true);
            lungMaxL->setVisible(true);
            lungMaxValue->setVisible(true);
        }//aperture
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
