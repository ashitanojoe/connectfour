/*

	Filename			:				gameboard.cpp
	Programmer		:				Joe Waller
	Last Modified	:				04/16/2002
	Description		:				This file contains the code for the member functions of
												the class CGameboard.  The difinition for this class is in
												the file gameboard.h
*/

#define COL_FULL		-1
#define MOVE_OK			0
#define WINNER			1
#define BOARD_FULL		2

#include"gameboard.h"
#include<iostream>

using namespace std;

/* CGameboard constructor ****************************************************/
// This is the CGameboard constructor.  This will initialize an empty board
/* ------------------------------------------------------------------------- */
CGameboard::CGameboard()
{
	for(int i=0; i<6; i++)
		for(int j=0; j<7; j++)
			grid[i][j] = ' ';
	moves = 0;
}

/* InsertMove ****************************************************************/
// This CGameboard member function will accept and int and a char as the
// column and turn respectively and will insert the move into the board.
// This will return a certain value depending on the state of the board after
// the insert
/* ------------------------------------------------------------------------- */
int CGameboard::InsertMove(int move, char turn)
{

	for(int i=5; i>=0; i--)
		if(grid[i][move] == ' ')		// if the space is blank
		{
			grid[i][move] = turn;

			/** Win detection code *************************************************/
			/***********************************************************************/

			// Check for vertical victory
			if(i<=2)
				if((grid[i][move] == grid[i+1][move]) && (grid[i][move] == grid[i+2][move]) &&
					(grid[i][move] == grid[i+3][move]))
					return WINNER;
			// End check

			// Check for horizontal victory
			if(move > 3)
				for(int j=6; j>=move; j--)
					if((grid[i][j] == grid[i][j-1]) && (grid[i][j] == grid[i][j-2]) &&
						 (grid[i][j] == grid[i][j-3]))
						return WINNER;
			if(move < 4)
				for(int j=0; j<=move; j++)
					if((grid[i][j] == grid[i][j+1]) && (grid[i][j] == grid[i][j+2]) &&
						 (grid[i][j] == grid[i][j+3]))
						return WINNER;
			// End check

			// Check for diagonal victory for inserts into the lower half of the board
			if(i>=3)
			{
				if(move<=3)
					if((grid[i][move] == grid[i-1][move+1]) && (grid[i][move] == grid[i-2][move+2]) &&
						 (grid[i][move] == grid[i-3][move+3]))
						return WINNER;
				if(move>=3)
					if((grid[i][move] == grid[i-1][move-1]) && (grid[i][move] == grid[i-2][move-2]) &&
						 (grid[i][move] == grid[i-3][move-3]))
						return WINNER;
				if(i<5)
				{
					if((move > 0) && (move < 5))
						if((grid[i][move] == grid[i+1][move-1]) && (grid[i][move] == grid[i-1][move+1]) &&
						   (grid[i][move] == grid[i-2][move+2]))
							return WINNER;
					if((move < 6) && (move > 1))
						if((grid[i][move] == grid[i+1][move+1]) && (grid[i][move] == grid[i-1][move-1]) &&
						   (grid[i][move] == grid[i-2][move-2]))
							return WINNER;
					if(i==3)
					{
						if((move > 1) && (move < 6))
							if((grid[i][move] == grid[i+2][move-2]) && (grid[i][move] == grid[i+1][move-1]) &&
								 (grid[i][move] == grid[i-1][move+1]))
								return WINNER;
						if((move < 5) && (move > 0))
							if((grid[i][move] == grid[i+2][move+2]) && (grid[i][move] == grid[i+1][move+1]) &&
								 (grid[i][move] == grid[i-1][move-1]))
								return WINNER;
					}						
				}
			}
			// End check

			// Check for diagonal victory for inserts into the upper half of the board
			if(i<3)
			{
				if(move<=3)
					if((grid[i][move] == grid[i+1][move+1]) && (grid[i][move] == grid[i+2][move+2]) &&
						 (grid[i][move] == grid[i+3][move+3]))
						return WINNER;
				if(move>=3)
					if((grid[i][move] == grid[i+1][move-1]) && (grid[i][move] == grid[i+2][move-2]) &&
						 (grid[i][move] == grid[i+3][move-3]))
						return WINNER;
				if(i>0)
				{
					if((move > 0) && (move < 5))
						if((grid[i][move] == grid[i-1][move-1]) && (grid[i][move] == grid[i+1][move+1]) &&
						   (grid[i][move] == grid[i+2][move+2]))
							return WINNER;
					if((move < 6) && (move > 1))
						if((grid[i][move] == grid[i-1][move+1]) && (grid[i][move] == grid[i+1][move-1]) &&
						   (grid[i][move] == grid[i+2][move-2]))
							return WINNER;
					if(i==2)
					{
						if((move > 1) && (move < 6))
							if((grid[i][move] == grid[i-2][move-2]) && (grid[i][move] == grid[i-1][move-1]) &&
								 (grid[i][move] == grid[i+1][move+1]))
								return WINNER;
						if((move < 5) && (move > 0))
							if((grid[i][move] == grid[i-2][move+2]) && (grid[i][move] == grid[i-1][move+1]) &&
								 (grid[i][move] == grid[i+1][move-1]))
								return WINNER;
					}						
				}
			}
			// End check

			/** End win detection code (this works, I promise) *********************/
			/***********************************************************************/
			
			// If increment the moves counter.  If it is 42 (the grid is full) then
			// return BOARD_FULL
			moves++;
			if(moves == 42)
				return BOARD_FULL;

			// If there was no winner then return MOVE_OK (0)
			return MOVE_OK;
		}
	
	// If the column is full then return COL_FULL (-1)
	return COL_FULL;
}

/* NumChildren ***************************************************************/
// This CGameboard member function will return the number of children of the
// board's state
/* ------------------------------------------------------------------------- */
int CGameboard::NumChildren()
{
	int children = 0;
	for(int i=0; i<7; i++)
		if(grid[0][i] == ' ')
			children++;
	return children;
}

/* sbe ***********************************************************************/
// This function will return the static board evaluation of the board's state
// Basically I am counting up the number of Xs or Os and the number of
// usable blank spaces.  For example, if there are 2 Xs and 2 spaces then
// the sbe would be added the value for having two Xs or Os in a row.
// However, if there was an oppenent blocking then no value would be added.
// For an example, if there were 2 Os, 1 X, and 1 space, then no value would
// be added.  This is done for all the possible ways to win.
/* ------------------------------------------------------------------------- */
int CGameboard::sbe()
{
	int num_x, num_o, num_space;
	int eval = 0;

	// this does the evaltion on vertical options
	for(int i=0; i<7; i++)
	{
		for(int j=5; j>2; j--)
		{
			num_x = num_o = num_space = 0;
			for(int k=0; k<4; k++)
			{
				if(grid[j-k][i] == 'X')
					num_x++;
				else if(grid[j-k][i] == 'O')
					num_o++;
				else if(grid[j-k][i] == ' ')
					num_space++;
			}
			eval += AddEval(num_x, num_o, num_space);
		}
	}

	// this does horizontal
	for(i=5; i>=0; i--)
	{
		for(int j=0; j<4; j++)
		{
			num_x = num_o = num_space = 0;
			for(int k=0; k<4; k++)
			{
				if(grid[i][j+k] == 'X')
					num_x++;
				else if(grid[i][j+k] == 'O')
					num_o++;
				else if(i == 5)
					num_space++;
				else if(grid[i+1][j+k] != ' ')
					num_space++;
			}
			eval += AddEval(num_x, num_o, num_space);
		}
	}

	// This does diagonal
	for(i=0; i<2; i++)
	{
		for(int j=0; j<4; j++)
		{
			num_x = num_o = num_space = 0;
			for(int k=0; k<4; k++)
			{
				if(grid[i+k][j+k] == 'X')
					num_x++;
				else if(grid[i+k][j+k] == 'O')
					num_o++;
				else if(grid[i+k+1][j+k] != ' ')
					num_space++;
			}
			eval += AddEval(num_x, num_o, num_space);
			num_x = num_o = num_space = 0;
			for(k=0; k<4; k++)
			{
				if(grid[i+k][6-j-k] == 'X')
					num_x++;
				else if(grid[i+k][6-j-k] == 'O')
					num_o++;
				else if(grid[i+k+1][6-j-k] != ' ')
					num_space++;
			}
			eval += AddEval(num_x, num_o, num_space);
		}
	}

	for(int j=0; j<4; j++)
	{
		num_x = num_o = num_space = 0;
		for(int k=0; k<4; k++)
		{
			if(grid[5-k][j+k] == 'X')
				num_x++;
			else if(grid[5-k][j+k] == 'O')
				num_o++;
			else if(k==0)
				num_space++;
			else if(grid[5-k+1][j+k] != ' ')
				num_space++;
		}
		eval += AddEval(num_x, num_o, num_space);
		num_x = num_o = num_space = 0;
		for(k=0; k<4; k++)
		{
			if(grid[5-k][6-j-k] == 'X')
				num_x++;
			else if(grid[5-k][6-j-k] == 'O')
				num_o++;
			else if(k==0)
				num_space++;
			else if(grid[5-k+1][6-j-k] != ' ')
				num_space++;
		}
		eval += AddEval(num_x, num_o, num_space);	
	}

	return eval;
}

/* ColumnFull ****************************************************************/
// This CGameboard member function will return whether or not a given column
// is full
/* ------------------------------------------------------------------------- */
bool CGameboard::ColumnFull(int col)
{
	return (grid[0][col] != ' ');
}

/* AddEval *******************************************************************/
// This is a CGameboard member function that is used by the sbe to add
// up the state of the board
/* ------------------------------------------------------------------------- */
int CGameboard::AddEval(int& x_val, int& o_val, int& space_val)
{
	int buf = 0;

	if((x_val + space_val) == 4)
	{
		switch(x_val)
		{
			case 1 :		buf += 2;
							break;
			case 2 :		buf += 5;
							break;
			case 3 :		buf += 100;
							break;
			case 4 :		buf += 100000000;
							break;
		}
	}
	if((o_val + space_val) == 4)
	{
		switch(o_val)
		{
			case 1 :		buf -= 5;
									break;
			case 2 :		buf -= 10;
									break;
			case 3 :		buf -= 4000;
									break;
			case 4 :		buf -= 100000;
		}
	}
	return buf;
}

/* OutputGameBoard ***********************************************************/
// Simple CGameboard member function to output the current state of the board
/* ------------------------------------------------------------------------- */
void CGameboard::OutputGameBoard()
{
	cout << "  1   2   3   4   5   6   7\n";
	cout << "+---------------------------+\n";
	for(int i=0; i<5; i++)
	{
		cout << "| " << grid[i][0] << " | " << grid[i][1] << " | "
			 << grid[i][2] << " | " << grid[i][3] << " | " << grid[i][4]
			 << " | " << grid[i][5] << " | " << grid[i][6] << " |\n";
		cout << "-----------------------------\n";
	}
	cout << "| " << grid[5][0] << " | " << grid[5][1] << " | "
		 << grid[5][2] << " | " << grid[5][3] << " | " << grid[5][4]
		 << " | " << grid[5][5] << " | " << grid[5][6] << " |\n";
	cout << "+---------------------------+\n";
}

