#include <iostream>
#include "headerTools.h"
#include "terminalTools.h"

using namespace std;

int main(int argC, char** args)
{
    if(argC == 1)
    {
        cout << "No arguments were passed, one was expected" << endl;
        return -1;
    }

    Header header;
    string filename = args[1];

    header.addVarToDict("FILENAME", filename);

    header.readTableFromTemplate();

    header.handleFlagCommands();

    clearTerminal();

    cout << header.makeHeader();

    return 0;
}
