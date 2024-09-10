#include "file.cpp"
#include "parser.cpp"
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    cout << "Chordpro Renderer 2.0\n";

    // arg 0 is always the relative program path
    if (argc > 1)
    {
        cout << argv[1] << "\n";

        ChordproContent chordpro = {};
        read_file(&chordpro, argv[1]);
        parse_chordpro(chordpro);
    }

    cout << endl;

    return 0;
}
