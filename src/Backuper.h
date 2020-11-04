
#ifndef BACKUPER_H
#define	BACKUPER_H

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

///Handles creating backup files and adding items to backup
class Backuper {
public:
    Backuper(std::string sourcePath,std::string destinationPath);
    ~Backuper();
    void backup();
private:
    ///Path to the folder to be backed up
    std::string sourcePath;
    ///Path to the folder where backup will be stored
    std::string destinationPath;
    ///Full path (with backup file name) to the backup file
    std::string outputPath;
    ///Get full path (with backup file name) to the backup file
    std::string getOutputPath() const;
    ///Check if file exists
    bool fileExists() const;
    ///Get the current time
    /**
     * 
     * @return Current time in milliseconds
     */
    int getTime() const;
    ///Write information about time of backup into the backup file
    void writeTimeOfChange(std::fstream & output);
    ///Get name of the backup from the full path to the folder
    std::string getName() const;
};

#endif	/* BACKUPER_H */

