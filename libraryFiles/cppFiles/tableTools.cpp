#include <iostream>
#include <vector>
#include "timeTools.h"
#include "stringTools.h"
#include "fileTools.h"
#include "colorTools.h"
#include "tableTools.h"

using namespace std;

int Table::calcTableWidth()
{
    return sumOfWidthsVector() + sumOfMarginsWidth() + numSepChars();
}

int Table::sumOfWidthsVector()
{
    int sumWidths = 0;

    for(int i = 0; i < cellWidths.size(); i++)
    {
        sumWidths += cellWidths[i];
    }

    return sumWidths;
}

int Table::sumOfMarginsWidth()
{
    return cellWidths.size() * margins * 2;
}

int Table::numSepChars()
{
    return cellWidths.size() + 1;
}

string Table::generateRowSep()
{
    string rowSepStr = charToStr(outBorder);
    rowSepStr = padRight(rowSepStr, rowSep, calcTableWidth() - 1);
    return rowSepStr + charToStr(outBorder) + "\n";
}

string Table::generateRowBuffer()
{
    string rowBuffer = charToStr(outBorder) + padRight("", ' ', margins);
    
    for(int i = 0; i < cellWidths.size(); i++)
    {
        rowBuffer += padRight("", ' ', cellWidths[i]);
        if(i < cellWidths.size() - 1)
            rowBuffer += generateColSep();
    }

    return rowBuffer + padRight("", ' ', margins) + charToStr(outBorder) + "\n";
}

string Table::generateColSep()
{
    return padCenter(charToStr(colSep), ' ', 1 + 2 * margins);
}

string Table::generateRowCellContents(int row)
{
    vector<vector<vector<string>>> linesTable = generateLinesTable();

    string rowContents = "";

    int deepestCell = getDeepestCellInRow( linesTable, row);

    for(int i = 0; i < deepestCell; i++)
    {
        rowContents += generateContentsLine(linesTable[row], i, row);
    }

    return rowContents;
}

int Table::getDeepestCellInRow(vector<vector<vector<string>>>& linesTable, int row)
{
    int deepest = 0;

    for(int i = 0; i < linesTable[row].size(); i++)
    {
        if(deepest < linesTable[row][i].size())
            deepest = linesTable[row][i].size();
    }

    return deepest;
}

string Table::generateContentsLine(vector<vector<string>> lineContents, int lin, int row)
{
    string completedLine = charToStr(outBorder) + padRight("", ' ', margins);

    for(int i = 0; i < lineContents.size(); i++)
    {
        if(lineContents[i].size() == 0)
            lineContents[i].push_back("");
        if(lin < lineContents[i].size())
        {
            completedLine += getColoredTerminalString(padRight(lineContents[i][lin], ' ', cellWidths[i]), getColor(cellColors[row][i]));
        }
        else
        {
            completedLine += padRight("", ' ', cellWidths[i]);
        }
        if(i < lineContents.size() - 1)
        {
            completedLine += generateColSep();
        }
    }

    return completedLine + padRight("", ' ', margins) + charToStr(outBorder) + "\n";
}

vector<vector<vector<string>>> Table::generateLinesTable()
{
    vector<vector<vector<string>>> linesTable;
    vector<vector<string>> linesRow;

    for(int i = 0; i < table.size(); i++)
    {
        linesTable.push_back(linesRow);

        for(int j = 0; j < cellWidths.size(); j++)
        {

            vector<string> newEntry = maxLineLength(table[i][j], ' ', cellWidths[j]);

            linesTable[i].push_back(newEntry);
        }
    }

    return linesTable;
}

string Table::generateTableRow(int row)
{
    string generatedRow = "";

    generatedRow = generateRowSep();
    generatedRow += generateRowBuffer();
    generatedRow += generateRowCellContents(row);
    generatedRow += generateRowBuffer();

    return generatedRow;
}

string Table::generateFullTable()
{
    string tableString = "";

    for(int i = 0; i < table.size(); i++)
    {
        tableString += generateTableRow(i);
    }

    return tableString + generateRowSep();
}

Table::Table(int setMargin, char setOutBorder, char setRowSep, char setColSep, int setDefCellWidth)
{
    margins = setMargin;
    outBorder = setOutBorder;
    rowSep = setRowSep;
    colSep = setColSep;
    defCellWidth = setDefCellWidth;

    vector<string> tableStart;
    tableStart.push_back("");
    table.push_back(tableStart);

    cellWidths.push_back(defCellWidth);

    vector<int> colorStart;
    colorStart.push_back(0);
    cellColors.push_back(colorStart);
}

int Table::getMargins()
{
    return margins;
}

void Table::setMargins(int toSet)
{
    margins = toSet;
}

char Table::getOutBorder()
{
    return outBorder;
}

void Table::setOutBorder(char toSet)
{
    outBorder = toSet;
}

char Table::getRowSep()
{
    return rowSep;
}

void Table::setRowSep(char toSet)
{
    rowSep = toSet;
}

char Table::getColSep()
{
    return colSep;
}

void Table::setColSep(char toSet)
{
    colSep = toSet;
}

void Table::addColToTable(int colWidth)
{
    if(colWidth == -1)
        colWidth = defCellWidth;
    for(int i = 0; i < table.size(); i++)
    {
        table[i].push_back("");
        cellColors[i].push_back(0);
    }
    
    cellWidths.push_back(colWidth);
}

void Table::setCellWidth(int col, int width)
{
    if(col < cellWidths.size())
        cellWidths[col] = width;
    else
        cout << "Attempted to set width of cells out of bounds" << endl;
}

void Table::delColFromTable(int col)
{
    if(table[0].size() > 1)
    {
        if(col < table[0].size())
        {
            for(int i = 0; i < table.size(); i++)
            {
                table[i].erase(table[i].begin() + col);
                cellColors[i].erase(cellColors[i].begin() + col);
            }
        }
        else
            cout << "Tried to remove column out of bounds" << endl;
    }
    else
        cout << "Cannot have fewer than 1 column in the table" << endl;
    cellWidths.erase(cellWidths.begin() + col);
}

void Table::addRowToTable()
{
    vector<string> newRow;
    vector<int> newColors;
    
    for(int i = 0; newRow.size() < table[0].size(); i++)
    {
        newRow.push_back("");
        newColors.push_back(0);
    }


    cellColors.push_back(newColors);
    table.push_back(newRow);
}

void Table::delRowFromTable(int row)
{
    if(table.size() > 1)
    {
        if(row < table.size())
        {
            table.erase(table.begin() + row);
            cellColors.erase(cellColors.begin() + row);
        }
        else
            cout << "Tried to remove row out of bounds" << endl;
    }
    else
        cout << "Cannot have fewer than 1 row in the table" << endl;
}

void Table::setCellContent(string contents, int i, int j)
{
    table[i][j] = contents;
}

string Table::getCellContent(int i, int j)
{
    return table[i][j];
}

void Table::setCellColor(int color, int i, int j)
{
    cellColors[i][j] = color;
}

int Table::getCellColor(int i, int j)
{
    return cellColors[i][j];
}

int Table::getTableCharWidth()
{
    return calcTableWidth();
}

string Table::getTableRow(int row)
{
    string generatedRow = generateTableRow(row);
    generatedRow += generateRowSep();

    return generatedRow;
}

string Table::getFullTable()
{
    return generateFullTable();
}

int Table::getNumCols()
{
    return cellWidths.size();
}

int Table::getNumRows()
{
    return table.size();
}