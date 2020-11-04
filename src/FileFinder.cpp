#include "FileFinder.h"
using namespace std;

FileFinder::FileFinder(const std::string& inputPath,const string & file,  const std::string& outputPath) :
inputPath(inputPath), outputPath(outputPath),file(file) {
    input.open(inputPath.c_str(), ios::binary | ios::in);
    input.seekg(0, ios::end);
    length = input.tellg();
    input.seekg(0);
}

int FileFinder::findAndRestore() {
    files = 0;
    unsigned long int position = 4;
    input.seekg(position);
    char type;
    while (position < length) {
        input.read((char*) &type, sizeof (char));
        position++;
        if (type == 'F') {
            char increment;
            input.read((char*) &increment, sizeof (char));
            position++;
            if (increment == 'T') {
                jumpThroughTheRest(position, input);
                continue;
            }
            unsigned long int sizeOfFile;
            int nameLength;
            input.read((char*) &sizeOfFile, sizeof (unsigned long int));
            input.read((char*) &nameLength, sizeof (int));
            char * name = new char[nameLength + 1];
            input.read(name, nameLength * sizeof (char));
            name[nameLength] = 0;
            string nameOnly = extractName(name);
            if (strcmp(file.c_str(), nameOnly.c_str()) == 0) {
                files++;
                restoreFile(nameOnly, sizeOfFile);
            }
            position += sizeof (unsigned long int)+sizeOfFile * sizeof (char) + sizeof (int)+nameLength * sizeof (char);
            input.seekg(position);
            delete [] name;
        } else {
            jumpThroughFolder(position, input);
        }
    }
    input.close();
    return files;
    
}

void FileFinder::restoreFile(string name, unsigned long int size) {
    string out = getName(name);
    writeFile(out,size);
}

string FileFinder::getName(const string& name) {
    //if this is the first found file do not alter the name
    if (files == 1) {
        return outputPath + "/" + name;
    }
    int size = name.size();
    int i = 0;
    while (size - i - 1 > -1 && name[size - i - 1] != '.') {
        i++;
    }
    if (size - i - 1 < 0) {
        stringstream s;
        s << files;
        string n;
        s >> n;
        return outputPath + "/" + name + "(" + n + ")";
    }
    string end = name.substr(size - i - 1);
    string beg = name.substr(0, size - i - 1);
    stringstream s;
    s << files;
    string n;
    s >> n;
    return outputPath + "/" + beg + "(" + n + ")" + end;
}