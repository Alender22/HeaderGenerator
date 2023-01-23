/*******************************************************************************
*                                                                              *
*------------------------------------------------------------------------------*
*                            |                                                 *
* Author                     | Lucas Alexander Ethington                       *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                            |                                                 *
* Date started (yyyy/mm/dd)  | 2023/01/22                                      *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                            |                                                 *
* Last edited (yyyy/mm/dd)   | 2023/01/23                                      *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                            |                                                 *
* Purpose                    | The third version of my header generator, this  *
*                            | time largely based on my tableTools.cpp file.   *
*                            | It generates a table, which is then slightly    *
*                            | changed into a valid cpp header                 *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                            |                                                 *
* Filename                   | 3_0-headerGenerator.cpp                         *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                                                                              *
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "stringTools.h"
#include "tableTools.h"
#include "3_0-headerGenerator.h"

using namespace std;

int main()
{
    table theTable = readTemplate("template.txt");
    cout << makeHeader(theTable);
}

table readTemplate(string templateFile)
{
    ifstream inFile(templateFile);
    table theTable;
    string line;
    if(getline(inFile, line))
        theTable.cellWidths = getCellWidths(line);

    while(getline(inFile, line))
    {
        theTable.mat.push_back(splitStringAt(line, '~'));
    }

    int longestKey = getLongestKey(theTable);
    //theTable.cellWidths.push_back(30);
    //theTable.cellWidths.push_back(43);

    addDefaultWidths(theTable);

    return theTable;
}

int getLongestKey(table theTable)
{
    int longest = 0;
    for(int i = 0; i < theTable.mat.size(); i++)
    {
        if(longest < theTable.mat[i][0].length())
            longest = theTable.mat[i][0].length();
    }
    return longest;
}

string makeHeader(table theTable)
{
    string start = padRight("/", theTable.outBorder, getTableWidth(theTable) - 1) + theTable.outBorder + "\n";
    string margin = padRight(charToStr(theTable.outBorder), ' ', getTableWidth(theTable) - 1) + theTable.outBorder + "\n";
    string end = padRight(charToStr(theTable.outBorder), theTable.outBorder, getTableWidth(theTable) - 1) + "/" + "\n";

    string tableStr = makeTable(theTable);

    for(int i = 0; i < theTable.margins; i++)
    {
        tableStr = margin + tableStr + margin;
    }

    return start + tableStr + end;
}

vector<int> getCellWidths(string cellWidths)
{
    vector<string> widthTokens = splitStringAt(cellWidths, '~');
    vector<int> widths;

    for(int i = 0; i < widthTokens.size(); i++)
    {
        widths.push_back(stoi(widthTokens[i]));
    }

    return widths;
}