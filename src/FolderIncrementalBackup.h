#ifndef FOLDERINCREMENTALBACKUP_H
#define	FOLDERINCREMENTALBACKUP_H

#include "Folder.h"
#include "Finder.h"
#include "JumpThrough.h"

///Creates full incremental backup of the folder and makes incremental backup of all its contents
class FolderIncrementalBackup : public Folder,  public JumpThrough {
public:
    FolderIncrementalBackup(fstream & output,const string & inputPath,const string & relativePath,int timeOfChange);
    void backup();
private:
    ///Size of the backup file
    unsigned long int length;
    ///Last time of change in the backup file
    int timeOfChange;
    ///Gets time of the last change from the backup file
    /**
     * 
     * @param path Path to the backup file
     * @return time of change in miliseconds
     */
    int getTimeOfChange(const string & path) const;
    ///Check if the folder is already in the backup
    /**
     * If the folder is not in the backup full backup of it is made. 
     * If it is in the backup, incremental backup is made.
     **/    
    bool findFolder(const string & path) ;
    ///Check if the file is newer than the backup file. If it is, backup has to be made.
    bool isNewer(const string & path) const;
};

#endif	/* FOLDERINCREMENTALBACKUP_H */

