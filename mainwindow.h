#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GUI/add.h"
#include "GUI/index.h"
#include "GUI/listino.h"
#include "GUI/search.h"
#include "GUI/details.h"
#include "GUI/model.h"
#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QCloseEvent>
#include <QLayout>

class MainWindow:public QWidget{
    Q_OBJECT
    private:
        Model* modello;
        QMenuBar* menu;
        QVBoxLayout* main;
        QString file;
        Index* index;
        Add* add;
        Listino* list;
        Search* search;
        Details* det;
        int pos;
        virtual void closeEvent(QCloseEvent*) override;
    public:
        //costruttore/distruttore
        explicit MainWindow(QWidget* =nullptr);
        ~MainWindow()override =default;
    public slots:
        void indexSet() const;
        void addSet() const;
        void addEl();
        void delForm() const;
        void listSet() const;
        void searchSet() const;
        void searchEl() const;
        void showDet(int);
        void alterEl();
        void removeEl();
        bool save();
        void load();
        void exportCSV();
        //utility
        bool checkFieldsAdd(string) const;
        bool checkFieldsAlter(string) const;
};//MainWindow

#endif
