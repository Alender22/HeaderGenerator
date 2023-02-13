#include <iostream>
#include "colorTools.h"

using namespace std;

//This function takes a given string and color, and brackets 
//  the string with the ANSI escape codes to print the string
//  to terminal in that color. 
string getColoredTerminalString(string toPrint, string color)
{
    if(color == "red")
        return setForegroundColor(toPrint, 255, 0, 0);
    if(color == "green")
        return setForegroundColor(toPrint, 0, 255, 0);
    if(color == "blue")
        return setForegroundColor(toPrint, 0, 0, 255);
    else
        return toPrint;
}

//This function translates colors from integers to names,
//  for the table generator. 
//  TODO: change this to be table generator internal, and
//        use only the set to RGB value functions
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

//Sets the color of text background to the given RGB value
//  using ANSI escape codes.
string setBackgroundColor(string toSet, int r, int g, int b)
{
    return "\033[48;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + toSet + "\033[0m";
}

//Sets the color of text to the given RGB value
//  using ANSI escape codes.
string setForegroundColor(string toSet, int r, int g, int b)
{
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m" + toSet + "\033[0m";
}

//Sets color of text and background to given rgb values
string setForeAndBackgroundColor(string toSet, int rf, int gf, int bf, int rb, int gb, int bb)
{
    return "\033[38;2;" + to_string(rf) + ";" + to_string(gf) + ";" + to_string(bf) + "m" + 
           "\033[48;2;" + to_string(rb) + ";" + to_string(gb) + ";" + to_string(bb) + "m" + toSet + "\033[0m";
}