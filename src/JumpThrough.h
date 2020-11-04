/* 
 * File:   JumpThrough.h
 * Author: ubuntu
 *
 * Created on May 5, 2013, 10:57 PM
 */

#ifndef JUMPTHROUGH_H
#define	JUMPTHROUGH_H


#include <fstream>
#include <string.h>

///Interface with methods for jumping through files when the information in them are not needed
class JumpThrough {
protected:
    ///Jump through the file. Used when we only want to get information about folders.
    void jumpThroughFile(unsigned long int & position,std::fstream & file);
    ///Jump through the folder. Used when we only want to get information about files.
    void jumpThroughFolder(unsigned long int& position,std::fstream & file);
    ///Jump through the rest of the file
    /**
     * Used when folder has incremental backup ('T' on the second position of file header)
     * so the program doesn't need to read the old file
     **/
    void jumpThroughTheRest(unsigned long int & position,std::fstream & file);
    
};

#endif	/* JUMPTHROUGH_H */

