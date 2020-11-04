/* 
 * File:   FolderFinder.h
 * Author: ubuntu
 *
 * Created on May 4, 2013, 6:50 PM
 */

#ifndef FOLDERFINDER_H
#define	FOLDERFINDER_H

#include "Finder.h"
#include <fstream>
#include <string.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>

///Class which searches for specific folder in the backup and restores it (or them) with its contents
class FolderFinder : public Finder {
public:
    FolderFinder(const std::string& inputPath,const std::string & folder,  const std::string& outputPath);
    ///Search and restore folder 
    /**
     * 
     * @return Number of folders restored
     */
    int findAndRestore();
private:
    ///Path to the backup file
    std::string inputPath;
    ///Where to extract found folders
    std::string outputPath;
    ///Name of the searched folder
    std::string folder;
    ///Number of folders found
    int files;
    ///Size of the backup
    unsigned long int length;
    ///Path to the found folder in the backup (every file in the backup which is in this folder has this prefix
    std::string prefix;
    unsigned int prefixLength;
    ///Path to the output (starting with prefix)
    std::string outputName;
    ///Get name of restored folder
    /**
     * if there are multiple folders of desired name in the backup
     * this function adds number of the folder to its name
     **/
    std::string getName(const std::string & name);
    ///Go through the rest of the backup and restores all folders and files which belong to the found folder
    void restoreContent(unsigned long int position);
    ///Restore folder belonging under the found folder
    void findAndRestoreFolder(unsigned long int & position);
    ///Restore file belonging under the found folder
    void findAndRestoreFile(unsigned long int & position);
    ///Compare name of the folder in the backup to the searched folder
    bool compareNames(const std::string & name) const;
    ///get output location to found file or folder
    std::string getFullOutputName(const std::string & name);
    ///Restore the searched folder
    void restoreFirstFolder();
};

#endif	/* FOLDERFINDER_H */

