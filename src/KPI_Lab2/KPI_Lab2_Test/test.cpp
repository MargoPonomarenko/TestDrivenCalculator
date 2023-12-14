#include "pch.h"
#include "../KPI_Lab2/KPI_Lab2.h"
#include "../KPI_Lab2/CalculatorState.cpp"


class AlgorithmTest : public ::testing::Test {
protected:
	string fileName;
	string initData;
	vector<string> parsedData;
	void SetUp() override {
		if (getenv("GITHUB_ACTIONS")) {
			fileName = "src/KPI_Lab2/KPI_Lab2/data.txt";
		}
		else {
			/*fileName = "../../../KPI_Lab2/KPI_Lab2/data.txt";*/
			fileName = "../../KPI_Lab2/KPI_Lab2/data.txt";
		}
		initData = readFromFile(fileName);
		parsedData = Parse(initData);
	}

	void TearDown() override {}
};

TEST_F(AlgorithmTest, CheckFileExistence) {
	EXPECT_EQ(isFileExist(fileName), true);
}

TEST_F(AlgorithmTest, CheckFileNonExistence) {
	EXPECT_EQ(isFileExist(""), false);
	EXPECT_EQ(isFileExist("data.txt"), false);
}

TEST_F(AlgorithmTest, ReadingFromFile) {
	string actualData = readFromFile(fileName);
	string expectedData = "1 2 3 + 4 5 6 =";
	EXPECT_EQ(actualData, expectedData);
}

TEST_F(AlgorithmTest, ExeptionReadingFromFile) {
	EXPECT_THROW(readFromFile("data.txt"), runtime_error);
}

TEST_F(AlgorithmTest, CheckParse) {
	vector<string> actualData = Parse(initData);
	vector<string> expectedData = { "1", "2", "3", "+", "4", "5", "6", "=" };
	EXPECT_EQ(actualData, expectedData);
}

TEST_F(AlgorithmTest, CheckParseEmptyString) {
	vector<string> actualData = Parse("");
	vector<string> expectedData = {};
	EXPECT_EQ(actualData, expectedData);
}

TEST_F(AlgorithmTest, CheckParseSpaces) {
	vector<string> actualData = Parse("  1   2 3  +  4 5 6  =  ");
	vector<string> expectedData = { "1", "2", "3", "+", "4", "5", "6", "=" };
	EXPECT_EQ(actualData, expectedData);
}

TEST_F(AlgorithmTest, CheckCalculate) {
	int actualData = Calculate(parsedData);
	int expectedData = 579;
	EXPECT_EQ(actualData, expectedData);
}

TEST(CalculateTest, CheckCalculateEmptyInput) {
	vector<string> parsedData = {};
	int actualData = Calculate(parsedData);
	int expectedData = 0;
	EXPECT_EQ(actualData, expectedData);
}

TEST(CalculateTest, CheckCalculateOneChar) {
	vector<string> parsedData = {"5"};
	int actualData = Calculate(parsedData);
	int expectedData = 5;
	EXPECT_EQ(actualData, expectedData);
}

TEST(CalculateTest, CheckCalculateTwoChars) {
	vector<string> parsedData = { "1", "2" };
	int actualData = Calculate(parsedData);
	int expectedData = 12;
	EXPECT_EQ(actualData, expectedData);
}

TEST(CalculateTest, CheckCalculateSubtraction) {
	vector<string> parsedData = { "1", "0", "-", "1", "0", "0", "="};
	int actualData = Calculate(parsedData);
	int expectedData = -90;
	EXPECT_EQ(actualData, expectedData);
}

TEST(CalculateTest, CheckCalculateMultiplication) {
	vector<string> parsedData = { "1", "0", "*", "2", "2", "=" };
	int actualData = Calculate(parsedData);
	int expectedData = 220;
	EXPECT_EQ(actualData, expectedData);
}

TEST(CalculateTest, CheckCalculateDivision) {
	vector<string> parsedData = { "1", "0", "0", "/", "3", "=" };
	int actualData = Calculate(parsedData);
	int expectedData = 33;
	EXPECT_EQ(actualData, expectedData);
}

TEST(CalculateTest, CheckCalculateRounding) {
	vector<string> parsedData = { "9", "/", "1", "0", "=" };
	int actualData = Calculate(parsedData);
	int expectedData = 0;
	EXPECT_EQ(actualData, expectedData);
}

TEST(CalculateTest, CheckCalculateMissingNumber) {
	vector<string> parsedData = { "1", "2", "3", "+"};
	int actualData = Calculate(parsedData);
	int expectedData = 123;
	EXPECT_EQ(actualData, expectedData);
}

TEST(CalculateTest, CheckCalculateMissingEqual) {
	vector<string> parsedData = { "1", "2", "3", "+", "4", "5", "6"};
	int actualData = Calculate(parsedData);
	int expectedData = 456;
	EXPECT_EQ(actualData, expectedData);
}

TEST(CalculatorStateTest, CheckSetAndGet) {
	CalculatorState calculator;
	calculator.setScreen(12);
	EXPECT_EQ(calculator.getScreen(), 12);
}

TEST(CalculatorStateTest, CheckSetAndGetFirstNumber) {
	CalculatorState calculator;
	calculator.setFirstNumber(10);
	EXPECT_EQ(calculator.getFirstNumber(), 10);
}

TEST(CalculatorStateTest, CheckSetAndGetOperation) {
	CalculatorState calculator;
	calculator.setOperation('-');
	EXPECT_EQ(calculator.getOperation(), '-');
}

TEST(CalculatorStateTest, CheckSetAndGetStartSecondNumber) {
	CalculatorState calculator;
	calculator.setStartSecondNumber(true);
	EXPECT_TRUE(calculator.isStartSecondNumber());
}

TEST(HandleKeyPressTest, CheckDigitInput) {
	CalculatorState calculator;
	HandleKeyPress(calculator, '1');
	EXPECT_EQ(calculator.getScreen(), 1);
}

TEST(HandleKeyPressTest, CheckOperationInput) {
	CalculatorState calculator;
	HandleKeyPress(calculator, '+');
	EXPECT_EQ(calculator.getOperation(), '+');
	EXPECT_EQ(calculator.getFirstNumber(), 0);
	EXPECT_TRUE(calculator.isStartSecondNumber());
}

TEST(HandleKeyPressTest, CheckEqualsInput) {
	CalculatorState calculator;
	calculator.setScreen(2);
	calculator.setFirstNumber(3);
	calculator.setOperation('+');
	calculator.setStartSecondNumber(true);
	HandleKeyPress(calculator, '=');
	EXPECT_EQ(calculator.getScreen(), 5);
	EXPECT_FALSE(calculator.isStartSecondNumber());
}

TEST(HandleKeyPressTest, ExeptionDivisionByZero) {
	CalculatorState calculator;
	calculator.setScreen(5);
	calculator.setFirstNumber(0);
	calculator.setOperation('/');
	HandleKeyPress(calculator, '=');
	EXPECT_THROW(HandleKeyPress(calculator, '='), out_of_range);
}