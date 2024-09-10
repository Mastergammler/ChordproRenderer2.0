#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;
using std::vector;

struct ChordproLine
{
    int line_number;
    string content;
};

struct ChordproContent
{
    vector<ChordproLine> chord_lines;
    vector<ChordproLine> kvp_lines;

    int total_lines;
};

struct Pair
{
    string key;
    string value;
};
