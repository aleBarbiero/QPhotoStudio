#include "Exception.h"

ErrValue::ErrValue(const std::string& m): msg(m) {}

ErrBond::ErrBond(const std::string& m): msg(m) {}

const char* ErrValue::what() const throw(){
    return msg.c_str();
}

const char* ErrBond::what() const throw(){
    return msg.c_str();
}
