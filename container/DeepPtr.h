#ifndef DEEPPTR_H
#define DEEPPTR_H

template<class T> class DeepPtr{
    private:
        T *el;
    public:
        //costruttori/distruttore
        DeepPtr(const DeepPtr&);
        DeepPtr(const T*t = nullptr) : el((t != nullptr) ? t->clone() : nullptr){}
        ~DeepPtr();
        //operatori
        DeepPtr& operator=(const DeepPtr&);
        T& operator*() const;
        T* operator->() const;
        bool operator==(const DeepPtr&) const;
        bool operator!=(const DeepPtr&) const;
        //metodi
        DeepPtr* clone() const;
        virtual T& getT() const;
};//DeepPtr
#endif
