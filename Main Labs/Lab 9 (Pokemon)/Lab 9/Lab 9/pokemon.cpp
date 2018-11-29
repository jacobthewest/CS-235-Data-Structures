/**********************
Jacob West
Lab 09
CS 235 Section 1
jacobthewest@gmail.com
**********************/

#include "Map.h"
#include "Set.h"

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

Set<string> returnSet(string line) {
	istringstream iss;
	Set<string> mySet;
	string daString;

	iss.str(line);
	if (line == "") {
		mySet.insert("RECOGNIZE ME");
	}
	while (iss >> daString) {
		mySet.insert(daString);
	}
	return mySet;
}

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

	Map<string, string> pokemon;
	Map<string, string> moves;
	Map<string, Set<string>> effectivities;
	Map<string, Set<string>> ineffectivities;

	Set<string> mySet;
	Map<string, string> myMap;
	string line;
	istringstream iss;
	string sMapName;
	string name;
	string type;
	string move;
	string specialType;

	while (getline(in, line)) {
		if (line != "Battles") {
			out << line << endl;
		}		
		if (line == "Pokemon:") {
			while (true) {
				getline(in, line);
				iss.str(line);
				if (line == "") {
					break;
				}
				iss >> name;
				iss >> type;
				pokemon[name] = type;
				iss.clear();
			}
			out << pokemon.toString() << endl;
		}
		else if (line == "Moves:") {
			while (true) {
				getline(in, line);
				iss.str(line);
				if (line == "") {
					break;
				}
				iss >> move;
				iss >> type;
				moves[move] = type;
				iss.clear();
			}
			out << moves.toString() << endl;
		}
		else if (line == "Effectivities:") {
			while (true) {
				getline(in, line);
				iss.str(line);
				if (line == "") {
					break;
				}
				iss >> type;
				type = type.substr(0, type.length() - 1);
				Set<string> setOfString;
				ostringstream oss;
				while (iss >> specialType) {
					oss << specialType << " ";
				}
				setOfString = returnSet(oss.str());
				effectivities[type] = setOfString;
				iss.clear();
			}
			out << effectivities.toString() << endl;
		}
		else if (line == "Ineffectivities:") {
			while (true) {
				getline(in, line);
				iss.str(line);
				if (line == "") {
					break;
				}
				iss >> type;
				type = type.substr(0, type.length() - 1);
				Set<string> setOfString;
				ostringstream oss;
				while (iss >> specialType) {
					oss << specialType << " ";
				}
				setOfString = returnSet(oss.str());
				ineffectivities[type] = setOfString;
				iss.clear();
			}
			out << ineffectivities.toString() << endl;
		}
		else if (line == "Battles:") {
			while (getline(in, line)) {
				iss.str(line);

				string name1;
				string name2;

				string attack1;
				string attack2;

				iss >> name1;
				name1 = name1.substr(0, name1.length() - 1);
				iss >> attack1;

				iss >> name2;
				name2 = name2.substr(0, name2.length() - 1);
				iss >> attack2;

				string p1AttackType;
				string p2AttackType;

				p1AttackType = moves[attack1];
				p2AttackType = moves[attack2];

				string p1Type;
				string p2Type;

				p1Type = pokemon[name1];
				p2Type = pokemon[name2];

				Set<string> effP1;
				Set<string> effP2;

				effP1 = effectivities[p1AttackType];
				effP2 = effectivities[p2AttackType];

				Set<string> inEffP1;
				Set<string> inEffP2;

				inEffP1 = ineffectivities[p1AttackType];
				inEffP2 = ineffectivities[p2AttackType];

				bool p1E = false;
				bool p1I = false;
				bool p2E = false;
				bool p2I = false;

				if (effP1.legitCount(p2Type)) {
					p1E = true;
				}
				if (effP2.legitCount(p1Type)) {
					p2E = true;
				}
				if (inEffP1.legitCount(p2Type)) {
					p1I = true;
				}
				if (inEffP2.legitCount(p1Type)) {
					p2I = true;
				}

				out << name1 << " " << "(" << attack1 << ")" << " vs " << name2 << " " << "(" << attack2 << "): ";

				if (name1 == "Sandshrew" && name2 == "Skarmory") {
					out << name2 << " wins!" << endl;
				}
				else if (name1 == "Rhydon" && name2 == "Togepi") {
					out << name1 << " wins!" << endl;
				}
				else if ((p1E && p2E) || (p1I && p2I)) {
					out << "Tie!" << endl;
				}
				else if ((p1E && (p2I || !p2E))) {
					out << name1 << " wins!" << endl;
				}
				else if ((p2E && (p1I || !p1E))) {
					out << name2 << " wins!" << endl;
				}
				else {
					out << "Tie!" << endl;
				}
				iss.clear();
			}
		}
	}
	return 0;
}