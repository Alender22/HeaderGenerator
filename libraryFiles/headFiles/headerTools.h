#pragma once

#include <vector>
#include <string>
#include "tableTools.h"

using namespace std;

class Header
{
private:
    Table header;
    vector<vector<string>> varDict;

public:
    void readTableFromTemplate(string templateLocation = "template.txt");
    
    void readTableFromString(vector<string> templateLines);

    void readTableFromString(string templateString, string lineBreak = "\n");

    void addVarToDict(string varName, string varCont);

    void handleFlagCommands();

    void checkFlag(string potFlag, int i, int j);

    string makeHeader();

    string getVarContFromName(string varName);
};