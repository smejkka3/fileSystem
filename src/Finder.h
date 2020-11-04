
#ifndef FINDER_H
#define	FINDER_H

#include <fstream>
#include <string.h>
#include "JumpThrough.h"

///Parent class for classes which search and restore files
class Finder : public JumpThrough {
public:
    Finder();
protected:
   std::fstream input;
   ///Restore one file from the backup
   /**
    * 
    * @param path Where the file will be stored
    * @param size Size of the restored file
    */
   void writeFile(const std::string & path,unsigned long int size);
   ///Get name of the file or folder from the full path
   std::string extractName(const std::string & path); 
   const static unsigned long int BUFFER_SIZE=500000000;
};

#endif	/* FINDER_H */

