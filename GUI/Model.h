#ifndef MODEL_H
#define MODEL_H
#include "container/Container.h"
#include "container/DeepPtr.h"
#include "model/Product.h"
#include "model/Reflex.h"
#include "model/Lens.h"
#include "model/Length.h"
#include "model/Aperture.h"
#include "model/Zoom.h"
#include "model/Accessory.h"
#include "MyXml.h"
#include <QString>
#include <QRegExp>
using namespace std;

class Model{
    private:
        Container<DeepPtr<Product>> Q;
    public:
        //costruttore/distruttore
        Model();
        ~Model();
        //carica/salva
        void saveF(const QString&) const;
        void loadF(const QString&);
        //metodi
        void insert(Product*);
        void remove(Product*);
        void alter(int,Product*);
        void remove(int i);
        int count() const;
        bool search(int i,const QRegExp&,const QString&) const;
        //bool searchV(int i,bool,const QString&) const;
        Container<DeepPtr<Product>> getQ() const;
};//Model

#endif
