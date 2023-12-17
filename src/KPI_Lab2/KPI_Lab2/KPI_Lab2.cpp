#include <iostream>
#include "KPI_Lab2.h"

using namespace std;

int main()
{
    string fileName;
    cout << "Enter file name with condition for calculation: ";
    cin >> fileName;

    string initData = readFromFile(fileName);
    vector<string> result = Parse(initData);

    int resultCalulation = Calculate(result);
    cout << "Result: " << resultCalulation << endl;
}