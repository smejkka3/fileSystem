#include "JumpThrough.h"
using namespace std;
void JumpThrough::jumpThroughFolder(unsigned long int & position,fstream & file) {
    int pathSize;
    file.read((char*) &pathSize, sizeof (int));
    position += sizeof (int)+pathSize;
    file.seekg(position);
}

void JumpThrough::jumpThroughTheRest(unsigned long int& position,fstream & file) {
    unsigned long int sizeOfFile;
    int pathSize;
    file.read((char*) &sizeOfFile, sizeof (unsigned long int));
    file.read((char*) &pathSize, sizeof (int));
    position += sizeof (unsigned long int)+sizeOfFile + sizeof (int)+pathSize;
    file.seekg(position);
}

void JumpThrough::jumpThroughFile(unsigned long int & position,fstream & file)  {
    file.seekg(++position); //Increment information must be left out
    unsigned long int sizeOfFile;
    int pathSize;
    file.read((char*) &sizeOfFile, sizeof (unsigned long int));
    file.read((char*) &pathSize, sizeof (int));
    position += sizeof (unsigned long int)+sizeOfFile + sizeof (int)+pathSize;
    file.seekg(position);
}
