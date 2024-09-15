#include "types.h"

void Debug_PrintMetadata(ChordproContent content)
{
    for (int i = 0; i < content.metadata.size(); i++)
        cout << content.metadata[i].key << " :: " << content.metadata[i].value
             << "\n";
}

void Debug_PrintText(ChordproContent content)
{
    for (int i = 0; i < content.chord_lines.size(); i++)
    {
        ChordproLine line = content.chord_lines[i];
        for (int i = 0; i < line.elements.size(); i++)
        {
            LineElement cur = line.elements[i];
            if (cur.is_chord) continue;

            cout << cur.content;
        }
        cout << "\n";
    }
}

void Debug_PrintChords(ChordproContent content)
{
    for (int i = 0; i < content.chord_lines.size(); i++)
    {
        ChordproLine line = content.chord_lines[i];
        for (int i = 0; i < line.elements.size(); i++)
        {
            LineElement cur = line.elements[i];
            if (!cur.is_chord) continue;

            cout << cur.content;
            if (cur.main_chord.number > -1)
            {
                cout << "(" << cur.main_chord.number;
            }
            if (cur.alternate_bass.number > -1)
            {
                cout << "/" << cur.alternate_bass.number;
            }
            if (cur.main_chord.number > -1)
            {
                cout << ")";
            }
            cout << " ";
        }
        cout << "\n";
    }
}

bool compareByLineNo(const ChordproLine a, const ChordproLine b)
{
    return a.line_number < b.line_number;
}

void Debug_PrintSheet(ChordproContent content)
{
    vector<ChordproLine> allLines;

    for (ChordproLine line : content.kvp_lines)
        allLines.push_back(line);
    for (ChordproLine line : content.chord_lines)
        allLines.push_back(line);

    sort(allLines.begin(), allLines.end(), compareByLineNo);

    for (ChordproLine line : allLines)
    {
        string content;
        if (line.elements.size() > 0)
        {
            for (auto ele : line.elements)
            {
                if (ele.is_chord)
                {
                    content.append("[");
                    content.append(ele.content);
                    content.append("]");
                }
                else
                {
                    content.append(ele.content);
                }
            }
        }
        else
        {
            content = line.content;
        }

        if (line.is_instruction)
        {
            cout << "\n";
        }
        cout << /*line.line_number << " | " << */ content << "\n";
    }
}
