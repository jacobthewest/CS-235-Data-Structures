/**********************
Jacob West
Lab 07
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#include "Maze.h"

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

	istringstream iss;
	string sSentence;
	int iLayerCounter = 0;
	bool bFirstLineRead = false;
	bool bLayerOneProcessed = false;
	int temp;
	Maze* mazeObj;
	ostringstream ossNum;
	ostringstream ossStr;

	//---------------Stuff to help with the Maze::toString() function-------------//

	//This will also help us populate the 3D maze with numbers when the time comes//

	//ossNum << "Solve Maze:" << endl;
	//ossStr << "Solve Maze:" << endl;
	//iLayerCounter++;
	////ossNum << "Layer " << iLayerCounter;
	//ossStr << "Layer " << iLayerCounter;

	getline(in, sSentence);
	iss.str(sSentence); //Puts sentence in iss

	//Store the values
	iss >> temp;
	const int iHeight = temp;

	iss >> temp;
	const int iWidth = temp;

	iss >> temp;
	const int iNumLayers = temp;

	//bFirstLineRead = true;

	//Call constructor
	mazeObj = new Maze(iHeight, iWidth, iNumLayers);
	iss.clear();
	getline(in, sSentence); //Clear the empty line

	istringstream other;
	//Load up the 3D array
	for (int l = 0; l < iNumLayers; l++) {
		for (int h = 0; h < iHeight; h++) {
			getline(in, sSentence);			
			other.str(sSentence);
			for (int w = 0; w < iWidth; w++) {
				other >> temp;
				mazeObj->setValue(h, w, l, temp);
			}
			other.clear();
		}
		getline(in, sSentence); //Handles the line between layers
	}
	out << mazeObj->toString();
	out << endl;
	if (mazeObj->find_maze_path()) {
		out << mazeObj->toStringSolved();
	}
	else {
		out << "No Solution Exists!";
	}	
	delete mazeObj;
	return 0;
}
//Class Code: supernova