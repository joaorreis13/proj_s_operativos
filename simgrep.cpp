#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <signal.h>
#include <sys/wait.h>

#include "macros.h"
#include "findPattern.h"
#include "searchDir.h"

using namespace std;

void sigint_handler(int sig)
{
    char c;
    cout << endl
         << "Are you sure you want to termiante?" << endl;
    c = getchar();

    if (c == 'y' || c == 'Y')
    {
        cout << "Program terminated" << endl;
        exit(0);
    }
    else if (c == 'n' || c == 'N')
    {
        return;
    }
    else
    {
        cout << "Char not recognized" << endl;
        sigint_handler(SIGINT);
    }
    return;
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

//manage options and call each function accodingly
int main(int argc, char *argv[])
{
    cout << "Possible test cases:" << endl;
    cout << "simgrep -n -r pattern dir" << endl;
    cout << "simgrep -n pattern dir/file" << endl;
    cout << "simgrep -w -n pattern file" << endl;
    cout << "simgrep -w pattern file" << endl;
    cout << "[default:] simgrep pattern dir/file" << endl;

    //setting up the signal
    struct sigaction action;
    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

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
        cout << "found directory" << endl;

        int status = 0;
        int pid = fork();

        if (pid == 0)
        {
            searchDir(fileDir, options, pattern);
            exit(0);
        }
        else
        {
            wait(&status);
            exit(status);
        }
    }
    else
    {
        if (hasCharOption(options, 'w'))
        {
            FILE *fp;
            fp = fopen(fileDir.c_str(), "r");
            char **outcome = findWord_w(fp, pattern, hasCharOption(options, 'n'));

            for (int i = 0; i < sizeof(outcome) - 1; i++)
                printf("%s", outcome[i]);
        }
        else
        {
            vector<string> answer = nameOfFilesWithPattern(fileDir, pattern, hasCharOption(options, 'n'));
            printLines(answer);
        }
    }

    return 0;
}
