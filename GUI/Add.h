#ifndef ADD_H
#define ADD_H
#include "model/Reflex.h"
#include "model/Accessory.h"
#include <QWidget>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QString>
using namespace std;

class Add:public QWidget{
    Q_OBJECT
    private:
        QFormLayout* qfl;
        QGroupBox* qgb;
        QHBoxLayout* img;
        QHBoxLayout* button;
        //etichette
        QLabel* marcaL;
        QLabel* modelloL;
        QLabel* tipoProdL;
        QLabel* compL;
            //reflex
        QLabel* ISOminL;
        QLabel* ISOmaxL;
        QLabel* pxL;
        QLabel* formatoL;
        QLabel* tropL;
            //accessori
        QLabel* tipoAccL;
        QLabel* infoL;
            //obiettivi
        QLabel* tipoObL;
        QLabel* lungMinL;
        QLabel* lungMaxL;
        QLabel* fMinL;
        QLabel* fMaxL;
        QLabel* stabL;
        QLabel* AFL;
        QLabel* angMinL;
        QLabel* angMaxL;
        QLabel* diamL;
        QLabel* moltL;
        //acquisizione_valori
        QLineEdit* marcaValue;
        QLineEdit* modelloValue;
        QComboBox* tipoProdValue;
        QLineEdit* compValue;
            //reflex
        QLineEdit* ISOminValue;
        QLineEdit* ISOmaxValue;
        QLineEdit* pxValue;
        QComboBox* formatoValue;
        QCheckBox* tropValue;
            //accessori
        QComboBox* tipoAccValue;
        QLineEdit* infoValue;
            //obiettivi
        QComboBox* tipoObValue;
        QLineEdit* lungMinValue;
        QLineEdit* lungMaxValue;
        QLineEdit* fMinValue;
        QLineEdit* fMaxValue;
        QCheckBox* stabValue;
        QCheckBox* AFValue;
        QLineEdit* angMinValue;
        QLineEdit* angMaxValue;
        QLineEdit* diamValue;
        QCheckBox* moltValue;
        //immagine_prodotto
        QLabel* imgL;
        //bottoni
        QPushButton* add;
        QPushButton* del;
    public:
        //costruttore
        Add(QWidget* =nullptr);
        //accessori
        string getMarca() const;
        string getModello() const;
        string getTipoProd() const;
        string getComp() const;
        unsigned int getISOMin() const;
        unsigned int getISOMax() const;
        unsigned int getPX() const;
        string getFormato() const;
        bool getTrop() const;
        string getTipoAcc() const;
        string getInfo() const;
        string getTipoOb() const;
        unsigned int getLungMin() const;
        unsigned int getLungMax() const;
        float getFMin() const;
        float getFMax() const;
        bool getStab() const;
        bool getAF() const;
        float getAngMin() const;
        float getAngMax() const;
        unsigned int getDiam() const;
        bool getMolt() const;
        QPushButton* getAdd() const;
        QPushButton* getDel() const;
        //modificatori
        void setMarca(QString);
        void setModello(QString);
        void setTipoProd(QString);
        void setComp(QString);
        void setISOMin(QString);
        void setISOMax(QString);
        void setPX(QString);
        void setFormato(QString);
        void setTrop(bool);
        void setTipoAcc(QString);
        void setInfo(QString);
        void setTipoOb(QString);
        void setLungMin(QString);
        void setLungMax(QString);
        void setFMin(QString);
        void setFMax(QString);
        void setStab(bool);
        void setAF(bool);
        void setAngMin(QString);
        void setAngMax(QString);
        void setDiam(QString);
        void setMolt(bool);
    public slots:
        void modify(QString);
        void delElement() const;
        void delForm() const;
};//insert

#endif
