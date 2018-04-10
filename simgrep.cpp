#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "macros.h"
#include "findPattern.h"

using namespace std;

int invalidArgs()
{
    printf("simgrep: Invalid arguments!\n");
    printf("simgrep: Usage: simgrep [options] pattern [file/dir]\n");
    printf("simgrep: Valid options: -i -l -n -c -w -r\n");

    return 1;
}

//manage options and call each function accodingly
int main(int argc, char *argv[])
{
    //check if valid arguments given when calling function
    if (argc < 2 || argv[argc - 1][0] == '-')
        return invalidArgs();
/*
    //variables
    bool recursive = false; // -r
    bool hasDir = false;    // has directory
    bool hasFile = false;   //has a file
    vector<char> options;   //options to run
    string pattern;         //pattern to look for
*/

    //read file wanted
    vector<string> file = readFile("test");

    //call function accordingly
    vector<string> answer = nameOfFilesWithPattern(file,"teste",true,true);

    for(unsigned int i = 0 ; i < answer.size();i++)
    {
        cout << answer.at(i) << endl;
    }

    return 0;  
}
