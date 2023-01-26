#include <iostream>
#include <vector>
#include <cmath>
#include "stringTools.h"

using namespace std;

vector<string> splitStringAt(string toSplit, char splitAt)
{
    vector<string> tokens;
    string token = "";

    if(toSplit == "")
        tokens.push_back("");

    for(int i = 0; i < toSplit.length(); i++)
    {
        if(toSplit[i] != splitAt)
        {
            token += toSplit[i];
        }
        else
        {
            tokens.push_back(token);
            token = "";
        }
    }
    if(token != "")
        tokens.push_back(token);

    return tokens;
}

vector<string> maxLineLength(string toBreak, char splitAt, int lineLength)
{
    vector<string> tokens = splitStringAt(toBreak, splitAt);
    vector<string> parts;
    string part = "";

    for(int i = 0; i < tokens.size(); i++)
    {
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
    string convertedString = "";
    for(int i = 0; i < original.length(); i++)
    {
        if(original[i] == tarChar)
        {
            convertedString += tarSubStr;
        }
        else
        {
            convertedString += original[i];
        }
    }
    return convertedString;
}

string replaceSubStringWithString(string original, string signalString, string tarSubStr)
{
    string formattedString = "";

    if(original.length() >= signalString.length())
    {
        for(int i = 0; original.length() >= signalString.length() + i; i++)
        {
            if(original.substr(i, signalString.length()) == signalString)
            {
                formattedString += tarSubStr;
                i += signalString.length() - 1;
            }
            else
            {
                if(i < original.length() - signalString.length() - 1)
                    formattedString += original[i];
            }
            if(i == original.length() - signalString.length())
                formattedString += original.substr(i - 1, signalString.length() + 1);
        }
    }
    else
        return original;

    return formattedString;
}

string removeCharFromString(string original, char toRemove)
{
    string cleaned;
    for(int i = 0; i < original.length(); i++)
    {
        if(original[i] != toRemove)
            cleaned += original[i];
    }
    return cleaned;
}

bool substringIn(string original, string sub)
{
    string check = replaceSubStringWithString(original, sub, sub + sub);

    if(check.length() != original.length())
    {  
        return true;
    }
    else
    {
        return false;
    }
}