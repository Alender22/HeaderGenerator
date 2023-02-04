#include <iostream>
#include "headerTools.h"
#include "terminalTools.h"
#include "cppFormatTools.h"
#include "colorTools.h"
#include "timeTools.h"

using namespace std;

int doFileFormatting(int argC, char** args);

int main(int argC, char** args)
{
    return doFileFormatting(argC, args);
}

int doFileFormatting(int argC, char** args)
{
    if(argC == 1)
    {
        cout << "No arguments were passed, one was expected" << endl;
        return -1;
    }

    Header header;
    string srcFilename = args[1];
    string destFilename;

    if(argC == 2)
        destFilename = srcFilename;
    else
        destFilename = args[2];

    header.addVarToDict("FILENAME", srcFilename);

    header.readTableFromTemplate();

    header.handleFlagCommands();

    clearTerminal();

    string headerStr = header.makeHeader();

    formatCPPFile(srcFilename, destFilename, headerStr);

    return 0;
}
