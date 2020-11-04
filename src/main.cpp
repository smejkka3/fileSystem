

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <ctime>
#include <dirent.h>
#include "Backuper.h"
#include "Restorer.h"
#include "FileFinder.h"
#include "FolderFinder.h"
#include "Comparator.h"
#include "Interface.h"
#include "InterfaceException.h"


using namespace std;

/**
 * \mainpage Backup program
 *
 * Archiving program similar to tar.
 *
 * \section sect1 Main Description
 * This program allows you to archive selected folder into one huge binary file
 * with .bup extension. Backup created with this program is always incremental thus it doesn't use 
 * excessive amount of space on the disk. User can restore everything, single file or folder from the backup.
 *
 */

int main(int argc, char** argv) {
    /*Backuper f("/home/ubuntu/Desktop/test","/home/ubuntu/Desktop/dest");
    f.backup();
    Restorer r("/home/ubuntu/Desktop/dest/test.bup","/home/ubuntu/Desktop/restore");
    r.restore();*/
   /* FileFinder ff("/home/ubuntu/Desktop/dest/test.bup","file.txt","/home/ubuntu/Desktop/restore");
    ff.findAndRestore();*/
    /*Comparator c("/home/ubuntu/Desktop/dest/test.bup","/home/ubuntu/Desktop/test","folder/f.txt");
    cout << c.findFile();*/

   
   try {
        Interface i(argc, argv);
        i.decide();
    } catch ( InterfaceException & e) {
        cout << e << endl;
    }

    

    return 0;
}

