#ifndef __VIEW_H__
#define __VIEW_H__
#include "Header.h"
#define LEFT 3 // Toa do trai man hinh ban co
#define TOP 1 // Toa do tren man hinh ban co
void FixConsoleWindow();
void GoToXY(int, int);
void DrawBoard(int);
void FixConsoleColor(int);
void Menu(int&, int&, _POINT _A[BOARD_SIZE][BOARD_SIZE], int&);
int Help();
int Continue();
void Statistic(int&, int&, int&, int&);
void Name(string& name1, string& name2);
void Exit();
void loading();
#endif
