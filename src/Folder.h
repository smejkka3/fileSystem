
#ifndef FOLDER_H
#define	FOLDER_H

#include "Item.h"

///Abstract class for full and incremental folder backup
class Folder : public Item {
public:
    Folder(fstream& output, const string& inputPath,const string & relativePath);
protected:
    ///Check if the item is folder of file
    bool isFolder(string path) const;
 };

#endif	/* FOLDER_H */

