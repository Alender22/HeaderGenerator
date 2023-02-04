#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> readFileLineByLine(string fileName)
{
    vector<string> lines;
    ifstream inFile(fileName);
    string line;

    while(getline(inFile, line))
    {
        lines.push_back(line);
    }

    inFile.close();

    return lines;
}

string readFileToString(string fileName)
{
    vector<string> lines = readFileLineByLine(fileName);
    string fileString = "";

    for(int i = 0; i < lines.size(); i++)
    {
        fileString += lines[i] + '\n';
    }

    return fileString;
}

void writeStringToFile(string fileName, string fileContents)
{
    ofstream outfile(fileName);

    outfile << fileContents;

    outfile.close();
}