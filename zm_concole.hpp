#pragma once


#include <windows.h>


inline void gotoxy(int x, int y)
{
	COORD c;
	c.X = x - 1;
	c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

inline void cleanConsole()
{
	system("cls");
}
