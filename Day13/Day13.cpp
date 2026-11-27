#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "../Helpful_Commands.cpp"
#include <unordered_map>
#include <deque>
#include <cmath>
using namespace std;
typedef long long ll;

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
struct node
{
    int x;
    int y;
    int aPresses;
    int bPresses;
};
deque<node> searchQueue;
unordered_map<int,bool> visitedNodes;
vector<int> buttonA;
vector<int> buttonB;
vector<int> target;

void processNode(node currNode)
{
    visitedNodes[currNode.x+currNode.y*20000] = true;
    if(currNode.aPresses < 100)
    {
        node aNode;
        aNode.x = currNode.x + buttonA[0];
        aNode.y = currNode.y + buttonA[1];
        if(aNode.x <= target[0] && aNode.y <= target[1] && visitedNodes.find(aNode.x+aNode.y*20000) == visitedNodes.end())
        {
            aNode.aPresses = currNode.aPresses+1;
            aNode.bPresses = currNode.bPresses;
            searchQueue.push_front(aNode);
        }
    }
    if(currNode.bPresses < 100)
    {
        node bNode;
        bNode.x = currNode.x + buttonB[0];
        bNode.y = currNode.y + buttonB[1];
        if(bNode.x <= target[0] && bNode.y <= target[1]&& visitedNodes.find(bNode.x+bNode.y*20000) == visitedNodes.end())
        {
            bNode.aPresses = currNode.aPresses;
            bNode.bPresses = currNode.bPresses+1;
            searchQueue.push_front(bNode);
        }
    }
}

int getTicketsRequire(vector<int>&target)
{
    visitedNodes.clear();
    while(searchQueue.size() > 0)searchQueue.pop_back();
    node startNode;
    startNode.x = 0;
    startNode.y = 0;
    startNode.aPresses = 0;
    startNode.bPresses = 0;
    searchQueue.push_front(startNode);
    while(searchQueue.size()>0)
    {
        node nextNode = searchQueue.front();
        searchQueue.pop_front();
        if(nextNode.x == target[0] && nextNode.y == target[1]){
            return nextNode.aPresses * 3 + nextNode.bPresses;}
        processNode(nextNode);
    }
    return 0;
}

void part1()
{
    vector<string> lines = readInput();
    int total = 0;
    for(int i = 2; i < lines.size();i+=4){
        buttonA = stripNumsInt(lines[i-2]);
        buttonB = stripNumsInt(lines[i-1]);
        target = stripNumsInt(lines[i]);
        total += getTicketsRequire(target);
    }
    cout << total << endl;
}

vector<ll> longTarget;

ll getTicketsRequiredCramer()
{
    ll c1 = longTarget[0];
    ll c2 = longTarget[1];
    ll a1 = buttonA[0];
    ll a2 = buttonA[1];
    ll b1 = buttonB[0];
    ll b2 = buttonB[1];
    double x = double(double(c1*b2) - double(b1*c2))/double(double(a1*b2)-double(b1*a2));
    double y = double(double(c2*a1) - double(a2*c1))/double(double(a1*b2)-double(b1*a2));
    if(round(x) != x)return 0;
    if(round(y) !=y) return 0;
    return ll(x) * 3 + ll(y);
}

void part2()
{
   vector<string> lines = readInput();
    ll total = 0;
    for(int i = 2; i < lines.size();i+=4){
        buttonA = stripNumsInt(lines[i-2]);
        buttonB = stripNumsInt(lines[i-1]);
        longTarget = stripNumsLong(lines[i]);
        longTarget[0] += 10000000000000;
        longTarget[1] += 10000000000000;
        total += getTicketsRequiredCramer();
    }
    cout << total << endl;
}

int main()
{
    //part1();
    part2();
    return 0;
}
