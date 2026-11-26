#include <vector>
#include <iostream>
#include <fstream>
#include <string>
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

void part1()
{
    string line = readInput()[0];
    vector<ll> stones = stripNumsLong(line);
    vector<ll> dupStones = vector<ll>(stones.size(),1);
    for(int i = 0; i < 25;i++)
    {
        int size = stones.size();
        for(int j = 0;j<size;j++)
        {
            ll stone = stones[j];
            if(stone == 0){
                stones[j] = 1;
                continue;
            }
            int digitCount = to_string(stone).size();
            if(digitCount % 2 == 0){
                ll leftSide = stone/ pow(10,digitCount/2);
                ll rightSide = stone % int(pow(10,digitCount/2));
                stones[j] = leftSide;
                bool unique = true;
                for(int k = 0; k < j;k++)
                {
                    if(stones[k]==rightSide){
                        dupStones[k]+=dupStones[j];
                        unique = false;
                        break;
                    }
                }
                if(unique){
                    stones.push_back(rightSide);
                    dupStones.push_back(dupStones[j]);
                }
                continue;
            }
            stones[j] *= 2024;
        }
    }
    ll total = 0;
    for(ll i : dupStones)
    {
        total+=i;
    }
    cout << total << endl;
}

void part2()
{
    string line = readInput()[0];
    vector<ll> stones = stripNumsLong(line);
    vector<ll> dupStones = vector<ll>(stones.size(),1);
    for(int i = 0; i < 75;i++)
    {
        int size = stones.size();
        for(int j = 0;j<size;j++)
        {
            ll stone = stones[j];
            if(stone == 0){
                stones[j] = 1;
                continue;
            }
            int digitCount = to_string(stone).size();
            if(digitCount % 2 == 0){
                ll leftSide = stone/ pow(10,digitCount/2);
                ll rightSide = stone % int(pow(10,digitCount/2));
                stones[j] = leftSide;
                bool unique = true;
                for(int k = 0; k < j;k++)
                {
                    if(stones[k]==rightSide){
                        dupStones[k]+=dupStones[j];
                        unique = false;
                        break;
                    }
                }
                if(unique){
                    stones.push_back(rightSide);
                    dupStones.push_back(dupStones[j]);
                }
                continue;
            }
            stones[j] *= 2024;
        }
        vector<ll> newStones;
        vector<ll> newDupStones;
        for(int i = 0; i < stones.size();i++)
        {
            bool dup = false;
            for(int j = 0; j<newStones.size();j++)
            {
                if(newStones[j]==stones[i])
                {
                    newDupStones[j] += dupStones[i];
                    dup = true;
                }
            }
            if(dup)continue;
            newStones.push_back(stones[i]);
            newDupStones.push_back(dupStones[i]);
        }
        stones = newStones;
        dupStones = newDupStones;
    }
    ll total = 0;
    for(ll i : dupStones)
    {
        total+=i;
    }
    cout << total << endl;
}

int main()
{
    part1();
    part2();
    return 0;
}

