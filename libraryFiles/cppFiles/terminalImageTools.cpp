#include <iostream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include "terminalTools.h"
#include "colorTools.h"
#include "fileTools.h"
#include "stringTools.h"
#include "terminalImageTools.h"

using namespace std;

void renderImage(string fileName, int squish)
{
    int wid = getTermWidth();
    int hei = getTermHeight() - 1;

    if(wid % 2 == 1)
        wid--;

    vector<vector<vector<int>>> colMap;

    colMap = readBMPFileToVector(fileName);

    colMap = resizeImage(colMap, squish);

    string image = convertImageToString(colMap);

    cout << image;
}

string convertImageToString(vector<vector<vector<int>>> imageVector)
{
    string image = "";

    int wid = getTermWidth();
    int hei = getTermHeight();

    for(int j = 0; j < imageVector.size() - 1; j += 2)
    {
        for(int i = 0; i < imageVector[j].size(); i++)
        {
            image += setForeAndBackgroundColor("\u2580", imageVector[imageVector.size() - 1 - j][i][0], imageVector[imageVector.size() - 1 - j][i][1], imageVector[imageVector.size() - 1 - j][i][2],
                                                        imageVector[imageVector.size() - 2 - j][i][0], imageVector[imageVector.size() - 2 - j][i][1], imageVector[imageVector.size() - 2 - j][i][2]);
                
        }

        if(j > hei * 2)
            break;

        image += "\n";

        if(j + 3 == imageVector.size())
        {
            for(int i = 0; i < imageVector[j].size(); i++)
                image += setForegroundColor("\u2580", imageVector[0][i][0], imageVector[0][i][1], imageVector[0][i][2]);
        }

    }
    return image + "\n";
}

vector<vector<vector<int>>> readBMPFileToVector(string fileName)
{
    vector<vector<vector<int>>> colMap;

    vector<char> fileBytes = readBinaryFile(fileName);
    int bitmapOffset, pixelWidth, pixelHeight;

    memcpy(&bitmapOffset, &fileBytes[10], sizeof(int));
    memcpy(&pixelWidth, &fileBytes[18], sizeof(int));
    memcpy(&pixelHeight, &fileBytes[22], sizeof(int));

    for(int h = 0; h < pixelHeight; h++)
    {
        vector<vector<int>> row;
        for(int w = 0; w < pixelWidth; w++)
        {
            vector<int> color;
            int pixelStart = bitmapOffset + h * pixelWidth * 3 + w * 3;

            int r = (fileBytes[pixelStart + 2] + 255) % 255;
            int g = (fileBytes[pixelStart + 1] + 255) % 255;
            int b = (fileBytes[pixelStart + 0] + 255) % 255;

            color.push_back(r);
            color.push_back(g);
            color.push_back(b);

            row.push_back(color);
        }
        colMap.push_back(row);
    }

    return colMap;
}

vector<vector<vector<int>>> resizeImage(vector<vector<vector<int>>> original, int factor)
{
    vector<vector<vector<int>>> resized;

    vector<vector<vector<int>>> layover;

    for(int i = 0; i < original.size() - factor - 1; i += factor)
    {
        vector<vector<int>> row;
        for(int j = 0; j < original[i].size() - 1 - factor; j += factor)
        {
            vector<int> color;

            int r = 0;
            int g = 0;
            int b = 0;

            int rSum = 0;
            int gSum = 0;
            int bSum = 0;

            for(int k = 0; k < factor; k++)
            {
                for(int l = 0; l < factor; l++)
                {
                    rSum += original[k + i][l + j][0];
                    gSum += original[k + i][l + j][1];
                    bSum += original[k + i][l + j][2];
                }
            }            

            r = rSum / (factor * factor);
            g = gSum / (factor * factor);
            b = bSum / (factor * factor);

            color.push_back(r);
            color.push_back(g);
            color.push_back(b);

            row.push_back(color);
        }
        resized.push_back(row);
    }
    return resized;
}

void outputHeaderInfo(vector<char> fileBytes)
{

    string varTypes[29]{"word", "dword", "word", "word", "dword", "dword", "long", "long", "word", "word",
                      "dword", "dword", "long", "long", "dword", "dword", "dword", "dword", "dword",
                      "dword", "dword", "ciexyztriple", "dword", "dword", "dword", "dword", "dword",
                      "dword", "dword"};

    string fieldNames[29] {"FileType: ", "FileSize: ", "Reserved1: ", "Reserved2: ",
                           "BitmapOffset: ", "bV5Size: ", "bV5Width: ", "bV5Height: ", 
                           "bV5Planes: ", "bV5BitCount: ", "bV5Compression: ", "bV5SizeImage: ",
                           "bV5XPeslPerMeter: ", "bV5YPelsPerMeter: ", "bV5ClrUsed: ",  "bV5ClrImportant: ", 
                           "bV5RedMask: ", "bV5GreenMask: ", "bV5BlueMask: ", "bV5AlphaMask: ", "bV5CsType: ", "bV5Endpoints: ",
                           "bV5GammaRed: ", "bV5GammaGreen: ", "bV5GammaBlue: ", "bV5Intent: ", "bV5ProfileData: ", "bV5ProfileSize: ",
                           "bV5Reserved: "};

    int j = 0;
    for(int i = 0; i < 29; i++)
    {
        if(varTypes[i] == "word")
        {
            int intVal;
            memcpy(&intVal, &fileBytes[j], sizeof(short));
            cout << "i: " << i << " j: " << j << " | " << fieldNames[i] << " | " << intVal << endl;
            j += 2;
        }
        if(varTypes[i] == "dword")
        {
            int intVal;
            memcpy(&intVal, &fileBytes[j], sizeof(int));
            cout << "i: " << i << " j: " << j << " | " << fieldNames[i] << " | " << intVal << endl;
            j += 4;   
        }
        if(varTypes[i] == "long")
        {
            int intVal;
            memcpy(&intVal, &fileBytes[j], sizeof(int));
            cout << "i: " << i << " j: " << j << " | " << fieldNames[i] << " | " << intVal << endl;
            j += 4;
        }
        if(varTypes[i] == "ciexyztriple")
        {
            cout << varTypes[i] << " | --- " << "fieldContent: " << fieldNames[i] << endl;
            j += 36;
        }
    }
}

int getImageHeight()
{
    return getTermHeight() * 2;
}

int getImageWidth()
{
    return getTermWidth();
}