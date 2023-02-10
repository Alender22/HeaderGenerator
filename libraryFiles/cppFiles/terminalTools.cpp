#include <iostream>
#include <sys/ioctl.h>

using namespace std;

//All of these functions use ANSI escape codes


//Places the cursor at a given coordinate in the terminal
void placeCursorAt(int i, int j)
{
    cout << "\033[" + to_string(i) + ";" + to_string(j) + "f";
}

//clears the current contents of the terminal
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

//Makes space by printing newlines to terminal, depricated
void makeSpace(int lines)
{
    for(int i = 0; i < lines; i++)
    {
        cout << endl;
    }
}

//Returns current width of terminal, in charachters
int getTermWidth()
{
    struct winsize termSize;
    ioctl(0, TIOCGWINSZ, & termSize);

    return termSize.ws_col;
}

//Returns current height of terminal in lines
int getTermHeight()
{
    struct winsize termSize;
    ioctl(0, TIOCGWINSZ, & termSize);

    return termSize.ws_row;
}