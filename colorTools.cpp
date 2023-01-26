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