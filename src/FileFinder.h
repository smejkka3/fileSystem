

#ifndef FILEFINDER_H
#define	FILEFINDER_H

#include "Finder.h"
#include <fstream>
#include <sstream>
///Class which searches for specific files in the backup and restores them if found
class FileFinder : public Finder {
public:
    FileFinder(const std::string & inputPath,const std::string & file,const std::string & outputPath);
    ///Search and restore file
    /**
     * 
     * @return number of files restores
     */
    int findAndRestore();
private:
    ///Size of the backup file
    unsigned long int length;
    ///Number of files found
    int files;
    ///Path to the backup file
    std::string inputPath;
    ///Where the found files are stored
    std::string outputPath;
    ///Name of the searched file
    std::string file;
    ///Restore found file from the backup
    void restoreFile(std::string name,unsigned long int size);
    ///Get name of restored file
    /**
     * if there are multiple files of desired name in the backup
     * this function adds number of the file to its name
     **/
    std::string getName(const std::string & name);
};

#endif	/* FILEFINDER_H */

