#include "Maze.h"

//Constructor to set height, width, and number of layers for the maze. Also creates a 3D array.
Maze::Maze(int h, int w, int numL) {
	this->height = h;
	this->width = w;
	this->numLayers = numL;

	this->three_dim = new int **[height]; //Create a triple pointer...
	for (int i = 0; i < height; i++) {
		three_dim[i] = new int*[width]; //Each element of height will be a pointer to a width pointer
		for (int j = 0; j < width; j++) {
			three_dim[i][j] = new int[numLayers]; //Each element of width will point to the number of layers
		}
	}
}
//Frees up the pointers to prevent memory leaks. Is called in the maze destructor
void Maze::deleteMemory() {
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; j++) {
			delete[] three_dim[i][j];
		}	
		delete[] three_dim[i];
	}
	delete[] three_dim;
}
/** Output maze (same order as input maze)
@return string of 2D layers
*/
string Maze::toString() const {
	std::ostringstream oss;
	oss << "Solve Maze:" << std::endl;
	for (int k = 0; k < numLayers; k++) {
		oss << "Layer " << (k + 1) << std::endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (three_dim[i][j][k] == 0) {
					oss << "_" << " ";
				}
				else if (three_dim[i][j][k] == 1) {
					oss << "X" << " ";
				}
				else {
					oss << three_dim[i][j][k] << " ";
				}
				//oss << three_dim[i][j][k] << " ";
			}
			oss << std::endl;
		}
		oss << std::endl;
	}
	return oss.str();
}
string Maze::toStringSolved() const {
	std::ostringstream oss;
	oss << "Solution:" << std::endl;
	for (int k = 0; k < numLayers; k++) {
		oss << "Layer " << (k + 1) << std::endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (three_dim[i][j][k] == 0) {
					oss << "_" << " ";
				}
				else if (three_dim[i][j][k] == 1) {
					oss << "X" << " ";
				}
				else {
					oss << three_dim[i][j][k] << " ";
				}
			}
			oss << std::endl;
		}
		oss << std::endl;
	}
	return oss.str();
}
void Maze::importMazes(string num, string str) {
	this->importedMazeAsNum = num;
	this->importedMazeAsString = str;
}
/** Solve maze
@return true if solveable, else false. RECURSIVE PART
*/
bool Maze::find_maze_path(int h, int w, int l) {
	// check boundary (base case #1) //Outside of the maze
	if ((h < 0) || (h >= this->height) ||
		(w < 0) || (w >= this->width) ||
		(l < 0) || (l >= this->numLayers)) return false;

	if (three_dim[h][w][l] != 0) return false; // blocked (base case #2)

	if ((h == this->height - 1) && (w == this->width - 1) && (l == this->numLayers - 1))
	{
		three_dim[h][w][l] = 3; // Success! (base case #3)
		return true;
	}
	three_dim[h][w][l] = 2; // Recursive case
	if (find_maze_path(h, w - 1, l) || //left
		find_maze_path(h, w + 1, l) || //right
		find_maze_path(h + 1, w, l) || //up
		find_maze_path(h - 1, w, l) || //down
		find_maze_path(h, w, l - 1) || //out
		find_maze_path(h, w, l + 1)) return true; //in	
	three_dim[h][w][l] = 0;
	return false;
}
/** Solve maze
@return true if solveable, else false
*/
bool Maze::find_maze_path() {
	return find_maze_path(0, 0, 0);
}
/** Set maze value
@parm height
@parm width
@parm layer
@parm value
*/	
void Maze::setValue(int height, int width, int layer, int value) {	
	three_dim[height][width][layer] = value;
}
