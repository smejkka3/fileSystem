CC=g++ -Wall -pedantic -Wno-long-long -O0 -ggdb

all: fileSystem doc

compile: fileSystem

clean:
	rm -f *.o;rm -f fileSystem;rm -rf doc;rm -f Config.txt

run:
	./fileSystem

doc:
	mkdir doc;doxygen

Backuper.o: ./src/Backuper.cpp ./src/Backuper.h ./src/FileIncrementalBackup.h ./src/FileFullBackup.h ./src/Item.h ./src/Finder.h ./src/JumpThrough.h ./src/FolderFullBackup.h ./src/Folder.h ./src/FolderIncrementalBackup.h
	$(CC) -c -o $@ $<

Comparator.o: ./src/Comparator.cpp ./src/Comparator.h ./src/JumpThrough.h ./src/Restorer.h ./src/Finder.h
	$(CC) -c -o $@ $<

FileFinder.o: ./src/FileFinder.cpp ./src/FileFinder.h ./src/Finder.h ./src/JumpThrough.h
	$(CC) -c -o $@ $<

FileFullBackup.o: ./src/FileFullBackup.cpp ./src/FileFullBackup.h ./src/Item.h
	$(CC) -c -o $@ $<

FileIncrementalBackup.o: ./src/FileIncrementalBackup.cpp ./src/FileIncrementalBackup.h ./src/FileFullBackup.h ./src/Item.h ./src/Finder.h ./src/JumpThrough.h
	$(CC) -c -o $@ $<

Finder.o: ./src/Finder.cpp ./src/Finder.h ./src/JumpThrough.h
	$(CC) -c -o $@ $<

Folder.o: ./src/Folder.cpp ./src/Folder.h ./src/Item.h
	$(CC) -c -o $@ $<

FolderFinder.o: ./src/FolderFinder.cpp ./src/FolderFinder.h ./src/Finder.h ./src/JumpThrough.h
	$(CC) -c -o $@ $<

FolderFullBackup.o: ./src/FolderFullBackup.cpp ./src/FolderFullBackup.h ./src/Folder.h ./src/Item.h ./src/FileFullBackup.h
	$(CC) -c -o $@ $<

FolderIncrementalBackup.o: ./src/FolderIncrementalBackup.cpp ./src/FolderIncrementalBackup.h ./src/Folder.h ./src/Item.h ./src/Finder.h ./src/JumpThrough.h ./src/FileIncrementalBackup.h ./src/FileFullBackup.h ./src/FolderFullBackup.h
	$(CC) -c -o $@ $<

Interface.o: ./src/Interface.cpp ./src/Interface.h ./src/Restorer.h ./src/Finder.h ./src/JumpThrough.h ./src/FileFinder.h ./src/Comparator.h ./src/Backuper.h ./src/FolderFinder.h ./src/InterfaceException.h
	$(CC) -c -o $@ $<

InterfaceException.o: ./src/InterfaceException.cpp ./src/InterfaceException.h
	$(CC) -c -o $@ $<

Item.o: ./src/Item.cpp ./src/Item.h
	$(CC) -c -o $@ $<

JumpThrough.o: ./src/JumpThrough.cpp ./src/JumpThrough.h
	$(CC) -c -o $@ $<

main.o: ./src/main.cpp ./src/Backuper.h ./src/Restorer.h ./src/Finder.h ./src/JumpThrough.h ./src/FileFinder.h ./src/FolderFinder.h ./src/Comparator.h ./src/Interface.h ./src/InterfaceException.h
	$(CC) -c -o $@ $<

Restorer.o: ./src/Restorer.cpp ./src/Restorer.h ./src/Finder.h ./src/JumpThrough.h
	$(CC) -c -o $@ $<

fileSystem: Backuper.o Comparator.o FileFinder.o FileFullBackup.o FileIncrementalBackup.o Finder.o Folder.o FolderFinder.o FolderFullBackup.o FolderIncrementalBackup.o Interface.o InterfaceException.o Item.o JumpThrough.o main.o Restorer.o
	g++ -o fileSystem Backuper.o Comparator.o FileFinder.o FileFullBackup.o FileIncrementalBackup.o Finder.o Folder.o FolderFinder.o FolderFullBackup.o FolderIncrementalBackup.o Interface.o InterfaceException.o Item.o JumpThrough.o main.o Restorer.o
