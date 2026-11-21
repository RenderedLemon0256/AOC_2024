#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "../Helpful_Commands.cpp"
using namespace std;

tuple<vector<int>,vector<int>> readInput()
{
    vector<int> listOne;
    vector<int> listTwo;
    string fileLine;
    fstream file("input.txt");
    while(getline(file,fileLine))
    {
        vector<int> nums = stripNumsInt(fileLine);
        listOne.push_back(nums[0]);
        listTwo.push_back(nums[1]);
    }
    return tuple<vector<int>,vector<int>>(listOne,listTwo);
}

void part1()
{
    tuple<vector<int>,vector<int>> lists = readInput();
    vector<int> listOne = get<0>(lists);
    vector<int> listTwo = get<1>(lists);
    sort(listOne.begin(),listOne.end());
    sort(listTwo.begin(),listTwo.end());
    
    int total = 0;
    for(int i = 0; i < listOne.size();i++)
    {
        total += abs(listOne[i] - listTwo[i]);
    }
    cout << total << endl;
}

void part2()
{
    tuple<vector<int>,vector<int>> lists = readInput();
    vector<int> listOne = get<0>(lists);
    vector<int> listTwo = get<1>(lists);

    int total = 0;
    for(int i : listOne)
    {
        int count = 0;
        for(int j : listTwo){if(i == j) {count++;}}
        total += count * i;
    }
    cout << total;
}

int main()
{
    part1();
    part2();
    return 0;
}

