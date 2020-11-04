
#ifndef COMPARATOR_H
#define	COMPARATOR_H

#include <string>

#include "JumpThrough.h"
#include <sys/stat.h>
#include "fstream"

///Class which tells us if the file on disk is the same as the file in the backup
class Comparator : public JumpThrough {
public:
    Comparator(const std::string & backupPath,const std::string & folderPath, const std::string & relativePath);
    ///Search for the file in the backup and compare it to the file on disk if found 
    /**
     * @return 0 if file isn't in the backup
     * @return 1 if file on disk is same as the file in the backup
     * @return 2 if both files exist but they are different
     * @return 3 if file doesn't exist on disk
     **/ 
    int findFile();
private:
    std::fstream input;
    ///Path to the backup file
    std::string backupPath;
    ///Path to the folder from which is backup created
    std::string folderPath;
    ///Path to the file relative to main backup folder
    std::string relativePath;
    ///Get size of the backup file
    unsigned long int getLength(std::fstream & input);
    ///Get path to the file relative to backup
    std::string getFullRelativePath();
    ///Get absolute path to the desired file
    /**
     * 
     * @param name Relative path to the file
     **/
    std::string getAbsolutePath(const std::string & name);
    ///Compares file on disk and file in the backup
    /**
     * @return true if files are same
     * @return false if files are different
     * @param size Size of the file in the backup
     * @param path Path to the file on disk
     */
    bool compareFile(unsigned long int size,const std::string & path);
    ///Get size of the desired file
    unsigned long int getSize(const std::string & path) const;
    bool checkIfFileExists();
};

#endif	/* COMPARATOR_H */

