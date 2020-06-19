#ifndef LISTINO_H
#define LISTINO_H

#include "model.h"
#include "model/product.h"
#include "model/reflex.h"
#include "model/accessory.h"
#include "model/lens.h"
#include "model/aperture.h"
#include "model/length.h"
#include "model/zoom.h"
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
