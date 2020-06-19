#ifndef MYXML_H
#define MYXML_H

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

class MyXml{
    public:
        //costruttore/distruttore
        MyXml()=default;
        ~MyXml()=default;
        //metodi
        Container<DeepPtr<Product>> load(const QString&) const;
        void save(const QString&,const Container<DeepPtr<Product>>&) const;
};//myXml

#endif
