simgrep: simgrep.cpp findPattern.cpp searchDir.cpp
	g++ -std=c++11 -o simgrep -Wall -Wextra simgrep.cpp findPattern.cpp searchDir.cpp
