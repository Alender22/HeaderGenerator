#include <iostream>
#include "headerTools.h"
#include "terminalTools.h"
#include "cppFormatTools.h"

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

    string headerStr = header.makeHeader();

    cout << headerStr;

    formatCPPFile(filename, args[2], headerStr);

    return 0;
}
