/*
Game of life is a zero-player game originally devised the British mathematician John Horton Conway in 1970.
It is the best-known example of a cellular automaton.The game is fully automated(except if user choose the option
to manually set game fields).
Game takes place on the fixed sized board,where each grid has one of two possible states-alive or dead.
In every iteration,methods check and calculate how many alive neighbours each grid has-the result is
written in the second array,then the second array shows result of current round.
Game has no goal-it will run as long as there are changes on the board.
*/


#pragma once

class GameOfLife
{
private:
	enum Sizes { INTERNAL_ROWS = 14, INTERNAL_COLUMNS = 18, EXTERNAL_ROWS = 16, EXTERNAL_COLUMNS = 20 };//Fixed array sizes
	enum CellState { DEAD, ALIVE };//Each grid can have one of these states
	enum Directions { FIRST_TO_SECOND, SECOND_TO_FIRST };//Possible assignment directions
	bool m_firstGameBoard[EXTERNAL_ROWS][EXTERNAL_COLUMNS];//There will be two same sized gameboards needed
	bool m_secondGameBoard[EXTERNAL_ROWS][EXTERNAL_COLUMNS];
	bool m_direction;//This boolean controls which board will be the giver and which will be the taker
	bool m_isOver;//This boolean controls whether game is over or not
	unsigned long m_iteration;//This variable counts each iteration
public:
	GameOfLife();
	void setStartingState();//Sets starting state of the gameboards
	short neighbourCount(bool gameBoard[][EXTERNAL_COLUMNS], const int &currentRow, const int &currentColumn)const;//Counts neighbours of each grid
	void update();//Updates the state of the gameboard before showing it
	bool nextRound(bool gameBoard[][EXTERNAL_COLUMNS], const int &currentRow, const int &currentColumn, const int &counter);//Set state each grid will have in the next round
	void show()const;//Shows state of the gameboard after current iteration
	bool checkIsOver()const;//Checks the conditions to finish the game
};