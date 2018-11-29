/**********************
Jacob West
Lab 05
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#include "ExpressionManager.h"
#include <iostream>
#include <sstream>	
#include <stack>

using namespace std;

//----------Lab requirement functions-----------//

/** Return the infix items from the expression
throw an error if the expression
1) is not balanced.
2) the number of operators IS NOT one less than the number of operands.
3) there are adjacent operators. */
string ExpressionManager::infix(void) {
	return this->infixString;
}
/** Return a postfix representation of the infix expression */
string ExpressionManager::postfix(void) {
	return this->postfixString;
}
/** Return the integer value of the infix expression */
int ExpressionManager::value(void) {
	return this->valueOfExpression;
}
/** Return the infix vector'd expression items */
string ExpressionManager::toString() const {
	return "";
}

/****
Bonus:
(BONUS) Return a prefix representation of the infix expression
string ExpressionManager::prefix(void){}
*****/

//----------Video Functions-----------//

//Returns true if the string is a left parenthesis
bool ExpressionManager::isLeftParen(std::string s) {
	if (s == "(" || s == "[" || s == "{") {
		return true;
	}
	else {
		return false;
	}
}
//Returns true if the string is a right parenthesis
bool ExpressionManager::isRightPren(std::string s) {
	if (s == ")" || s == "]" || s == "}") {
		return true;
	}
	else {
		return false;
	}
}
//Returns true if the two strings are matching braces/parentheses/brackets
bool ExpressionManager::isPair(std::string left, std::string right) {
	if (left == "(" && right == ")") {
		return true;
	}
	else if (left == "[" && right == "]") {
		return true;
	}
	else if (left == "{" && right == "}") {
		return true;
	}
	else {
		return false;
	}
}
//Returns true if the string is an operator (+, -, *, or %s)
bool ExpressionManager::isOperator(string s) {
	if (s == "+" || s == "-" || s == "*" || s == "/" || s == "%") {
		return true;
	}
	else {
		return false;
	}
}
//Returns true if the input strring "s" is an integer
bool ExpressionManager::isNumber(string s) {
	//uses stringstream to check if conversion to int suceeded
	int iNumber;
	std::istringstream iss(s); //Add s to iss
	//read s into our integer value
	iss >> iNumber;
	if (iss.fail()) {
		//Not a number (specifically an integer)
		iss.clear();
		return false;
	}
	else {
		return true;
	}
}
//Returns an precedence (as an integer) based on the predefined operator precedences
int ExpressionManager::precedence(std::string sOperator) {
	if (sOperator == "(" || sOperator == "[" || sOperator == "{") {
		return 0;
	}
	else if (sOperator == "+" || sOperator == "-") {
		return 1;
	}
	else if (sOperator == "*" || sOperator == "/" || sOperator == "%") {
		return 2;
	}
	else {
		throw "Error: All of your data is terrible bro!";
	}
}

//----------Other Functions-----------//

//Returns true if the brackets/braces/parenthesis match each other in the correct order
	//and if they have a partner
bool ExpressionManager::isBalanced(std::string sRestOfSentence) {
	stack<string> stringStack;
	std::istringstream iss(sRestOfSentence); //For reading in input.
	std::string tempInput;
	string sIgnoreMe;
	iss >> sIgnoreMe;

	while (iss >> tempInput) { //Keep working with the stack until we have no more input from the sentence
		//We will ingnore any token that is not a bracket, parenthesis, or brace;
		if (isLeftParen(tempInput)) {
			stringStack.push(tempInput); //Push to the stack
		}
		else if (isRightPren(tempInput)){
			//Compare to the top element of the stack. If it is the same kind,
			//we will pop the top of the stack. If not the same, the expression
			//is not balanced.
			
			//Unbalanced: ex: }
			if (stringStack.empty()) {
				throw string("Paren Mis-match");
				return false;
			}
			//mismatch pair ex: ( ]
			else if (!isPair(stringStack.top(), tempInput)) {
				throw string("Paren Mis-match");
				return false;
			}
			//It has a match, so it is normal 
			else if (isPair(stringStack.top(), tempInput)) {
				stringStack.pop();
			}
		}
	}

	//Does the expression have only 1 left paren remaining? Ex: ( with no closing partner
	if (!stringStack.empty()) {
		if (isLeftParen(stringStack.top())){
			throw string("Unbalanced");
			return false;
		}
	}
	return true; //NO error
}
//Takes the expression, removes the word "expression: " and sets the infix string
void ExpressionManager::convertToInfix(std::string sExpressionSentence) {
	//Remove the word "Expression: " from sExpressionSentence
	istringstream iss(sExpressionSentence);
	string sIntroWord;
	iss >> sIntroWord;

	const int INTRO_WORD_LENGTH = sIntroWord.length() + 1; //+1 for the space after it
	string sRestOfSentence = sExpressionSentence.substr(INTRO_WORD_LENGTH); //gets everything after the intro word
	this->infixString = sRestOfSentence;
}
void ExpressionManager::calcValFromPostfix(string sExpressionSentence) {
	string sPostfixSentence;
	sPostfixSentence = this->postfixString;
	//Stack will hold only integers
	stack<int> stackOfInts;
	stringstream sentence(sPostfixSentence);
	string sTemp;
	
	
	while (!sentence.eof()) {
		sentence >> sTemp;
		if (isNumber(sTemp)) {
			stackOfInts.push(stoi(sTemp)); //stoi(someString) converts a string to an int
		}
		else if (isOperator(sTemp)){
			if (stackOfInts.size() >= 2) {
				//Pop the top two elements off of the stack;
				int iRight = stackOfInts.top();
				stackOfInts.pop();
				int iLeft = stackOfInts.top();
				stackOfInts.pop();

				//Find the new value
				int iValue = doMath(iLeft, sTemp, iRight);
				//Push the new value to the top of the stack
				stackOfInts.push(iValue);
			}
		}
	}

	if (stackOfInts.size() == 1) {
		//Expression was valid
		this->valueOfExpression = stackOfInts.top();
	}
	else {
		this->valueOfExpression = stoi(sPostfixSentence);
	}
}
//Returns an int and performs calculations for the stack
int ExpressionManager::doMath(int left, string operand, int right) {
	if (operand == "+") {
		return left + right;
	}
	else if (operand == "-") {
		return left - right;
	}
	else if (operand == "*") {
		return left * right;
	}
	else if (operand == "/") {
		return left / right;
	}
	else if (operand == "%") {
		return left % right;
	}
	else {
		return -666;
	}
}
//Sets the the member "postfixString"
void ExpressionManager::setPostfix(string sExpressionSentence) {
	string sPostFixString;
	sPostFixString = infixToPostfix(sExpressionSentence);
	this->postfixString = sPostFixString;
}
//Returns a postfix string converted from infix notation
string ExpressionManager::infixToPostfix(string sExpressionSentence) {
	string stringWithoutIntroWord;
	convertToInfix(sExpressionSentence);
	stringWithoutIntroWord = this->infixString;

	istringstream iss(stringWithoutIntroWord); //puts the workable sentence in a stringstream
	stack<string> stackOfOperators;
	ostringstream oss;

	string sTemp;

	while (!iss.eof()) {

		iss >> sTemp;

		if (isNumber(sTemp)) {
			//It's an int. Add it to the output string
			oss << sTemp << " ";
		}
		else if (isOperator(sTemp)) {

			if (stackOfOperators.empty()) {
				stackOfOperators.push(sTemp);
			}
			else {

				//It's an operator
				int iTempPrecedence = precedence(sTemp);
				int iTopOfStackPrecedence;
				string sTopOfStack;

				sTopOfStack = stackOfOperators.top();
				iTopOfStackPrecedence = precedence(sTopOfStack);

				//Top of stack holds a parenthesis...push onto stack
				if (isLeftParen(stackOfOperators.top()) || isRightPren(stackOfOperators.top())) {
					stackOfOperators.push(sTemp);
				}
				//If tempPrecedence is higher than topPrecendence, push onto stack
				else if (iTempPrecedence == 2 && (iTopOfStackPrecedence == 0 || iTopOfStackPrecedence == 1)) {
					stackOfOperators.push(sTemp);
				}
				//tempPrecedence is lower than topPrecedence...
				else if (iTempPrecedence < iTopOfStackPrecedence) {
					//Pop from top of stack to output until tempPresedence is higher than iTopOfStackPrecedence
					int iTopOfStackPreecedenceForThisFunction = iTopOfStackPrecedence;
					while (iTempPrecedence <= iTopOfStackPreecedenceForThisFunction) {
						if (!stackOfOperators.empty()) {
							string sTopOfStackPrep = stackOfOperators.top(); //Prepare top of stack for the top
							if (isLeftParen(sTopOfStackPrep)) {
								//leave it alone and move on with life...
								break;
							}
							else {
								oss << sTopOfStackPrep << " "; //Output top element to the output
								stackOfOperators.pop(); //Pop top of stack
								iTopOfStackPreecedenceForThisFunction = precedence(sTopOfStackPrep); //reset presendene for the top of the stack
							}
						}
						else {
							break;
						}
					} //Now the current operator has higher precedence than the top element of the stack

					stackOfOperators.push(sTemp); //Now we push the operator onto the stack
				}
				//Temp operator has same precendence as the top of the stack operator && the DO NOT have precedence of 2
				else if ((iTempPrecedence == iTopOfStackPrecedence) && iTempPrecedence != 2) {
					//Pop from top of stack to output until tempPresedence is higher than iTopOfStackPrecedence
					int iTopOfStackPreecedenceForThisFunction = iTopOfStackPrecedence;
					while (iTempPrecedence <= iTopOfStackPreecedenceForThisFunction) {
						if (!stackOfOperators.empty()) {
							string sTopOfStackPrep = stackOfOperators.top(); //Prepare top of stack for the top
							if (isLeftParen(sTopOfStackPrep)) {
								//leave it alone and move on with life...
								break;
							}
							else {
								oss << sTopOfStackPrep << " "; //Output top element to the output
								stackOfOperators.pop(); //Pop top of stack
								iTopOfStackPreecedenceForThisFunction = precedence(sTopOfStackPrep); //reset presendene for the top of the stack
							}
						}
						else {
							break;
						}
					}
					//iTempPrecedence is now higher than iTopOfStackPrecedenceForThisFunction
					stackOfOperators.push(sTemp);
				}
				//If they are both equal and of precedence #2
				else if (iTempPrecedence == 2 && iTopOfStackPrecedence == 2) {
					oss << stackOfOperators.top() << " ";
					stackOfOperators.pop();
					stackOfOperators.push(sTemp);
				}
			}
		}
		//Is a left parenthesis
		else if (isLeftParen(sTemp)) {
			stackOfOperators.push(sTemp);
		}
		//Is a right parenthesis
		else if (isRightPren(sTemp)) {
			while (!isPair(stackOfOperators.top(), sTemp)) {
				//Pop from top of stack to the output.
				oss << stackOfOperators.top() << " ";
				stackOfOperators.pop();
			}
			//Top of the stack and the current operator are a pair now..
			//Pop opening parenthesis off the top of the stack, but don't add it to the output
			stackOfOperators.pop();
		}
	}
	//We have reached the end of the expression
	//Now we will pop of all of the remaining operators from the stack to the output
		//until the stack is empty

	while (!stackOfOperators.empty()) {
		oss << stackOfOperators.top() << " ";
		stackOfOperators.pop();
	}
	string sOutputString = oss.str();
	return sOutputString;
}
//Returns true if an illegal operator exists in the expression string
bool ExpressionManager::illegalOperatorsExist(string sExpression) {
	istringstream iss(sExpression);

	while (!iss.eof()) {
		string sTemp;
		iss >> sTemp;
		if (!isNumber(sTemp)) {
			if (!isParen(sTemp)) {
				if (!isOperator(sTemp)) {
					return true; //illegal operator
				}
			}
		}
	}
	//Did not find illegal operators
	return false;
}
//Returns true if the string is a parenthesis
bool ExpressionManager::isParen(string s) {
	if (isLeftParen(s) || isRightPren(s)) {
		return true;
	}
	else {
		return false;
	}
}
//Returns true if no exceptions exist after the isBalanced(string) function is called
bool ExpressionManager::isRestOk(string sExpressionSentence) {
	std::istringstream iss(sExpressionSentence); //For reading in input.
	std::string tempInput;
	string sIgnoreMe;
	iss >> sIgnoreMe;

	int iNumOperator = 0;
	int iNumOperand = 0;

	string sCurr;
	string sPrev;

	bool bFirstItemInStackHasBeenEvaluated = false;

	while (!iss.eof()) {

		if (!bFirstItemInStackHasBeenEvaluated) {

			iss >> sCurr;

			//First item in list is a right paren...
			if (isRightPren(sCurr)) {
				throw string("Unbalanced");
				return false;
			}			
			//First item in expression is an operator.. ie: "- 5" or just "-"
			else if (isOperator(sCurr)) {
				throw string("Missing Operands");
				return false;
			}			
			bFirstItemInStackHasBeenEvaluated = true;
			sPrev = sCurr;
			continue;
		}

		sPrev = sCurr;
		iss >> sCurr;

		//Number
		if (isNumber(sCurr)) {
			string expression = "That's cool bro";
			iNumOperand++;

			//Adjacent operands exist ex: 3 5 * 2 +
			if (adjacentOperand(sPrev, sCurr)) {
				throw string("Missing Operators");
				return false;
			}
		}
		//Operator
		else if (isOperator(sCurr)) {
			iNumOperator++;
			
			//Adjacent operators ex: 5 + + 10
			if (adjacentOperator(sPrev, sCurr)) {
				throw string("Missing Operands");
				return false;
			}
			//Checks for ( + 2 )
			else if (isOperator(sCurr) && isLeftParen(sPrev)) {
				throw string("Missing Operands");
				return false;
			}
		}
		//Paren
		else if (isParen(sCurr)) {
			//Checks for 2 ( + 3 - 7 ) No operator between num and paren
			if (isLeftParen(sCurr) && isNumber(sPrev)) {
				throw string("Missing Operators");
				return false;
			}
			//Checks for ( 2 + ) 
			else if (isRightPren(sCurr) && isOperator(sPrev)) {
				throw string("Missing Operands");
				return false;
			}
		}
		//Not a number, operator, or paren
		else {
			throw string("Illegal Operator");
			return false;
		}		
	}

	//Checks to make sure num of operands is 1 more than num of operators
	if (iNumOperand != (iNumOperator + 1)) {
		throw string("Missing Operands");
		return false;
	}

	return true; //No errors encountered;
}
//Returns true if there are adjacent operators
bool ExpressionManager::adjacentOperator(string left, string right) {
	if (isOperator(left) && isOperator(right)) {
		return true; //Error on its way
	}
	else {
		return false;
	}
}
//Returns true if there are adjacent operands
bool ExpressionManager::adjacentOperand(string left, string right) {
	if (isNumber(left) && isNumber(right)) {
		return true; //Error on its way
	}
	else {
		return false;
	}
}