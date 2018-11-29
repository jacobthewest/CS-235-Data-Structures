/**********************
Jacob West
Lab 07
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#ifndef MAZE_H
#define MAZE_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
using std::string;

#include "MazeInterface.h"

class Maze : public MazeInterface
{
private:
	int height;
	int width;
	int numLayers;
	int ***three_dim;
	string importedMazeAsString;
	string importedMazeAsNum;
	std::vector<string> p;;
public:
	Maze(void) {}
	Maze(int height, int width, int iNumLayers);
	~Maze(void) { deleteMemory(); }
	
	void deleteMemory();
	void importMazes(string num, string str);
	//bool findPath(int height, int width, int numLayers);
	virtual void setValue(int height, int width, int layer, int value);
	virtual bool find_maze_path();
	bool find_maze_path(int h, int w, int l);
	virtual string toString() const;
	string toStringSolved() const;
	/*The maze output consists of height x width layers, with:
	Each new layer is preceded by "Layer #".
		Open cells are output as an underscore character("_"). (The solved maze may have unvisited open cells.)
		Blocked cells are output as the character "X".
		The solution path is output as the number 2.
		And the exit cell is output as the number 3.
		Put a space between each cell value.*/

	enum CellValue { OPEN, BLOCKED, PATH, EXIT, TEMPORARY };
};
#endif // MAZE_H