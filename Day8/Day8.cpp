#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "../Helpful_Commands.cpp"
using namespace std;

vector<string> readInput()
{
    string fileLine;
    fstream file("input.txt");
    vector<string> lines;
    while(getline(file,fileLine))
    {
        lines.push_back(fileLine);
    }
    return lines;
}

void part1()
{
    vector<string> lines =readInput();
    unordered_map<int,bool> filledSpaces;
    for(int y = 0; y < lines.size();y++)
    {
        for(int x = 0;x < lines[0].size();x++)
        {
            char antennae = lines[y][x];
            if(antennae == '.')continue;
            for(int y2 = 0;y2<lines.size();y2++)
            {
                for(int x2=0;x2<lines.size();x2++)
                {
                    if(x==x2&&y==y2)continue;
                    char antennae2 = lines[y2][x2];
                    if(antennae != antennae2) continue;
                    int newY = (y2-y) + y2;
                    int newX = (x2-x) + x2;
                    if(newX < 0 || newX >= lines[0].size() || newY < 0 || newY >= lines.size())continue;
                    filledSpaces[newY*51+newX] = true;
                }
            }
        }
    }
    cout << filledSpaces.size() << endl;
}

void part2()
{
    vector<string> lines =readInput();
    unordered_map<int,bool> filledSpaces;
    for(int y = 0; y < lines.size();y++)
    {
        for(int x = 0;x < lines[0].size();x++)
        {
            char antennae = lines[y][x];
            if(antennae == '.')continue;
            for(int y2 = 0;y2<lines.size();y2++)
            {
                for(int x2=0;x2<lines[0].size();x2++)
                { 
                    char antennae2 = lines[y2][x2];
                    if(antennae != antennae2) continue;
                    if(x==x2&&y==y2){
                        filledSpaces[y*51+x] = true;
                        continue;
                    }
                    int yDiff = (y2-y);
                    int xDiff = (x2-x);
                    int newY = y2 + yDiff;
                    int newX = x2 + xDiff;
                    
                    while(newX >= 0 && newX < lines[0].size() && newY >= 0 && newY < lines.size())
                    {
                        filledSpaces[newY*51+newX] = true;
                        newX += xDiff;
                        newY += yDiff;
                    }
                }
            }
        }
    }
    cout << filledSpaces.size() << endl;
}

int main()
{
    part1();
    part2();
    return 0;
}

