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

struct Pair
{
    string key;
    string value;
};

struct LineElement
{
    bool is_chord;
    string content;
};

// TODO: it seems like the concept of metadat lines etc diverges a bit
//  this is not quite the same
struct ChordproLine
{
    int line_number;
    string content;
    vector<LineElement> elements;
};

struct ChordproContent
{
    vector<Pair> metadata;
    vector<Pair> instruction_lines;
    vector<ChordproLine> chord_lines;
    vector<ChordproLine> kvp_lines;

    int total_lines;
};

enum Key
{
    C,
    CS,
    D,
    DS,
    E,
    F,
    FS,
    G,
    GS,
    A,
    AS,
    B
};
