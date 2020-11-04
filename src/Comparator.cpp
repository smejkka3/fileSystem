#include "Comparator.h"
#include "Restorer.h"
using namespace std;

Comparator::Comparator(const std::string& backupPath, const std::string& folderPath, const std::string& relativePath) :
backupPath(backupPath), folderPath(folderPath), relativePath(relativePath) { }

int Comparator::findFile() {
    if (!checkIfFileExists()) {
        return 3;
    }
    input.open(backupPath.c_str(), ios::in | ios::binary);
    unsigned long int length = getLength(input);
    unsigned long int position = 4;
    input.seekg(position);
    char type;
    string fullRelativePath = getFullRelativePath();
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
            if (strcmp(name, fullRelativePath.c_str()) == 0) {
                bool result = compareFile(sizeOfFile, getAbsolutePath(relativePath));
                delete [] name;
                input.close();
                if (result) {
                    return 1;
                }
                return 2;
            }
            position += sizeof (unsigned long int)+sizeOfFile * sizeof (char) + sizeof (int)+nameLength * sizeof (char);
            input.seekg(position);
            delete [] name;
        } else {
            jumpThroughFolder(position, input);
        }
    }
    input.close();
    return 0;
}

unsigned long int Comparator::getLength(fstream & input) {
    input.seekg(0, ios::end);
    unsigned long int length = input.tellg();
    input.seekg(0);
    return length;
}

string Comparator::getFullRelativePath() {
    int size = folderPath.size();
    int i = 0;
    while (folderPath[size - i - 1] != '/') {
        i++;
    }
    return folderPath.substr(size - i) + "/" + relativePath;
}

string Comparator::getAbsolutePath(const std::string& name) {
    return folderPath + "/" + name;
}

bool Comparator::compareFile(unsigned long int size, const string & path) {
    if (getSize(path) != size) {
        return false;
    }
    ifstream file(path.c_str(), ios::in | ios::binary);
    for (unsigned long int i = 0; i < size; i++) {
        char a, b;
        input.read((char*) &a, sizeof (char));
        file.read((char*) &b, sizeof (char));
        if (a != b) {
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}

unsigned long int Comparator::getSize(const string & path) const {
    struct stat buf;
    stat(path.c_str(), &buf);
    return buf.st_size;
}

bool Comparator::checkIfFileExists() {
    string path = getAbsolutePath(relativePath);
    ifstream test(path.c_str());
    if (test.good()) {
        test.close();
        return true;
    }
    return false;
} 