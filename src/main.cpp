#include "debug.cpp"
#include "file.cpp"
#include "globals.cpp"
#include "parser.cpp"
#include "transposer.cpp"
#include "types.h"

using std::cout;
using std::endl;

int parse_transpose_count(const char* arg)
{
    const char* prefix = "-t";
    if (strncmp(arg, prefix, strlen(prefix)) == 0)
    {
        const char* numberStart = arg + strlen(prefix);
        return atoi(numberStart) % KEY_MAX_COUNT;
    }
    return 0;
}

int main(int argc, char* argv[])
{
    cout << "Chordpro Renderer 2.0\n\n";

    Globals_Init();

    // arg 0 is always the relative program path
    if (argc > 1)
    {
        cout << argv[1] << "\n";

        ChordproContent chordpro = {};
        read_file(&chordpro, argv[1]);
        parse_chordpro(&chordpro);
        determine_chords(&chordpro);

        if (argc > 2)
        {
            int transposeBy = parse_transpose_count(argv[2]);
            transpose(&chordpro, transposeBy);
        }

        Debug_PrintChords(chordpro);
    }

    cout << endl;

    return 0;
}
