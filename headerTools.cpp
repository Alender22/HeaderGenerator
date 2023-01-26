#include <iostream>
#include <vector>
#include "tableTools.h"
#include "fileTools.h"
#include "timeTools.h"
#include "terminalTools.h"
#include "headerTools.h"

using namespace std;

void Header::readTableFromTemplate(string templateLocation)
{
    Table commentTable;
    vector<string> templateLines = readFileLineByLine(templateLocation);

    vector<string> widthStrings = splitStringAt(templateLines[0], '~');
    vector<int> cellWides;

    for(int i = 0; i < widthStrings.size(); i++)
    {
        cellWides.push_back(stoi(widthStrings[i]));
        if(i == 0)
            commentTable.setCellWidth(i, cellWides[i]);
    }
    
    templateLines.erase(templateLines.begin());

    for(int i = 0; i < templateLines.size(); i++)
    {
        if(i == commentTable.getNumRows())
            commentTable.addRowToTable();

        vector<string> singleLine = splitStringAt(templateLines[i], '~');

        for(int j = 0; j < singleLine.size(); j++)
        {
            if(j == commentTable.getNumCols())
            {
                if(j < cellWides.size())
                    commentTable.addColToTable(cellWides[j]);
                else
                    commentTable.addColToTable();
            }

            commentTable.setCellContent(singleLine[j], i, j);
        }
    }

    header = commentTable;
}

string Header::makeHeader()
{
    string borderEnd = padRight("", header.getOutBorder(), header.getTableCharWidth() - 1);
    string borderBuffer = padRight(charToStr(header.getOutBorder()), ' ', header.getTableCharWidth() - 1) + header.getOutBorder() +"\n";

    return "/" + borderEnd + "\n" + borderBuffer + header.getFullTable() + borderBuffer + borderEnd + "/" + "\n" ;
}

void Header::handleFlagCommands()
{
    for(int i = 0; i < header.getNumRows(); i++)
    {
        for(int j = 0; j < header.getNumCols(); j++)
        {
            checkFlag(header.getCellContent(i, j), i, j);
        }
    }
}

void Header::checkFlag(string potFlag, int i, int j)
{
    if(substringIn(potFlag, "#var-"))
    {
        string varName = replaceSubStringWithString(potFlag, "#var-", "");
        header.setCellContent(getVarContFromName(varName), i, j);
    }
    if(potFlag == "#getSysDate")
    {
        header.setCellContent(getDate_YYYY_MM_DD_Format(), i, j);
    }
    if(potFlag == "#userinput")
    {
        clearTerminal();

        header.setCellColor(1, i, j);

        string userIn;

        cout << "Please enter the contents of the cell containing the " + getColoredTerminalString("red", "red") + " '#userinput': " << endl;

        cout << header.getTableRow(i);

        getline(cin, userIn);

        clearTerminal();

        header.setCellContent(userIn, i, j);

        header.setCellColor(0, i, j);
    }
}

void Header::addVarToDict(string varName, string varCont)
{
    vector<string> valuePair;
    valuePair.push_back(varName);
    valuePair.push_back(varCont);

    varDict.push_back(valuePair);
}

string Header::getVarContFromName(string varName)
{
    for(int i = 0; i < varDict.size(); i++)
    {
        if(varDict[i][0] == varName)
            return varDict[i][1];
    }
    return varName + " not found";
}