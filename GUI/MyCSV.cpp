#include "MyCSV.h"
#include "container/Container.cpp"
#include "container/DeepPtr.cpp"
#include <QTextStream>
#include <QDir>

void MyCSV::exportCSV(const Container<DeepPtr<Product>>& container) const{
    if(!QDir("output").exists())
        QDir().mkdir("output");
    QFile saveF("output/QPhotoStudio.csv");
    saveF.setFileName("output/QPhotoStudio.csv");
    if(saveF.open(QIODevice::WriteOnly)){
        QTextStream stream(&saveF);
        for(auto el=container.begin();el!=container.end();++el){
            stream.operator<<(QString::fromStdString((*el)->CSV())).operator<<("\n");
        }//for
    }//if
    saveF.close();
}//exportPDF
