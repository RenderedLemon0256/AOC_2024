#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "../Helpful_Commands.cpp"
using namespace std;

vector<vector<int>> readInput()
{
    string fileLine;
    fstream file("input.txt");
    vector<vector<int>> lines;
    while(getline(file,fileLine))
    {
        lines.push_back(stripNumsInt(fileLine));
    }
    return lines;
}

bool isReportSafe(vector<int> report)
{
    int dir = -1;
    for(int i = 1; i < report.size();i++)
    {
        int curDir = report[i] > report[i-1];
        if(dir == -1) {dir = curDir;}
        else if(curDir != dir) {return false;}

        int diff = abs(report[i] - report[i-1]);
        if(diff < 1 || diff > 3) {return false;}
    }
    return true;
}

void part1()
{
    vector<vector<int>> reports = readInput();
    int total = 0;
    for(vector<int> report : reports)
    {
        total += isReportSafe(report);
    }
    cout << total << endl;
}

bool isReportSafeDamp(vector<int> report)
{
    int safe = isReportSafe(report);
    for(int i = 0; i < report.size();i++)
    {
        vector<int> cutReport = report;
        cutReport.erase(cutReport.begin()+i);
        safe = isReportSafe(cutReport);
        if(safe) {return true;}
    }
    return false;
}

void part2()
{
    vector<vector<int>> reports = readInput();
    int total = 0;
    for(vector<int> report : reports)
    {
        total += isReportSafeDamp(report);
    }
    cout << total;
}

int main()
{
    part1();
    part2();
    return 0;
}