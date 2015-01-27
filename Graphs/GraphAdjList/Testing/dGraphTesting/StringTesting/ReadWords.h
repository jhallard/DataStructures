#ifndef READWORDS_H
#define READWORDS_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::string> readFile() {

    std::vector<std::string> file;
    std::string line;
    file.reserve(10500);
    std::ifstream infile("Testing/dGraphTesting/StringTesting/words.txt", std::ios_base::in);
    while (getline(infile, line, '\n'))
    {
        file.push_back (line);
    }

    return file;
}

#endif