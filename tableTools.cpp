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
* Purpose                    | This is a ibrary which offerst tools, based on  *
*                            | stringTools.cpp, to make easily sized terminal  *
*                            | tables                                          *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                            |                                                 *
* Filename                   | tableTools.cpp                                  *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                                                                              *
*******************************************************************************/

#include <iostream>
#include <vector>
#include "stringTools.h"
#include "tableTools.h"

using namespace std;

string makeTable(table toTable)
{
    int totalWidth = getTableWidth(toTable);

    addDefaultWidths(toTable);
    
    string outTable = "";

    for(int i = 0; i < toTable.mat.size(); i++)
    {
        outTable += makeTableRow(toTable, i);
    }

    outTable += makeRowSeperator(toTable);

    return outTable;
}

int getTableWidth(table toTable)
{
    int totalWidth = 0;

    for(int i = 0; i < toTable.cellWidths.size(); i++)
    {
        totalWidth += toTable.cellWidths[i];
    }
    return toTable.cellWidths.size() * 2 * toTable.margins+ toTable.cellWidths.size() + 1 + totalWidth;
}

string makeTableRow(table toTable, int newRow)
{
    return makeRowSeperator(toTable) + makeRowMargin(toTable) + makeCellContents(toTable, newRow) + makeRowMargin(toTable);
}

string makeCellContents(table toTable, int newRow)
{
    vector<vector<string>> rowVec = makeRowVector(toTable.mat[newRow], toTable.cellWidths);
    int longestCell = getLongestCell(rowVec);
    string cellContents = "";

    for(int i = 0; i < longestCell; i++)
    {
        string line = padRight(charToStr(toTable.outBorder), ' ', toTable.margins + 1);
        for(int j = 0; j < toTable.cellWidths.size(); j++)
        {
            if(j < rowVec.size())
            {
                if(rowVec[j].size() > i)
                {
                    line += padRight(rowVec[j][i], ' ', toTable.cellWidths[j]);
                }
                else
                {
                    line += padRight("", ' ', toTable.cellWidths[j]);
                }
            }
            else
                line += padRight("", ' ', toTable.cellWidths[j]);
            if(j < toTable.cellWidths.size() -1)
                line += padCenter(charToStr(toTable.cellSeperator), ' ', toTable.margins * 2 + 1);
        }
        cellContents += line + padLeft(charToStr(toTable.outBorder), ' ', toTable.margins + 1) + "\n";
    }
    return cellContents;
}

string makeRowSeperator(table toTable)
{
    return padRight(charToStr(toTable.outBorder), toTable.inBorder, getTableWidth(toTable) - 1) + toTable.outBorder + "\n";
}

string makeRowMargin(table toTable)
{
    string margin = padRight(charToStr(toTable.outBorder), ' ', toTable.margins + charToStr(toTable.outBorder).length());
    for(int i = 0; i < toTable.cellWidths.size(); i++)
    {
        margin += padRight("", ' ', toTable.cellWidths[i]);
        if(i < toTable.cellWidths.size() - 1)
            margin += padCenter(charToStr(toTable.cellSeperator), ' ', toTable.margins * 2 + 1);
    }
    return padRight(margin, ' ', toTable.margins + margin.length()) + toTable.outBorder + "\n";
}

vector<vector<string>> makeRowVector(vector<string> row, vector<int> cellWidths)
{
    vector<vector<string>> rowVec;
    for(int i = 0; i < row.size(); i++)
    {
        rowVec.push_back(maxLineLength(row[i], ' ', cellWidths[i]));
    }
    return rowVec;
}

int getLongestCell(vector<vector<string>> rowVec)
{
    int longest = 0;
    for(int i = 0; i < rowVec.size(); i++)
    {
        if(rowVec[i].size() > longest)
            longest = rowVec[i].size();
    }
    return longest;
}

int numberOfMostColumns(table theTable)
{
    int mostCollumns = 0;

    for(int i = 0; i < theTable.mat.size(); i++)
    {
        if(theTable.mat[i].size() > mostCollumns)
            mostCollumns = theTable.mat[i].size();
    }
    
    return mostCollumns;
}

void addDefaultWidths(table& theTable)
{
    int numWidthsToAdd = numberOfMostColumns(theTable) - theTable.cellWidths.size();
    if(numWidthsToAdd > 0)
        cout << "Adding " << numWidthsToAdd << " default cell widths" << endl;

    for(int i = 0; numberOfMostColumns(theTable) > theTable.cellWidths.size(); i++)
    {
        theTable.cellWidths.push_back(25);
    }
}