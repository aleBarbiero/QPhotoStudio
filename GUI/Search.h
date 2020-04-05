#ifndef SEARCH_H
#define SEARCH_H

#include "Model.h"
#include "MyXml.h"
#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QString>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QString>

class Search:public QWidget{
    Q_OBJECT
    private:
        QHBoxLayout* searchL;
        QVBoxLayout* tabL;
        QTableWidget* tab;
        QLineEdit* searchValue;
        QComboBox* filter;
        QPushButton* search;
        QPushButton* del;
        QList<int> index;
        bool s;
    public:
        //costruttore
        Search(QWidget* =nullptr);
        //accessori_e_modificatori
        QPushButton* getSearch() const;
        QPushButton* getDel() const;
        QString getSearchWord() const;
        QTableWidget* getTab() const;
        QList<int> getIndex() const;
        bool getS() const;
        void setIndex(Model*);
        void find(Model*);
        void goBack(Model*);
};

#endif
