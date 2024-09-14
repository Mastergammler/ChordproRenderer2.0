#include "globals.cpp"
#include "types.h"

// PERF: this is basically O(7n) where n = number of chords
int find_chord_value(string chordString)
{
    for (const auto& pair : KeyMap)
    {
        if (chordString.find(pair.second) != string::npos)
        {
            int chordNumber = pair.first;

            if (chordString.find(SHARP) != string::npos)
            {
                chordNumber++;
            }
            else if (chordString.find(FLAT) != string::npos)
            {
                chordNumber--;
            }

            if (chordNumber > 11) chordNumber = 0;
            if (chordNumber < 0) chordNumber = 11;

            return chordNumber;
        }
    }

    return CHORD_UNINIT;
}

// NOTE: for the replace, it's always the first one or two chars
//-> so i can know this, based on what the number is

void determine_chords(ChordproContent* content)
{
    for (int i = 0; i < content->all_chords.size(); i++)
    {
        LineElement* cur = content->all_chords[i];
        string chordStr = cur->content;
        Chord chord = {};

        int idx = chordStr.find_first_of('/');
        if (idx != string::npos)
        {
            // length = idx - 0
            string firstHalf = chordStr.substr(0, idx);
            string secondHalf = chordStr.substr(idx + 1);
            chord.number = find_chord_value(firstHalf);
            chord.alternate_bass = find_chord_value(secondHalf);
        }
        else
        {
            chord.number = find_chord_value(chordStr);
            chord.alternate_bass = CHORD_UNINIT;
        }

        cur->chord = chord;
    }
}
