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

            cout << cur.content << " ";
        }
        cout << "\n";
    }
}
