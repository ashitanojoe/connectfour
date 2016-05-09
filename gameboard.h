/*

	Filename			:				gameboard.h
	Programmer		:				Joe Waller
	Last Modified	:				04/16/2002
	Description		:				This file contains the class definition of the CGameboard
												class to be used by the Connect Four program.  This header file
												needs to be included in any file that uses the CGameboard class.

*/

class CGameboard
{
	public:
		CGameboard();
		int InsertMove(int move, char turn);
		void OutputGameBoard();
		int NumChildren();
		int sbe();			// static board evaluator
		int AddEval(int& x_val, int& o_val, int& space_val);
		bool ColumnFull(int col);

	private:
		char grid[6][7];
		int moves;
};
