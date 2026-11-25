#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <cmath>
#include "../Helpful_Commands.cpp"
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
    vector<char> ops;
};
 
bool hitsTarget(vector<ll>& nums, node& currNode)
{
    ll total = nums[1];
    if(currNode.ops.size() != nums.size()-2)return false;
    for (int i = 0; i < currNode.ops.size();i++)
    {
        if(currNode.ops[i] == '*') total *= nums[i+2];
        if(currNode.ops[i] == '+') total += nums[i+2];
        if(currNode.ops[i] == '|') total = total * pow(10,to_string(nums[i+2]).size()) + nums[i+2];
    }
    if(total == nums[0]) return true;
    return false;
}

deque<node> searchQueue;
int maxNodeDepth= 0;
void processNode(node currNode)
{
    if(currNode.ops.size() >= maxNodeDepth)return;

    node addNode;
    addNode.ops = currNode.ops;
    addNode.ops.push_back('+');

    node timesNode;
    timesNode.ops = currNode.ops;
    timesNode.ops.push_back('*');

    node catNode;
    catNode.ops = currNode.ops;
    catNode.ops.push_back('|');

    searchQueue.push_front(addNode);
    searchQueue.push_front(timesNode);
    searchQueue.push_front(catNode);
}

bool LinePossible(string line)
{
    //dfs through the possible operators
    vector<ll> nums = stripNumsLong(line);
    maxNodeDepth = nums.size() -2;
    node startNode;
    searchQueue.push_front(startNode);
    while(searchQueue.size() > 0)
    {
        node newNode = searchQueue.front();
        searchQueue.pop_front();
        if(hitsTarget(nums,newNode))return true;
        processNode(newNode);
    }
    return false;
}

void part1()
{
    vector<string> lines = readInput();
    ll total = 0;
    for(string line : lines)
    {
        if(LinePossible(line))total+= stripNumsLong(line)[0];
    }
    cout << total;
}

void part2()
{

}

int main()
{
    part1();
    part2();
    return 0;
}

