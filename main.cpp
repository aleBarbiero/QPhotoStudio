#include "mainwindow.h"
#include "GUI/model.h"
#include <QApplication>
#include <QFile>
#include <QFont>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QFile File(":/GUI/style.qss");
    File.open(QFile::ReadOnly);
    QString ss = QLatin1String(File.readAll());
    qApp->setStyleSheet(ss);
    return a.exec();
}//main

