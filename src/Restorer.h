
#ifndef RESTORER_H
#define	RESTORER_H

#include <string>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include "Finder.h"

///Restores all items from the backup
class Restorer : public Finder {
public:
    Restorer(const std::string & inputPath,const std::string & outputPath);
    ///Restore everything
    void restore();
private:
    std::string inputPath,outputPath;
    ///size of the backup file
    unsigned long int length;
    ///Restore single file from backup
    void restoreFile(unsigned long int & position);
    ///Restore single folder from the backup
    void restoreFolder(unsigned long int & position);
    const static unsigned long int BUFFER_SIZE=500000000;
    
};

#endif	/* RESTORER_H */

