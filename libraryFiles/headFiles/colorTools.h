#pragma once

#include <string>

using namespace std;

string getColoredTerminalString(string toPrint, string color);
string getColor(int num);
string setBackgroundColor(string toSet, int r, int g, int b);
string setForegroundColor(string toSet, int r, int g, int b);
string setForeAndBackgroundColor(string toSet, int rf, int gf, int bf, int rb, int gb, int bb);