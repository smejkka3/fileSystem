
#include "Interface.h"

using namespace std;

Interface::Interface(int argc, char** argv) {
    this->argc = argc;
    this->argv = argv;
}

void Interface::decide() {
    if (argc == 1) {
        getDefaultPaths();
        if (dayOfWeek()) {
            callBackup();
        }
        cout << endl << "For list of functions use option -help" << endl;
    }

    if (argc > 1) {
        if (strcmp("-help", argv[1]) == 0) {
            callHelp();
            return;
        }
        if (strcmp("-config", argv[1]) == 0) {
            callConfig();
            return;
        }
        if (strcmp("-restore", argv[1]) == 0) {
            callRestore();
            return;
        }
        if (strcmp("-findFile", argv[1]) == 0) {
            callFindFile();
            return;
        }
        if (strcmp("-findFolder", argv[1]) == 0) {
            callFindFolder();
            return;
        }
        if (strcmp("-compare", argv[1]) == 0) {
            callCompare();
            return;
        }

        if (argc != 3) {
            throw InterfaceException("Wrong number of arguments");
        }

        folderToBackupPath = argv[1];
        destinationPath = argv[2];
        callBackup();

    }


}

void Interface::callBackup() {
    if (!(folderExists(folderToBackupPath))) {
        throw InterfaceException("Wrong path to folder to be backed up");
    }
    if (!(folderExists(destinationPath))) {
        throw InterfaceException("Wrong path to folder where backup should be stored");
    }
    Backuper f(folderToBackupPath, destinationPath);
    f.backup();
    cout << "Folder was successfully backed up to " << destinationPath << endl;
}

void Interface::callCompare() {
    string comparedFile;
    if (argc == 3) {
        getDefaultPaths();
        comparedFile = argv[2];
    } else {
        if (argc != 5) {
            throw InterfaceException("Wrong number of arguments");
        }
        backupFilePath = argv[2];
        folderToBackupPath = argv[3];
        comparedFile = argv[4];
    }
    if (!(fileExists(backupFilePath))) {
        throw InterfaceException("Wrong path to backup file");
    }
    if (!(folderExists(folderToBackupPath))) {
        throw InterfaceException("Wrong path to folder from which backup is created");
    }

    Comparator c(backupFilePath, folderToBackupPath, comparedFile);
    int number = c.findFile();

    switch (number) {
        case 0: cout << "File is not in the backup" << endl;
            break;
        case 1: cout << "File in the backup is the same as the file on disk" << endl;
            break;
        case 2: cout << "File in the backup is different from the file on disk" << endl;
            break;
        case 3: cout << "File was not found on the disk" << endl;
            break;
    }

}

void Interface::callFindFolder() {
    string searchedFolder;
    if (argc == 3) {
        getDefaultPaths();
        searchedFolder = argv[2];
    } else {
        if (argc != 5) {
            throw InterfaceException("Wrong number of arguments");
        }
        backupFilePath = argv[2];
        restorePath = argv[3];
        searchedFolder = argv[4];
    }
    if (!(fileExists(backupFilePath))) {
        throw InterfaceException("Wrong path to backup file");
    }
    if (!(folderExists(restorePath))) {
        throw InterfaceException("Wrong path to restore folder");
    }

    FolderFinder f(backupFilePath, searchedFolder, restorePath);
    int number = f.findAndRestore();
    cout << number << " folders restored to " << restorePath << endl;
}

void Interface::callFindFile() {
    string searchedFile;
    if (argc == 3) {
        getDefaultPaths();
        searchedFile = argv[2];
    } else {
        if (argc != 5) {
            throw InterfaceException("Wrong number of arguments");
        }
        backupFilePath = argv[2];
        restorePath = argv[3];
        searchedFile = argv[4];
    }
    if (!(fileExists(backupFilePath))) {
        throw InterfaceException("Wrong path to backup file");
    }
    if (!(folderExists(restorePath))) {
        throw InterfaceException("Wrong path to restore folder");
    }
    FileFinder f(backupFilePath, searchedFile, restorePath);
    int number = f.findAndRestore();
    cout << number << " files restored to " << restorePath << endl;
}

void Interface::callRestore() {
    if (argc == 2) {
        getDefaultPaths();
    } else {
        if (argc != 4) {
            throw InterfaceException("Wrong number of arguments");
        }
        backupFilePath = argv[2];
        restorePath = argv[3];
    }
    if (!(fileExists(backupFilePath))) {
        throw InterfaceException("Wrong path to backup file");
    }
    if (!(folderExists(restorePath))) {
        throw InterfaceException("Wrong path to restore folder");
    }
    Restorer r(backupFilePath, restorePath);
    r.restore();
    cout << "Archive was successfully restored to " << restorePath << endl;
}

void Interface::callHelp() {
    cout << "The program offers these functions: " << endl;
    delimiter();
    cout << argv[0] << " -config" << endl <<
            "option -config creates empty configuration file" << endl;
    delimiter();
    cout <<  argv[0] << "  [Path to folder to be backed up] [Path to folder where output will be stored] \n" <<
            "Running program without no options creates backup of default folder or specific folder if arguments are supplied" << endl;
    delimiter();
    cout << argv[0] << " -restore [Path to the backup file] [Path to folder where archive will be restored] \n" <<
            "option -restore restores all files from the backup. If no arguments are supplied default parameters will be used" << endl;
    delimiter();
    cout << argv[0] << " -findFile [Path to the backup file] [Path to folder where found files will be restored] [Searched file] \n" <<
            "option -findFile looks for specific file in the backup. If more files are found all are restored. If first two arguments are missing, default parameters will be used. Third argument must be used." << endl;
    delimiter();
    cout << argv[0] << " -findFolder [Path to the backup file] [Path to folder where found folders will be restored] [Searched folder] \n" <<
            "option -findFolder looks for specific folder in the backup. If more folders are found all are restored. If first two arguments are missing, default parameters will be used. Third argument must be used." << endl;
    delimiter();
    cout << argv[0] << " -compare [Path to the backup file] [Path to folder from which is the backup file created] [Relative path to file that should be compared]\n" <<
            "option -compare Checks if file in the backup is different from the file on disk. If first two arguments are missing, default parameters will be used. Third argument must be used.\n" <<
            "For example: \"backup - compare /users/ubuntu/dest/backup.bup /users/ubuntu/folder directory/file1\" compares /users/ubuntu/folder/directory/file1 to the file in the backup" << endl;
}

void Interface::delimiter() {
    cout << "----------------------------------------" << endl;
}



void Interface::getDefaultPaths() {
    string absolutePath = getPathToOut();
    absolutePath += "Config.txt";
    ifstream in(absolutePath.c_str(), ios::in);
    if (in.fail()) {
        cout <<  "For list of functions use option -help" << endl << endl;
        throw (InterfaceException("Config file not found"));
    }
    string line;
    while (getline(in, line)) {
        string text;
        replace(line.begin(), line.end(), '=', ' ');

        stringstream s;
        s << line;
        s >> text;

        if (line == "") {
            continue;
        }
        if (text == "FOLDER_TO_BACKUP") {
            s >> folderToBackupPath;
            continue;
        }
        if (text == "WHERE_TO_BACKUP") {
            s >> destinationPath;
            continue;
        }
        if (text == "DEFAULT_BACKUP_FILE") {
            s >> backupFilePath;
            continue;
        }
        if (text == "WHERE_TO_RESTORE") {
            s >> restorePath;
            continue;
        }
        if (text == "DAYS") {
            continue;
        }
        in.close();
        throw (InterfaceException("Corrupted config file"));
    }
    in.close();
}

bool Interface::dayOfWeek() {
    string absolutePath = getPathToOut();
    absolutePath += "Config.txt";
    ifstream in(absolutePath.c_str(), ios::in);
    if (in.fail()) {
        throw (InterfaceException("Config file not found"));
    }
    string line;
    bool flag = true;
    while (getline(in, line)) {
        string text;
        replace(line.begin(), line.end(), '=', ' ');

        stringstream s;
        s << line;
        s >> text;

        if (line == "" || text != "DAYS") {
            continue;
        }
        if (text == "DAYS") {
            int day = getDay();
            while (s >> text) {
                if (day == convertDay(text)) {
                    in.close();
                    return true;
                }
            }
            flag = false;
            break;
        }

    }
    if (flag) {
        in.close();
        throw (InterfaceException("Corrupted config file"));
    }
    in.close();
    return false;
}

int Interface::getDay() {
    struct timeval miliseconds;
    struct tm* timeStructure;
    gettimeofday(&miliseconds, NULL);
    timeStructure = localtime(&miliseconds.tv_sec);
    return timeStructure->tm_wday;
}

bool Interface::folderExists(string path) {
    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
        return S_ISDIR(st.st_mode);
    } else {
        return false;
    }
}

bool Interface::fileExists(std::string path) {
    ifstream test(path.c_str());
    if (test.good()) {
        test.close();
        return true;
    }
    return false;
}

string Interface::getPathToOut() {
    string pathToFile = argv[0];
    int size = pathToFile.size();
    int i = 0;
    while (pathToFile[size - i - 1] != '/') {
        i++;
    }
    return pathToFile.substr(0, size - i);
}

int Interface::convertDay(const string & path) const {
    if (path == "Mon" || path == "mon" || path == "monday" || path == "Monday") {
        return 1;
    }
    if (path == "Tue" || path == "tue" || path == "tuesday" || path == "Tuesday") {
        return 2;
    }
    if (path == "Wen" || path == "wen" || path == "wednesday" || path == "Wednesday") {
        return 3;
    }
    if (path == "Thu" || path == "thu" || path == "thursday" || path == "Thursday") {
        return 4;
    }
    if (path == "Fri" || path == "fri" || path == "friday" || path == "Friday") {
        return 5;
    }
    if (path == "Sat" || path == "sat" || path == "saturday" || path == "Saturday") {
        return 6;
    }
    if (path == "Sun" || path == "sun" || path == "sunday" || path == "Sunday") {
        return 0;
    }
    return 8;
}

void Interface::callConfig() {
    string path=getPathToOut();
    path+="Config.txt";
    ofstream config(path.c_str(),ios::out);
    config << "FOLDER_TO_BACKUP = \nWHERE_TO_BACKUP = \nDEFAULT_BACKUP_FILE = \nWHERE_TO_RESTORE = \n" <<
            "DAYS = " << endl;
    config.close();
    cout << "Configuration file successfully created" << endl;
}
