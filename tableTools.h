#pragma once

#include <iostream>
#include <vector>
#include "timeTools.h"
#include "stringTools.h"
#include "fileTools.h"
#include "colorTools.h"

using namespace std;

class Table
{
private:

    vector<vector<string>> table;
    vector<vector<int>> cellColors;
    vector<vector<string>> varDict;
    vector<int> cellWidths;

    int margins;
    char outBorder;
    char rowSep;
    char colSep;

    int defCellWidth;

    int calcTableWidth();

    int sumOfWidthsVector();

    int sumOfMarginsWidth();

    int numSepChars();

    string generateRowSep();

    string generateRowBuffer();

    string generateColSep();

    string generateRowCellContents(int row);

    int getDeepestCellInRow(vector<vector<vector<string>>>& linesTable, int row);

    string generateContentsLine(vector<vector<string>> lineContents, int lin, int row);

    vector<vector<vector<string>>> generateLinesTable();

    string generateTableRow(int row);

    string generateFullTable();

public:

    Table(int setMargin = 1, char setOutBorder = '*', char setRowSep = '-', char setColSep = '|', int setDefCellWidth = 20);

    int getMargins();

    void setMargins(int toSet);

    char getOutBorder();

    void setOutBorder(char toSet);

    char getRowSep();

    void setRowSep(char toSet);

    char getColSep();

    void setColSep(char toSet);

    void addColToTable(int colWidth = -1);

    void setCellWidth(int col, int width);

    void delColFromTable(int col);

    void addRowToTable();

    void delRowFromTable(int row);

    void setCellContent(string contents, int i, int j);

    string getCellContent(int i, int j);

    void setCellColor(int color, int i, int j);

    int getCellColor(int i, int j);

    int getTableCharWidth();

    string getTableRow(int row);

    string getFullTable();

    int getNumCols();

    int getNumRows();
};