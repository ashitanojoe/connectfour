/*

	Filename			:				globals.h
	Programmer		:				Joe Waller
	Last Modified	:				04/16/2002
	Description		:				This file contains the function definition for all the
												global functions to be used in the Connect Four program.
												This header needs to be included in any file that uses these
												functions

*/

#include"gameboard.h"

int GetNumPlayers();
void DoTwoPlayer();
void DoSinglePlayer();
int minimax(CGameboard board, int cur_ply, int& max_ply);
int max(int val[], int num_elem);
int min(int val[], int num_elem);
int SearchGameTree(CGameboard& game, int& j, int& i, int& max_ply, int& max_eval, int old_choice);
