/* 
 * File:   Item.h
 * Author: ubuntu
 *
 * Created on May 1, 2013, 9:33 PM
 */

#ifndef ITEM_H
#define	ITEM_H

#include <fstream>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include<dirent.h>
#include <string.h>
using namespace std;


///Abstract class for files and folders
class Item {
public:
    Item(fstream & output, const string & inputPath, const string & relativePath);
    virtual ~Item();
    ///Create backup
    virtual void backup() = 0;
protected:
    ///Stream of the backup file
    fstream & output;
    ///Path to the folder to be saved
    string inputPath;
    ///Relative path to the file or folder in the backup structure
    string relativePath;
    ///Converts c++ string to cstring
    /**
     * 
     * @param source string which is to be converted
     * @param destination cstring which holds the output
     */
    void convertString(const string & source, char * destination);
};

#endif	/* ITEM_H */

