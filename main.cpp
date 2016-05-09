/*

	Filename		:				main.cpp
	Programmer		:				Joe Waller
	Last Modified	:				04/16/2002
	Description		:				This is the main file in a program that will execute a
									Connect Four game.  The game will two modes:

									1.	Single Player Mode -
												The game will be played by one human and one
												computer player.  The AI for the computer is
												implemented using the Minimax algorithm.
									2.	Two Player Mode -
												Two local humans will engaged in an intense
												battle to see who can be the first to put four
												in a row.

									Rules are exactly the same as in traditional Connect Four
*/

#include"globals.h"

int main()
{
	switch(GetNumPlayers())
	{
		case 1: DoSinglePlayer();
						break;
		case 2: DoTwoPlayer();
						break;
	}
  return 0;
}

