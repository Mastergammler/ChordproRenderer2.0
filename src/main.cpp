#include "debug.cpp"
#include "file.cpp"
#include "parser.cpp"
#include "types.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    cout << "Chordpro Renderer 2.0\n\n";

    // arg 0 is always the relative program path
    if (argc > 1)
    {
        cout << argv[1] << "\n";

        ChordproContent chordpro = {};
        read_file(&chordpro, argv[1]);
        parse_chordpro(&chordpro);

        Debug_PrintChords(chordpro);
    }

    cout << endl;

    return 0;
}
