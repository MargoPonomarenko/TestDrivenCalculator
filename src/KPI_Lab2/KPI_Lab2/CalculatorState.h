#ifndef CALCULATORSTATE_H
#define CALCULATORSTATE_H

class CalculatorState {
private:
    int screen;
    int first_number;
    char operation;
    bool start_second_number;

public:
    CalculatorState() : screen(0), first_number(0), operation('+'), start_second_number(false) {}
    void setScreen(int value);
    int getScreen() const;
    void setFirstNumber(int value);
    int getFirstNumber() const;
    void setOperation(char op);
    char getOperation() const;
    void setStartSecondNumber(bool flag);
    bool isStartSecondNumber() const;
};

#endif // CALCULATORSTATE_H