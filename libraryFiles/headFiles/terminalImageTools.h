#pragma once

#include <vector>
#include <string>

#include "terminalTools.h"
#include "colorTools.h"
#include "fileTools.h"
#include "stringTools.h"
#include "terminalImageTools.h"

using namespace std;

void renderImage(string fileName, int squish);
string convertImageToString(vector<vector<vector<int>>> imageVector);
vector<vector<vector<int>>> readBMPFileToVector(string fileName);
vector<vector<vector<int>>> resizeImage(vector<vector<vector<int>>> original, int factor);
void outputHeaderInfo(vector<char> fileBytes);
int getImageHeight();
int getImageWidth();