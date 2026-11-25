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
int getGuardPos(vector<string>& lines)
{
    for(int y = 0; y < lines.size();y++)
    {
        for(int x = 0; x < lines[0].size();x++)
        {
            if(lines[y][x] == '^') return x + y * 131;
        }
    }
    return 0;
}

void part1()
{
    vector<string> lines = readInput();
    int guardPosRaw = getGuardPos(lines);
    int y = guardPosRaw / 131;
    int x = guardPosRaw % 131;
    unordered_map<int,bool> guardPositions;
    guardPositions[y*131+x] = true;
    vector<vector<int>> directions = {{0,-1},{1,0},{0,1},{-1,0}};
    int edge = 0; //0123 = NESW
    int xOff = directions[edge][0];
    int yOff = directions[edge][1];
    x+=xOff;
    y+=yOff;
    while(x >= 0 && x < lines[0].size() && y >= 0  && y < lines.size())
    {
        if(lines[y][x] == '#')
        {
            x-=xOff;
            y-=yOff;
            edge++;
            if(edge > 3) edge = 0;
            xOff = directions[edge][0];
            yOff = directions[edge][1];
            guardPositions[y*131+x] = true;
            continue;
        }
        guardPositions[y*131+x] = true;
        x+=xOff;
        y+=yOff;
    }
    cout << guardPositions.size() << endl;
}
vector<vector<int>> directions = {{0,-1},{1,0},{0,1},{-1,0}};
bool canSolve(vector<string>& lines,int blockX, int blockY, int startX,int startY)
{
    int y = startY;
    int x = startX;
    unordered_map<int,vector<bool>> guardPositions;
    guardPositions[y*131+x] = {false,false,false,false};
    guardPositions[y*131+x][0] = true;
    int edge = 0; //0123 = NESW
    int xOff = directions[edge][0];
    int yOff = directions[edge][1];
    x+=xOff;
    y+=yOff;
    while(x >= 0 && x < lines[0].size() && y >= 0  && y < lines.size())
    {
        if(guardPositions.find(y*131+x) != guardPositions.end() && guardPositions[y*131+x][edge]) return false;
        if(lines[y][x] == '#' || (blockX == x && blockY == y))
        {
            x-=xOff;
            y-=yOff;
            edge++;
            if(edge > 3) edge = 0;
            xOff = directions[edge][0];
            yOff = directions[edge][1];
            continue;
        }
        if(guardPositions.find(y*131+x) == guardPositions.end()) guardPositions[y*131+x] = {false,false,false,false};
        guardPositions[y*131+x][edge] = true;
        x+=xOff;
        y+=yOff;
    }
    return true;
}

vector<int> getPossiblePlaces(vector<string>& lines)
{
    int guardPosRaw = getGuardPos(lines);
    int y = guardPosRaw / 131;
    int x = guardPosRaw % 131;
    unordered_map<int,int> guardPositions;
    guardPositions[y*131+x] = true;
    vector<vector<int>> directions = {{0,-1},{1,0},{0,1},{-1,0}};
    int edge = 0; //0123 = NESW
    int xOff = directions[edge][0];
    int yOff = directions[edge][1];
    x+=xOff;
    y+=yOff;
    while(x >= 0 && x < lines[0].size() && y >= 0  && y < lines.size())
    {
        if(lines[y][x] == '#')
        {
            x-=xOff;
            y-=yOff;
            edge++;
            if(edge > 3) edge = 0;
            xOff = directions[edge][0];
            yOff = directions[edge][1];
            continue;
        }
        guardPositions[y*131+x] = max(0,guardPositions[y*131+x]+1);
        x+=xOff;
        y+=yOff;
    }
    vector<int> places;
    for(auto const& pos: guardPositions)
        places.push_back(pos.first);
    return places;
}

void part2()
{
    vector<string> lines = readInput();
    vector<int> possiblePlaces = getPossiblePlaces(lines);
    int rawGuard = getGuardPos(lines);
    int guardX = rawGuard % 131;
    int gaurdY = rawGuard / 131;
    int total = 0;
    for(int i = 0; i < possiblePlaces.size();i++)
    {
        int x = possiblePlaces[i] % 131;
        int y = possiblePlaces[i] /131;
        if(!canSolve(lines,x,y,guardX,gaurdY)) total++;
    }
    cout << total;
}

int main()
{
    part1();
    part2();
    return 0;
}

