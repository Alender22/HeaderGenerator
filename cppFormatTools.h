#pragma once

#include <string>

using namespace std;

void formatCPPFile(string srcFilename, string destFileName, string headerStr);
void editIndentation(vector<string>& fileLines);