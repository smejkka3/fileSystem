#include "Folder.h"

Folder::Folder(fstream& output, const string& inputPath,const string & relativePath) : Item::Item(output,inputPath,relativePath) {}
    
bool Folder::isFolder(string path) const {
    struct stat buf;
    stat(path.c_str(), &buf);
    return S_ISDIR(buf.st_mode);
}







