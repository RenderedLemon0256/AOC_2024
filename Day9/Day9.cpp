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

void part1()
{
    string rawLine = readInput()[0]; //only one line in input
    vector<long long> newLine;
    int currId = 0;
    for(int i = 0; i < rawLine.size();i++)
    {
        int character = 0;
        if(i%2==0) //add id
        {
           character = currId;
        }
        if(i%2==1) //add spaces
        {
            character = -1;
        }
        for(int j = 0; j < rawLine[i] - '0';j++)
        {
            newLine.push_back(character);
        }
        if(i%2==1)currId++;
        continue;
    }
    // for(int i:newLine) 
    // {
    //     if(i!=-1)cout << i;
    //     else {cout << '.';}
    // }
    bool swapped = true;
    while(swapped)
    {
        swapped = false;
        int rightIndex = -1;
        for(int i = newLine.size()-1;i >= 0;i--)
        {
            if(newLine[i] == -1)continue; 
            rightIndex = i;
            break;
        }
        if(rightIndex == -1)break;
        int leftIndex = -1;
        for(int i = 0; i < rightIndex;i++)
        {
            if(newLine[i]!=-1)continue;
            leftIndex = i;
            break;
        }
        if(leftIndex == -1)break;
        newLine[leftIndex] = newLine[rightIndex];
        newLine[rightIndex] = -1;
        swapped = true;
    }
    long long total = 0;
    for(int i = 0; i < newLine.size();i++)
    {
        if(newLine[i]==-1)break;
        total += newLine[i] *i;
    }
    cout << total << endl;
  
    
}

void part2()
{
    string rawLine = readInput()[0]; //only one line in input
    vector<long long> newLine;
    vector<int> ids;
    int currId = 0;
    for(int i = 0; i < rawLine.size();i++)
    {
        int character = 0;
        if(i%2==0) //add id
        {
           character = currId;
           ids.push_back(currId);
        }
        if(i%2==1) //add spaces
        {
            character = -1;
        }
        for(int j = 0; j < rawLine[i] - '0';j++)
        {
            newLine.push_back(character);
        }
        if(i%2==1)currId++;
        continue;
    }
    
    while(ids.size() > 0)
    {
        int rightIndex = -1;
        int rightLength = 0;
        for(int i = newLine.size()-1;i >= 0;i--)
        {
            if(rightIndex == -1)
            {
                if (newLine[i] == -1 || newLine[i] >= ids.size())continue; //haven't found first id yet
                rightIndex = i; //found first id
                rightLength++;
                ids.erase(ids.begin()+newLine[rightIndex]);
                continue;
            }
            if (newLine[i] != newLine[rightIndex])break; //end of id block
            rightLength++; //in id block
        }
        if(rightIndex == -1)break;

        int leftIndex = -1;
        int leftLength = 0;
        for(int i = 0;i < rightIndex;i++)
        {
            if(leftIndex == -1)
            {
                if (newLine[i] != -1)continue; //haven't found space yet
                leftIndex = i; //found first space
                leftLength++;
                continue;
            }
            if (newLine[i] != -1)
            {
                if(leftLength >= rightLength)break;//fits
                leftLength = 0; //doesn't fit
                leftIndex = -1;
                continue;
                
            }; //end of space block
            leftLength++; //in space block
        }
        if(leftIndex == -1)continue;;
        if(leftLength < rightLength)continue;;

        for(int i = 0; i < rightLength;i++)
        {
            newLine[leftIndex+i] = newLine[rightIndex-i];
            newLine[rightIndex-i] = -1;
        }
    }
    long long total = 0;
    for(int i = 0; i < newLine.size();i++)
    {
        if(newLine[i]==-1)continue;;
        total += newLine[i] *i;
    }
    cout << total << endl;
    // for(int i:newLine) 
    // {
    //     if(i!=-1)cout << i;
    //     else {cout << '.';}
    // }
}

int main()
{
    part1();
    part2();
    return 0;
}

