#pragma once

#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <vector>

using std::cerr;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::map;
using std::string;
using std::vector;

struct Pair
{
    string key;
    string value;
};

const int CHORD_UNINIT = -1;

struct Chord
{
    int number;
    int char_count;
};

struct LineElement
{
    bool is_chord;
    string content;
    Chord main_chord;
    Chord alternate_bass;
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
    vector<LineElement*> all_chords;

    int total_lines;
};
