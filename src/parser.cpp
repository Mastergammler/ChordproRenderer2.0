#include "types.h"

void parse_chordpro(ChordproContent content)
{
    vector<Pair> pairs;
    for (int i = 0; i < content.kvp_lines.size(); i++)
    {
        string line = content.kvp_lines[i].content;

        int startIdx = line.find_first_of('{');
        int endIdx = line.find_first_of('}');
        int sep = line.find_first_of(':');

        int keyLength = sep - (startIdx + 1);
        int valueLength = endIdx - (sep + 1);

        string key = line.substr(startIdx + 1, keyLength);
        string value = line.substr(sep + 1, valueLength);

        Pair p = {key, value};
        pairs.push_back(p);
    }

    for (int i = 0; i < pairs.size(); i++)
        cout << pairs[i].key << " :: " << pairs[i].value << "\n";
}
