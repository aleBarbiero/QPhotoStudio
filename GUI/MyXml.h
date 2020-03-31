#ifndef MYXML_H
#define MYXML_H

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

class MyXml{
    public:
        //costruttore/distruttore
        MyXml()=default;
        ~MyXml()=default;
        //metodi
        Container<DeepPtr<Product>> load(const QString&) const;
        void save(const QString&,const Container<DeepPtr<Product>>&) const;
};//myXml

#endif // YML_H
