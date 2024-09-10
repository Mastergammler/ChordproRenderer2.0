#include "types.h"

void read_file(ChordproContent* content, const char* path)
{
    ifstream file(path);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << path << endl;
    }

    string line;
    int lineNo = 1;
    while (getline(file, line))
    {
        bool isKvpLine = line[0] == '{';
        bool isChordLine = line.find_first_of('[') != string::npos &&
                           line.find_first_of(']') != string::npos;

        ChordproLine cpl = {};
        cpl.line_number = lineNo;
        cpl.content = line;

        if (isKvpLine)
            content->kvp_lines.push_back(cpl);
        else if (isChordLine)
            content->chord_lines.push_back(cpl);
        else
        {
            // do nothing, because irrelevant text or empty line
        }

        lineNo++;
    }

    content->total_lines = content->chord_lines.size() +
                           content->kvp_lines.size();

    cout << "File has " << content->total_lines << " lines";
}
