#ifndef CALCULATOR_TESTER_HPP
#define CALCULATOR_TESTER_HPP
#include "Calculator.h"
using namespace std;

class Tester {
public:

    void run()
    {
        failedTests = 0;
        // Level 0
        TestAddition();
        TestSubtraction();
        TestMultiplication();
        TestDivision();
        TestFormulaWithSpaces();

        // Level 1
        TestRoot();
        TestPow();
        TestFractional();
        TestComplicatedFormula_noBrackets();
        TestComplicatedFormula_root();
        TestComplicatedFormula_rootAndPower();
        TestErroneousFormula_rootTypoNoBrackets();

        // Boss fight
        TestComplicatedFormula_brackets();
        TestComplicatedFormula_bracketsBeforeRoot();
        TestComplicatedFormula_bracketsAfterRoot();
        TestErroneousFormula_missingOpeningBracket();
        TestErroneousFormula_missingClosingBracket();
        TestErroneousFormula_missing_param();

        // Extras
        std::cout << "Extra tests:" << std::endl;
        TestDivisionByZero();
        TestEmptyFormula();
        TestBackwardsBrackets();
        TestNonMath();
        TestNegativeNr();
        TestNegativeWithBrackets();
        TestSqrtOfNegative();
        TestOnlyParentheses();

        evaluateTestOutcomes();

    }

private:
    int failedTests;

    void TestAddition()
    {
        Calculator c;
        double result = c.evaluate("10+-2");
        checkResult(8, result);
    }

    void TestSubtraction()
    {
        Calculator c;
        double result = c.evaluate("10-2");
        checkResult(8, result);
    }

    void TestMultiplication()
    {
        Calculator c;
        double result = c.evaluate("3*2");
        checkResult(6, result);
    }

    void TestDivision()
    {
        Calculator c;
        double result = c.evaluate("10/3");
        checkResult(3.3, result, 0.05);
    }
    void TestFormulaWithSpaces()
    {
        Calculator c;
        double result = c.evaluate(" 10 / 3*2 +   8 ");
        checkResult(14.7, result, 0.05);
    }

    void TestPow()
    {
        Calculator c;
        double result = c.evaluate("10^3");
        checkResult(1000, result);
    }

    void TestRoot()
    {
        Calculator c;
        double result = c.evaluate("3root125");
        checkResult(5, result, 0.05); // cubic root needs a bit of a threshold...
    }

    void TestFractional()
    {
        Calculator c;
        double result = c.evaluate("2.3+2.7");
        checkResult(5, result);
    }

    void TestComplicatedFormula_noBrackets()
    {
        Calculator c;
        double result = c.evaluate("12+20*3-50/2+3");
        checkResult(50, result);
    }

    void TestComplicatedFormula_root()
    {
        Calculator c;
        double result = c.evaluate("12+2*2root25+3");
        checkResult(25, result);
    }

    void TestComplicatedFormula_rootAndPower()
    {
        Calculator c;
        double result = c.evaluate("12+2*2root25+10^4+6-3");
        checkResult(10025, result);
    }

    void TestErroneousFormula_rootTypoNoBrackets()
    {
        Calculator c;
        // calculator prints an error msg and returns with 0
        double result = c.evaluate("12+2*2rwot25+10^4+6-3");
        checkResult(0, result);
    }

    void TestComplicatedFormula_brackets()
    {
        Calculator c;
        double result = c.evaluate("2root(22+(33-2root25+14)*2+(5-2))");
        checkResult(10.4403d, result, 0.01d);
    }

    void TestComplicatedFormula_bracketsBeforeRoot()
    {
        Calculator c;
        double result = c.evaluate("((2+2)*2-6)root25+10^4+6-3");
        checkResult(10008, result);
    }

    void TestComplicatedFormula_bracketsAfterRoot()
    {
        Calculator c;
        double result = c.evaluate("2root((10-5)*4/(2+80))");
        checkResult(0.493, result, 0.01);
    }

    void TestErroneousFormula_missingOpeningBracket()
    {
        Calculator c;
        double result = c.evaluate("(2+2)*2-6)root25+10^4+6-3");
        checkResult(0, result);
    }

    void TestErroneousFormula_missingClosingBracket()
    {
        Calculator c;
        double result = c.evaluate("((2+2)*2-6root25+10^4+6-3");
        checkResult(0, result);
    }

    void TestErroneousFormula_missing_param()
    {
        Calculator c;
        double result = c.evaluate("12+2*root25+10^4+6-3");
        checkResult(0, result);
    }

    void checkResult(const double expected, const double actual, const double threshold = 0.0d)
    {
        if( actual >= expected - threshold &&
            actual <= expected + threshold )
        {
            cout << "Test ran OK." << endl;
        }else{
            cout << "Invalid result! Expected: " << expected << " actual: " << actual << endl;
            ++failedTests;
        }
    }

    void evaluateTestOutcomes()
    {
        if(0 != failedTests){
            cout << failedTests << " tests failed." << endl;
        }else{
            cout << "All tests passed!" << endl;
        }
    }

    // Extra

    void TestDivisionByZero() {
        Calculator c;
        double result = c.evaluate("5/0");
        checkResult(0, result);
    }

    void TestBackwardsBrackets() {
        Calculator c;
        double result = c.evaluate(")3+4(");
        checkResult(0, result);
    };

    void TestEmptyFormula(){
        Calculator c;
        double result = c.evaluate("");
        checkResult(0, result);
    }

    void TestNonMath(){
        Calculator c;
        double result = c.evaluate("Asd(2+2)fasdfa");
        checkResult(0, result);
    }

    void TestNegativeNr() {
        Calculator c;
        double result = c.evaluate("-2-3");
        checkResult(-5, result);
    }

    void TestNegativeWithBrackets() {
        Calculator c;
        double result = c.evaluate("-2-(-1-2)");
        checkResult(1, result);
    }

    void TestSqrtOfNegative() {
        Calculator c;
        double result = c.evaluate("2root-4");
        checkResult(0, result);
    }

    void TestOnlyParentheses() {
        Calculator c;
        double result = c.evaluate("((()((()))()))");
        checkResult(0, result);
    }
};



#endif //CALCULATOR_TESTER_HPP
