#include "Restorer.h"
using namespace std;

Restorer::Restorer(const std::string& inputPath, const std::string& outputPath) :
inputPath(inputPath), outputPath(outputPath) {
    struct stat buf;
    stat(inputPath.c_str(), &buf);
    length = buf.st_size;
}

void Restorer::restore() {
    input.open(inputPath.c_str(), ios::binary | ios::in);

    unsigned long int position = 4;
    input.seekg(position);
    char type;
    while (position < length) {
        input.read((char*) &type, sizeof (char));
        position++;
        if (type == 'D') {
            restoreFolder(position);
        } else {
            restoreFile(position);
        }
    }
    input.close();
}

void Restorer::restoreFolder(unsigned long int& position) {
    int nameLength;
    input.read((char*) &nameLength, sizeof (int));
    char * name = new char[nameLength + 1];
    input.read(name, nameLength * sizeof (char));
    position += sizeof (int)+nameLength * sizeof (char);
    name[nameLength] = 0;
    string path = outputPath + "/" + name;
    mkdir(path.c_str(), 0700);
    delete [] name;
}

void Restorer::restoreFile(unsigned long int& position) {
    char increment;
    input.read((char*) &increment, sizeof (char));
    position++;
    if (increment == 'T') {
        jumpThroughTheRest(position,input);
        return;
    }
    unsigned long int sizeOfFile;
    int nameLength;
    input.read((char*) &sizeOfFile, sizeof (unsigned long int));
    input.read((char*) &nameLength, sizeof (int));
    char * name = new char[nameLength + 1];
    input.read(name, nameLength * sizeof (char));
    name[nameLength] = 0;
    string path=outputPath + "/" + name;
    writeFile(path,sizeOfFile);
    position += sizeof (unsigned long int)+sizeOfFile * sizeof (char) + sizeof (int)+nameLength * sizeof (char);
    delete [] name;
}

