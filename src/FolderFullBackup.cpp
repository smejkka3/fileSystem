#include "FolderFullBackup.h"
using namespace std;

FolderFullBackup::FolderFullBackup(fstream & output, const string& inputPath,const string & relativePath) : Folder::Folder(output, inputPath,relativePath) { }

void FolderFullBackup::backup() {
    output.seekp(0,ios::end);
    Item * item;
    DIR *thisFolder;
    struct dirent *content;
    string contentPath;
    string newRelativePath;
    writeHeader();

    thisFolder = opendir(inputPath.c_str()); //some check later
    while ((content = readdir(thisFolder))) {
        if (strcmp(content->d_name, ".") != 0 && strcmp(content->d_name, "..")) {
            contentPath = inputPath + "/" + content->d_name;
            newRelativePath=relativePath+"/" + content->d_name;
            if (isFolder(contentPath)) {
                item = new FolderFullBackup(output, contentPath,newRelativePath);
            } else {
                 item = new FileFullBackup(output, contentPath,newRelativePath);
            }
            item->backup();
            delete item;
        }
    }
    closedir(thisFolder);
    
}


void FolderFullBackup::writeHeader() {
    char type='D';
    output.write((char*) &type, sizeof (char));
    int length=relativePath.length();
    output.write((char*)&length,sizeof(int));
    char * temp= new char[length];
    convertString(relativePath,temp);
    output.write(temp,length*sizeof(char));
    delete [] temp;
}

