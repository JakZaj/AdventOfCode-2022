#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define at_most_total_size 100000
#define total_disk_space 70000000
#define needed_unused_space 30000000

class File {
public:
    string name;
    int size;
    File(string n, int s) {
        name = n;
        size = s;
    }
    ~File() {
    }
};

class Directory {
public:
    string name;
    int totalSize;
    Directory* outermostDir;
    Directory* parrentDir;
    vector<Directory*> childrenDir;
    vector<File*> file;

    Directory(string n) {
        name = n;
        totalSize = 0;
        parrentDir = nullptr;
        outermostDir = this;
    }

    Directory(string n, Directory& parrent, Directory& out) {
        name = n;
        totalSize = 0;
        parrentDir = &parrent;
        outermostDir = &out;
    }
    ~Directory() {
        for (size_t i = 0; i < file.size(); i++)
        {
            delete file.at(i);
        }
        file.clear();

        for (size_t i = 0; i < childrenDir.size(); i++)
        {
            delete childrenDir.at(i);
        }
        childrenDir.clear();
    }

    int calculateTotalSize() {
        for (size_t i = 0; i < file.size(); i++)
        {
            totalSize += file.at(i)->size;
        }
        for (size_t i = 0; i < childrenDir.size(); i++)
        {
            totalSize += childrenDir.at(i)->calculateTotalSize();
        }
        return totalSize;
    }

    int calculateSumTotalSizes(int atMost) {
        int result = 0;
        if (totalSize < atMost)
            result = totalSize;
        for (size_t i = 0; i < childrenDir.size(); i++)
        {
            result += childrenDir.at(i)->calculateSumTotalSizes(atMost);
        }
        return result;
    }
    int findDirectoryToDeleted(int atLeast) {
        int smalestFound = totalSize;
        
        int tmpToCheck = 0;
        for (size_t i = 0; i < childrenDir.size(); i++)
        {
            tmpToCheck = childrenDir.at(i)->findDirectoryToDeleted(atLeast);
            if (smalestFound < atLeast) {
                smalestFound = tmpToCheck;
                continue;
            }
            if (tmpToCheck >= atLeast && tmpToCheck < smalestFound)
                smalestFound = tmpToCheck;
        }
        return smalestFound;
    }

    Directory* addChildrenDir(Directory* d) {
        d->parrentDir = this;
        d->outermostDir = outermostDir;
        childrenDir.push_back(d);
        return d;
    }

    Directory* getDirectory(string n) {
        if(n == "/") {
            return outermostDir;
        }
        if (n == "..") {
            return parrentDir;
        }

        for (size_t i = 0; i < childrenDir.size(); i++){
            if (n == childrenDir.at(i)->name)
                return childrenDir.at(i);
        }
        return nullptr;
    }

    Directory* doOperationCD(string n) {
        
        Directory* ptrDirectoryTmp = this->getDirectory(n);

        if (ptrDirectoryTmp == nullptr) {
            return this;
        }
        
        return ptrDirectoryTmp;
    }

    void addFile(File* f) {
        file.push_back(f);
    }
    
};

size_t splitString(const string& txt, vector<string>& strs, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    while (pos != string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    strs.push_back(txt.substr(initialPos, min(pos, txt.size()) - initialPos + 1));

    return strs.size();
}


int main()
{
    ifstream myfile("input.txt");
    
    string line;
    vector<string> lineSplit;
    Directory* ptrDirectory = nullptr;

    if (myfile.is_open())
    {
        while (getline(myfile, line)) {
            splitString(line, lineSplit, ' ');

            if (lineSplit.at(1) == "ls") {
                while (getline(myfile, line)) {
                    if (splitString(line, lineSplit, ' ') == 3) {
                        break;
                    }

                    if (lineSplit.at(0) == "dir") 
                        ptrDirectory->addChildrenDir(new Directory(lineSplit.at(1)));
                    else
                        ptrDirectory->addFile(new File(lineSplit.at(1), stoi(lineSplit.at(0))));

                } 
            }
            if (lineSplit.at(1) == "cd")
            {
                if (ptrDirectory == nullptr) 
                    ptrDirectory = new Directory(lineSplit.at(2));
                else
                    ptrDirectory = ptrDirectory->doOperationCD(lineSplit.at(2));
                
            }
        }
        if (ptrDirectory != nullptr) {
            ptrDirectory = ptrDirectory->outermostDir;
            ptrDirectory->calculateTotalSize();
            cout << "Sum of the total sizes " << ptrDirectory->calculateSumTotalSizes(at_most_total_size)<< "\n";
            cout << "Smallest directory to deleted " << ptrDirectory->findDirectoryToDeleted(needed_unused_space - (total_disk_space - ptrDirectory->outermostDir->totalSize) ) << "\n";
        }

        myfile.close();
        myfile.clear();
    }

    else cout << "Unable to open file";

    lineSplit.clear();
    delete ptrDirectory;

    return 0;
}

