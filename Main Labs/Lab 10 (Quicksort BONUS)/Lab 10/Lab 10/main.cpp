/**************
Jacob West
LAB 10
***************/

#include "QS.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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

	//STUFF GOES HERE
	istringstream iss;
	string line;
	string command;
	int num;

	QS<int> myQuickSort;

	while (getline(in, line)) {
		iss.clear();
		iss.str(line);
		iss >> command;
		out << command << " ";

		if (command == "QuickSort") {
			iss >> num;
			out << num << " ";
			if (myQuickSort.createArray(num)) {
				out << "OK";
			}
			else {
				out << "Error";
			}
			out << endl;
		}
		else if (command == "Capacity") {
			out << myQuickSort.capacity() << endl;
		}
		else if (command == "Clear") {
			if (myQuickSort.clear()) {
				out << "OK";
			}
			else {
				out << "Problem";
			}
			out << endl;
		}
		else if (command == "AddToArray") {
			istringstream forThisLoop;
			ostringstream forThisLoopAlso;
			string inputToISS;

			inputToISS = line.substr(11);
			forThisLoop.str(inputToISS);

			string printMe;
			
			out << " ";
			bool error = false;

			string imANum;
			while (forThisLoop >> imANum) {
				num = stoi(imANum);
				if (myQuickSort.addElement(num)) {
					forThisLoopAlso << num << ",";
				}
				else {
					error = true;
				}
			}
			//Now remove the trailing comma
			printMe = forThisLoopAlso.str();
			printMe = printMe.substr(0, printMe.length() - 1);

			out << printMe;
			
			if (!error) {
				out << " OK";
			}
			else {
				out << " Error";
			}
			out << endl;
		}
		else if (command == "PrintArray") {
			out << myQuickSort.toString() << endl;
			iss.clear();
			line = "";
		}
		else if (command == "Size") {
			out << myQuickSort.size() << endl;
		}
		else if (command == "MedianOfThree") {
			//Get the left and right numbers
			size_t left;
			size_t right;
			
			iss >> left;
			iss >> right;
			out << left << "," << right << " = " << myQuickSort.medianOfThree(left ,right) << endl;
		}
		else if (command == "Partition") {
			size_t left;
			size_t right;
			size_t pivotIndex;

			iss >> left;
			iss >> right;
			iss >> pivotIndex;

			out << left << "," << right << "," << pivotIndex << " = " << myQuickSort.partition(left, right, pivotIndex) << endl;
		}
		iss.clear();
	}
	
	return 0;
}