#ifndef FILEFULLBACKUP_H
#define	FILEFULLBACKUP_H

#include "Item.h"
///Class which creates full backup of the file
class FileFullBackup : public Item {
public:
    FileFullBackup(fstream& output, const string& inputPath,const string & relativePath);
    void backup();
    void writeHeader();
protected:
    ///Get size of the file to be saved
    unsigned long int getSize() const;
    ///Size of the file to be saved
    unsigned long int size;
    const static unsigned long int BUFFER_SIZE=500000000;
};

#endif	/* FILEFULLBACKUP_H */

