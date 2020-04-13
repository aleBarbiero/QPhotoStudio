#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GUI/Add.h"
#include "GUI/Index.h"
#include "GUI/Listino.h"
#include "GUI/Search.h"
#include "GUI/Details.h"
#include "GUI/Model.h"
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
        void listSet() const;
        void searchSet() const;
        void searchEl() const;
        void showDet(int);
        void alterEl();
        void removeEl();
        void save();
        void load();
};//MainWindow

#endif
