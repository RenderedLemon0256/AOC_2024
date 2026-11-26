#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "../Helpful_Commands.cpp"
#include <unordered_map>
using namespace std;

struct point
{
    int x;
    int y;
};
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

vector<point> getTrailHeads(vector<string>& lines)
{
    
    vector<point> trailHeads;
    for(int line = 0; line < lines.size();line++)
    {
        for(int i = 0; i < lines[line].size();i++)
        {
            if(lines[line][i] == '0')
            {
                point newPoint;
                newPoint.x = i;
                newPoint.y = line;
                trailHeads.push_back(newPoint);
            }
        }
    }
    return trailHeads;
}

queue<point> searchQueue;

void processPoint(point pt,vector<string>& lines)
{
    int yOff = 0;
    for(int xOff = -1; xOff <= 1;xOff+=2)
    {
        int newX = pt.x+xOff; 
        int newY = pt.y+yOff;
        if(newX < 0 || newX >= lines[0].size())continue;
        int newNum = lines[newY][newX]-'0';
        int currNum = lines[pt.y][pt.x] - '0';
        if( newNum != currNum +1)
        {
            continue;
        }
        point newPt;
        newPt.x = newX;
        newPt.y = newY;
        searchQueue.push(newPt);
    }
    int xOff = 0;
    for(int yOff = -1; yOff <= 1;yOff+=2)
    {
        int newX = pt.x+xOff; 
        int newY = pt.y+yOff;
        if( newY < 0 || newY >= lines.size())continue;
        int newNum = lines[newY][newX]-'0';
        int currNum = lines[pt.y][pt.x] - '0';
        if( newNum != currNum +1)
        {
            continue;
        }
        point newPt;
        newPt.x = newX;
        newPt.y = newY;
        searchQueue.push(newPt);
    }
}

int findTrailHeadScore(point trailHead,vector<string>& lines)
{
    int score = 0;
    unordered_map<int,bool> trailEnds;
    searchQueue.push(trailHead);
    while(searchQueue.size() > 0)
    {
        point newPoint = searchQueue.front();
        searchQueue.pop();
        if(lines[newPoint.y][newPoint.x]-'0' == 9)trailEnds[newPoint.y*76+newPoint.x];
        processPoint(newPoint,lines);
    }
    return trailEnds.size();
}

int findTrailHeadRating(point trailHead,vector<string>& lines)
{
    int score = 0;
    searchQueue.push(trailHead);
    while(searchQueue.size() > 0)
    {
        point newPoint = searchQueue.front();
        searchQueue.pop();
        if(lines[newPoint.y][newPoint.x]-'0' == 9)score++;
        processPoint(newPoint,lines);
    }
    return score;
}

void part1()
{
    vector<string> lines = readInput();
    vector<point> trailHeads = getTrailHeads(lines);
    int total = 0;
    for(point trailHead : trailHeads)
    {
        total += findTrailHeadScore(trailHead,lines);
    }
    cout << total << endl;
}

void part2()
{
    vector<string> lines = readInput();
    vector<point> trailHeads = getTrailHeads(lines);
    int total = 0;
    for(point trailHead : trailHeads)
    {
        total += findTrailHeadRating(trailHead,lines);
    }
    cout << total << endl;
}

int main()
{
    part1();
    part2();
    return 0;
}

