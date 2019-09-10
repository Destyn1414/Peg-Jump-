/* pegJump.cpp

   Author: *** Your name(s) here. ***
   Program: #3, Peg Jump
   CS 141, Spring 2019

   Description:
		  This program represents a peg jumping puzzle  A
		move is made by a peg jumping over another peg into an empty
		spot, where the jumped peg is then removed from the board. The
		game ends when there are no more valid moves to make. The object
		is to eliminate as many pegs as possible.

		Sample output:

			Welcome to the peg jump puzzle!
			Enter '-' to exit, or '+' for instructions.

							A B C
							D E F
					G H I J K L M
					N O P * Q R S
					T U V W X Y Z
							1 2 3
							4 5 6

			1. Enter the peg to move: +

			Welcome to the peg jump puzzle. The board starts out with a
			single blank position, represented by the '*'.  To make a
			move, select the letter of a peg.  A peg must be able to
			jump over an adjacent peg into a blank position for a move
			to be valid.  The jumped peg is then removed from the board.
			The game is over when there are no valid moves left. At any
			point enter '-' to exit, or '+' for instructions.

			1. Enter the peg to move: E

							A B C
							D * F
					G H I * K L M
					N O P E Q R S
					T U V W X Y Z
							1 2 3
							4 5 6

			2. Enter the peg to move: w

							A B C
							D * F
					G H I W K L M
					N O P * Q R S
					T U V * X Y Z
							1 2 3
							4 5 6

			3. Enter the peg to move: 5

							A B C
							D * F
					G H I W K L M
					N O P * Q R S
					T U V 5 X Y Z
							1 * 3
							4 * 6

			4. Enter the peg to move: 2
			*** Invalid move, please retry. ***
			4. Enter the peg to move: r

							A B C
							D * F
					G H I W K L M
					N O P R * * S
					T U V 5 X Y Z
							1 * 3
							4 * 6

			5. Enter the peg to move: R

							* * *
							* 1 *
					* * * * * * *
					* * * + * * *
					* * * * * * *
							* 2 *
							* * *

			There is more than one possible move.  Which move do you want? 1

							A B C
							D R F
					G H I * K L M
					N O P * * * S
					T U V 5 X Y Z
							1 * 3
							4 * 6

			6. Enter the peg to move: -

			Exiting...

			27 pieces remaining. Ouch!
 */

#include <iostream>
#include <cctype>     // For toupper()
#include<string>
using namespace std;

const int NumberOfPegs = 121;
const int PegsPerRow = 11;

//-------------------------------------------------------------------------------------
void displayInstructions()
{
	cout
		<< "Welcome to the peg jump puzzle. The board starts out with a \n"
		<< "single blank position, represented by the '*'.  To make a \n"
		<< "move, select the letter of a peg.  A peg must be able to \n"
		<< "jump over an adjacent peg into a blank position for a move \n"
		<< "to be valid.  The jumped peg is then removed from the board. \n"
		<< "The game is over when there are no valid moves left. At any \n"
		<< "point enter '-' to exit, or '+' for instructions. \n"
		<< endl;
}

void displayBoard(char board[])
{
	// Skip the first row and the last row in the array
	for (int i = 0 + PegsPerRow; i < NumberOfPegs - PegsPerRow; i++) {
		if (board[i] == '#') {
			cout << "  ";     // print a space
		}
		else {
			cout << board[i] << " ";    // print the stored character
		}
		if (((i + 1) % PegsPerRow) == 0) {
			// end of a row
			cout << endl;
		}
	}
}

void displayMoveOptions(char board[], int desiredCharacterLocation, int possiblePegs[])
{
	int pegIndex = 0;
	// Skip the first row and the last row in the array
	for (int i = 0 + PegsPerRow; i < NumberOfPegs - PegsPerRow; i++) {
		if (board[i] == '#') {
			cout << "  ";     // print a space
		}
		else {
			if (i == possiblePegs[pegIndex]) {
				cout << (pegIndex + 1) << " ";    // print the option number
				pegIndex++;
			}
			else if (i == desiredCharacterLocation) {
				cout << "+ ";    // print the desired location
			}
			else {
				cout << "* ";
			}
		}
		if (((i + 1) % PegsPerRow) == 0) {
			// end of a row
			cout << endl;
		}
	}
}

int getCharacterLocation(char board[], char userInput) {

	int desiredCharacterLocation = -1;

	for (int i = 0; i < NumberOfPegs; i++) {

		if (board[i] == userInput) {

			desiredCharacterLocation = i;

		}
	}

	return desiredCharacterLocation;
}


int findPossiblePegs(char board[], int desiredLocation, int possiblePegs[])
{
	// returns available move options
	int numPegs = 0;
	// making sure it's a valid board index
	if (desiredLocation < 0) {
		return 0;
	}

	if (board[desiredLocation - 22] == '*' && board[desiredLocation - 11] != '*') { // up
		possiblePegs[numPegs++] = desiredLocation - 22;
	}
	if (board[desiredLocation - 2] == '*' && board[desiredLocation - 1] != '*') { // left
		possiblePegs[numPegs++] = desiredLocation - 2;
	}
	if (board[desiredLocation + 2] == '*' && board[desiredLocation + 1] != '*') { // right
		possiblePegs[numPegs++] = desiredLocation + 2;
	}
	if (board[desiredLocation + 22] == '*' && board[desiredLocation + 11] != '*') { // below
		possiblePegs[numPegs++] = desiredLocation + 22;
	}

	return numPegs;
}

bool gameEnded(char board[]) {
	int possiblePegs[NumberOfPegs];
	for (int i = 0; i < NumberOfPegs; i++) {
		if (isalnum(board[i]) &&
			findPossiblePegs(board, getCharacterLocation(board, board[i]), possiblePegs) > 0) {

			return false;
		}
	}

	return true;
}

//-------------------------------------------------------------------------------------
int main()
{
	//Variable declarations
	char userInput = ' ';
	string messageDisplayed;
	int desiredCharacterLocation;
	int gameMove = 1, numberOfPiecesLeft = 32;
	char board[] = {
			'#','#','#','#','#','#','#','#','#','#','#',
			'#','#','#','#','#','#','#','#','#','#','#',
			'#','#','#','#','A','B','C','#','#','#','#',
			'#','#','#','#','D','E','F','#','#','#','#',
			'#','#','G','H','I','J','K','L','M','#','#',
			'#','#','N','O','P','*','Q','R','S','#','#',
			'#','#','T','U','V','W','X','Y','Z','#','#',
			'#','#','#','#','1','2','3','#','#','#','#',
			'#','#','#','#','4','5','6','#','#','#','#',
			'#','#','#','#','#','#','#','#','#','#','#',
			'#','#','#','#','#','#','#','#','#','#','#'
	};

	int startingCharacterLocation = getCharacterLocation(board, '*');


	cout << "Welcome to the peg jump puzzle! \n"
		<< "Enter '-' to exit, or '+' for instructions. "
		<< endl;

	displayBoard(board);

	while (!gameEnded(board)) {

		cout << gameMove << ". Enter the peg to move: ";
		cin >> userInput;

		cout << endl;

		userInput = toupper(userInput);

		if (userInput == '+') {

			displayInstructions();
			continue;
		}
		else if (userInput == '-') {
			cout << "Exiting..." << endl;
			cout << endl;
			break;
		}
		else {
			desiredCharacterLocation = getCharacterLocation(board, userInput);

			// clear list of possible peg positions
			int possiblePegs[NumberOfPegs];
			for (int i = 0; i < NumberOfPegs; i++) {
				possiblePegs[i] = -1;
			}

			int numPegs = findPossiblePegs(board, desiredCharacterLocation, possiblePegs);
			int pegIndex = 0;
			if (numPegs == 0) {
				// not valid
				cout << "*** Invalid move, please retry. ***" << endl;
				continue;
			}
			if (numPegs > 1) {
				// show options (more than 1 possible move)
				displayMoveOptions(board, desiredCharacterLocation, possiblePegs);

				cout << "There is more than one possible move.  Which move do you want? ";
				cin >> pegIndex;
				pegIndex--;
			}

			// do move
			startingCharacterLocation = possiblePegs[pegIndex];
			char ch = board[desiredCharacterLocation];
			board[desiredCharacterLocation] = '*';

			int dif = desiredCharacterLocation - startingCharacterLocation;
			board[desiredCharacterLocation - dif / 2] = '*';

			board[startingCharacterLocation] = ch;

			displayBoard(board);
			gameMove++;
			numberOfPiecesLeft--;

		}

	}

	//messageDisplayed = "Ouch!";

	//switch (numberOfPiecesLeft)
	//{
	//case 1:
	//	messageDisplayed = "esf";
	//	break;
	//case 2:
	//	messageDisplayed = "esf";
	//	break;
	//case 3:
	//	messageDisplayed = "esf";
	//	break;
	//case 4:
	//	messageDisplayed = "esf";
	//	break;
	//}

	if (numberOfPiecesLeft >= 5) {

		messageDisplayed = "Ouch!";
	}
	else if (numberOfPiecesLeft == 4) {

		messageDisplayed = "Needs Improvement.";
	}
	else if (numberOfPiecesLeft == 3) {

		messageDisplayed = "OK.";
	}
	else if (numberOfPiecesLeft == 2) {

		messageDisplayed = "Good!";
	}
	else if (numberOfPiecesLeft == 1) {

		messageDisplayed = "Excellent!";
	}

	cout << numberOfPiecesLeft << " pieces remaining. " << messageDisplayed << endl;

	return 0;
}//end main()