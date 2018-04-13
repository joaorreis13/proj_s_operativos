#ifndef _SEARCHDIR_H_
#define _SEARCHDIR_H_

#include <vector>
#include <string>

void searchDir(std::string dir, std::vector<char> options, std::string pattern);

bool hasCharOption(std::vector<char> options, char option);


#endif /* _SEARCHDIR_H_ */