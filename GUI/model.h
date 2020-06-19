#ifndef MODEL_H
#define MODEL_H
#include "container/container.h"
#include "container/deepPtr.h"
#include "model/product.h"
#include "model/reflex.h"
#include "model/lens.h"
#include "model/length.h"
#include "model/aperture.h"
#include "model/zoom.h"
#include "model/accessory.h"
#include "myXml.h"
#include "myCSV.h"
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
        void exportCSV() const;
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
