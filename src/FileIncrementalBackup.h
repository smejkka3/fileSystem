
#ifndef FILEINCREMENTALBACKUP_H
#define	FILEINCREMENTALBACKUP_H


#include "FileFullBackup.h"
#include "Finder.h"
#include "JumpThrough.h"

///Class which creates incremental backup of the file
/**
 * Searches for the file in the backup. 
 * If it is found information about increment is noted
 * and new full backup is made. If it isn't full backup is made 
 * without any other changes.
 **/
class FileIncrementalBackup : public FileFullBackup, public JumpThrough {
public:
    FileIncrementalBackup(fstream& output, const string& inputPath, const string & relativePath);
    void backup();
private:
    ///Length of the backup file
    unsigned long int length;
    ///Look for file in the backup
    bool findFile(const string & path);
    ///Set information about increment to true ('T' in the backup)
    /**
     * 
     * @param position Where in the backup is information about increment located
     */
    void setIncrement(unsigned long int position);
};

#endif	/* FILEINCREMENTALBACKUP_H */

