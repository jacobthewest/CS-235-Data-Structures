/**********************
Jacob West
Lab 08
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#include "BST.h"

#include <iostream>
#include <fstream>
#include <sstream>

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

	string sDesiredCommand;
	istringstream iss;
	string sLine;
	BST<int> obj;
	
	//Go through all of the lines in the file
	while (getline(in, sLine)) {
		iss.clear();
		iss.str(sLine);

		iss >> sDesiredCommand;
		out << sDesiredCommand << " ";

		if (sDesiredCommand == "Add") {

			int iValue;
			iss >> iValue;
			out << iValue << " ";

			//Output if the node was successfully added
			if (obj.addNode(iValue)) {
				out << "True";
			}
			else {
				out << "False";
			}
		}
		else if (sDesiredCommand == "PrintBST") {
			//Prints the tree
			out << obj.toString();
		}
		else if (sDesiredCommand == "Remove") {

			int iValue;
			iss >> iValue;
			out << iValue << " ";

			//Output if the node was successfully removed
			if (obj.removeNode(iValue)) {
				out << "True";
			}
			else {
				out << "False";
			}
		}
		else if (sDesiredCommand == "Clear") {
			//Output if the tree was successfully cleared
				//This also works for freeing up memory and
				//The clearTree() function is called in the destructor
			if (obj.clearTree()) {
				out << "True";
			}
			else {
				out << "False";
			}
		}
		out << endl;
	}
	
	return 0;
}
//Class Code: supernova