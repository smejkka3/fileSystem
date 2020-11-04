#include "Item.h"

Item::Item(fstream& output, const string& inputPath,const string & relativePath) :
output(output),inputPath(inputPath),relativePath(relativePath) {}

void Item::convertString(const string & source, char* destination) {
    for (unsigned int i=0;i<source.length();i++) {
        destination[i]=source[i];
    }
}

Item::~Item() {}   
