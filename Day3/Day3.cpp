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

enum functPart
{
    MUL,
    NUM1,
    COMMA,
    NUM2,
    BRACKET,
    NONE,
    DIS,
    DO,
    DONT
};

void part1()
{
    vector<string> lines = readInput();
    string mul = "mul(";
    int mulIndex = -1;
    int num1 = -1;
    int num2 = -1;
    int total = 0;
    functPart part = NONE;
    for(string line : lines)
    {
    for(char letter : line)
    {
        if(part == NONE && letter == 'm')
        {
            mulIndex = 1;
            part = MUL;
            continue;
        }
        if(part == MUL)
        {
            if(letter == mul[mulIndex])
            {
                mulIndex++;
                if(mulIndex > 3)
                {
                    part = NUM1;
                    continue;
                }
            }
            else
            {
                part = NONE;
                continue;
            }
        }
        if(part == NUM1)
        {
            if(letter - '0' > 9 || letter - '0' < 0)
            {
                if(letter != ','){
                num1 = -1;
                part =NONE;
                continue;
                }
                part = NUM2;
                continue;
            }
            if(num1 == -1) {
                num1 = letter - '0';
                continue;
            }
            if(to_string(num1).size() == 3){
                num1 = -1;
                part =NONE;
                continue;
            }
            num1 *= 10;
            num1 += letter - '0';
        }
        if(part == NUM2)
        {
            if(letter - '0' > 9 || letter - '0' < 0)
            {
                if(letter != ')'){
                num1 = -1;
                num2 = -1;
                part =NONE;
                continue;
                }
                total += num1 * num2;
                num1  = -1;
                num2 = -1;
                part = NONE;
                continue;
            }
            if(num2 == -1) {
                num2 = letter - '0';
                continue;
            }
            if(to_string(num2).size() == 3){
                num1 = -1;
                num2 = -1;
                part =NONE;
                continue;
            }
            num2 *= 10;
            num2 += letter - '0';
        }
    }
    }
    cout << total << endl;
}


void part2()
{
    vector<string> lines = readInput();
    string mul = "mul(";
    int mulIndex = -1;
    string dont = "don't()";
    int dontIndex = -1;
    string doStr = "do()";
    string dis = "do";
    int disIndex = -1;
    int doIndex = -1;
    int num1 = -1;
    int num2 = -1;
    int total = 0;
    bool active = true;
    functPart part = NONE;
    for(string line : lines)
    {
    for(int i = 0; i < line.size();i++)
    {
        char letter = line[i];
        if(part == NONE && letter == 'm')
        {
            mulIndex = 1;
            part = MUL;
            continue;
        }
        if(part == MUL)
        {
            if(letter == mul[mulIndex])
            {
                mulIndex++;
                if(mulIndex > 3)
                {
                    part = NUM1;
                    continue;
                }
            }
            else
            {
                part = NONE;
                continue;
            }
        }
        if(part == NUM1)
        {
            if(letter - '0' > 9 || letter - '0' < 0)
            {
                if(letter != ','){
                num1 = -1;
                part =NONE;
                continue;
                }
                part = NUM2;
                continue;
            }
            if(num1 == -1) {
                num1 = letter - '0';
                continue;
            }
            if(to_string(num1).size() == 3){
                num1 = -1;
                part =NONE;
                continue;
            }
            num1 *= 10;
            num1 += letter - '0';
        }
        if(part == NUM2)
        {
            if(letter - '0' > 9 || letter - '0' < 0)
            {
                if(letter != ')'){
                num1 = -1;
                num2 = -1;
                part =NONE;
                continue;
                }
                if(active){total += num1 * num2;}
                num1  = -1;
                num2 = -1;
                part = NONE;
                continue;
            }
            if(num2 == -1) {
                num2 = letter - '0';
                continue;
            }
            if(to_string(num2).size() == 3){
                num1 = -1;
                num2 = -1;
                part =NONE;
                continue;
            }
            num2 *= 10;
            num2 += letter - '0';
        }
        if(part == NONE && letter == 'd')
        {
            part = DIS;
            disIndex = 1;
            continue;
        }
        if(part == DIS)
        {
            if(disIndex > 1)
            {
                if(letter == '(')
                {
                    part = DO;
                    doIndex = 3;
                    continue;
                }
                if(letter = 'n')
                {
                    part = DONT;
                    dontIndex = 3;
                    continue;
                }
                part = NONE;
                i--;
                continue;
            }
            if(letter=dis[disIndex]){disIndex++;}
            else
            {
                part = NONE;
                i--;
                continue;
            }
        }
        if(part == DO)
        {
            if(doIndex >= doStr.size()){
                active = true;
                part = NONE;
                i--;
                continue;
            }
            if(letter=doStr[doIndex]){doIndex++;}
            else
            {
                part = NONE;
                i--;
                continue;
            }
        }
        if(part == DONT)
        {
            if(dontIndex >= dont.size()){
                active = false;
                part = NONE;
                i--;
                continue;
            }
            if(letter=dont[dontIndex]){dontIndex++;}
            else
            {
                part = NONE;
                i--;
                continue;
            }
        }
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

