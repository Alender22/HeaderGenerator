#include <iostream>
#include "stringTools.h"

using namespace std;

int main(int argC, char** args)
{
    string test = "Now it's time to test splitting at a single charachter, which should also work.";
    string split = " ";

    vector<string> tokens = splitStringAt(test, split);

    for(int i = 0; i < 5; i++)
        cout << endl;

    for(int i = 0; i < tokens.size(); i++)
        cout << tokens[i] << endl;
}
