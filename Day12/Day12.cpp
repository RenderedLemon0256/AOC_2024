#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <unordered_map>
#include "../Helpful_Commands.cpp"
using namespace std;

struct point
{
    int x;
    int y;
    vector<bool> edges;
    point(int xIn, int yIn)
    {
        x = xIn;
        y = yIn;
        edges = {true,true,true,true};
    }
    friend bool operator==(point& lhs, point& rhs)
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

};

struct region
{
    vector<point> squares;
    char plant;
    unordered_map<int,vector<bool>> squaresMap;
    void addSquare(point pt)
    {
        for (int i = 0;i <squares.size();i++)
        {
            int xDiff = squares[i].x-pt.x;
            int yDiff = squares[i].y-pt.y;
            if(xDiff == 1 && yDiff == 0) {
                squares[i].edges[0] = false;
                squaresMap[squares[i].x*141+squares[i].y][0] = false;
                pt.edges[2] = false;
            }
            if(xDiff == -1 && yDiff == 0) {
                squares[i].edges[2] = false;
                squaresMap[squares[i].x*141+squares[i].y][2] = false;
                pt.edges[0] = false;
            }
            if(yDiff == 1 && xDiff == 0){
                squares[i].edges[3] = false;
                squaresMap[squares[i].x*141+squares[i].y][3] = false;
                pt.edges[1] = false;
            }
            if(yDiff == -1 && xDiff == 0){
                squares[i].edges[1] = false;
                squaresMap[squares[i].x*141+squares[i].y][1] = false;
                pt.edges[3] = false;
            }
        }
        squares.push_back(pt);
        squaresMap[pt.y + (pt.x*141)] = pt.edges;
    }
    bool squareInRegion(int x, int y) const
    {
        if(squaresMap.find(y + (x * 141)) == squaresMap.end()) {return false;}
        return true;
    }
    int getArea() const
    {
        return squares.size();
    }
    int getPerimeter() const
    {
        int total = 0;
        for(point square : squares)
        {
            for(bool edge : square.edges)
            {
                total += edge;
            }
        }
        return total;
    }
    int getSides() const
    {
        //start with first point and find it's first edge
        unordered_map<int,vector<bool>> newEdges;
        int total = 0;
        while(true)
        {
        int edge = 0; //0123 -> NESW
        int xOff = 0;
        int yOff = 0;
        int startX = 0;
        int startY = 0;
        for(int j = 0; j < squares.size();j++)
        {
            point pt = squares[j];
            for(int i = 0;i < 4;i++)
            {
                if(newEdges.find(pt.x*141 + pt.y) != newEdges.end()){
                    if(!newEdges.at(pt.x*141 + pt.y)[i]) continue; 
                    newEdges[pt.x*141 + pt.y][i] = false;
                    edge = i;
                    xOff = (((i) % 2) *(i-2))*-1; 
                    yOff = ((i+1) % 2) *((i*-1)+1);
                    startX = pt.x;
                    startY = pt.y;
                    j = squares.size();
                    break;
                }
                else 
                {   if(!squaresMap.at(pt.x*141+pt.y)[i]) continue;
                    newEdges[pt.x * 141 + pt.y] = squaresMap.at(pt.x*141+pt.y);
                    newEdges[pt.x * 141 + pt.y][i] = false;
                    edge = i;
                    xOff = (((i) % 2) *(i-2))*-1;  //works out rather than doing the 4 if statements
                    yOff = ((i+1) % 2) *((i*-1)+1);
                    startX = pt.x;
                    startY = pt.y;
                    j = squares.size();
                    break;
                }
            }
        }
        if(!edge && !xOff && !yOff) break;
        
        int startEdge = edge;
        int sides = 0; //we start at zero instead of 1 because of the duplicated edge at the end
        //we go right until we hit a point that doesn't have (top) edge
        int x = startX + xOff; //starting with them offset so it doesn't trigger the completed check
        int y = startY + yOff;
        while(x != startX || y != startY || edge != startEdge)
        {
            //if the point isn't in the region at all, we know that we have a 90 degree turn clockwise
            if(!squareInRegion(x,y))
            {
                sides++;
                x-=xOff;
                y-=yOff;
                if(newEdges.find(x*141+y)==newEdges.end()) newEdges[x*141+y] = squaresMap.at(x*141+y);
                newEdges[x*141+y][edge] = false;

                edge++;
                if(edge > 3) edge = 0;
                xOff = ((edge % 2) *(edge-2))*-1;  
                yOff = ((edge+1) % 2) *((edge*-1)+1);
                
                continue;
            }
            if(newEdges.find(x*141+y) != newEdges.end())
            {
                if(newEdges.at(x*141+y)[edge])
                {
                newEdges[x*141+y][edge] = false;
                x+=xOff;
                y+=yOff;
                continue;
                }
            }
            else{
                newEdges[x*141+y] = squaresMap.at(x*141+y);
                newEdges[x*141+y][edge] = false;
                if(squaresMap.at(x*141+y)[edge]) {
                x+=xOff;
                y+=yOff;
                continue;
                }
            }

            //if it is in the region, we have a 90 degree turn anti-clockwise
            newEdges[x*141+y][edge] = false;
            sides++;
            edge--;
            if(edge < 0) edge = 3;
            xOff = ((edge % 2) *(edge-2))*-1;  
            yOff =  ((edge+1) % 2) *((edge*-1)+1);
            x+=xOff;
            y+=yOff;
            //repeat this algorithm until we hit the first point on the same edge
        }
        total += sides;
        }
        return total;
    }
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

vector<int> getAdjCompRegions(const point& pt, char plant, const vector<string>& lines, const vector<region>& regions)
{
    vector<int> adjRegions;
    for(int i = 0; i < regions.size();i++)
        {
            if(regions[i].plant != plant) continue;
            if(regions[i].squareInRegion(pt.x-1,pt.y)) {
                bool dup = false;
                for(int j : adjRegions) if(j== i) dup=true;
                if(!dup) adjRegions.push_back(i); 
            }
            if(regions[i].squareInRegion(pt.x,pt.y-1)) {
                bool dup = false;
                for(int j : adjRegions) if(j== i) dup=true;
                if(!dup) adjRegions.push_back(i); 
            }
        }
    return adjRegions;
}

void part1()
{
    vector<string> lines = readInput();
    vector<region> regions;
    for(int x = 0; x < lines.size();x++)
    {
        for(int y = 0; y < lines[0].size();y++)
        {
            point pt(x,y);
            char plant = lines[x][y];
            vector<int> adjCompRegions = getAdjCompRegions(pt,plant,lines,regions);
            if(adjCompRegions.size() > 2) cout << "ERROR";
            if(adjCompRegions.size() == 2){
                int reg1 = adjCompRegions[0];
                int reg2 = adjCompRegions[1];
                if(regions[reg1].squares.size() >= regions[reg2].squares.size())
                {
                    regions[reg1].addSquare(pt);
                    for(point square : regions[reg2].squares)
                    {
                        regions[reg1].addSquare(square);
                    }
                    regions.erase(regions.begin() + reg2);
                }
                else
                {
                    regions[reg2].addSquare(pt);
                    for(point square : regions[reg1].squares)
                    {
                        regions[reg2].addSquare(square);
                    }
                    regions.erase(regions.begin() + reg1);
                }
                continue;
            }
            if(adjCompRegions.size() == 1)
            {
                regions[adjCompRegions[0]].addSquare(pt);
                continue;
            }
            if(adjCompRegions.size() == 0)
            {
                region newRegion;
                newRegion.addSquare(pt);
                newRegion.plant = plant;
                regions.push_back(newRegion);
            }
        }
        
    }
    int total = 0;
    int total2 = 0;
    for(const region reg : regions)
    {
        int area =  reg.getArea();
        int perm = reg.getPerimeter();
        total += area*perm; 
        int sides = reg.getSides();
        total2 += area*sides;
        cout << "x";
    }
    cout << endl;
    cout << total << endl;
    cout << total2 << endl;
}

int main()
{
    part1();
    return 0;
}
