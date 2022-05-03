#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "MODEL.h"
void StartGame(int& _COMMAND, int& _X, int& _Y, bool& _TURN, _POINT _A[BOARD_SIZE][BOARD_SIZE]);
void MoveLeft(int& _X, int& _Y, _POINT _A[BOARD_SIZE][BOARD_SIZE]);
void MoveRight(int& _X, int& _Y, _POINT _A[BOARD_SIZE][BOARD_SIZE]);
void MoveUp(int& _X, int& _Y, _POINT _A[BOARD_SIZE][BOARD_SIZE]);
void MoveDown(int& _X, int& _Y, _POINT _A[BOARD_SIZE][BOARD_SIZE]);
int Control(bool _TURN, int& _X, int& _Y, _POINT _A[BOARD_SIZE][BOARD_SIZE], int& _COMMAND, string, string);

#endif
