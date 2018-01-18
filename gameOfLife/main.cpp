#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include "gameOfLife.h"


int main()
{
	std::srand(static_cast<int>(std::time(NULL)));
	GameOfLife obj;
	obj.setStartingState();
	while (!obj.checkIsOver()) {
		obj.update();
		obj.show();
		Sleep(500);
		system("CLS");
	}
	return 0;
}