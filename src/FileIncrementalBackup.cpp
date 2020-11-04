#include "FileIncrementalBackup.h"
using namespace std;

FileIncrementalBackup::FileIncrementalBackup(fstream& output, const string& inputPath, const string & relativePath) :
FileFullBackup::FileFullBackup(output, inputPath, relativePath) {
    unsigned long int temp = output.tellg();
    output.seekg(0, ios::end);
    length = output.tellg();
    output.seekg(temp);
}

void FileIncrementalBackup::backup() {
    unsigned long int startingPosition = output.tellp(); //Save position of writing pointer because of searching through the files
    findFile(relativePath);
    output.seekp(0, ios::end);
    FileFullBackup::backup();
    output.seekp(startingPosition);
}

bool FileIncrementalBackup::findFile(const string& path) {
    unsigned long int position = 4;
    output.seekg(position);
    char type;
    while (position < length) {
        output.read((char*) &type, sizeof (char));
        position++;
        if (type == 'F') {
            char increment;
            output.read((char*) &increment, sizeof (char));
            position++;
            if (increment == 'T') {
                jumpThroughTheRest(position,output);
                continue;
            }
            unsigned long int incrementPosition = position - 1;
            unsigned long int sizeOfFile;
            int nameLength;
            output.read((char*) &sizeOfFile, sizeof (unsigned long int));
            output.read((char*) &nameLength, sizeof (int));
            char * name = new char[nameLength + 1];
            output.read(name, nameLength * sizeof (char));
            name[nameLength] = 0;
            if (strcmp(name, path.c_str()) == 0) {
                delete [] name;
                setIncrement(incrementPosition);
                return true;
            }
            position += sizeof (unsigned long int)+sizeOfFile * sizeof (char) + sizeof (int)+nameLength * sizeof (char);
            output.seekg(position);
            delete [] name;
        } else {
            jumpThroughFolder(position,output);
        }
    }
    return false;
}


void FileIncrementalBackup::setIncrement(unsigned long int position) {
    output.seekp(position);
    char increment = 'T';
    output.write((char*) &increment, sizeof (char));
}


