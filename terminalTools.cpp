#include <iostream>
#include <sys/ioctl.h>

using namespace std;

int getTermWidth()
{
    struct winsize termSize;
    ioctl(0, TIOCGWINSZ, & termSize);

    return termSize.ws_col;
}

int getTermHeight()
{
    struct winsize termSize;
    ioctl(0, TIOCGWINSZ, & termSize);

    return termSize.ws_row;
}

void placeCursorAt(int i, int j)
{
    cout << "\033[" + to_string(i) + ";" + to_string(j) + "f";
}

void clearTerminal()
{
    for(int i = 0; i <= getTermHeight(); i++)
    {
        placeCursorAt(i, 1);
        cout << "\033[2K";
    }

    placeCursorAt(1, 1);
}

void makeSpace(int lines)
{
    for(int i = 0; i < lines; i++)
    {
        cout << endl;
    }
}