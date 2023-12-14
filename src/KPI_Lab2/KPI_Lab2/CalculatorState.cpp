#include "CalculatorState.h"

void CalculatorState::setScreen(int value) {
    screen = value;
}

int CalculatorState::getScreen() const {
    return screen;
}

void CalculatorState::setFirstNumber(int value) {
    first_number = value;
}

int CalculatorState::getFirstNumber() const {
    return first_number;
}

void CalculatorState::setOperation(char op) {
    operation = op;
}

char CalculatorState::getOperation() const {
    return operation;
}

void CalculatorState::setStartSecondNumber(bool flag) {
    start_second_number = flag;
}

bool CalculatorState::isStartSecondNumber() const {
    return start_second_number;
}