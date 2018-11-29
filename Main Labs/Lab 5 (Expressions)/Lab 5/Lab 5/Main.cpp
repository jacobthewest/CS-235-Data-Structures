/**********************
Jacob West
Lab 05
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#include "ExpressionManager.h"
#include <iostream>
#include <fstream>

using namespace std;

//Check for memory leaks
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK    ;

#endif

int main(int argc, char * argv[])
{
	VS_MEM_CHECK;

	if (argc < 3)
	{
		cerr << "Please provide name of input and output files";
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out)
	{
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	//Create a pointer to an expression manger object
	ExpressionManager expressionManagerObject;
	
	string sInput;
	while (!in.eof()) {		
		getline(in, sInput);
		
		//Output "expression" to our output file
		out << sInput << endl;
		
		try {
			expressionManagerObject.isBalanced(sInput); //Checks for balance
		}
		catch (string error) {
			out << "Infix: Caught exception: NOT Infix: " << error << endl << endl;
			continue;
		}

		try {
			expressionManagerObject.isRestOk(sInput);
		}
		catch (string error) {
			out << "Infix: Caught exception: NOT Infix: " << error << endl << endl;
			continue;
		}

		//No errors were found with the expression so we are going to run the rest of the program
		expressionManagerObject.convertToInfix(sInput);
		out << expressionManagerObject.toString();

		out << "Infix: " << expressionManagerObject.infix() << endl;

		expressionManagerObject.setPostfix(sInput);
		out << "Postfix: " << expressionManagerObject.postfix() << endl;

		expressionManagerObject.calcValFromPostfix(sInput);
		out << "Value: " << expressionManagerObject.value() << endl << endl;
	}
	//delete expressionManagerObject;
	return 0;
}

//Peer review due tomorrow
//black hole