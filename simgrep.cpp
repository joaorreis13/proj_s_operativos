#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "macros.h"
#include "findPattern.h"

using namespace std;

void printAnswer(vector<string> answer)
{
    for (unsigned int i = 0; i < answer.size(); i++)
    {
        cout << answer.at(i) << endl;
    }
}

bool isDirectory(string dir)
{
    struct stat path_stat;
    if (stat(dir.c_str(), &path_stat) < 0)
    {
        cerr << "File/Directory not found" << endl;
        exit(3);
    }
    if (S_ISDIR(path_stat.st_mode))
        return true;
    else if (S_ISREG(path_stat.st_mode))
        return false;

    cerr << "File/Directory not found" << endl;
    exit(4);
}

int invalidArgs()
{
    printf("simgrep: Invalid arguments!\n");
    printf("simgrep: Usage: simgrep [options] pattern [file/dir]\n");
    printf("simgrep: Valid options: -i -l -n -c -w -r\n");

    return 1;
}

bool isValidOption(char option)
{
    return option == 'i' || option == 'l' || option == 'n' ||
           option == 'c' || option == 'w' || option == 'r';
}

bool hasCharOption(vector<char> options, char option)
{
    for(unsigned int i = 0; i < options.size();i++)
    {
        if(options[i] == option)
        return true;
    }
    return false;
}

//manage options and call each function accodingly
int main(int argc, char *argv[])
{
    //variables
    //bool recursive = false; // -r
    //bool hasDir = false;    // has directory
    //bool hasFile = false;   //has a file
    vector<char> options; //options to run
    string pattern;       //pattern to look for
    string fileDir;       //directory of file

    //check if valid arguments given when calling function
    if (argc < 2 || argv[argc - 1][0] == '-')
    {
        invalidArgs();
        return 1;
    }

    int i = 1; // j = 0;
    //parsing values
    for (; i < argc; i++)
    {
        //check if its a option
        if (argv[i][0] == '-')
        {
            if (isValidOption(argv[i][1])) //valid option
            {
                options.push_back(argv[i][1]);
            }
            else //not a valid option
            {
                invalidArgs();
                return 2;
            }
        }
        else if (i == argc - 2)
        {
            pattern = argv[i];
            fileDir = argv[i + 1];
            break;
        }
        else
        {
            invalidArgs();
            exit(4);
        }
    }

    //checking if fileDir is a file
    if (isDirectory(fileDir))
    {
    }

    //call function accordingly
    vector<string> answer = nameOfFilesWithPattern(fileDir, pattern, hasCharOption(options,'i'), hasCharOption(options,'n'));

    printAnswer(answer);

    return 0;
}
