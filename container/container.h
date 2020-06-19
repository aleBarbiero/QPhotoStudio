#ifndef CONTAINER_H
#define CONTAINER_H
template<class T> class Container{

    friend class Iterator;//classe_iteratore_per_modificare_il_contenitore
    friend class Const_iterator;//classe_iteratore_per_visitare_il_contenitore

    private:
        class Node{//classe_interna_per_gli_elementi_del_contenitore
            public:
                //campi
                T info;
                Node* pre;
                Node* next;
                //costruttori/distruttore
                Node();
                Node(const T& =T(),Node* =nullptr,Node* =nullptr);
                Node(const Node&)=default;//copia
                ~Node();//distruttore
                //operatori
                Node& operator=(const Node&)=default;
        };//Node

        //campi
        Node* first;
        Node* last;
        int size;
        //metodi_privati
        static Node* copia(const Node*,Node*&);
        static bool equal(const Node* a,const Node* b);

    public:
        class Iterator{
            friend class Container<T>;
            private:
                //campi
                Node* nodo;
                bool end;
                //costruttore_privato_accessibile_solo_da_Container
                Iterator(Node*,bool=false);
            public:
                //costruttore/distruttore
                Iterator();
                ~Iterator()=default;
                //operatori
                Iterator& operator+(int);
                Iterator& operator-(int);
                Iterator& operator++();
                Iterator& operator--();
                Iterator operator++(int);
                Iterator operator--(int);
                bool operator==(const Iterator&) const;
                bool operator!=(const Iterator&) const;
                T& operator * () const;
                T* operator -> () const;
        };//Iterator

        Iterator begin();
        Iterator end();

        class Const_Iterator{
            friend class Container<T>;
            private:
                //campi
                Node* nodo;
                bool end;
                //costruttore_privato_accessibile_solo_da_Container
                Const_Iterator(Node*,bool=false);
            public:
                //costruttore/distruttore
                Const_Iterator();
                ~Const_Iterator()=default;
                //operatori
                Const_Iterator& operator+(int);
                Const_Iterator& operator-(int);
                Const_Iterator& operator++();
                Const_Iterator& operator--();
                Const_Iterator operator++(int);
                Const_Iterator operator--(int);
                bool operator==(const Const_Iterator&) const;
                bool operator!=(const Const_Iterator&) const;
                const T& operator*() const;
                const T* operator->() const;
        };//Const_Iterator

        Const_Iterator begin() const;
        Const_Iterator end() const;

        //costruttore/distruttore
        Container();
        Container(const Container&);
        ~Container();
        //operatori
        Container& operator=(const Container&);
        bool operator==(const Container&) const;
        bool operator!=(const Container&) const;
        //metodi
        int getSize() const;
        bool isEmpty() const;
        Iterator find(T&) const;//trova_l'elemento_richiesto_e_ritorna_un_iteratore_che_lo_punta
        void pushFirst(const T&);//aggiunge_in_prima_posizione
        void pushLast(const T&);//aggiunge_in_ultima_posizione
        Iterator pushPos(Iterator,T&);//aggiunge_in_posizione_successiva_all'elemento_puntato
        void deleteFirst();//elimina_in_prima_posizione
        void deleteLast();//elimina_in_ultima_posizione
        Iterator deletePos(Iterator);//elimina_in_posizione_specificata
        void deleteThis(const T&);//elimina_tutti_gli_elementi_con_il_campo_dati_specificato
        void deleteAll();//elimina_tutti_gli_elementi
        void sortC();//ordina
};//Container

//IMPLEMENTAZIONE DEI METODI DI NODE,ITERATOR e CONST_ITERATOR

//Node
template<class T> Container<T>::Node::Node():info(),pre(nullptr),next(nullptr){}//Node

template<class T> Container<T>::Node::Node(const T& newI,Node* newS,Node* newF):info(newI),pre(newS),next(newF){}

template<class T> Container<T>::Node::~Node(){
    if(next)
        delete next;
}//~Node

//Iterator
template<class T> Container<T>::Iterator::Iterator():nodo(nullptr),end(false){}//Iterator

template<class T> Container<T>::Iterator::Iterator(Node* point,bool b):nodo(point),end(b){}//Iterator

template<class T> typename Container<T>::Iterator& Container<T>::Iterator::operator+(int i){
    while(i){
        operator++();
        i--;
    }//while
    return *this;
}//+

template<class T> typename Container<T>::Iterator& Container<T>::Iterator::operator-(int i){
    while(i){
        operator--();
        i--;
    }//while
    return *this;
}//-

template<class T> typename Container<T>::Iterator& Container<T>::Iterator::operator++(){
    if(!end && nodo){
        if(nodo->next==nullptr){
            nodo=nodo+1;
            end=true;
        }else
            nodo=nodo->next;
    }//if
    return *this;
}//++

template<class T> typename Container<T>::Iterator& Container<T>::Iterator::operator--(){
    if(end){
        nodo=nodo-1;
        end=false;
    }else if(nodo)
            nodo=nodo->prev;
    return *this;
}//--

template<class T> typename Container<T>::Iterator Container<T>::Iterator::operator++(int){
    Iterator temp=*this;
    if(nodo && !end){
        if(nodo->next==nullptr){
            nodo=nodo+1;
            end=true;
        }else
            nodo=nodo->next;
    }//if_else
    return temp;
}//++int

template<class T> typename Container<T>::Iterator Container<T>::Iterator::operator--(int){
    Iterator temp=*this;
    if(end){
        nodo=nodo-1;
        end=false;
    }else if(nodo)
                nodo=nodo->pre;
    return temp;
}//--int

template<class T> bool Container<T>::Iterator::operator==(const Iterator& i) const{
    return nodo==i.nodo;
}//==

template<class T> bool Container<T>::Iterator::operator!=(const Iterator& i) const{
    return nodo!=i.nodo;
}// !=

template<class T> T& Container<T>::Iterator::operator*() const{
    return nodo->info;
}//*

template<class T> T* Container<T>::Iterator::operator->() const{
    return &(nodo->info);
}//*

template<class T> typename Container<T>::Iterator Container<T>::begin(){
    return Iterator(first);
}//begin

template<class T> typename Container<T>::Iterator Container<T>::end(){
    if(!first)
        return Iterator();
    else
        return Iterator(last+1,true);
}//end

//Const_Iterator
template<class T> Container<T>::Const_Iterator::Const_Iterator():nodo(nullptr),end(false){}//Const_Iterator

template <class T> Container<T>::Const_Iterator::Const_Iterator(Node* point,bool b):nodo(point),end(b){}//Const_Iterator

template <class T> typename Container<T>::Const_Iterator& Container<T>::Const_Iterator::operator+(int i){
    while(i){
        operator++();
        i--;
    }//while
    return *this;
}//+

template <class T> typename Container<T>::Const_Iterator& Container<T>::Const_Iterator::operator-(int i){
    while(i){
        operator--();
        i--;
    }//while
    return *this;
}//-

template <class T> typename Container<T>::Const_Iterator& Container<T>::Const_Iterator::operator++(){
    if(!end && nodo){
        if(nodo->next==nullptr){
            nodo=nodo+1;
            end=true;
        }else
            nodo=nodo->next;
    }//if
    return *this;
}//++

template <class T> typename Container<T>::Const_Iterator& Container<T>::Const_Iterator::operator--(){
    if(end){
        nodo=nodo-1;
        end=false;
    }else if(nodo)
            nodo=nodo->prev;
    return *this;
}//--

template<class T> typename Container<T>::Const_Iterator Container<T>::Const_Iterator::operator++(int){
    Iterator temp=*this;
    if(nodo && !end){
        if(nodo->next==nullptr){
            nodo=nodo+1;
            end=true;
        }else
            nodo=nodo->next;
    }//if_else
    return temp;
}//++int

template<class T> typename Container<T>::Const_Iterator Container<T>::Const_Iterator::operator--(int){
    Iterator temp=*this;
    if(end){
        nodo=nodo-1;
        end=false;
    }else if(nodo)
                nodo=nodo->pre;
    return temp;
}//--int

template<class T> bool Container<T>::Const_Iterator::operator==(const Const_Iterator& i) const{
    return nodo==i.nodo;
}//==

template<class T> bool Container<T>::Const_Iterator::operator!=(const Const_Iterator& i) const{
    return nodo!=i.nodo;
}// !=

template<class T> const T& Container<T>::Const_Iterator::operator*() const{
    return nodo->info;
}//*

template<class T> const T* Container<T>::Const_Iterator::operator->() const{
    return &(nodo->info);
}//*

template<class T> typename Container<T>::Const_Iterator Container<T>::begin() const{
    return Const_Iterator(first);
}//begin

template<class T> typename Container<T>::Const_Iterator Container<T>::end() const{
    if(!first)
        return Const_Iterator();
    else
        return Const_Iterator(last+1,true);
}//end

#endif//Container
