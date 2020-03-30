#ifndef PRODUCT_H
#define PRODUCT_H

#include<sstream>
#include<QXmlStreamWriter>
using namespace std;

class Product{
	private:
		string marca;
		string nomeModello;
        float prezzo;
	public:
		//costruttori_e_distruttore
        Product(string="No data",string="No data",float=0.00);
		Product(const Product&) = default;
		virtual ~Product() = default;
		
		//ridefinizione_operatori
		Product& operator=(const Product&) = default;
		bool operator==(const Product&);
		bool operator!=(const Product&);
		bool operator>(const Product&);
		bool operator>=(const Product&);
		bool operator<(const Product&);
        bool operator<=(const Product&);
        //friend ostream& operator<<(ostream&,const Product&);

		//metodi_accessori_e_modificatori
        string getMarca() const;
		void setMarca(string newM);
        string getNomeModello() const;
		void setNomeModello(string newNM);
        float getPrezzo() const;
        void setPrezzo(float newP);
		//virtuali
        virtual string print() const;
		virtual string getType() const=0;
		//XML
        virtual void XML(QXmlStreamWriter&)const;
};//Product

/*ostream& operator<<(ostream& os,const Product& p){;
    os<<"Marca: "<<p.marca<<"\n";
    os<<"Modello: "<<p.nomeModello<<"\n";
    os<<"Prezzo: "<<p.prezzo<<"\n";
    return os;
}//operator<<*/

#endif
