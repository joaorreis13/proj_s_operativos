#ifndef _FINDPATTERN_H_
#define _FINDPATTERN_H_

#include <string>
#include <vector>

/**
 * Converts a file to a vector of string, each string is a line of the file
 * @param fileName
 *              Name of the file to convert
 * @return Vector of lines of the file
 */
std::vector<std::string> readFile(std::string fileName);

//NOTE: THIS FUNCTION IS TO BE CALLED IF -c OPTION IS SENT
/**
 * Loops through the file lines and counts how many of the lines
 * have the pattern wanted
 * @param fileLines
 *              Vector with strings, each string correspond to a line of the file
 * @param pattern
 *              Pattern that is to find in the file
 * @return Number of lines with pattern in the file
 */
//int numberOfLinesWithPattern(const std::vector<std::string> &fileLines, std::string pattern);

//NOTE: THIS FUNCITON IS TO BE CALLED IF -l OPTION IS SENT
/**
 * Searches in all the files of a given directory for pattern
 * @param pattern
 *              String to look after
 * @return Vector with the names of the files with pattern
 */
std::vector<std::string> nameOfFilesWithPattern(std::string pattern);

/**
 * Searches in the file for a pattern
 * @param fileDir
 *              String with directory
 * @param pattern
 *              Pattern that is beeing looked for
 * @param i
 *              If option -i is activated (ignore capital letters)
 * @param n
 *              If option -n is activated (displays the number of the line before the line itself)
 * @return Vector of strings with the results
 */
std::vector<std::string> nameOfFilesWithPattern(std::string fileDir, std::string pattern, bool n);

void printLines(const std::vector<std::string> &lines);

//(PATH -r ou -l/SEM PATH) NUMERO DA LINHA
#endif /* _FINDPATTERN_H_ */