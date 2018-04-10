#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#include "macros.h"
#include "findPattern.h"

using namespace std;

vector<string> readFile(string fileName)
{
    fstream myFile;
    string line;
    myFile.open(fileName.c_str());
    if (!myFile.is_open())
    {
        cerr << "Error opening file" << endl;
        exit(1);
    }

    vector<string> file;

    while (!myFile.eof())
    {
        getline(myFile, line);
        file.push_back(line);
    }

    return file;
}

int numberOfLinesWithPattern(const vector<string> &fileLines, string pattern)
{
    int counter = 0;
    //for each line of the document
    for (unsigned int i = 0; i < fileLines.size(); i++)
    {
        //check if the line has the pattern
        if (fileLines.at(i).find(pattern) != string::npos)
            counter++;
    }
    return counter;
}

vector<string> nameOfFilesWithPattern(string pattern)
{
    //TODO
    vector<string> linesWithPattern;
    return linesWithPattern;
}

vector<string> nameOfFilesWithPattern(const vector<string> &fileLines, string pattern, bool optionI, bool optionN)
{
    vector<string> linesWithPattern;

    //for each line of the document
    for (unsigned int i = 0; i < fileLines.size(); i++)
    {
        //check if that line in particular has the pattern
        if (fileLines.at(i).find(pattern) != string::npos)
        {
            string result;
            if (optionN)
            {
                result = to_string(i+1);
                result += ": ";
                result += fileLines.at(i);
            }

            else //dont have the line
                result = fileLines.at(i);

            linesWithPattern.push_back(result);
        }
    }

    return linesWithPattern;
}