#include <iostream>
#include <vector>
#include <cmath>
#include "fileTools.h"
#include "stringTools.h"
#include "cppFormatTools.h"

using namespace std;

void formatCPPFile(string srcFilename, string destFileName, string headerStr)
{
    vector<string> fileLines = readFileLineByLine(srcFilename);
    headerStr += '\n';

    editIndentation(fileLines);

    for(int i = 0; i < fileLines.size(); i++)
    {
        headerStr += fileLines[i] + '\n';
    }

    writeStringToFile(destFileName, headerStr);
}

void editIndentation(vector<string>& fileLines)
{
    int spaceCount = 0;

    for(int i = 0; i < fileLines.size(); i++)
    {
        while(fileLines[i][0] == ' ' || fileLines[i][0] == '\t')
        {
            if(fileLines[i][0] == ' ')
            {
                spaceCount += 1;
            }
            if(fileLines[i][0] == '\t')
            {
                spaceCount += 4;
            }
            fileLines[i] = fileLines[i].substr(1);
        }

        if(spaceCount > 0)
            fileLines[i] = padRight("", ' ', floor(spaceCount / 2)) + fileLines[i];
        spaceCount = 0;
    }
}