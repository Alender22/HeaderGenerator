#pragma once

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> readFileLineByLine(string fileName);
string readFileToString(string fileName);
void writeStringToFile(string fileName, string fileContents);

vector<char> readBinaryFile(string fileName);
void writeBinaryFile(string fileName, vector<char> contents);