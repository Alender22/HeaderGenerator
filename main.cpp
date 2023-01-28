#include <iostream>
#include "headerTools.h"
#include "terminalTools.h"
#include "cppFormatTools.h"

using namespace std;

int doFileFormatting(int argC, char** args);

int main(int argC, char** args)
{
    string origin = "testchekingtesthow welltestthis is working now";
    string splt = "test";

    vector<string> tokens = splitStringAt(origin, splt);

    for(int i = 0; i < tokens.size(); i++)
    {
        cout << "|" << tokens[i] << "|" << endl;
    }

    //return doFileFormatting(argC, args);
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
