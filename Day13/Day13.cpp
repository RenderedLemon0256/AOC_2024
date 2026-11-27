#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "../Helpful_Commands.cpp"
#include <unordered_map>
#include <deque>
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

struct longNode
{
    ll x;
    ll y;
    ll aPresses;
    ll bPresses;
};
deque<longNode> longSearchQueue;
vector<ll> longTarget;

void processLongNode(longNode currNode)
{
    longNode aNode;
    aNode.x = currNode.x + buttonA[0];
    aNode.y = currNode.y + buttonA[1];
    if(aNode.x <= target[0] && aNode.y <= target[1])
    {
        aNode.aPresses = currNode.aPresses+1;
        aNode.bPresses = currNode.bPresses;
        longSearchQueue.push_front(aNode);
    }
    
    longNode bNode;
    bNode.x = currNode.x + buttonB[0];
    bNode.y = currNode.y + buttonB[1];
    if(bNode.x <= target[0] && bNode.y <= target[1])
    {
        bNode.aPresses = currNode.aPresses;
        bNode.bPresses = currNode.bPresses+1;
        longSearchQueue.push_front(bNode);
    }
}

ll getTicketsLongRequire(vector<ll>&longTarget)
{
    while(longSearchQueue.size() > 0)longSearchQueue.pop_back();
    longNode startNode;
    startNode.x = 0;
    startNode.y = 0;
    startNode.aPresses = 0;
    startNode.bPresses = 0;
    longSearchQueue.push_front(startNode);
    while(longSearchQueue.size()>0)
    {
        longNode nextNode = longSearchQueue.front();
        longSearchQueue.pop_front();
        if(nextNode.x == target[0] && nextNode.y == target[1]){
            cout << "x";
            return nextNode.aPresses * 3 + nextNode.bPresses;}
        processLongNode(nextNode);
    }
    return 0;
}

void part2()
{
    vector<string> lines = readInput();
    int total = 0;
    for(int i = 2; i < lines.size();i+=4){
        buttonA = stripNumsInt(lines[i-2]);
        buttonB = stripNumsInt(lines[i-1]);
        longTarget = stripNumsLong(lines[i]);
        longTarget[0] +=  10000000000000;
        longTarget[1] +=  10000000000000;

        total += getTicketsLongRequire(longTarget);
    }
    cout << total;
}

int main()
{
    part1();
    part2();
    return 0;
}
