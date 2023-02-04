#include <iostream>
#include <sys/ioctl.h>

using namespace std;

void placeCursorAt(int i, int j)
{
    cout << "\033[" + to_string(i) + ";" + to_string(j) + "f";
}

void clearTerminal()
{
    struct winsize termSize;
    ioctl(0, TIOCGWINSZ, & termSize);

    for(int i = 0; i <= termSize.ws_row; i++)
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