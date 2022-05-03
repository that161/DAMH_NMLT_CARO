#ifndef __MODEL_H__
#define __MODEL_H__
#include "VIEW.h"

void ResetData(int& _COMMAND, int& _X, int& _Y, bool& _TURN, _POINT _A[BOARD_SIZE][BOARD_SIZE]);
int CheckBoard(int, int, bool& _TURN, _POINT _A[BOARD_SIZE][BOARD_SIZE]);
int ProcessFinish(int pWhoWin, int _X, int _Y, bool& _TURN, _POINT _A[BOARD_SIZE][BOARD_SIZE], int&, int&, string, string);
int TestBoard(int, _POINT _A[BOARD_SIZE][BOARD_SIZE], int, int, int);

int CheckRow(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j);
int CheckCol(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j);
int CheckMainDiagonal(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j);
int CheckSubDiagonal(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j);

int BlockRow(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j, int count);
int BlockCol(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j, int count);
int BlockMainDiagonal(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j, int count);
int BlockSubDiagonal(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j, int count);

void Save(string fileName, fstream& myfile, int _X, int _Y, bool _TURN, int Limit, int demthang1, int demthang2, int demluot1, int demluot2, _POINT _A[BOARD_SIZE][BOARD_SIZE], string name1, string name2);
void Load(string fileName, fstream& myfile, int& _X, int& _Y, bool& _TURN, int& Limit, int& demthang1, int& demthang2, int& demluot1, int& demluot2, _POINT _A[BOARD_SIZE][BOARD_SIZE], string& name1, string& name2);
void LoadGame(string fileName, fstream& myfile, int& _COMMAND, int& _X, _POINT _A[BOARD_SIZE][BOARD_SIZE], int& line);
bool isFileExist(string name);
vector<string> getAllFileName(string director);

#endif
