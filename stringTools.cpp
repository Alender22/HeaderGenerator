/*******************************************************************************
*                                                                              *
*------------------------------------------------------------------------------*
*                            |                                                 *
* Author                     | Lucas Alexander Ethington                       *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                            |                                                 *
* Date started (yyyy/mm/dd)  | 2023/01/22                                      *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                            |                                                 *
* Last edited (yyyy/mm/dd)   | 2023/01/23                                      *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                            |                                                 *
* Purpose                    | This is a small library of tools to manipulate  *
*                            | strings with                                    *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                            |                                                 *
* Filename                   | stringTools.cpp                                 *
*                            |                                                 *
*------------------------------------------------------------------------------*
*                                                                              *
*******************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include "stringTools.h"

using namespace std;

vector<string> splitStringAt(string toSplit, char splitAt)
{
    vector<string> tokens;
    string token = "";

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
        if(part.length() + tokens[i].length() + 1 <= lineLength)
        {
            part += tokens[i] + ' ';
        }
        else
        {
            parts.push_back(part.substr(0, part.length()-1));
            part = tokens[i] + ' ';
        }
    }
    parts.push_back(part.substr(0, part.length()-1));
    return parts;
}

string padString(string toPad, char padChar, int tarSize, bool padRight)
{
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