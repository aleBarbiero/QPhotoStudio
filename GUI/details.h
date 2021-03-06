#ifndef DETAILS_H
#define DETAILS_H

#include "model.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QIntValidator>
#include <QCheckBox>

class Details:public QWidget{
    private:
        QGroupBox* qgb;
        QFormLayout* qfl;
        //etichette
        QLabel* marcaL;
        QLabel* modelloL;
        QLabel* tipoProdL;
        QLabel* compL;
        QLabel* prezzoL;
            //reflex
        QLabel* ISOminL;
        QLabel* ISOmaxL;
        QLabel* pxL;
        QLabel* formatoL;
        QLabel* tropL;
            //accessori
        QLabel* tipoAccL;
        QLabel* infoL;
            //obiettivi
        QLabel* tipoObL;
        QLabel* lungMinL;
        QLabel* lungMaxL;
        QLabel* fMinL;
        QLabel* fMaxL;
        QLabel* stabL;
        QLabel* AFL;
        QLabel* angMinL;
        QLabel* angMaxL;
        QLabel* diamL;
        QLabel* moltL;
        //valori
        QLabel* marcaValue;
        QLabel* modelloValue;
        QLabel* tipoProdValue;
        QLineEdit* compValue;
        QLineEdit* prezzoValue;
            //reflex
        QLineEdit* ISOminValue;
        QLineEdit* ISOmaxValue;
        QLineEdit* pxValue;
        QLabel* formatoValue;
        QCheckBox* tropValue;
            //accessori
        QLabel* tipoAccValue;
        QLineEdit* infoValue;
            //obiettivi
        QLabel* tipoObValue;
        QLineEdit* lungMinValue;
        QLineEdit* lungMaxValue;
        QLineEdit* fMinValue;
        QLineEdit* fMaxValue;
        QCheckBox* stabValue;
        QCheckBox* AFValue;
        QLineEdit* angMinValue;
        QLineEdit* angMaxValue;
        QLineEdit* diamValue;
        QCheckBox* moltValue;
        //pulsanti
        QPushButton* alter;
        QPushButton* remove;
    public:
        //costruttore
        Details(QWidget* =nullptr);
        //accessori
       void setDet(Model*,int,QList<int>);
       void delDet() const;
       QPushButton* getAlter() const;
       QPushButton* getRemove() const;
       string getMarca() const;
       string getModello() const;
       string getTipoProd() const;
       string getComp() const;
       float getPrezzo() const;
       unsigned int getISOMin() const;
       unsigned int getISOMax() const;
       unsigned int getPX() const;
       string getFormato() const;
       bool getTrop() const;
       string getTipoAcc() const;
       string getInfo() const;
       string getTipoOb() const;
       unsigned int getLungMin() const;
       unsigned int getLungMax() const;
       float getFMin() const;
       float getFMax() const;
       bool getStab() const;
       bool getAF() const;
       float getAngMin() const;
       float getAngMax() const;
       unsigned int getDiam() const;
       bool getMolt() const;
};

#endif
