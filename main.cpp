#include <iostream>
#include "headerTools.h"
#include "terminalTools.h"
#include "cppFormatTools.h"

using namespace std;

int main(int argC, char** args)
{
    Header header;
    string srcFilename, destFilename;

    if(argC == 1)
    {
        cout << "No arguments were passed, one was expected" << endl;
        return -1;
    }

    srcFilename = args[1];

    if(argC == 2)
        destFilename = srcFilename;
    else
        destFilename = args[2];

    header.addVarToDict("FILENAME", srcFilename);

    header.readTableFromTemplate();

    header.handleFlagCommands();

    clearTerminal();

    string headerStr = header.makeHeader();

    cout << headerStr;

    formatCPPFile(srcFilename, destFilename, headerStr);

    return 0;
}
