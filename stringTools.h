#pragma once

#include <vector>

using namespace std;

vector<string> splitStringAt(string toSplit, char splitAt);
vector<string> maxLineLength(string toBreak, char splitAt, int lineLength);
string padString(string toPad, char padChar, int tarSize, bool padRight);
string padRight(string toPad, char padChar, int tarSize);
string padLeft(string toPad, char padChar, int tarSize);
string padCenter(string toPad, char padChar, int tarSize);
string charToStr(char cha);