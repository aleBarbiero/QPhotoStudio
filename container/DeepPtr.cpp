#include "DeepPtr.h"

//costruttori/distruttore
template<class T> DeepPtr<T>::DeepPtr(const DeepPtr& newEl){//copia_da_DeepPtr
    el=(newEl.el)->clone();
}//DeepPtr

template<class T> DeepPtr<T>::~DeepPtr(){
    if(el)
        delete el;
}//~DeepPtr

//operatori
template<class T> T& DeepPtr<T>::operator*() const{
    return *el;
}//*

template<class T> DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& newEl){
    if(this!=&newEl){
        if(el)
            delete el;
        if(newEl.el)
            el=(newEl.el->clone());
        else
            el=nullptr;
    }//if
    return *this;
}//=

template<class T> T* DeepPtr<T>::operator->() const{
    return el;
}//->

template<class T> bool DeepPtr<T>::operator==(const DeepPtr& newEl) const{
    return el->Product::operator==(*newEl.el);
}//==

template<class T> bool DeepPtr<T>::operator!=(const DeepPtr& newEl) const{
    return el->Product::operator!=(newEl.el);
}// !=

template<class T> bool DeepPtr<T>::operator>(const DeepPtr& newEl) const{
    return el->Product::operator>(*newEl.el);
}//operator>

template<class T> bool DeepPtr<T>::operator>=(const DeepPtr& newEl) const{
    return el->Product::operator>=(newEl.el);
}//>=

template<class T> bool DeepPtr<T>::operator<(const DeepPtr& newEl) const{
    return el->Product::operator<(newEl.el);
}//operator<

template<class T> bool DeepPtr<T>::operator<=(const DeepPtr& newEl) const{
    return el->Product::operator<=(newEl.el);
}//operator<=

//metodo
template<class T> typename DeepPtr<T>::DeepPtr* DeepPtr<T>::clone() const{
    return new DeepPtr(*this);
}//const

template<class T> T& DeepPtr<T>::getT() const{
    return *el;
}//getT
