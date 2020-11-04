/* 
 * File:   InterfaceException.h
 * Author: ubuntu
 *
 * Created on May 14, 2013, 7:20 PM
 */

#ifndef INTERFACEEXCEPTION_H
#define	INTERFACEEXCEPTION_H

#include <string>
#include <iostream>
///Class handling exceptions which can occur during work with interface
class InterfaceException {
public:

    InterfaceException(const std::string & text);
private:
    std::string text;
    ///Print info about exception
    friend std::ostream & operator <<(std::ostream & os, const InterfaceException & e);
};


#endif	/* INTERFACEEXCEPTION_H */

