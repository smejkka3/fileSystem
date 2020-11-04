
#include "FolderIncrementalBackup.h"
#include "FileIncrementalBackup.h"
#include "FolderFullBackup.h"


using namespace std;

FolderIncrementalBackup::FolderIncrementalBackup(fstream& output, const string& inputPath, const string & relativePath, int timeOfChange) : Folder::Folder(output, inputPath, relativePath) {
    this->timeOfChange = timeOfChange;
    unsigned long int temp = output.tellg();
    output.seekg(0, ios::end);
    length = output.tellg();
    output.seekg(temp);
}

void FolderIncrementalBackup::backup() {
    Item * item;
    DIR *thisFolder;
    struct dirent *content;
    string contentPath;
    string newRelativePath;

    thisFolder = opendir(inputPath.c_str()); //some check later
    while ((content = readdir(thisFolder))) {
        if (strcmp(content->d_name, ".") != 0 && strcmp(content->d_name, "..")) {
            contentPath = inputPath + "/" + content->d_name;
            newRelativePath = relativePath + "/" + content->d_name;
            if (isFolder(contentPath)) {
                if (findFolder(newRelativePath)) {
                    item = new FolderIncrementalBackup(output, contentPath, newRelativePath, timeOfChange);
                } else {
                    item = new FolderFullBackup(output, contentPath, newRelativePath);
                }
            } else {
                if (isNewer(contentPath)) {
                    item = new FileIncrementalBackup(output,contentPath,newRelativePath);
                } else {
                    continue;
                }
            }
            item->backup();
            delete item;
        }
    }
    
    closedir(thisFolder);
 //   output.seekg(startingPosition);
}

int FolderIncrementalBackup::getTimeOfChange(const string& path) const {
    struct stat buf;
    stat(path.c_str(), &buf);
    return buf.st_ctim.tv_sec;
}

bool FolderIncrementalBackup::findFolder(const string & path)  {
    unsigned long int position = 4;
    output.seekg(position);
    char  type;
    
    while (position < length) {
        output.read((char*)&type, sizeof (char));
        position++;
        if (type == 'D') {
            int nameLength;
            output.read((char*) &nameLength, sizeof (int));
            char * name = new char[nameLength + 1];
            output.read(name, nameLength * sizeof (char));
            position += sizeof (int)+nameLength * sizeof (char);
            name[nameLength] = 0;
            if (strcmp(name, path.c_str()) == 0) {
                delete [] name;
                return true;
            }
            delete [] name;
        } else {
            jumpThroughFile(position,output);
        }
    }
    return false;
}


bool FolderIncrementalBackup::isNewer(const string & path) const {
    if (getTimeOfChange(path)>timeOfChange) {
        return true;
    }
    return false;
}



