#include "MODEL.h"

void ResetData(int& _COMMAND, int& _X, int& _Y, bool& _TURN, _POINT _A[BOARD_SIZE][BOARD_SIZE]) //Ham khoi tao du lieu mac dinh cho ma tran ban co
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_A[i][j].x = 4 * j + LEFT + 2; // Trung voi hoanh do man hinh ban co
			_A[i][j].y = 2 * i + TOP + 1; // Trung voi tung do man hinh ban co
			_A[i][j].c = 0; // 0 nghia la chua ai danh dau, neu danh dau phai theo quy dinh nhu sau: -1 là luot true danh, 1 là luot false danh
		}
	}
	_TURN = true; _COMMAND = -1; // gan luot va phim mac dinh
	_X = _A[0][0].x; _Y = _A[0][0].y; // thiet lap lai toa do man hinh ban dau
}

int CheckBoard(int pX, int pY, bool& _TURN, _POINT _A[BOARD_SIZE][BOARD_SIZE])         //Ham danh dau vao ma tran ban co
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0)
			{
				if (_TURN == true) _A[i][j].c = -1; // Neu luot hien hanh la true thi c = -1
				else _A[i][j].c = 1; // Neu luot hien hanh la false thi c = 1
				return _A[i][j].c;
			}
		}
	}
	return 0;
}

int TestBoard(int Limit, _POINT _A[BOARD_SIZE][BOARD_SIZE], int pX, int pY, int c) //Ham kiem tra dieu kien thang thua
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].x == pX && _A[i][j].y == pY)
			{
				if (_A[i][j].c == c)
				{
					if ((CheckRow(_A, c, i, j) == c) || (CheckCol(_A, c, i, j) == c) || (CheckMainDiagonal(_A, c, i, j) == c) || (CheckSubDiagonal(_A, c, i, j) == c)) return c;
					else if (Limit == 144) return 0;
					else return 2;
				}
			}
		}
	}
}

int ProcessFinish(int pWhoWin, int _X, int _Y, bool& _TURN, _POINT _A[BOARD_SIZE][BOARD_SIZE], int& demthang1, int& demthang2, string name1, string name2) //Ham xu ly khi nguoi choi thang/thua
{
	int dem = 0, mau = 241;
	switch (pWhoWin)
	{
	case 1: case -1: case 0:
	{
		PlaySound(L"WIN.wav", NULL, SND_FILENAME | SND_ASYNC);
		if (pWhoWin == -1) demthang1++;
		else if (pWhoWin == 1) demthang2++;
		do {
			FixConsoleColor(mau);
			GoToXY(72, 15);
			cout << "* * * * * * * * * * * * * * * * *";
			GoToXY(72, 16);
			cout << "*                               *";
			GoToXY(74, 17);
			if (pWhoWin == -1)
				cout << "WINNER IS:	" << name1;
			if (pWhoWin == 1)
				cout << "WINNER IS:	" << name2;
			if (pWhoWin == 0)
				cout << "      DRAW      ";

			GoToXY(72, 17);
			cout << "*";
			GoToXY(104, 17);
			cout << "*";
			GoToXY(72, 18);
			cout << "*                               *";
			GoToXY(72, 19);
			cout << "* * * * * * * * * * * * * * * * *";
			if (mau == 254) mau = 239;
			mau++;
			dem++;
			Sleep(150);
		} while (dem < 30);
		break;
	}
	case 2:
		_TURN = !_TURN; // Doi luot neu khong co gi xay ra
		break;
	}
	return pWhoWin;
}

int CheckRow(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j)  //Kiem tra hang
{
	int count = 1, k = 1, chan;
	while ((_A[i][j - 1].c == c) && (j - 1 >= 0))    //doi vi tri kiem tra sang ben trai
		j--;
	while ((_A[i][j + k].c == c) && (j + k < BOARD_SIZE))    //Kiem tra tu trai sang phai
	{
		count++;
		k++;
		if (count == 4)
		{
			chan = BlockRow(_A, c, i, j, count);
			if (chan == 0) return c;
		}
		else
		if (count == 5)
		{
			chan = BlockRow(_A, c, i, j, count);
			if (chan != 2) return c;
			break;
		}
	}
	return 2;
}

int CheckCol(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j)  //Kiem tra cot
{
	int count = 1, k = 1, chan;
	while ((_A[i - 1][j].c == c) && (i - 1 >= 0))    //doi vi tri kiem tra sang phia tren
		i--;
	while ((_A[i + k][j].c == c) && (i + k < BOARD_SIZE))    //Kiem tra tu tren xuong duoi
	{
		count++;
		k++;
		if (count == 4)
		{
			chan = BlockCol(_A, c, i, j, count);
			if (chan == 0) return c;
		}
		else
		if (count == 5)
		{
			chan = BlockCol(_A, c, i, j, count);
			if (chan != 2) return c;
			break;
		}
	}
	return 2;
}

int CheckMainDiagonal(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j)    // Kiem tra duong cheo
{
	int count = 1, k = 1, chan;
	while ((_A[i - 1][j - 1].c == c) && (i - 1 >= 0) && (j - 1 >= 0))    //doi vi tri kiem tra sang phia tren ben trai
	{
		i--;
		j--;
	}
	while ((_A[i + k][j + k].c == c) && (i + k < BOARD_SIZE) && (j + k < BOARD_SIZE))    //Kiem tra cheo xuong
	{
		count++;
		k++;
		if (count == 4)
		{
			chan = BlockMainDiagonal(_A, c, i, j, count);
			if (chan == 0) return c;
		}
		else
		if (count == 5)
		{
			chan = BlockMainDiagonal(_A, c, i, j, count);
			if (chan != 2) return c;
			break;
		}
	}
	return 2;
}

int CheckSubDiagonal(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j)
{
	int count = 1, k = 1, chan;
	while ((_A[i + 1][j - 1].c == c) && (i + 1 < BOARD_SIZE) && (j - 1 >= 0))    //doi vi tri kiem tra sang ben phia duoi ben trai
	{
		i++;
		j--;
	}
	while ((_A[i - k][j + k].c == c) && (i - k >= 0) && (j + k < BOARD_SIZE))    //Kiem tra cheo len
	{
		count++;
		k++;
		if (count == 4)
		{
			chan = BlockSubDiagonal(_A, c, i, j, count);
			if (chan == 0) return c;
		}
		else
		if (count == 5)
		{
			chan = BlockSubDiagonal(_A, c, i, j, count);
			if (chan != 2) return c;
			break;
		}
	}
	return 2;
}

int BlockRow(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j, int count)
{
	int chan = 0;
	if (count == 4)
	{
		if ((_A[i][j - 1].c == -c) || (_A[i][j - 2].c == -c) || (j - 1 < 0) || (j - 2 < 0)) chan++;
		if ((_A[i][j + 4].c == -c) || (_A[i][j + 5].c == -c) || (j + 4 >= BOARD_SIZE) || (j + 5 >= BOARD_SIZE)) chan++;
	}
	if (count == 5)
	{
		if ((_A[i][j - 1].c == -c) || (j - 1 < 0)) chan++;
		if ((_A[i][j + 5].c == -c) || (j + 5 >= BOARD_SIZE)) chan++;
	}
	return chan;
}

int BlockCol(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j, int count)
{
	int chan = 0;
	if (count == 4)
	{
		if ((_A[i - 1][j].c == -c) || (_A[i - 2][j].c == -c) || (i - 1 < 0)) chan++;
		if ((_A[i + 4][j].c == -c) || (_A[i + 5][j].c == -c) || (i + 4 >= BOARD_SIZE)) chan++;
	}
	if (count == 5)
	{
		if ((_A[i - 1][j].c == -c) || (i - 1 < 0)) chan++;
		if ((_A[i + 5][j].c == -c) || (i + 5 >= BOARD_SIZE)) chan++;
	}
	return chan;
}

int BlockMainDiagonal(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j, int count)
{
	int chan = 0;
	if (count == 4)
	{
		if ((_A[i - 1][j - 1].c == -c) || (_A[i - 2][j - 2].c == -c) || (i - 1 < 0) || (j - 1 < 0) || (i - 2 < 0) || (j - 2 < 0)) chan++;
		if ((_A[i + 4][j + 4].c == -c) || (_A[i + 5][j + 5].c == -c) || (i + 4 >= BOARD_SIZE) || (j + 4 >= BOARD_SIZE) || (i + 5 >= BOARD_SIZE) || (j + 5 >= BOARD_SIZE)) chan++;
	}
	if (count == 5)
	{
		if ((_A[i - 1][j - 1].c == -c) || (i - 1 < 0) || (j - 1 < 0)) chan++;
		if ((_A[i + 5][j + 5].c == -c) || (i + 5 >= BOARD_SIZE) || (j + 5 >= BOARD_SIZE)) chan++;
	}
	return chan;
}

int BlockSubDiagonal(_POINT _A[BOARD_SIZE][BOARD_SIZE], int c, int i, int j, int count)
{
	int chan = 0;
	if (count == 4)
	{
		if ((_A[i + 1][j - 1].c == -c) || (_A[i + 2][j - 2].c == -c) || (i + 1 >= BOARD_SIZE) || (j - 1 < 0) || (i + 2 >= BOARD_SIZE) || (j - 2 < 0)) chan++;
		if ((_A[i - 4][j + 4].c == -c) || (_A[i - 5][j + 5].c == -c) || (i - 4 < 0) || (j + 4 >= BOARD_SIZE) || (i - 5 < 0) || (j + 5 >= BOARD_SIZE)) chan++;
	}
	if (count == 5)
	{
		if ((_A[i + 1][j - 1].c == -c) || (i + 1 >= BOARD_SIZE) || (j - 1 < 0)) chan++;
		if ((_A[i - 5][j + 5].c == -c) || (i - 5 < 0) || (j + 5 >= BOARD_SIZE)) chan++;
	}
	return chan;
}

void Save(string fileName, fstream& myfile, int _X, int _Y, bool _TURN, int Limit, int demthang1, int demthang2, int demluot1, int demluot2, _POINT _A[BOARD_SIZE][BOARD_SIZE], string name1, string name2) //Luu thong tin
{
	myfile.open(fileName + ".txt", ios::out | ios::trunc | ios::binary);
	myfile << name1 << "\n";
	myfile << name2 << "\n";
	myfile << _X << "\n";
	myfile << _Y << "\n";
	myfile << _TURN << "\n";
	myfile << Limit << "\n";;
	myfile << demthang1 << "\n";
	myfile << demluot1 << "\n";
	myfile << demthang2 << "\n";
	myfile << demluot2 << "\n";

	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			myfile << _A[i][j].x << "\n";
			myfile << _A[i][j].y << "\n";
			myfile << _A[i][j].c << "\n";
		}
	myfile.close();
	FixConsoleColor(240);
}

void Load(string fileName, fstream& myfile, int& _X, int& _Y, bool& _TURN, int& Limit, int& demthang1, int& demthang2, int& demluot1, int& demluot2, _POINT _A[BOARD_SIZE][BOARD_SIZE], string& name1, string& name2)
{
	system("cls");

	myfile.open(fileName + ".txt", ios::in | ios::binary);
	while (!myfile.eof())
	{
		myfile >> name1;
		myfile >> name2;
		myfile >> _X;
		myfile >> _Y;
		myfile >> _TURN;
		myfile >> Limit;
		myfile >> demthang1;
		myfile >> demluot1;
		myfile >> demthang2;
		myfile >> demluot2;

		for (int i = 0; i < BOARD_SIZE; i++)
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				myfile >> _A[i][j].x;
				myfile >> _A[i][j].y;
				myfile >> _A[i][j].c;
				if (_A[i][j].c == -1)
				{
					FixConsoleColor(242);
					GoToXY(_A[i][j].x, _A[i][j].y);
					cout << 'X';
				}
				else if (_A[i][j].c == 1)
				{
					FixConsoleColor(244);
					GoToXY(_A[i][j].x, _A[i][j].y);
					cout << 'O';
				}
			}
	}
	myfile.close();
	DrawBoard(BOARD_SIZE);
}