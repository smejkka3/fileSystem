
#ifndef INTERFACE_H
#define	INTERFACE_H

#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <dirent.h>
#include <sstream>
#include <sys/stat.h>
#include "Restorer.h"
#include "FileFinder.h"
#include "Comparator.h"
#include "Backuper.h"
#include "FolderFinder.h"
#include "InterfaceException.h"

#include <sys/time.h> 
#include <time.h> 

#include <algorithm>

///Class providing user interaction 
class Interface {
public:
    Interface(int argc, char** argv);
    ///Choose which action should be performed according to command line arguments
    void decide();
private:
    int argc;
    char ** argv;
    ///Show list of options
    void callHelp();
    ///Print delimiting sequence in help
    void delimiter();
    ///Store default path into private variables from config file
    void getDefaultPaths();
    ///Run restoring procedure
    void callRestore();
    ///Run looking for files
    void callFindFile();
    ///Run looking for folders
    void callFindFolder();
    ///Run comparing of files on disk and in the backup
    void callCompare();
    ///Generates empty configuration file
    void callConfig();
    ///Run backup
    void callBackup();
    ///Decide if current day is on the list in the config file
    /**
     * 
     * @return true if the day is in the config file
     * @return false if the day is not in the config file
     */
    bool dayOfWeek();
    ///Get current day of the week
    /**
     * 
     * @return number of day [0-6]
     */
    int getDay();
    ///Convert string representation of day into integer representation
    int convertDay(const std::string & day) const;
    ///Check if file exists
    /**
     * 
     * @param path path to file that will be checked
     */
    bool fileExists(std::string path);
    //Check if folder exists
    /**
     * 
     * @param path path to folder that will be checked
     */
    bool folderExists(std::string path);
    ///Get absolute path to folder from which program runs
    std::string getPathToOut();
    ///Path to folder which is being backed up
    std::string folderToBackupPath;
    ///Path to folder where backup is stored
    std::string destinationPath;
    ///Path to the backup file
    std::string backupFilePath;
    ///Path to folder where items should be restored
    std::string restorePath;
};

#endif	/* INTERFACE_H */

