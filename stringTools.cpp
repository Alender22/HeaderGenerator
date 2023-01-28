#include <iostream>
#include <vector>
#include <cmath>
#include "stringTools.h"

using namespace std;

vector<string> splitStringAt(string toSplit, string splitAt)
{
    vector<string> tokens;
    string token = "";

    for(int i = 0; i < toSplit.length() - splitAt.length() + 1; i++)
    {

        if(toSplit.substr(i, splitAt.length()) != splitAt)
        {
            token += toSplit[i];
        }
        else
        {
            tokens.push_back(token);
            token = "";
            i += splitAt.length() - 1;
        }

        if(i >= toSplit.length() - splitAt.length() - 1)
        {
            if(toSplit.substr(toSplit.length() - splitAt.length()) != splitAt)
            {
                token += toSplit.substr(i + 1);
                break;
            }
        }
    }
    
    tokens.push_back(token);

    return tokens;
}

vector<string> splitStringAt(string toSplit, char splitAt)
{
    return splitStringAt(toSplit, charToStr(splitAt));
}

vector<string> maxLineLength(string toBreak, char splitAt, int lineLength)
{
    vector<string> tokens = splitStringAt(toBreak, splitAt);
    vector<string> parts;
    string part = "";

    for(int i = 0; i < tokens.size(); i++)
    {
        if(tokens[i].length() > lineLength)
        {
            string tmp = tokens[i].substr(0, lineLength - part.length());
            string rest = tokens[i].substr(lineLength - part.length());

            tokens[i] = tmp;
            tokens.insert(tokens.begin() + i + 1, rest);
        }

        if(part.length() + tokens[i].length() <= lineLength)
        {
            part += tokens[i];
        }
        else
        {
            parts.push_back(part.substr(0, part.length()));
            part = tokens[i];
        }
        
        if(part.length() + 1 <= lineLength)
        {
            part += ' ';
        }
        else
        {
            parts.push_back(part.substr(0, part.length()));
            part = "";
        }
    }
    if(part != "")
        parts.push_back(part.substr(0, part.length()));

    return parts;
}

string padString(string toPad, char padChar, int tarSize, bool padRight)
{
    if(tarSize <= 0)
    {
        cout << "TarSize for padding strings must be greator 0." << endl;
        return toPad;
    }
    while(toPad.length() < tarSize)
    {
        if(padRight)
            toPad += padChar;
        else
            toPad = padChar + toPad;
    }
    return toPad;
}

string padRight(string toPad, char padChar, int tarSize)
{
    return padString(toPad, padChar, tarSize, true);
}

string padLeft(string toPad, char padChar, int tarSize)
{
    return padString(toPad, padChar, tarSize, false);
}

string padCenter(string toPad, char padChar, int tarSize)
{
    string padded = padLeft(toPad, padChar, tarSize - ceil((tarSize - toPad.length()) / 2));
    return padRight(padded, padChar, tarSize);
}

string charToStr(char cha)
{
    string str = "";
    return str += cha;
}

string replaceCharWithString(string original, char tarChar, string tarSubStr)
{
    return replaceSubStringWithString(original, charToStr(tarChar), tarSubStr);
}

string replaceSubStringWithString(string original, string signalString, string tarSubStr)
{
    string formattedString = "";

    vector<string> tokens = splitStringAt(original, signalString);

    for(int i = 0; i < tokens.size(); i++)
    {
        formattedString += tokens[i];

        if(i < tokens.size() - 1)
            formattedString += tarSubStr;
    }

    return formattedString;
}

string removeCharFromString(string original, char toRemove)
{
    return removeSubStrFromSt(original, charToStr(toRemove));
}

string removeSubStrFromSt(string original, string toRemove)
{
    vector<string> tokens = splitStringAt(original, toRemove);
    string withRemoved = "";

    for(int i = 0; i < tokens.size(); i++)
    {
        withRemoved += tokens[i];
    }

    return withRemoved;
}

bool substringIn(string original, string sub)
{
    vector<string> tokens = splitStringAt(original, sub);

    if(tokens.size() > 1)
        return true;
    else
        return false;
}