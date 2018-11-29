/*********
	Jacob West
*********/

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Archer.h"
#include "Arena.h"
#include "ArenaInterface.h"
#include "Cleric.h"
#include "Fighter.h"
#include "FighterInterface.h"
#include "Robot.h"

using namespace std;

//--------------Code to check for memory leaks--------------------//
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif
//------------------------------------------------------------//


int main(int argc, char * argv[])
{
	VS_MEM_CHECK               // enable memory leak check

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

	//---------Variables-----------//
	const string NO_ABILITY = "NO ABILITY";
	const string USE_ABILITY = "USE ABILITY";
	const string GET_FIGHTER = "getFighter";
	const string GET_SIZE = "getSize";
	const string ADD_FIGHTER = "addFighter";
	const string REMOVE_FIGHTER = "removeFighter";
	const string RESET = "reset";
	const string BATTLE = "battle";
	string sTempString;
	bool bUseAbilityAndRegenerateFunctions;
	Arena arenaObject; //Used to call the vector of fighter pointers
	bool bFirstLineHasBeenProcessed = false;
	

	//Loop through all of the things that they want to enter until nothing else is entered.
	while (!in.eof()) { //While the input file is not empty, get the data

		if (!bFirstLineHasBeenProcessed) {
			//Read in the first line
			getline(in, sTempString); //we use "in" here instead of "cin" because "in" will read in input
				//from our input file

			//Will special abilities be enabled...
			if (sTempString == NO_ABILITY) {
				bUseAbilityAndRegenerateFunctions = false;
				//regenerate() and useAbility() methods in the fighter classes should NOT be called. 
			}
			else if (sTempString == USE_ABILITY) {
				bUseAbilityAndRegenerateFunctions = true;
				//regenerate() and useAbility() methods in the fighter classes should be called. 
			}
			bFirstLineHasBeenProcessed = true; //Forces us to never check for abilities again
				//for the rest of the program.
		}
		else {
			//Get the command from the string, then go into the appropriate if statement.

			getline(in, sTempString);
			out << sTempString; //Output to our output file
			int iPositionOfFirstSpace = sTempString.find(" ");
			string sDesiredCommand = sTempString.substr(0, iPositionOfFirstSpace);

			if (sDesiredCommand == GET_FIGHTER) {
				string sName = sTempString.substr(iPositionOfFirstSpace + 1);
				FighterInterface* desiredFighter = arenaObject.getFighter(sName);

				//Output the fighter's information using to the toString() function based off the class type
				//will evaluate to true if the pointer is not a nullptr
				if (desiredFighter) {
					out << endl << "  " << desiredFighter->toString() << endl;
				}
				else {
					out << " NULL" << endl;
				}
			}
			else if (sDesiredCommand == GET_SIZE) {
				out << " " << arenaObject.getSize() << endl;
			}
			else if (sDesiredCommand == ADD_FIGHTER) {
				//Get rest of the string to pass to the funcion
				string sRestOfTheString = sTempString.substr(iPositionOfFirstSpace + 1);//W/out the second 
					//parameter it reads until the end of sTempString
				//Was a fighter successfully added?
				if (arenaObject.addFighter(sRestOfTheString)) {
					out << " Added" << endl;
				}
				else {
					//Fighter was not added
					out << " Invalid" << endl;
				}
			}
			else if (sDesiredCommand == REMOVE_FIGHTER) {
				string sName = sTempString.substr(iPositionOfFirstSpace + 1);//W/out the second 
					//parameter it reads until the end of sTempString. We need to add 1 so it doesn't
					//include the space in the name

					//Was a fighter successfully removed?
				if (arenaObject.removeFighter(sName)) {
					out << " True" << endl;
				}
				else {
					//Fighter was not added
					out << " False" << endl;
				}
			}
			else if (sDesiredCommand == RESET) {
				//Search the vector of fighter pointers to reset the fighter
				string sName = sTempString.substr(iPositionOfFirstSpace + 1);
				if (arenaObject.resetFighter(sName)) {
					//True if successfully reset
					out << " Success" << endl;
				}
				else {
					out << " Failed" << endl;
				}
			}
			else if (sDesiredCommand == BATTLE) {

				//Get the fighters for the battle
				int iPositionOfSecondSpace = sTempString.find(" ", iPositionOfFirstSpace + 1);
					//Searches for our second space, starts at the position after the first space
				int iLengthOfSecondWord = iPositionOfSecondSpace - iPositionOfFirstSpace - 2;

				string sFighter1Name = sTempString.substr(iPositionOfFirstSpace + 1, iLengthOfSecondWord + 1); 
					//substr(startingIndex, lenOfCharacters);
				string sFighter2Name = sTempString.erase(0, iPositionOfSecondSpace + 1);
					//This skips over the first space and name and the second space and gets the second name.

				FighterInterface* fighter1 = arenaObject.getFighter(sFighter1Name);
				FighterInterface* fighter2 = arenaObject.getFighter(sFighter2Name);

				out << endl << endl << "  " << fighter1->toString();
				out << endl << "  " << fighter2->toString();

				//FIXME: need to error handle for wrong input names
				//FIXME: make robot bonus damage apply to only one turn

				bool bFirstRoundProcessed = false;
				bool bFinalRoundCompleted = false;
				bool bTheBattleIsOver = false;

				//battle until a player's current HP goes to zero or lower
				while (!bTheBattleIsOver) {
					if (!bFirstRoundProcessed) {
						out << endl;
					}
					else {
						bFirstRoundProcessed = true;
					}
					//----Fighter 1's turn---//
					if (bUseAbilityAndRegenerateFunctions) {
						fighter1->regenerate();
						fighter1->useAbility();
					}
					//calculate damage done
					int fighterf1DamgeDone = fighter1->getDamage();
					//apply damage to fighter 2
					fighter2->takeDamage(fighterf1DamgeDone);
					//If fighter 2 has zero or less hit points, print the status of each fighter(fighter’s toString() method) 
					//and end the battle
					if (fighter2->getCurrentHP() < 1) {
						bTheBattleIsOver = true;
						out << endl << "  " << fighter1->toString();
						out << endl << "  " << fighter2->toString();
						if (!bFinalRoundCompleted) {
							out << endl;
							bFinalRoundCompleted = true;
						}
						//I will end the battle by putting fighter 2's turn in an else statement.
					}
					else {
						//---Figher 2's turn---//
						if (bUseAbilityAndRegenerateFunctions) {
							fighter2->regenerate();
							fighter2->useAbility();
						}
						//calculate damage done
						int fighter2DamgeDone = fighter2->getDamage();
						//apply damage to fighter 1
						fighter1->takeDamage(fighter2DamgeDone);
						//Print the status of each fighter(fighter’s toString() method)
						out << endl << "  " << fighter1->toString();
						out << endl << "  " << fighter2->toString();
						if (fighter1->getCurrentHP() < 1) {
							out << endl;
							bFinalRoundCompleted = true;
							bTheBattleIsOver = true;
						}
					}
				}
			}
		}
	}
	in.close(); //closes our file
	//system("pause");
	return 0;
}