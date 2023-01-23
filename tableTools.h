#pragma once 

#include <vector>

using namespace std;

struct table
{
    vector<vector<string>> mat;
    vector<int> cellWidths;
    int margins = 1;
    char outBorder = '*';
    char inBorder = '-';
    char cellSeperator = '|';
};

string makeTable(table toTable);
int getTableWidth(table toTable);
string makeTableRow(table toTable, int newRow);
string makeCellContents(table toTable, int newRow);
string makeRowSeperator(table toTable);
string makeRowMargin(table toTable);
vector<vector<string>> makeRowVector(vector<string> row, vector<int> cellWidths);
int getLongestCell(vector<vector<string>> rowVec);
int numberOfMostColumns(table theTable);
void addDefaultWidths(table& theTable);