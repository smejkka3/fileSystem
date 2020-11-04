
#include "InterfaceException.h"
using namespace std;

InterfaceException::InterfaceException(const string & text) : text(text) {}

ostream & operator <<(ostream & os, const InterfaceException & e) {
    os << e.text;
    return os;
}
