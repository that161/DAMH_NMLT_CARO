#include "CONTROL.h"

void StartGame(int& _COMMAND, int& _X, int& _Y, bool& _TURN, _POINT _A[BOARD_SIZE][BOARD_SIZE])   //Bat dau game
{
	system("cls");
	FixConsoleColor(15);
	ResetData(_COMMAND, _X, _Y, _TURN, _A);  // Khoi tao du lieu goc
	DrawBoard(BOARD_SIZE); // Ve man hinh game
	FixConsoleColor(240);
}

void MoveRight(int& _X, int& _Y, _POINT _A[BOARD_SIZE][BOARD_SIZE])  //Di chuyen ben phai
{
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x)
	{
		_X += 4;
		GoToXY(_X, _Y);
	}
}

void MoveLeft(int& _X, int& _Y, _POINT _A[BOARD_SIZE][BOARD_SIZE])  //Di chuyen ben trai
{
	if (_X > _A[0][0].x)
	{
		_X -= 4;
		GoToXY(_X, _Y);
	}
}

void MoveDown(int& _X, int& _Y, _POINT _A[BOARD_SIZE][BOARD_SIZE])   //Di chuyen xuong
{
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y)
	{
		_Y += 2;
		GoToXY(_X, _Y);
	}
}

void MoveUp(int& _X, int& _Y, _POINT _A[BOARD_SIZE][BOARD_SIZE])   //Di chuyen len
{
	if (_Y > _A[0][0].y)
	{
		_Y -= 2;
		GoToXY(_X, _Y);

	}
}

int Control(bool _TURN, int& _X, int& _Y, _POINT _A[BOARD_SIZE][BOARD_SIZE], int& _COMMAND, string name1, string name2) //Dieu khien va danh dau
{
	if (_TURN == true)
	{
		GoToXY(56, 5);
		FixConsoleColor(242);
		cout << "PLAYER 1 : " << name1;
		GoToXY(87, 5);
		cout << "                            ";
		GoToXY(_X, _Y);
		do {
			_COMMAND = toupper(_getch());
			if (_COMMAND == 65) MoveLeft(_X, _Y, _A);	//A
			else if (_COMMAND == 87) MoveUp(_X, _Y, _A);	//S
			else if (_COMMAND == 83) MoveDown(_X, _Y, _A);		//W
			else if (_COMMAND == 68) MoveRight(_X, _Y, _A);		//D
			else if (_COMMAND == 27)
			{
				Exit();
			}
		} while ((_COMMAND != 32) && (_COMMAND != 'L'));
	}
	else
	{
		GoToXY(87, 5);
		FixConsoleColor(244);
		cout << "PLAYER 2 : " << name2;
		GoToXY(56, 5);
		cout << "                            ";
		GoToXY(_X, _Y);
		do {
			_COMMAND = toupper(_getch());
			if (_COMMAND == 75) MoveLeft(_X, _Y, _A);	//K
			else if (_COMMAND == 72) MoveUp(_X, _Y, _A);	//H
			else if (_COMMAND == 80) MoveDown(_X, _Y, _A);	//P
			else if (_COMMAND == 77) MoveRight(_X, _Y, _A);	//M
			else if (_COMMAND == 27)
			{
				Exit();
			}
		} while ((_COMMAND != 13) && (_COMMAND != 'L'));
	}
	return _COMMAND;
}