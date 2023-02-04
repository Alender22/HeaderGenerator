#include <iostream>
#include "colorTools.h"

using namespace std;

string getColoredTerminalString(string toPrint, string color)
{
    if(color == "red")
        return "\x1B[31m" + toPrint + "\033[0m";
    if(color == "green")
        return "\x1B[32m" + toPrint + "\033[0m";
    if(color == "blue")
        return "\x1B[34m" + toPrint + "\033[0m";
    else
        return toPrint;
}

string getColor(int num)
{
    switch (num)
    {
    case(1):
        return "red";
        break;
    case(2):
        return "green";
        break;
    case(3):
        return "blue";
        break;
    default:
        return "white";
        break;
    }
}

string setBackgroundColor(string toSet, int r, int g, int b)
{
    return "\033[48;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + toSet + "\033[0m";
}

string setForegroundColor(string toSet, int r, int g, int b)
{
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + toSet + "\033[0m";
}

string setForeAndBackgroundColor(string toSet, int rf, int gf, int bf, int rb, int gb, int bb)
{
    return "\033[38;2;" + to_string(rf) + ";" + to_string(gf) + ";" + to_string(bf) + "m" + 
           "\033[48;2;" + to_string(rb) + ";" + to_string(gb) + ";" + to_string(bb) + "m" + toSet + "\033[0m";
}