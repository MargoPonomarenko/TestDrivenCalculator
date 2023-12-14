#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "CalculatorState.h"

using namespace std;

bool isFileExist(string fileName) {
    ifstream file;
    file.open(fileName);
    if (file) {
        return true;
    }
    else {
        char errorMessage[256];
        strerror_s(errorMessage, sizeof(errorMessage), errno);
        cerr << "Error while opening file: " << errorMessage << endl;
        return false;
    }
}

string readFromFile(string fileName) {
    ifstream file(fileName);

    if (!isFileExist(fileName)) {
        throw runtime_error("Errors occurred while opening a file  " + fileName);
    }

    string content;
    string line;

    while (getline(file, line)) {
        content += line;
    }

    file.close();

    return content;
}

vector<string> Parse(string input) {
    vector<string> result;
    stringstream ss(input);
    string token;

    while (ss >> token) {
        result.push_back(token);
    }

    return result;
}

void HandleKeyPress(CalculatorState& calculator, char key) {
    // Get the current values of the screen and the first number
    int current_screen = calculator.getScreen();
    int current_first_number = calculator.getFirstNumber();

    // Get the current operation and the new number start flag
    char current_operation = calculator.getOperation();
    bool start_new_number = calculator.isStartSecondNumber();

    // Process the entered keys
    if ('0' <= key && key <= '9') {
        int digit = key - '0';

        if (start_new_number) {
            calculator.setScreen(digit);
        }
        else {
            calculator.setScreen(current_screen * 10 + digit);
        }
        calculator.setStartSecondNumber(false);
    }
    else if (key == '+' || key == '-' || key == '*' || key == '/') {
        // Processing operation symbols
        calculator.setOperation(key);
        calculator.setStartSecondNumber(true);
        calculator.setFirstNumber(current_screen);
    }
    else if (key == '=') {
        switch (current_operation) {
        case '+':
            calculator.setScreen(current_first_number + current_screen);
            break;
        case '-':
            calculator.setScreen(current_first_number - current_screen);
            break;
        case '*':
            calculator.setScreen(current_first_number * current_screen);
            break;
        case '/':
            if (current_screen != 0) {
                calculator.setScreen(current_first_number / current_screen);
            }
            else {
                throw out_of_range("Error: Division by zero");
            }
            break;
        default:
            cerr << "Error: Invalid operation\n";
            break;
        }

        calculator.setStartSecondNumber(false);
    }
    else {
        cerr << "Error: Invalid key\n";
    }
}

int Calculate(vector<string> keyPresses) {
    CalculatorState calculator;

    for (const string& key : keyPresses) {
        if (!key.empty()) {
            char firstChar = key[0];
            HandleKeyPress(calculator, firstChar);
        }
    }

    int result = calculator.getScreen();

    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        if (!keyPresses.empty()) {
            outputFile << result;
        }
        else {
            result = 0;
            outputFile << result;
        }
        outputFile.close();
    }
    else {
        cerr << "Error: Unable to open the output file." << endl;
    }

    return result;
}
