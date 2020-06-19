#ifndef MYPDF_H
#define MYPDF_H

#include "container/container.h"
#include "container/deepPtr.h"
#include "model/product.h"
#include "model/reflex.h"
#include "model/accessory.h"
#include "model/lens.h"
#include "model/aperture.h"
#include "model/length.h"
#include "model/zoom.h"
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
