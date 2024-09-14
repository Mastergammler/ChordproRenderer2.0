#include "globals.cpp"
#include "types.h"

// PERF: this is basically O(7n) where n = number of chords
Chord find_chord_value(string chordString)
{
    Chord chord = {};
    chord.number = CHORD_UNINIT;

    for (const auto& pair : KeyMap)
    {
        if (chordString.find(pair.second) != string::npos)
        {
            chord.number = pair.first;
            chord.char_count = 1;

            if (chordString.find(SHARP) != string::npos)
            {
                chord.number++;
                chord.char_count++;
            }
            else if (chordString.find(FLAT) != string::npos)
            {
                chord.number--;
                chord.char_count++;
            }

            chord.number = chord.number % KEY_MAX_COUNT;
        }
    }

    return chord;
}

// NOTE: for the replace, it's always the first one or two chars
//-> so i can know this, based on what the number is

void determine_chords(ChordproContent* content)
{
    Chord empty = {};
    empty.number = CHORD_UNINIT;

    for (int i = 0; i < content->all_chords.size(); i++)
    {
        LineElement* cur = content->all_chords[i];
        string chordStr = cur->content;

        int idx = chordStr.find_first_of('/');
        if (idx != string::npos)
        {
            // length = idx - 0
            string firstHalf = chordStr.substr(0, idx);
            string secondHalf = chordStr.substr(idx + 1);
            cur->main_chord = find_chord_value(firstHalf);
            cur->alternate_bass = find_chord_value(secondHalf);
        }
        else
        {
            cur->main_chord = find_chord_value(chordStr);
            cur->alternate_bass = empty;
        }
    }
}

int positive_modulo(int no, int modulo)
{
    return (no % modulo + modulo) % modulo;
}

void transpose(ChordproContent* content, int semitonShift)
{
    for (int i = 0; i < content->all_chords.size(); i++)
    {
        LineElement* cur = content->all_chords[i];
        if (cur->main_chord.number < 0) continue;

        // TODO: do some 'isPresent' or something?
        if (cur->main_chord.number > -1)
        {
            int transposedNo = positive_modulo(cur->main_chord.number + semitonShift,
                                               KEY_MAX_COUNT);
            cur->main_chord.number = transposedNo;
        }
        if (cur->alternate_bass.number > -1)
        {
            int transposedNo = positive_modulo(cur->alternate_bass.number + semitonShift,
                                               KEY_MAX_COUNT);
            cur->alternate_bass.number = transposedNo;
        }
    }

    for (int i = 0; i < content->all_chords.size(); i++)
    {
        LineElement* cur = content->all_chords[i];
        if (cur->main_chord.number < 0) continue;
        int splitIdx = cur->content.find_first_of('/');

        if (splitIdx != string::npos)
        {
            auto it = KeyMap.find(cur->alternate_bass.number);
            string alternateReplacement;
            if (it == KeyMap.end())
            {
                // TODO: handle sharp and flat differentiation
                alternateReplacement = KeyMap[cur->alternate_bass.number - 1] +
                                       SHARP;
            }
            else
            {
                alternateReplacement = it->second;
            }

            cur->content.replace(splitIdx + 1,
                                 cur->alternate_bass.char_count,
                                 alternateReplacement);
        }

        auto it = KeyMap.find(cur->main_chord.number);
        string replacement;
        if (it == KeyMap.end())
        {
            replacement = KeyMap[cur->main_chord.number - 1] + SHARP;
        }
        else
        {
            replacement = it->second;
        }

        cur->content.replace(0, cur->main_chord.char_count, replacement);
    }
}
