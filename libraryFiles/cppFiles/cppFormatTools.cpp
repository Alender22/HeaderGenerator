#include <iostream>
#include <vector>
#include <cmath>
#include "fileTools.h"
#include "stringTools.h"
#include "cppFormatTools.h"
#include "headerTools.h"

using namespace std;

void formatCPPFile(string srcFilename, string destFileName, string headerStr)
{
    vector<string> fileLines = readFileLineByLine(srcFilename);
    headerStr += '\n';

    editIndentation(fileLines);
    insertComments(fileLines);

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

void insertComments(vector<string>& codeLines , string commentLocation)
{
    vector<string> commentLines = readFileLineByLine(commentLocation);
    vector<string> commentPair;
    vector<string> codeCommentLines;

    for(int i = 0; i < codeLines.size(); i++)
    {
        for(int j = 0; j < commentLines.size(); j++)
        {
            commentPair = splitStringAt(commentLines[j], '~');

            if(commentPair.size() == 2)
            {
                if(substringIn(codeLines[i], commentPair[0]))
                {
                    Header commentFormatter;

                    commentFormatter.readTableFromString("80\n" + commentPair[1]);

                    codeCommentLines.push_back("\n\n\n" + commentFormatter.makeHeader());
                }
            }
        }
        codeCommentLines.push_back(codeLines[i]);
    }

    codeLines = codeCommentLines;
}