#include "Backuper.h"
#include "FileIncrementalBackup.h"
#include "FileFullBackup.h"
#include "FolderFullBackup.h"
#include "FolderIncrementalBackup.h"
using namespace std;

Backuper::Backuper(string sourcePath, string destinationPath) :
sourcePath(sourcePath), destinationPath(destinationPath) {
    outputPath = getOutputPath();
}

Backuper::~Backuper() { }

void Backuper::backup() {
    bool existence = fileExists();
    fstream output;
    int timeOfChange;
    if (existence) {
         output.open(outputPath.c_str(),ios::in | ios::out | ios::binary);
         output.read((char*)&timeOfChange,sizeof(int));
         output.seekg(0);
    } else {
         output.open(outputPath.c_str(),ios::out | ios::binary);
    }
    Item * rootFolder;
    if (existence) {
        rootFolder = new FolderIncrementalBackup(output, sourcePath,getName(),timeOfChange);
    } else {
        rootFolder = new FolderFullBackup(output, sourcePath,getName());
    }
    writeTimeOfChange(output);
    rootFolder->backup();
    delete rootFolder;
    output.close();
}

string Backuper::getOutputPath() const {
    return destinationPath + "/" + getName() + ".bup";
}

bool Backuper::fileExists() const {
    ifstream test(outputPath.c_str());
    bool result=test.good();
    test.close();
    return result;
}

int Backuper::getTime() const {
    time_t timer;
    time(&timer);
    return timer;
}

void Backuper::writeTimeOfChange(fstream & output) {
    int time = getTime();
    output.write((char*) &time, sizeof (time));
}

string Backuper::getName() const {
    int size = sourcePath.size();
    int i = 0;
    while (sourcePath[size - i - 1] != '/') {
        i++;
    }
    return sourcePath.substr(size - i);
}