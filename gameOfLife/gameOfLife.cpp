#include <iostream>
#include <cstdlib>
#include <ctime>
#include "gameOfLife.h"

/*
Default constructor will initialize all game fields with 0 value and set the first assignment direction
Whole gameboard is built with the external size,but the game actually takes place on the board with
internal size
*/
GameOfLife::GameOfLife()
{
	for (int y = 0; y < EXTERNAL_ROWS; ++y) {
		for (int x = 0; x < EXTERNAL_COLUMNS; ++x) {
			m_firstGameBoard[y][x] = DEAD;
			m_secondGameBoard[y][x] = DEAD;
		}
	}
	m_direction = FIRST_TO_SECOND;
	m_isOver = false;
	m_iteration = 0;
}

/*
This method will set the starting state of both gameboards.If user choose to assign game fields automatically,
the rand method will assign either dead or alive state randomly to the first game board.These values will be
also copied to the second board.
User may also decide to create a custom states' gameboard by setting each field manually.
*/
void GameOfLife::setStartingState()
{
	short choice = 0;
	do {
		std::cout << "Make choice: " << '\n';
		std::cout << "1.Set board state automatically" << '\n';
		std::cout << "2.Set board state manually" << '\n';
		std::cin >> choice;
	} while ((!(choice == 1)) && (!(choice == 2)));
	if (choice == 1) {
		for (int y = 1; y <= INTERNAL_ROWS; ++y) {
			for (int x = 1; x <= INTERNAL_COLUMNS; ++x) {
				m_firstGameBoard[y][x] = (std::rand() % 2);
				m_secondGameBoard[y][x] = m_firstGameBoard[y][x];
			}
		}
	}
	else if (choice == 2) {
		short setAlive = 0;
		std::cout << "All cells are dead at the beginning" << '\n';
		for (int y = 1; y <= INTERNAL_ROWS; ++y) {
			for (int x = 1; x <= INTERNAL_COLUMNS; ++x) {
				do {
					std::cout << "Do you wish to set cell on coordinate: " << y << ',' << x << " alive?" << '\n';
					std::cout << "Press 1 if yes,or 0 if no" << '\n';//as every grid is initialized with the state DEAD
					std::cin >> setAlive;
				} while ((!(setAlive == 0)) && (!(setAlive == 1)));
				if (setAlive == 1) {
					m_firstGameBoard[y][x] = ALIVE;
				}
				m_secondGameBoard[y][x] = m_firstGameBoard[y][x];
			}
		}
	}
}

/*
This method takes as a parameter one of the gameboards and coordinates, counts how many alive neighbours it has,
and returns the result.
*/
short GameOfLife::neighbourCount(bool gameBoard[][EXTERNAL_COLUMNS], const int &currentRow, const int &currentColumn)const
{
	short counter = 0;
	for (int y = (currentRow - 1); y <= (currentRow + 1); ++y) {//checks the state of the above and below grid
		for (int x = (currentColumn - 1); x <= (currentColumn + 1); ++x) {//checks the state of the left and right neigbour
			if (gameBoard[y][x])//if checked grid is alive,increment the counter
				++counter;
		}
	}
	if (gameBoard[currentRow][currentColumn])//if given grid is also alive,the counter must be decremented by one
		--counter;
	return counter;
}


/*
This method will actually update the state of gameboards.
It iterates through every single grid from 1 to (INTERAL_SIZE),and update the current state of the grid.
There are two boards which are switched after every round-one of boards is "the taker" of
the updated state of the other board,while in the next loop,the roles are switched.
*/
void GameOfLife::update()
{
	short neighbourCounter = 0;
	for (int y = 1; y <= INTERNAL_ROWS; ++y) {
		for (int x = 1; x <= INTERNAL_COLUMNS; ++x) {
			if (m_direction == FIRST_TO_SECOND) {
				neighbourCounter = neighbourCount(m_firstGameBoard, y, x);
				m_secondGameBoard[y][x] = nextRound(m_firstGameBoard, y, x, neighbourCounter);
			}
			else {
				neighbourCounter = neighbourCount(m_secondGameBoard, y, x);
				m_firstGameBoard[y][x] = nextRound(m_secondGameBoard, y, x, neighbourCounter);
			}
		}
	}
	m_direction = !m_direction;
	++m_iteration;
}

/*
This method will update the state of each grid.The current state depends from the game rules:
-The cell will be dead in the next round if it is alive but has less than 2 alive neighbours in this round
-The cell will be alive in the next round if it is alive and has 2 or 3 alive neighbours in this round
-The cell will be dead in the next round if it is alive and has more than 3 alive neighbours in this round
-The cell will be alive in the next round if it is dead but has exact 3 alive neighbours in this round
-If none of these conditions is true,the cell will have same state in the next round
*/
bool GameOfLife::nextRound(bool gameBoard[][EXTERNAL_COLUMNS], const int &currentRow, const int &currentColumn, const int &counter)
{
	if ((gameBoard[currentRow][currentColumn]) && (counter < 2)) {
		return DEAD;
	}
	else if ((gameBoard[currentRow][currentColumn]) && ((counter == 2) || (counter == 3))) {
		return ALIVE;
	}
	else if ((gameBoard[currentRow][currentColumn]) && (counter > 3)) {
		return DEAD;
	}
	else if (!(gameBoard[currentRow][currentColumn]) && (counter == 3)) {
		return ALIVE;
	}
	else {
		return (gameBoard[currentRow][currentColumn]);
	}
}

/*
This method shows the current state of the gameboard after each game iteration.
*/
void GameOfLife::show()const
{
	if (m_direction == FIRST_TO_SECOND) {
		for (int y = 0; y < EXTERNAL_ROWS; ++y) {
			std::cout << '\n';
			for (int x = 0; x < EXTERNAL_COLUMNS; ++x) {
				if (m_firstGameBoard[y][x])
					std::cout << '*';
				else
					std::cout << '.';
			}
		}
	}
	else {
		for (int y = 0; y < EXTERNAL_ROWS; ++y) {
			std::cout << '\n';
			for (int x = 0; x < EXTERNAL_COLUMNS; ++x) {
				if (m_secondGameBoard[y][x])
					std::cout << '*';
				else
					std::cout << '.';
			}
		}
	}
	std::cout << '\n';
}

/*
This method checks if the game over condition is true.
The game will end if there will be no changes in the current round comparing to the previous one
*/
bool GameOfLife::checkIsOver()const
{
	short allGrids = (INTERNAL_ROWS*INTERNAL_COLUMNS);
	short sameGridsCounter = 0;
	for (int y = 0; y < INTERNAL_ROWS; ++y) {
		for (int x = 0; x < INTERNAL_COLUMNS; ++x) {
			if (m_firstGameBoard[y][x] == m_secondGameBoard[y][x]) {
				++sameGridsCounter;
			}
		}
	}
	if ((sameGridsCounter == allGrids) && (m_iteration > 2)) {
		return true;
	}
	return false;
}



