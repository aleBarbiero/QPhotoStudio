#ifndef EXCEPTION_H
#define EXCEPTION_H
#include<exception>
#include<string>
#include<iostream>

class ErrValue: public std::exception {
    private:
        std::string msg;
    public:
        virtual const char* what() const throw();
        ErrValue(const std::string& ="Generic Error");
        ~ErrValue(){}
};

class ErrBond: public std::exception {
    private:
        std::string msg;
    public:
        virtual const char* what() const throw();
        ErrBond(const std::string& ="Generic Error");
        ~ErrBond(){}
};

#endif // EXCEPTION_H
