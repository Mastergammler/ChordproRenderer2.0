#pragma once

#include "types.h"

static map<int, string> KeyMap;

const char SHARP = '#';
const char FLAT = 'b';

const int KEY_MAX_COUNT = 12;

void Globals_Init()
{
    KeyMap[0] = "C";
    KeyMap[2] = "D";
    KeyMap[4] = "E";
    KeyMap[5] = "F";
    KeyMap[7] = "G";
    KeyMap[9] = "A";
    KeyMap[11] = "B";
}
