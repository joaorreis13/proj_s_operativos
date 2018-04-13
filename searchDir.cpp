#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/wait.h>
#include "searchDir.h"
#include "findPattern.h"

using namespace std;

bool hasCharOption(vector<char> options, char option)
{
    for (unsigned int i = 0; i < options.size(); i++)
    {
        if (options[i] == option)
            return true;
    }
    return false;
}

void searchDir(string dir, vector<char> options, string pattern)
{
    //cout << "teste   " << endl;
    DIR *dirp;
    struct dirent *dp;
    struct stat stat_buff;
    string name;

    dirp = opendir(dir.c_str());
    if (dirp == NULL)
    {
        cout << ">> Error in dirp " << endl;
        exit(6);
    }

    while ((dp = readdir(dirp)) != NULL) // loop directory
    {
        name = dir + "/" + dp->d_name;

        if (dp->d_name[0] == '.')
            continue;

        if (lstat(name.c_str(), &stat_buff) == -1) //gather info
        {
            cerr << "lstat error" << endl;
            exit(4);
        }

        //check if its a file or a folder
        if (S_ISREG(stat_buff.st_mode)) //its a file
        {
            std::vector<std::string> lines = nameOfFilesWithPattern(name, pattern, hasCharOption(options, 'n'));
            printLines(lines);
        }
        else if (S_ISDIR(stat_buff.st_mode))
        {
            if (hasCharOption(options, 'r'))
            {
                int pid = fork();

                if (pid == 0)
                {
                    searchDir(name, options, pattern);
                    exit(0);
                }
                //cout << "found a folder" << endl;
            }
            else
            {
                cerr << name << "is a folder" << endl;
                exit(6);
            }
        }
    }

    closedir(dirp);
    int status;

    while (wait(&status) > 0)
    {
    }

    //wait(NULL);
}