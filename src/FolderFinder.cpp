#include "FolderFinder.h"
using namespace std;

FolderFinder::FolderFinder(const std::string& inputPath, const string & folder, const std::string& outputPath) :
inputPath(inputPath), outputPath(outputPath), folder(folder) {
    input.open(inputPath.c_str(), ios::binary | ios::in);
    input.seekg(0, ios::end);
    length = input.tellg();
    input.seekg(0);
}

int FolderFinder::findAndRestore() {
    unsigned long int position = 4;
    input.seekg(position);
    char type;
    files=0;
    while (position < length) {
        input.read((char*) &type, sizeof (char));
        position++;
        if (type == 'D') {
            int nameLength;
            input.read((char*) &nameLength, sizeof (int));
            char * name = new char[nameLength + 1];
            input.read(name, nameLength * sizeof (char));
            position += sizeof (int)+nameLength * sizeof (char);
            name[nameLength] = 0;
            string nameOnly = extractName(name);
            if (strcmp(folder.c_str(), nameOnly.c_str()) == 0) {
                files++;
                outputName = getName(folder);
                prefix = name;
                restoreFirstFolder();
                restoreContent(position);
                input.seekg(position);
            }
            delete [] name;
        } else {
            jumpThroughFile(position, input);
        }
    }
    return files;
}

string FolderFinder::getName(const string& name) {
    //if this is the first found file do not alter the name
    if (files == 1) {
        return name;
    }
    stringstream s;
    s << files;
    string n;
    s >> n;
    return name + "(" + n + ")";
}

void FolderFinder::restoreContent(unsigned long int position) {
    prefixLength = prefix.length();
    char type;
    while (position < length) {
        input.read((char*) &type, sizeof (char));
        position++;
        if (type == 'D') {
            findAndRestoreFolder(position);
        } else {
            findAndRestoreFile(position);
        }
    }
}

void FolderFinder::findAndRestoreFolder(unsigned long int & position) {
    int nameLength;
    input.read((char*) &nameLength, sizeof (int));
    char * name = new char[nameLength + 1];
    input.read(name, nameLength * sizeof (char));
    position += sizeof (int)+nameLength * sizeof (char);
    name[nameLength] = 0;
    if (compareNames(name)) {
        string path = getFullOutputName(name);
        mkdir(path.c_str(), 0700);
    }
    delete [] name;
}

void FolderFinder::findAndRestoreFile(unsigned long int& position) {
    char increment;
    input.read((char*) &increment, sizeof (char));
    position++;
    if (increment == 'T') {
        jumpThroughTheRest(position, input);
        return;
    }
    unsigned long int sizeOfFile;
    int nameLength;
    input.read((char*) &sizeOfFile, sizeof (unsigned long int));
    input.read((char*) &nameLength, sizeof (int));
    char * name = new char[nameLength + 1];
    input.read(name, nameLength * sizeof (char));
    name[nameLength] = 0;
    if (compareNames(name)) {
        string path = getFullOutputName(name);
        writeFile(path, sizeOfFile);
    }
    position += sizeof (unsigned long int)+sizeOfFile * sizeof (char) + sizeof (int)+nameLength * sizeof (char);
    delete [] name;
}

bool FolderFinder::compareNames(const string& name) const {
    if (name.length()<prefixLength) {
        return false;
    }
    string beg = name.substr(0, prefixLength);
    if (beg == prefix) {
        return true;
    }
    return false;
}

string FolderFinder::getFullOutputName(const string & name) {
    string end = name.substr(prefixLength);
    return outputPath+"/"+outputName  + end;
}



void FolderFinder::restoreFirstFolder() {
    string path = outputPath+"/"+outputName;
    mkdir(path.c_str(), 0700);
}


