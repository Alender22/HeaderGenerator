#include <iostream>
#include <vector>
#include "headerTools.h"
#include "terminalTools.h"
#include "cppFormatTools.h"
#include "colorTools.h"
#include "timeTools.h"
#include "stringTools.h"
#include "fileTools.h"

using namespace std;

const string DEFAULT_LOCATION = "/home/lucas/.local/bin/makeHeaderTemplateDefault.txt";

struct commandDict
{
    vector<string> keys;
    vector<string> contents;
};

int runCommands(int argC, char** args);
int doFileFormatting(string inFileName, string outFileName = "-1NoArg", string templateLocation = DEFAULT_LOCATION);
commandDict readCommands(int argC, char** args);

int main(int argC, char** args)
{
    return runCommands(argC, args);
}

int runCommands(int argC, char** args)
{
    if(argC == 1)
    {
        cout << "No arguments were passed" << endl;
        return -1;
    }

    commandDict commands = readCommands(argC, args);
    string templateLocation = DEFAULT_LOCATION;
    string inFileName = "", outFileName;

    for(int i = 0; i < commands.keys.size(); i++)
    {
        if(commands.keys[i] == "sourceFileName")
        {
            inFileName = commands.contents[i];
        }
        if(commands.keys[i] == "destFileName")
        {
            outFileName = commands.contents[i];
        }
        if(commands.keys[i] == "userTemplate")
        {
            templateLocation = commands.contents[i];
        }
        if(commands.keys[i] == "setDefaultTemplate")
        {
            cout << "Enter the contents of your desired template line by line. When finished, enter #exit." << endl;
            string line, lines = "";

            do
            {
                getline(cin, line);
                if(line != "#exit")
                    lines += line + '\n';
            } while (line != "#exit");

            writeStringToFile(DEFAULT_LOCATION, lines);
            
            return 1;
        }
        if(commands.keys[i] == "readDefaultTemplate")
        {
            vector<string> lines = readFileLineByLine(DEFAULT_LOCATION);
            for(int j = 0; j < lines.size(); j++)
            {
                cout << lines[j] << endl;
            }

            return 2;
        }
    }

    if(inFileName != "")
        doFileFormatting(inFileName, outFileName, templateLocation);

    return 0;
}

int doFileFormatting(string inFileName, string outFileName, string templateLocation)
{
    Header header;
    string srcFilename = inFileName;
    string destFilename;

    if(outFileName == "-1NoArg")
        destFilename = srcFilename;
    else
        destFilename = outFileName;

    vector<string> pathString = splitStringAt(destFilename, '/');

    header.addVarToDict("FILENAME", pathString[pathString.size() - 1]);

    //header.readTableFromTemplate("~/.local/bin/makeHeaderTemplateDefault.txt");
    header.readTableFromTemplate(templateLocation);

    header.handleFlagCommands();

    clearTerminal();

    string headerStr = header.makeHeader();

    formatCPPFile(srcFilename, destFilename, headerStr);

    cout << srcFilename << " | " << destFilename << endl;

    return 0;
}

commandDict readCommands(int argC, char** args)
{
    commandDict dict;
    for(int i = 0; i < argC; i++)
    {
        string arg = args[i];
        if(arg == "-i")
        {
            dict.keys.push_back("sourceFileName");
            dict.contents.push_back(args[i + 1]);
        }
        if(arg == "-o")
        {
            dict.keys.push_back("destFileName");
            dict.contents.push_back(args[i + 1]);
        }
        if(arg == "--use-given-template")
        {
            dict.keys.push_back("userTemplate");
            dict.contents.push_back(args[i + 1]);
        }
        if(arg == "--set-default-template")
        {
            dict.keys.push_back("setDefaultTemplate");
            dict.contents.push_back("");
        }
        if(arg == "--read-default-template" || arg == "-r")
        {
            dict.keys.push_back("readDefaultTemplate");
            dict.contents.push_back("");
        }
    }

    return dict;
}