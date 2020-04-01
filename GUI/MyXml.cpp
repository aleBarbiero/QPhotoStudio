#include "MyXml.h"
#include "container/Container.cpp"
#include "container/DeepPtr.cpp"

void MyXml::save(const QString& name, const Container<DeepPtr<Product>>& cont) const{
    QSaveFile saveF(name);
    saveF.setFileName(name);
    if(saveF.open(QIODevice::WriteOnly)){
        QXmlStreamWriter streamW(&saveF);
        streamW.setAutoFormatting(true);
        streamW.writeStartDocument();
        streamW.writeStartElement(QString::fromStdString("Product"));
        //variabile_tipo_auto_definito_C++11
        for(auto el=cont.begin();el!=cont.end();++el){
            (*el)->XML(streamW);
        }//for
        streamW.writeEndElement();
        streamW.writeEndDocument();
        saveF.commit();
    }//if
}//save

Container<DeepPtr<Product>> MyXml::load(const QString& file) const{
    Container<DeepPtr<Product>> temp;
    QFile saveFile(file);
    if(saveFile.open(QIODevice::ReadOnly)){//1
      QXmlStreamReader read(&saveFile);
      if(read.readNextStartElement() && read.name()=="Product"){//2
        while(read.readNextStartElement()){
          QStringRef type=read.name();
          read.readNextStartElement();
          if(type==QString::fromStdString("ObiettivoZoom"))
              read.readNextStartElement();
          std::string marca=read.readElementText().toStdString();
          read.readNextStartElement();
          std::string modello=read.readElementText().toStdString();
          read.readNextStartElement();
          float prezzo=read.readElementText().toFloat();
          if(type==QString::fromStdString("Reflex")){
            read.readNextStartElement();
            std::string formato=read.readElementText().toStdString();
            read.readNextStartElement();
            unsigned int ISOmin=static_cast<unsigned int>(read.readElementText().toInt());
            read.readNextStartElement();
            unsigned int ISOmax=static_cast<unsigned int>(read.readElementText().toInt());
            read.readNextStartElement();
            unsigned int px=static_cast<unsigned int>(read.readElementText().toInt());
            read.readNextStartElement();
            std::string temp_t=read.readElementText().toStdString();
            bool trop;
            if(temp_t=="SI")
                trop=true;
            else
                trop=false;
            Reflex ref(marca,modello,prezzo,ISOmin,ISOmax,px,Reflex::fromStrToType(formato),trop);
            temp.pushLast(&ref);
          }else if(type==QString::fromStdString("Accessorio")){
              read.readNextStartElement();
              std::string tipo=read.readElementText().toStdString();
              read.readNextStartElement();
              std::string compat=read.readElementText().toStdString();
              read.readNextStartElement();
              std::string note=read.readElementText().toStdString();
              Accessory acc(marca,modello,prezzo,Accessory::fromStrToType(tipo),compat,note);
              temp.pushLast(&acc);
          }else{
            read.readNextStartElement();
            unsigned int lung=static_cast<unsigned int>(read.readElementText().toInt());
            read.readNextStartElement();
            float focale=read.readElementText().toFloat();
            read.readNextStartElement();
            std::string temp_s=read.readElementText().toStdString();
            bool stab;
            if(temp_s=="SI")
                stab=true;
            else
                stab=false;
            read.readNextStartElement();
            std::string temp_af=read.readElementText().toStdString();
            bool af;
            if(temp_af=="SI")
                af=true;
            else
                af=false;
            read.readNextStartElement();
            float angolo=read.readElementText().toFloat();
            read.readNextStartElement();
            unsigned int diam=static_cast<unsigned int>(read.readElementText().toInt());
            read.readNextStartElement();
            std::string compat=read.readElementText().toStdString();
            if(type==QString::fromStdString("ObiettivoFocaleFissa")){
                read.readNextStartElement();
                unsigned int lungMax=static_cast<unsigned int>(read.readElementText().toInt());
                read.readNextStartElement();
                float angoloMax=read.readElementText().toFloat();
                Aperture ap(marca,modello,prezzo,lung,lungMax,focale,compat,stab,af,angolo,angoloMax,diam);
                temp.pushLast(&ap);
            }else if(type==QString::fromStdString("ObiettivoLunghezzaFissa")){
                read.readNextStartElement();
                float focaleMax=read.readElementText().toFloat();
                Length len(marca,modello,prezzo,lung,focale,focaleMax,compat,stab,af,angolo,diam);
                temp.pushLast(&len);
            }else{
                read.readNextStartElement();
                unsigned int lungMax=static_cast<unsigned int>(read.readElementText().toInt());
                read.readNextStartElement();
                float angoloMax=read.readElementText().toFloat();
                read.readNextStartElement();
                read.readNextStartElement();
                float focaleMax=read.readElementText().toFloat();
                read.readNextStartElement();
                std::string temp_mol=read.readElementText().toStdString();
                bool mol;
                if(temp_mol=="SI")
                    mol=true;
                else
                    mol=false;
                Zoom z(marca,modello,prezzo,lung,lungMax,focale,focaleMax,compat,stab,af,angolo,angoloMax,diam,mol);
                temp.pushLast(&z);
            }//internal_if
          }//obiettivi_vari
          read.skipCurrentElement();
        }//while
      }//external_if_2
    }//external_if_1
    saveFile.close();
    return temp;
}//load

