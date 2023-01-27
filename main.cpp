#include <iostream>
#include "stringTools.h"

using namespace std;

int main(int argC, char** args)
{
    string test = "testtesttesttestd";
    string split = "test";

    vector<string> tokens = splitStringAt(test, split);

    for(int i = 0; i < 5; i++)
        cout << endl;

    for(int i = 0; i < tokens.size(); i++)
        cout << "Main: " << "|" << tokens[i] << "|" << endl;
}
