#ifndef FOLDERFULLBACKUP_H
#define	FOLDERFULLBACKUP_H

#include "Folder.h"
#include "FileFullBackup.h"

///Creates full backup of the folder and all its contents
class FolderFullBackup : public Folder {
public:
    FolderFullBackup(fstream & output,const string & inputPath,const string & relativePath);
    void  backup();
private:
    void writeHeader();
};

#endif	/* FOLDERFULLBACKUP_H */

