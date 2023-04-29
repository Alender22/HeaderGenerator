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
    cout << "inserting comments:" << endl;
    string commentString = readFileToString(commentLocation);
    vector<string> commentLines = splitStringAt(commentString, "#funcDec:");
    vector<string> commentPair;
    vector<string> codeCommentLines;
    string templateBuffer = "";

    cout << "1" << endl;
    for(int i = 0; i < codeLines.size(); i++)
    {
        cout << "2" << endl;
        for(int j = 0; j < commentLines.size(); j++)
        {
            commentPair = splitStringAt(commentLines[j], '\n');
            cout << "3" << endl;
            if(commentPair.size() > 1 && commentPair[0] != "")
            {
                cout << "4" << endl;
                cout << "codeLine: |" << codeLines[i] << "| comment pair: |" << commentPair[0] << "|" << endl; 
                if(substringIn(codeLines[i], commentPair[0]))
                {
                    string commentBlockLines = "";
                    Header commentFormatter;
                    cout << "5" << endl;
                    for(int k = 1; k < commentPair.size(); k++)
                    {
                        if(commentPair[k] != "")
                        {
                            if(commentBlockLines != "")
                                commentBlockLines += '\n';
                            commentBlockLines += commentPair[k];
                        }
                    }

                    commentFormatter.readTableFromString(commentBlockLines);

                    codeCommentLines.push_back("\n" + commentFormatter.makeHeader());
                }
            }
        }
        cout << "6" << endl;
        if(substringIn(codeLines[i], "template"))
        {
            templateBuffer = codeLines[i];
        }
        else
        {
            codeCommentLines.push_back(templateBuffer + codeLines[i]);
            templateBuffer = "";
        }
        
    }

    cout << "7" << endl;

    codeLines = codeCommentLines;
}
