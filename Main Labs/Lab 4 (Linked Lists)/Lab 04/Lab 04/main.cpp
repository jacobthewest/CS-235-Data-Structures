/**********************
	Jacob West
	Lab 04
	CS 235 Section 1
	jacobthewest@gmail.com
**********************/

#include "LinkedListInterface.h" //Program requirements asked me to include both .h files.
#include "LinkedList.h"

#include <iostream>
#include <fstream>
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

	//Input commands
	const string INT = "INT"; //Instantiates a LinkedList<int> object for subsequent commands.	
	const string STRING = "STRING"; //Instantiates a LinkedList<string> object for subsequent commands.	
	const string INSERT_HEAD = "insertHead"; //insertHead <data> //Insert <data> at the head of the list.	
	const string INSERT_TAIL = "insertTail"; // insertTail <data>  //Insert <data> at the tail of the list.
	const string INSERT_AFTER = "insertAfter"; //insertAfter <match>,<data>  //Insert <data> after <match> found in the list.	
	const string REMOVE = "remove"; //remove <data>	//Remove <data> from the list.	
	const string AT = "at"; // at <index> //Return Node data from list Node at <index> (0 based). 	Return default type if out of bounds.
	const string SIZE = "size"; //Return the number of Nodes in the list.	
	const string CLEAR = "clear"; //Delete all Nodes in the list.	
	const string PRINT_LIST = "printList"; //Output Nodes in the list.

	LinkedList<int>* integerList = new LinkedList<int>();
	LinkedList<string>* stringList = new LinkedList<string>();

	//Get the data type
	//create an object of that data type. 
	//I need to worry only about getting string and ints
	string dataType;
	getline(in, dataType);
	out << dataType << " [" << dataType << "]" << endl;
	bool bIsInteger = false;

	if (dataType == INT) {
		//Create a linked list pointer to the head node of an INT data type
		bIsInteger = true;
	}
	else if (dataType == STRING) {
		//Create a linked list pointer to the head node of a STRING data type
	}
	else {
		//Throw an error
	}
	
		//Get the command while the input from the file is not over
	while (!in.eof()) {		
		string sDesiredCommand;
		in >> sDesiredCommand;
		out << sDesiredCommand << " ";
		int iParameter1;
		int iParameter2;
		string sParameter1;
		string sParameter2;


		if (sDesiredCommand == INSERT_HEAD) {

			if (bIsInteger) {
				in >> iParameter1;
				out << iParameter1 << " ";
				integerList->insertHead(iParameter1) ? out << "true" : out << "false";
			}
			else {
				in >> sParameter1;
				out << sParameter1 << " ";
				stringList->insertHead(sParameter1) ? out << "true" : out << "false";
			}
		}
		else if (sDesiredCommand == INSERT_TAIL) {

			if (bIsInteger) {
				in >> iParameter1;
				out << iParameter1 << " ";
				integerList->insertTail(iParameter1) ? out << "true" : out << "false";
			}
			else {
				in >> sParameter1;
				out << sParameter1 << " ";
				stringList->insertTail(sParameter1) ? out << "true" : out << "false";
			}
		}
		else if (sDesiredCommand == INSERT_AFTER) {

			if (bIsInteger) {
				in >> iParameter1;
				(bIsInteger) ? in >> iParameter2 : in >> sParameter2; //Get the second parameter
				out << iParameter1 << " " << iParameter2 << " ";
				integerList->insertAfter(iParameter1, iParameter2) ? out << "true" : out << "false";
			}
			else {
				in >> sParameter1;
				(bIsInteger) ? in >> iParameter2 : in >> sParameter2; //Get the second parameter
				out << sParameter1 << " " << sParameter2 << " ";
				stringList->insertAfter(sParameter1, sParameter2) ? out << "true" : out << "false";
			}
		}
		else if (sDesiredCommand == REMOVE) {

			if (bIsInteger) {
				in >> iParameter1;
				out << iParameter1 << " ";
				integerList->remove(iParameter1) ? out << "true" : out << "false";
			}
			else {
				in >> sParameter1;
				out << sParameter1 << " ";
				stringList->remove(sParameter1) ? out << "true" : out << "false";
			}
		}
		else if (sDesiredCommand == AT) {
			in >> iParameter1;
			out << iParameter1;	
			if (bIsInteger) {
				out << iParameter1 << " " << integerList->at(iParameter1);
			}
			else {
				out << sParameter1 << " " << stringList->at(iParameter1);
			}

			/*
			if (bIsInteger) {
				//handles empty lists
				(integerList == NULL) ? out << "" : 
			}			
			else {
				//handles empty lists
				if (stringList->head == NULL) {
					out << "";
				}
				else {
					out << sParameter1 << " " << stringList->at(iParameter1);
				}
				//(stringList == NULL) ? out << "" : out << sParameter1 << " " << stringList->at(iParameter1); //Here we use iParameter1 in the 
					//string list beause we need to access an index, not a string
			}
			*/
		}
		else if (sDesiredCommand == SIZE) {
			(bIsInteger) ? out << integerList->size() : out << stringList->size();
		}
		else if (sDesiredCommand == CLEAR) {
			if (bIsInteger) {
				integerList->clear() ? out << "true" : out << "false";
			}
			else {
				stringList->clear() ? out << "true" : out << "false";
			}
		}
		else if (sDesiredCommand == PRINT_LIST) {
			if (bIsInteger) {
				if (integerList->printList() == "") {
					out << "Empty";
				}
				else {
					out << integerList->printList();
				}
			}
			else {
				if (stringList->printList() == "") {
					out << "Empty";
				}
				else {
					out << stringList->printList();
				}
			}
		}
		else {
			out << "ERROR: \"" << sDesiredCommand << "\" is an invalid command!" << endl;
		}
		out << endl;
	}
	delete integerList;
	delete stringList;
	return 0;
}