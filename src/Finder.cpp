#include "Finder.h"
using namespace std;


Finder::Finder() {
    
}

void Finder::writeFile(const string& path,unsigned long int size) {
    ofstream output(path.c_str(),ios::out|ios::binary);
    while (size>BUFFER_SIZE) {
        char * buffer = new char[BUFFER_SIZE];
        input.read(buffer, BUFFER_SIZE);
        output.write(buffer,BUFFER_SIZE);
        size-=BUFFER_SIZE;
        delete [] buffer;
    }
    char * buffer = new char[size];
    input.read(buffer,size);
    output.write(buffer,size);
    delete [] buffer;
    output.close();
}

string Finder::extractName(const std::string& path) {
    int size = path.size();
    int i = 0;
    
    while (size-i-1 >0 && path[size - i - 1] != '/') {
        i++;
    }
    if (size-i-1==-1) {
        return path;
    }
    return path.substr(size - i);
}