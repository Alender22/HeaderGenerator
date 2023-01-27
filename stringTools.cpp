#include <iostream>
#include <vector>
#include <cmath>
#include "stringTools.h"

using namespace std;

vector<string> splitStringAt(string toSplit, string splitAt)
{
    vector<string> tokens;
    string token = "";

    while(toSplit.substr(0, splitAt.length()) == splitAt)
    {
        toSplit.erase(toSplit.begin(), toSplit.begin() + splitAt.length());

        if(toSplit == splitAt)
        {   
            tokens.push_back("");
            return tokens;
        }
    }

    while(toSplit.substr(toSplit.length() - splitAt.length(), splitAt.length()) == splitAt)
        toSplit.erase(toSplit.end() - splitAt.length(), toSplit.end() );

    cout << "|" << toSplit << "|" << endl;

    for(int i = 0; i < toSplit.length() - splitAt.length() + 1; i++)
    {
        cout << "Comparing:  " << toSplit.substr(i, splitAt.length()) << "  ===  " << splitAt << endl;

        if(toSplit.substr(i, splitAt.length()) == splitAt && i != 0)
        {
            token = toSplit.substr(0, i);
            tokens.push_back(token);

            toSplit = toSplit.substr(i + splitAt.length());
            i = 0;
        }
    }

    if(toSplit != "")
        tokens.push_back(toSplit);

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