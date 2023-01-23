#pragma once

table readTemplate(string templateFile);
int getLongestKey(table theTable);
string makeHeader(table theTable);
vector<int> getCellWidths(string cellWidths);