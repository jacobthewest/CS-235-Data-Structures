/**********************
Jacob West
Lab 06
CS 235 Section 1
jacobthewest@gmail.com
**********************/


#include "Deque.h"
#include "Queue.h"
#include "Stack.h"
#include "Station.h"
#include "Vector.h"

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

	string sSentence;
	istringstream iss;
	Station<int> stationObject;
	string sDesiredCommand;

	while (!in.eof()) {
		getline(in, sSentence);
		if (sSentence == "") {
			getline(in, sSentence);
		}
		iss.str(sSentence); //Puts sentence in iss

		iss >> sDesiredCommand;
		out << sDesiredCommand << " ";

		if (sDesiredCommand == "Add:station") {
			//Train car enters the station turntable. 
			int iTrainCarNum;
			iss >> iTrainCarNum;
			out << iTrainCarNum << " " << stationObject.addCar(iTrainCarNum);
		}
		else if (sDesiredCommand == "Add:queue") {
			//Train car is removed from the turntable and pushed to the Queue roundhouse. 
			out << stationObject.addQueue();
		}
		else if (sDesiredCommand == "Add:stack") {
			//Train car is removed from the turntable and pushed to the Stack roundhouse
			out << stationObject.addStack();
		}
		else if (sDesiredCommand == "Remove:station") {
			//A train car is removed from the turntable and pushed into the train vector. 
			out << stationObject.removeCar();
		}
		else if (sDesiredCommand == "Remove:queue") {
			//A train car is removed from Queue roundhouse and moved to the station turntable. 
			out << stationObject.removeQueue();
		}
		else if (sDesiredCommand == "Remove:stack") {
			//A train car is removed from Stack roundhouse and moved to the station turntable
			out << stationObject.removeStack();
		}
		else if (sDesiredCommand == "Top:station") {
			//Display the current train car on station turntable
			out << stationObject.topCar();
		}
		else if (sDesiredCommand == "Top:queue") {
			//Display the train car at head of Queue roundhouse. 
			out << stationObject.topQueue();
		}
		else if (sDesiredCommand == "Top:stack") {
			//Display the train car at head of Stack roundhouse.
			out << stationObject.topStack();
		}
		else if (sDesiredCommand == "Size:queue") {
			//Output number of train cars in Queue/Stack roundhouse
			out << stationObject.sizeQueue();
		}
		else if (sDesiredCommand == "Size:stack") {
			//Output number of train cars in Queue/Stack roundhouse
			out << stationObject.sizeStack();
		}
		else if (sDesiredCommand == "Train:") {
			//Output the contents of the train vector
			out << stationObject.legitToString();
		}
		out << endl;
		iss.clear();
	}

	return 0;
}
