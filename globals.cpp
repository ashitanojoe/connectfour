/*

	Filename		:				globals.cpp
	Programmer		:				Joe Waller
	Last Modified	:				04/16/2002
	Description		:				This file contains all the code of the global functions
									that are used in the Connect Four.  The difinitions for these
									functions are in globals.h

*/

#define COL_FULL		-1
#define MOVE_OK		 	0
#define WINNER		 	1
#define BOARD_FULL 		2

#include"globals.h"
#include<iostream>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

/* GetNumPlayers *************************************************************/
// Function to read input from a user to determine whether the game played
// will be single player or multiplayer.  Function will return the choice of
// the user
/* ------------------------------------------------------------------------- */
int GetNumPlayers()
{
	int num_players=0;

	for(;;)
	{
  	cout << "Enter the number of players (1 or 2): ";
  	cin >> num_players;
		if((num_players != 1) && (num_players != 2))	// if the choice was not 1 or 2
			cout << "Invalid entry!\n";                 // then it is an invalid entry
		else
			return num_players;
	}
}

/* DoTwoPlayer ***************************************************************/
// This will execute a two human player game
/* ------------------------------------------------------------------------- */
void DoTwoPlayer()
{
	int turn, col, return_val;
	bool gameover=false;
	CGameboard game;
	char playerX[25];
	char playerO[25];			// that is player "O" as in the letter of the alphabet
	char cur_player;

	// First, get the player's names
	cout << "Player X, please enter your first name: ";
	cin >> playerX;
	cout << "Player O, please enter your first name: ";
	cin >> playerO;
	cout << endl;

	srand(time(NULL));	// seed the random number generator using the clock.
						// without doing this it tended to pick the same random
						// number everytime the program started
	turn = rand() % 2;	// generates a random 0 or 1
	
	if(turn == 0)
		cout << playerX << " (X), you have won the chance to go first.";
	else
		cout << playerO << " (O), you have won the chance to go first.";
	cout << endl << endl;

	while(!gameover)	// while there is no winner and the game is not full
	{
		game.OutputGameBoard();		// output the current state of the board
		for(;;)
		{
			if((turn % 2) == 0)		// if turn is even the playerX's turn
			{
				cout << playerX << " (X), please enter a column number (1-7): ";
				cur_player = 'X';	// sets the current player turn to X
			}
			else					// else playerO's turn
			{
				cout << playerO << " (O), please enter a column number (1-7): ";
				cur_player = 'O';    // sets the current turn to O
			}
			cin >> col;
			if((col > 0) && (col < 8))		// if a valid move
				break;
			else                          	// else invalid move
				cout << "Invalid move!\n\n";
		}
		cout << endl;
		return_val = game.InsertMove(col-1, cur_player);	// inserts a move and gets the
																											// return value

		// switch statement for all the possible return values after move
		switch(return_val)
		{
			case WINNER:		gameover = true;
								break;
			case MOVE_OK:		turn++;
								break;
			case COL_FULL:		cout << "Column is full!\n";
								break;
			case BOARD_FULL:	gameover = true;
								break;
		}
	}
	game.OutputGameBoard();                 // output the current state of the board
	if(return_val == WINNER)				// if we have a winner
	{
		cout << "We have a winner!\n";
		cout << "Congratulations ";
		if((turn % 2) == 0)
			cout << playerX;
		else
			cout << playerO;
		cout << ", you are the winner!\n";
	}
	else if (return_val == BOARD_FULL)           // else if the board is full
		cout << "The game is full, we have a tie.\n\n";
}

/* DoSinglePlayer ************************************************************/
// This will execute a game comsisting of one human and one computer player
/* ------------------------------------------------------------------------- */
void DoSinglePlayer()
{
	char playerO[25];
	bool gameover=false;
	CGameboard game;
	int max_ply=4, col;	// a max ply of 4 has given the best performance
	int turn, return_val;
	char cur_player;

	cout << "Player X is the computer player.\n";
	cout << "Player 0, please enter your first name: ";
	cin >> playerO;
	cout << endl << "Please enter a difficulty level.\n";
	cout << "Warning: Entering a number larger than 6 will cause\n"
			 << "the computer to run very slow.\n";
	cout << "Enter number 1-6 : ";
	cin >> max_ply;
	cout << endl;

	srand(time(NULL));
	turn = rand() % 2;		// generates a random 0 or 1
	
	if(turn == 0)
		cout << "The computer (X) has won the chance to go first.";
	else
		cout << playerO << " (O), you have won the chance to go first.";
	cout << endl << endl;

	int best_choice;
	while(!gameover)		// while the game is not over (!WINNER or !FULL)
	{
		// cout << "Static board evaluator: " << game.sbe() << endl;
		game.OutputGameBoard();
		for(;;)
		{
			if((turn % 2) == 0)		// computer's turn
			{
				int j = 0;
				int max_eval;
				for(int i=0; i<7; i++)
				{
					best_choice = SearchGameTree(game, j, i, max_ply, max_eval, best_choice);	// calls the game tree
					cout << best_choice << endl;
				}
				cur_player = 'X';													// search
				col = best_choice + 1;	// so the choice will be the correct column
				cout << endl << "The computer chose column " << col << ".\n";
				break;					// leave the for loop
			}
			else
			{
				// gets the player's move
				cout << playerO << " (O), please enter a column number (1-7): ";
				cur_player = 'O';
				cin >> col;
				if((col > 0) && (col < 8))
					break;
				else
					cout << "Invalid move!\n\n";
			}
		}
		cout << endl;
		return_val = game.InsertMove(col-1, cur_player);
		switch(return_val)
		{
			case WINNER:			gameover = true;
												break;
			case MOVE_OK:			turn++;
												break;
			case COL_FULL:		cout << "Column is full!\n";
												break;
			case BOARD_FULL:  gameover = true;
												break;
		}
	}
	game.OutputGameBoard();
	if(return_val == WINNER)
	{
		cout << "We have a winner!\n";
		if((turn % 2) == 0)
			cout << "You have been bested by the computer!\n";
		else
		{
			cout << playerO;
			cout << "Congratulations " << playerO << ", you are the winner!\n";
		}
	}
	if (return_val == BOARD_FULL)
		cout << "The game is full, we have a tie.\n\n";		
}

/* mimimax *******************************************************************/
// This is the minimax algorithm for searching the game tree.
/* ------------------------------------------------------------------------- */
int minimax(CGameboard board, int cur_ply, int& max_ply)
{
	int val[7];
	int k=0;

	if(cur_ply == max_ply)    // if searched to max_ply
		return board.sbe();			// return static board evaluator
	else
	{
		// for each child of board go to next depth
		for(int i=0; i<7; i++)
		{
			if(!board.ColumnFull(i))	// if the column is full then no need to
			{							// generate the child
				char buf='X';
				CGameboard buffer;
				buffer = board;
				if(cur_ply % 2 == 1)
					buf = 'O';
				if(buffer.InsertMove(i, buf) == WINNER)		// if a winner is found then
					val[k] = buffer.sbe();                  // do not continue branching.
				else										// else continue searching
					val[k] = minimax(buffer, cur_ply+1, max_ply);
				k++;
			}
		}
		if(cur_ply % 2 == 1)		// odd depth returns minimum value
			return min(val, k);
		else						// even depth returns maximum value
			return max(val, k);
	}
}

/* max ***********************************************************************/
// fuction to accept an integer array and its number of elements and return
// the maximum value in the array
/* ------------------------------------------------------------------------- */
int max(int val[], int num_elem)
{
	int max_val = val[0];
	for(int i=0; i<num_elem; i++)
		if(max_val < val[i])
			max_val = val[i];
	return max_val;
}

/* min ***********************************************************************/
// function to accept an integer array and its number of elements and return
// the maximum value in the array
/* ------------------------------------------------------------------------- */
int min(int val[], int num_elem)
{
	int min_val = val[0];
	for(int i=0; i<num_elem; i++)
		if(min_val > val[i])
			min_val = val[i];
	return min_val;
}

/* SearchGameTree ************************************************************/
// This function actually initiates the minimax search and returns the best
// choice to a move
/* ------------------------------------------------------------------------- */
int SearchGameTree(CGameboard& game, int& j, int& i, int& max_ply, int& max_eval, int old_choice)
{
	int int_buf, bestchoice = old_choice;
	CGameboard buffer;
	buffer = game;
	cout << "i: " << i << endl;
	if(!buffer.ColumnFull(i))
	{
		if(j == 0)									// this is only neccessary when max_eval has not
		{											// yet been changed (will only occur once)
			if(buffer.InsertMove(i, 'X') == WINNER)
				max_eval = buffer.sbe();
			else
				max_eval = minimax(buffer, 1, max_ply);
			bestchoice = i;
			cout << "Max Eval: " << max_eval << endl;
			j++;
		}
		else                       // do this if we already have a value for max_eval
		{
			if(buffer.InsertMove(i, 'X') == WINNER)
				int_buf = buffer.sbe();
			else
				int_buf = minimax(buffer, 1, max_ply);
			cout << "Int buff: " << int_buf << endl;
			cout << "Max Eval: " << max_eval << endl;
			cout << "i: " << i << endl;
			if(int_buf > max_eval)
			{
				cout << "Choice change" << endl;
				max_eval = int_buf;
				bestchoice = i;
			}
		}
	}
	//cout << "Return Value: " << bestchoice << endl;
	return bestchoice;						// return the best move
}


