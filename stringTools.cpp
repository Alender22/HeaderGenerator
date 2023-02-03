/*******************************************************************************
*                                                                              *
*------------------------------------------------------------------------------*
*                  |                                                           *
* Programmer       | Alender22                                                 *
*                  |                                                           *
*------------------------------------------------------------------------------*
*                  |                                                           *
* Date(yyyy/mm/dd) | 14:29:48/02/                                              *
*                  |                                                           *
*------------------------------------------------------------------------------*
*                  |                                                           *
* File             | ../MyLibraries/cppFiles/stringTools.cpp                   *
*                  |                                                           *
*------------------------------------------------------------------------------*
*                  |                                                           *
* Purpose          | Testing cross file insertion                              *
*                  |                                                           *
*------------------------------------------------------------------------------*
*                                                                              *
*******************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include "stringTools.h"

using namespace std;




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* Takes a string and a toSplit string, then splits the main string at every        *
* occurance of the subString                                                       *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

vector<string> splitStringAt(string toSplit, string splitAt)
{
  vector<string> tokens;
  string token = "";

  if(toSplit.length() < splitAt.length())
  {
    tokens.push_back(toSplit);
    return tokens;
  }

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




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* Splits a string at every occurance of a splitChar                                *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

vector<string> splitStringAt(string toSplit, char splitAt)
{
  return splitStringAt(toSplit, charToStr(splitAt));
}




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* Takes a string, a split char, and a length. Puts line breaks at the split char,  *
* such that the indevidual lines are less than or equal to given line lenght. Will *
* put line breaks elsewhere if necessary                                           *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

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




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* Pads a string to a certain length, with a given charachter, to either left or    *
* right                                                                            *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

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




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* Pads a string to a certain length, with a given charachter, to the right         *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

string padRight(string toPad, char padChar, int tarSize)
{
  return padString(toPad, padChar, tarSize, true);
}




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* Pads a string to a certain length, with a given charachter, to the left          *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

string padLeft(string toPad, char padChar, int tarSize)
{
  return padString(toPad, padChar, tarSize, false);
}




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* Pads a string to a certain length, keeping the original string centered          *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

string padCenter(string toPad, char padChar, int tarSize)
{
  string padded = padLeft(toPad, padChar, tarSize - ceil((tarSize - toPad.length()) / 2));
  return padRight(padded, padChar, tarSize);
}




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* Converts variables of type char to type string. Probably already in cpp...       *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

string charToStr(char cha)
{
  string str = "";
  return str += cha;
}




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* Replaces every instance of a given char in a string with a given substring       *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

string replaceCharWithString(string original, char tarChar, string tarSubStr)
{
  return replaceSubStringWithString(original, charToStr(tarChar), tarSubStr);
}




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* replaces every instance of a substring with a given string                       *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

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




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* removes every instance of a char from the string                                 *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

string removeCharFromString(string original, char toRemove)
{
  return removeSubStrFromSt(original, charToStr(toRemove));
}




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* removes every instance of a substring from the string                            *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

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




/***********************************************************************************
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
* returns whether or not a string contains a given substring                       *
*                                                                                  *
*----------------------------------------------------------------------------------*
*                                                                                  *
***********************************************************************************/

bool substringIn(string original, string sub)
{

  vector<string> tokens = splitStringAt(original, sub);

  if(tokens.size() > 1)
    return true;
  else
    return false;
}
