#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
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
bool lineIsRule(string line)
{
    if(line == "") return false;
    return line[2] == '|';
}
vector<vector<int>> getRulesFromInput(vector<string> lines)
{
    vector<vector<int>> rules;
    for(string line : lines)
    {
        if(!lineIsRule(line)) {continue;}
        vector<int> nums = stripNumsInt(line);
        rules.push_back(nums);
    }
    return rules;
}

bool lineIsUp(string line)
{
    if(line == "") return false;
    return line[2] == ',';
}

vector<vector<int>> getUpsFromInput(vector<string> lines)
{
    vector<vector<int>> updates;
    for(string line: lines)
    {
        if(!lineIsUp(line)) {continue;}
        updates.push_back(stripNumsInt(line));
    }
    return updates;
}
vector<vector<int>> rules;


bool updateIsValid(vector<int> update)
{
    // int listIndex = 0;
    // for(int num : update)
    // {
    //     while(list[listIndex] != num && listIndex < 99)
    //     {
    //         listIndex++;
    //     }
    //     if(listIndex == 99) {return false;}
    // }
    // return true;

    for(int i = 0; i < update.size()-1;i++)
    {
        for(int j = i+1; j < update.size();j++)
        {
            for(vector<int> rule : rules)
            {
                if(rule[0] == update[j] && rule[1] == update[i]) {
                    return false;}
            }
        }
    }
    return true;
}


bool comp (int a, int b)
{
    for(vector<int> rule : rules)
    {
        if(rule[0] == b && rule[1] == a) {return true;}
    }
    return false;
}

void part1()
{
    vector<string> lines = readInput();
    rules = getRulesFromInput(lines);
    vector<vector<int>> updates = getUpsFromInput(lines);
    // vector<int> list = vector<int>(100);
    // sort(list.begin(),list.end(),comp);
    int total = 0;
    for(vector<int> update : updates)
    {
        if(updateIsValid(update)){
            total += update[(update.size()-1)/2];
        }
    }
    cout << total << endl;
}

void part2()
{
     vector<string> lines = readInput();
    rules = getRulesFromInput(lines);
    vector<vector<int>> updates = getUpsFromInput(lines);
    // vector<int> list = vector<int>(100);
    // sort(list.begin(),list.end(),comp);
    int total = 0;
    for(vector<int> update : updates)
    {
        if(!updateIsValid(update)){
            sort(update.begin(),update.end(),comp);
            total += update[(update.size()-1)/2];
        }
    }
    cout << total;
}

int main()
{
    part1();
    part2();
    return 0;
}

