#include "Container.h"
#include <sstream>
using namespace std;

//costruttori/distruttore
template<class T> Container<T>::Container():first(nullptr),last(nullptr),size(0){}//Container

template <class T> Container<T>::~Container(){
    if(first)
        delete first;
}//Container

template <class T> Container<T>::Container(const Container& c){
    first=copia(c.first,last);
    size=c.size;
}//Container_copia

//metodo_copia
template<class T> typename Container<T>::Node* Container<T>::copia(const Node* newF,Node*& newL){
    if(!newF)
        return newL=nullptr;
    Node* nuovo=new Node(newF->info,nullptr,nullptr);
    Node* temp=nuovo;
    while(newF->next){
        newF=newF->next;
        temp->next=new Node(newF->info,temp,nullptr);
        temp=temp->next;
    }//while
    newL=temp;
    return nuovo;
}//copia

//metodo_confronto
template<class T> bool Container<T>::equal(const Node* a,const Node* b){
    if(a==b)
        return true;
    if(!a || !b)
        return false;
    return ((a->info==b->info) && equal(a->next,b->next));
}//equal

//operatori
template<class T> Container<T>& Container<T>::operator=(const Container& cont2){
    if(this!=&cont2){
        if(first)
            delete first;
        first=copia(cont2.first,last);
        size=cont2.size;
    }//if
    return *this;
}//=

template<class T> bool Container<T>::operator==(const Container& c) const{
    return equal(first,c.first);
}//==

template<class T> bool Container<T>::operator!=(const Container& c) const{
    return !(equal(first,c.first));
}// !=

//metodi
template<class T> int Container<T>::getSize() const{
    return size;
}//getSize

template<class T> bool Container<T>::isEmpty() const{
    return first==nullptr;
}//isEmpty

template<class T> typename Container<T>::Iterator Container<T>::find(T& el) const{
    Container<T>::Iterator iter=begin();
    for(iter;iter!=end();iter++){
        if(*iter==el)
            return iter;
    }//for
    return nullptr;
}//getSize

//inserimenti
template<class T> void Container<T>::pushFirst(const T& el){
    if(first){
        first->pre=new Node(el,nullptr,first);
        first=first->prev;
    }else{
        first=new Node(el,nullptr,nullptr);
        last=first;
    }//if_else
    size++;
}//pushFirst

template<class T> void Container<T>::pushLast(const T& el){
    size++;
    if(last){
        last->next=new Node(el,last);
        last=last->next;
    }else{
        first=new Node(el);
        last=first;
    }//if_else
}//pushLast

template<class T> typename Container<T>::Iterator Container<T>::pushPos(Iterator iter,T& el){
    Node* temp=new Node(el,iter.nodo,iter.nodo->next);
    if(iter.nodo==last)
        last=temp;
    else
        iter.nodo->next->pre=temp;
    iter.nodo->next=temp;
    size++;
    return Iterator(temp);
}//pushPos

//rimozioni
template<class T> void Container<T>::deleteFirst(){
    Node* temp=first;
    if(first!=last){
        first=first->next;
        first->pre=nullptr;
    }else{
        first=nullptr;
        last=nullptr;
    }//if_else
    size--;
    temp->next=nullptr;
    delete temp;
}//deleteFirst

template<class T> void Container<T>::deleteLast(){
    Node* temp=last;
    if(first!=last){
        last=last->pre;
        last->next=nullptr;
    }else{
        first=nullptr;
        last=nullptr;
    }//if_else
    size--;
    temp->pre=nullptr;
    delete temp;
}//deleteLast

template<class T> void Container<T>::deleteAll(){
    if(first)
        delete first;
    first=nullptr;
    last=nullptr;
    size=0;
}//deleteAll

template<class T> typename Container<T>::Iterator Container<T>::deletePos(Iterator iter){
    Iterator temp;
    if(iter.nodo==first && iter.nodo==last){//c'è_solo_un_elemento
        temp=end();
        first=nullptr;
        last=nullptr;
    }else if(iter.nodo==first){//elimino_il _primo
        first=iter.nodo->next;
        first->pre=nullptr;
        temp=Iterator(first);
    }else if(iter.nodo==last){//elimino_l'ultimo
        temp=end();
        iter.nodo->pre->next=nullptr;
        last=iter.nodo->pre;
    }else{//elimino_in_mezzo_alla_lista
        temp=Iterator(iter.nodo->next);
        iter.nodo->pre->next=iter.nodo->next;
        iter.nodo->next->pre=iter.nodo->pre;
        iter.nodo->next=nullptr;
        iter.nodo->pre=nullptr;
        delete iter.nodo;
    }//if_else
    size--;
    return temp;
}//deletePos

template<class T> void Container<T>::deleteThis(const T& el){
    Node* temp=first;
    Node* found=0;
    while(temp!=last){
        if(temp->info==el){
            found=temp;
            if(temp==first){
                temp=temp->next;
                deleteFirst();
            }else{
                temp->pre->next=temp->next;
                temp->next->pre=temp->pre;
                temp=temp->next;
                found->next=nullptr;
                delete found;
                size--;
            }//internal_if_else
        }else
            temp=temp->next;
    }//while
    if(temp->info==el)//controllo_l'ultimo_elemento
        deleteLast();
}//deleteThis

template<class T> void Container<T>::sortC(){
    Node* tempH=first;
    Node* tempLast=NULL;
    T temp;
    int swap;
    /*for(int i=0;i<getSize();i++){
        while(tempH->next){
            if(tempH->info<tempH->next->info){
                temp=tempH->info;
                tempH->info=tempH->next->info;
                tempH->next->info=temp;
                tempH=tempH->next;
            }else
                tempH=tempH->next;
        }//while
        tempH=first;
    }//for*/
    if(first==NULL)
        return;
    do{
        swap=0;
        tempH=first;
        while(tempH->next!=tempLast){
            if(tempH->info > tempH->next->info){
                temp=tempH->info;
                tempH->info=tempH->next->info;
                tempH->next->info=temp;
                swap=1;
            }
            tempH=tempH->next;
        }
        tempLast=tempH;
    }while(swap);
}//sort
