#include "types.h"

/**
 * This is an array of char* -> so basically char**
 * but since it's static i have to define it like this
 */
static const char* KEYWORDS[] = {"comment", "chorus"};

bool is_keyword(string word)
{
    int arrayElements = sizeof(KEYWORDS) / sizeof(char*);
    for (int i = 0; i < arrayElements; i++)
    {
        // using word == KEYWORD[i] would create a new temporary string object
        if (word.compare(KEYWORDS[i]) == 0) return true;
    }

    return false;
}

const char CHORD_OPEN = '[';
const char CHORD_CLOSE = ']';

void parse_chord_line(ChordproLine* line)
{
    int lastIdx = 0;
    LineElement ele = {};

    for (int i = 0; i < line->content.length(); i++)
    {
        char cur = line->content[i];

        if (cur == CHORD_OPEN)
        {
            int length = i - lastIdx;
            if (length > 0)
            {
                ele.content = line->content.substr(lastIdx, length);
                line->elements.push_back(ele);
                LineElement newEle = {};
                ele = newEle;
            }

            lastIdx = i + 1;
            ele.is_chord = true;
        }
        else if (cur == CHORD_CLOSE)
        {
            int length = i - lastIdx;
            ele.content = line->content.substr(lastIdx, length);
            line->elements.push_back(ele);

            LineElement next = {};
            ele = next;
            lastIdx = i + 1;
        }
    }

    // close up end, if there is a space between lastIdx and length
    // remember that lastIdx is set to i+1 at the end of the iteration
    // therefore it is equal to the length
    if (lastIdx < line->content.length())
    {
        int length = line->content.length() - lastIdx;
        ele.content = line->content.substr(lastIdx, length);
        line->elements.push_back(ele);
    }
}

void parse_chordpro(ChordproContent* content)
{
    for (int i = 0; i < content->kvp_lines.size(); i++)
    {
        string line = content->kvp_lines[i].content;

        int startIdx = line.find_first_of('{');
        int endIdx = line.find_first_of('}');
        int sep = line.find_first_of(':');

        int keyLength = sep - (startIdx + 1);
        int valueLength = endIdx - (sep + 1);

        string key = line.substr(startIdx + 1, keyLength);
        string value = line.substr(sep + 1, valueLength);

        Pair p = {key, value};

        if (is_keyword(p.key))
        {
            // TODO: this should retain line information?!
            content->instruction_lines.push_back(p);
        }
        else
        {
            content->metadata.push_back(p);
        }
    }

    // parsing chord lines
    for (int i = 0; i < content->chord_lines.size(); i++)
    {
        ChordproLine* line = &content->chord_lines[i];
        parse_chord_line(line);

        // accumulate for easy access
        for (int i = 0; i < line->elements.size(); i++)
        {
            LineElement* ele = &line->elements[i];
            if (ele->is_chord) content->all_chords.push_back(ele);
        }
    }
}
