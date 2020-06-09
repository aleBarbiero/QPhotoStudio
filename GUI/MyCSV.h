#ifndef MYPDF_H
#define MYPDF_H

#include "container/Container.h"
#include "container/DeepPtr.h"
#include "model/Product.h"
#include "model/Reflex.h"
#include "model/Accessory.h"
#include "model/Lens.h"
#include "model/Aperture.h"
#include "model/Length.h"
#include "model/Zoom.h"
#include <QFile>
#include <QSaveFile>
#include <QString>

class MyCSV{
    public:
        //costruttore/distruttore
        MyCSV()=default;
        ~MyCSV()=default;
        //metodi
        void exportCSV(const Container<DeepPtr<Product>>&) const;
};//myPDF


#endif // MYPDF_H
