#pragma once

#include <string>

using namespace std;

void formatCPPFile(string srcFilename, string destFileName, string headerStr);
void editIndentation(vector<string>& fileLines);
void insertComments(vector<string>& codeLines, string commentLocation = "commentsTemplate.txt");