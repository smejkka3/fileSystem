#include "FileFullBackup.h"
using namespace std;

FileFullBackup::FileFullBackup(fstream& output, const string& inputPath,const string & relativePath) : Item::Item(output,inputPath,relativePath) {
    size=getSize();
}


void FileFullBackup::backup() {
    output.seekp(0,ios::end);
    ifstream input(inputPath.c_str(), ios::binary | ios::in);
    writeHeader();
    
    //Writes file by parts because the whole file may not fit into the buffer
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
    input.close();
  }

void FileFullBackup::writeHeader() {
    char type = 'F';
    output.write((char*) &type, sizeof (char));
    
    //notes the fact that file has no increment
    char increment = 'F';
    output.write((char*) &increment, sizeof (char));
    output.write((char*) &size, sizeof (unsigned long int));
    int pathSize = relativePath.size();
    output.write((char*) &pathSize, sizeof (int));
    char * temp = new char[pathSize];
    convertString(relativePath,temp);
    output.write(temp, pathSize);
    delete [] temp;
}

unsigned long int FileFullBackup::getSize() const {
    struct stat buf;
    stat(inputPath.c_str(), &buf);
    return buf.st_size;
}