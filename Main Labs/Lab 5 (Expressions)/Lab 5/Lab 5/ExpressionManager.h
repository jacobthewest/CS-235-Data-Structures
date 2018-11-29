/**********************
Jacob West
Lab 05
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#ifndef EXPRESSION_MANAGER_H
#define EXPRESSION_MANAGER_H

#include "ExpressionManagerInterface.h"
using std::string;


class ExpressionManager : public ExpressionManagerInterface {
private:
	std::string infixString;
	std::string postfixString;
	int valueOfExpression;
public:
	//Constructor and destructor
	ExpressionManager(void) {};
	~ExpressionManager(void) {};

	//ExpressionManagerInterface virtual and pure virtual functions
	virtual string toString() const;
	virtual string infix(void);
	virtual string postfix(void);
	virtual int value(void);
	//BONUS: virtual string prefix(void)

	//Functions from the video
	bool isLeftParen(std::string s);
	bool isRightPren(std::string s);
	bool isPair(std::string left, std::string right);
	bool isOperator(string s);
	bool isNumber(string s);
	int precedence(std::string sOperator);

	//Other functions
	bool isBalanced(std::string sExpressionSentence);
	void convertToInfix(std::string sExpressionSentence);
	void calcValFromPostfix(string sExpressionSentence);
	int doMath(int left, string operand, int right);
	void setPostfix(string sExpressionSentence);
	string infixToPostfix(string sExpressionSentence);
	bool illegalOperatorsExist(string sExpression);
	bool isParen(string sCharacter);
	bool isRestOk(string sExpressionSentence);
	bool adjacentOperator(string left, string right);
	bool adjacentOperand(string left, string right);
};
#endif	// EXPRESSION_MANAGER_H