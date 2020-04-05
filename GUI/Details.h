#ifndef DETAILS_H
#define DETAILS_H

#include "Model.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QGroupBox>

class Details:public QWidget{
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
    QLabel* compValue;
    QLabel* prezzoValue;
        //reflex
    QLabel* ISOminValue;
    QLabel* ISOmaxValue;
    QLabel* pxValue;
    QLabel* formatoValue;
    QLabel* tropValue;
        //accessori
    QLabel* tipoAccValue;
    QLabel* infoValue;
        //obiettivi
    QLabel* tipoObValue;
    QLabel* lungMinValue;
    QLabel* lungMaxValue;
    QLabel* fMinValue;
    QLabel* fMaxValue;
    QLabel* stabValue;
    QLabel* AFValue;
    QLabel* angMinValue;
    QLabel* angMaxValue;
    QLabel* diamValue;
    QLabel* moltValue;
public:
    //costruttore
    Details(QWidget* =nullptr);
    //accessori
   void setDet(Model*,int,QList<int>);
   void delDet() const;
};

#endif
