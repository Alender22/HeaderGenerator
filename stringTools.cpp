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
        cout << "Before: " << toSplit << endl;
        cout << "|" << toSplit.substr(0, splitAt.length()) << "|" << splitAt << "|" << endl;
        //toSplit.erase(toSplit.begin(), toSplit.begin() + splitAt.length());
        toSplit = toSplit.substr(splitAt.length());
        cout << "After: " << toSplit << endl;

        if(toSplit == splitAt)
        {   
            tokens.insert(tokens.begin(), (""));
            return tokens;
        }

        cout << " ++ " << endl;
        tokens.insert(tokens.begin(), "");
        cout << "After2: " << toSplit << endl;

        if(toSplit.substr(0, splitAt.length()) != splitAt)
            break;
    }

    while(toSplit.substr(toSplit.length() - splitAt.length(), splitAt.length()) == splitAt)
    {
        toSplit.erase(toSplit.end() - splitAt.length(), toSplit.end() );
        tokens.push_back("");
    }

    for(int i = 0; i < toSplit.length() - splitAt.length(); i++)
    {
        if(toSplit.length() >= splitAt.length())
        {
            if(toSplit.substr(i, splitAt.length()) == splitAt && i != 0)
            {
                token = toSplit.substr(0, i);
                tokens.push_back(token);

                toSplit = toSplit.substr(i + splitAt.length());
                i = 0;
            }
        }
        else
            break;
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
    if(tarSize < toPad.length())
        cout << "tarSize given is smaller than string length. Doing nothing. " << endl;

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