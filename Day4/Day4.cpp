#include <vector>
#include <iostream>
#include <fstream>
#include <string>
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
bool spellsXmas(vector<string> lines, int x, int y,int xOff, int yOff)
{
    string xmas = "XMAS";
    int currX = x;
    int currY = y;
    for(int i = 0; i < xmas.size();i++)
    {
        if(currX >= lines.size() || currX < 0 || currY >= lines[0].size()||currY < 0) {return false;}
        if(lines[currX][currY] != xmas[i]) {return false;}
        currX+=xOff;
        currY+=yOff;
    }
    return true;
}

void part1()
{
    vector<string> lines = readInput();
    int total = 0;
    for(int i = 0;i < lines.size();i++)
    {
        for(int j = 0; j < lines.size();j++)
        {
            if(lines[i][j] != 'X') {continue;}
            if(spellsXmas(lines,i,j,1,0)) {total++;}
            if(spellsXmas(lines,i,j,-1,0)) {total++;}
            if(spellsXmas(lines,i,j,0,1)) {total++;}
            if(spellsXmas(lines,i,j,0,-1)) {total++;}
            if(spellsXmas(lines,i,j,1,1)) {total++;}
            if(spellsXmas(lines,i,j,-1,1)) {total++;}
            if(spellsXmas(lines,i,j,1,-1)) {total++;}
            if(spellsXmas(lines,i,j,-1,-1)) {total++;}
        //check if going any 8 directions spells xmas
        }
    }
    cout << total << endl;
}

bool isCrossMas(vector<string> lines,int x,int y)
{
    if(x + 1 >= lines.size() || x -1 < 0 || y +1 >= lines[0].size()|| y-1 < 0){return false;}
    //look clockwise around the a should lead to xssx, ssxx, sxxs, or xxss
    vector<string> combinations = {"MSSM","SSMM","SMMS","MMSS"};
    string corners = "";
    corners += lines[x+1][y+1];
    corners += lines[x+1][y-1];
    corners += lines[x-1][y-1];
    corners += lines[x-1][y+1];
    for(string combo : combinations)
    {
        if(corners == combo) {return true;}
    }
    return false;
}

void part2()
{
    vector<string> lines = readInput();
    int total = 0;
    for(int i = 0; i < lines.size();i++)
    {
        for(int j =0; j < lines[0].size();j++)
        {
            if(lines[i][j] != 'A'){continue;}
            if(isCrossMas(lines,i,j)){total++;}
        }
    }
    cout << total;
}

int main()
{
    part2();
    return 0;
}