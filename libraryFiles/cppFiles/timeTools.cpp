#include <iostream>
#include <vector>
#include <ctime>
#include "stringTools.h"
#include "timeTools.h"

using namespace std;

string getDate_YYYY_MM_DD_Format()
{
    time_t currTime;
    string retString;

    currTime = time(NULL);

    vector<string> dateTime = splitStringAt(replaceSubStringWithString(removeCharFromString(ctime(&currTime), '\n'), "  ", " "), ' ');

    if(dateTime[2].length() == 1)
        dateTime[2] = "0" + dateTime[2];

    retString = dateTime[4] + '/' + getMonthNumber(dateTime[1]) + '/' + dateTime[2];
    
    return retString;
}

string getMonthNumber(string monthAbb)
{
    if(monthAbb == "Jan")
        return "01";
    if(monthAbb == "Feb")
        return "02";
    if(monthAbb == "Mar")
        return "03";
    if(monthAbb == "Apr")
        return "04";
    if(monthAbb == "May")
        return "05";
    if(monthAbb == "Jun")
        return "06";
    if(monthAbb == "Jul")
        return "07";
    if(monthAbb == "Aug")
        return "08";
    if(monthAbb == "Sep")
        return "09";
    if(monthAbb == "Oct")
        return "10";
    if(monthAbb == "Nov")
        return "11";
    if(monthAbb == "Dec")
        return "12";
    return "Month abbreviation " + monthAbb + " was not recognized\n";
}