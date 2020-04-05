#ifndef LISTINO_H
#define LISTINO_H

#include "Model.h"
#include "model/Product.h"
#include "model/Reflex.h"
#include "model/Accessory.h"
#include "model/Lens.h"
#include "model/Aperture.h"
#include "model/Length.h"
#include "model/Zoom.h"
#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QString>
#include <QPushButton>
#include <QTableWidget>
#include <QMessageBox>

class Listino:public QWidget{
    Q_OBJECT
    private:
        //elementi_Qt
        QVBoxLayout* list;
        QTableWidget* tab;
        QTableWidget* reftab;
        QTableWidget* acctab;
        QTableWidget* lenstab;
        QPushButton* ref;
        QPushButton* lens;
        QPushButton* acc;
    public:
        //costruttore
        Listino(QWidget* =nullptr);
        //accessori
        void fullTab(Model*);
        void refTab(Model*);
        void accTab(Model*);
        void lensTab(Model*);
        QPushButton* getRef() const;
        QPushButton* getAcc() const;
        QPushButton* getLens() const;
        QTableWidget* getTable() const;
    public slots:
        void setRefTab();
        void setAccTab();
        void setLensTab();
};

#endif // LISTINO_H
