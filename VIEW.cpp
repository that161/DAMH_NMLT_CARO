#include "VIEW.h"
#include "CONTROL.h"
#include "MODEL.h"

void FixConsoleWindow() //Ham co dinh cua so
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GoToXY(int x, int y) //Ham dat toa do
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void DrawBoard(int pSize) //Ham ve ban co
{
	FixConsoleColor(240);
	char a = 196, b = 197, c = 179;
	for (int i = 0; i < pSize; i++)
	{
		for (int j = 0; j <= pSize; j++)
		{
			GoToXY(LEFT + 4 * i, TOP + 1 + j * 2);
			cout << c;
			GoToXY(LEFT + 1 + i * 4, TOP + 2 * j);
			cout << a << a << a;
			GoToXY(LEFT + 4 * 12, TOP + 1 + j * 2);
			cout << c;
		}
	}
	for (int l = 0; l <= pSize; l++)
	{
		for (int k = 0; k <= pSize; k++)
		{
			GoToXY(LEFT + 4 * l, TOP + 2 * k);
			cout << b;
		}
	}
	GoToXY(LEFT - 1, TOP + 25);
	cout << "                                                   ";
}

void FixConsoleColor(int k) // Ham doi mau chu
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, k);
}

void Menu(int& _COMMAND, int& _X, _POINT _A[BOARD_SIZE][BOARD_SIZE], int& line)
{
	char doc = 179, ngang = 196;
	char goc1 = 218, goc2 = 191, goc3 = 192, goc4 = 217;
	line = 13;
	_X = 47;
	system("cls");
	Sleep(100);
	FixConsoleColor(249);
	GoToXY(20, 4);
	cout << " 0000        0       0      0  00000      0000      0        0000       00";  Sleep(100);
	FixConsoleColor(250);
	GoToXY(20, 5);
	cout << "0           0  0     0 0  0 0  0         0         0  0     0    0    0    0";  Sleep(100);
	FixConsoleColor(246);
	GoToXY(20, 6);
	cout << "0   000    0 00 0    0  00  0  00000     0        0 00 0    0 0      0      0";   Sleep(100);
	FixConsoleColor(252);
	GoToXY(20, 7);
	cout << "0    0    0      0   0      0  0         0       0      0   0   0     0    0"; Sleep(100);
	FixConsoleColor(243);
	GoToXY(20, 8);
	cout << " 0000    0        0  0      0  00000      0000  0        0  0     0     00";  Sleep(100);
	GoToXY(54, 13);
	FixConsoleColor(237);
	cout << " NEW GAME";
	Sleep(100);
	GoToXY(54, 15);
	FixConsoleColor(236);
	cout << " LOAD GAME";
	Sleep(100);
	GoToXY(54, 17);
	FixConsoleColor(235);
	cout << " GAME GUIDE";
	Sleep(100);
	GoToXY(54, 19);
	FixConsoleColor(234);
	cout << " EXIT" << endl;
	FixConsoleColor(244);
	for (int j = 38; j < 79; j++)
	{
		GoToXY(j, 22);
		cout << ngang;
		GoToXY(116 - j, 10);
		cout << ngang;
		Sleep(25);
	}
	GoToXY(37, 10);
	cout << goc1;
	GoToXY(79, 22);
	cout << goc4;
	for (int i = 11; i < 23; i++)
	{
		GoToXY(37, i);
		cout << doc;
		GoToXY(79, 32 - i);
		cout << doc;
		Sleep(25);
	}
	GoToXY(79, 10);
	cout << goc2;
	GoToXY(37, 22);
	cout << goc3;
	Sleep(100);
	GoToXY(47, 13);
	cout << ">>";
	do {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 72)
		{
			if (line >= 15)
			{
				GoToXY(_X, line);
				cout << "  ";
				MoveUp(_X, line, _A);
				cout << ">>";
			}
		}
		else if (_COMMAND == 80)
		{
			if (line <= 17)
			{
				GoToXY(_X, line);
				cout << "  ";
				MoveDown(_X, line, _A);
				cout << ">>";
			}
		}
		else if (_COMMAND == 27) //Thoat
		{
			Exit();
		}
	} while (_COMMAND != 13);
}

bool isFileExist(string name) {
	fstream fileStream;
	fileStream.open(name + ".txt");
	if (fileStream.fail()) {
		return false;
	}

	return true;
}

vector<string> getAllFileName(string directory) {
	vector<string> files;
	WIN32_FIND_DATA fileData;
	wstring folder = wstring(directory.begin(), directory.end());
	HANDLE hFind = FindFirstFile(folder.c_str(), &fileData);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				wstring name(fileData.cFileName);
				files.push_back(string(name.begin(), name.end()));
			}
		} while (FindNextFile(hFind, &fileData));
		FindClose(hFind);
	}

	return files;
}

void LoadGame(string fileName, fstream& myfile, int& _COMMAND, int& _X, _POINT _A[BOARD_SIZE][BOARD_SIZE], int& line)
{

	char doc = 179, ngang = 196;
	char goc1 = 218, goc2 = 191, goc3 = 192, goc4 = 217;
	line = 13;
	_X = 47;
	system("cls");
	FixConsoleColor(249);
	GoToXY(20, 4);
	cout << " 0000        0       0      0  00000      0000      0        0000       00";
	FixConsoleColor(250);
	GoToXY(20, 5);
	cout << "0           0  0     0 0  0 0  0         0         0  0     0    0    0    0";
	FixConsoleColor(246);
	GoToXY(20, 6);
	cout << "0   000    0 00 0    0  00  0  00000     0        0 00 0    0 0      0      0";
	FixConsoleColor(252);
	GoToXY(20, 7);
	cout << "0    0    0      0   0      0  0         0       0      0   0   0     0    0";
	FixConsoleColor(243);
	GoToXY(20, 8);
	cout << " 0000    0        0  0      0  00000      0000  0        0  0     0     00";
	GoToXY(54, 13);
	FixConsoleColor(237);
	cout << " LOAD GAME";
	FixConsoleColor(248);
	GoToXY(40, 19);
	cout << "List Game:";

	vector<string> files = getAllFileName("*.txt");

	for (int i = 0; i < files.size(); i++) {
		GoToXY(40, 20 + i);
		cout << files[i].erase(files[i].length() - 4, 4) << endl;
	}
}

int Help()
{
	system("cls");
	GoToXY(50, 5);
	cout << "-----GAME GUIDE-----";
	Sleep(100);
	FixConsoleColor(242);
	GoToXY(23, 9);
	cout << "PLAYER 1 :";
	Sleep(200);
	GoToXY(13, 13);
	cout << "USING W, A, S, D TO MOVE";
	Sleep(200);
	GoToXY(13, 15);
	cout << "USING 'SPACE' TO MARK THE CHESS PIECES";
	Sleep(200);
	FixConsoleColor(244);
	GoToXY(72, 9);
	cout << "PLAYER 2:";
	Sleep(200);
	GoToXY(64, 13);
	cout << "USING ARROWS TO MOVE";
	Sleep(200);
	GoToXY(64, 15);
	cout << "USING 'ENTER' TO MARK THE CHESS PIECES";
	Sleep(200);
	FixConsoleColor(249);
	GoToXY(31, 18);
	cout << "Player who has enough five chess pieces in the row on the chess table ";
	Sleep(200);
	GoToXY(31, 20);
	cout << "and is not blocked two ends is winner";
	Sleep(200);
	FixConsoleColor(240);
	GoToXY(38, 23);
	cout << "L: SAVE GAME         Esc: EXIT";
	Sleep(200);
	GoToXY(10, 26);
	FixConsoleColor(241);
	cout << "(NOTE: WHEN SOMEONE WINS, THE GAME WILL STOP. IF YOU DO NOT WANT TO RESET DATA, CHOOSE TO CONTINUE)";
	Sleep(200);
	GoToXY(30, 28);
	cout << "(NOTE: CHOOSE NEW GAME, THE SYSTEM WILL RESET ALL DATA)";
	return toupper(_getch());
}

int Continue() //Ham xu ly sau khi ket thuc tro choi
{
	GoToXY(74, 26);
	FixConsoleColor(240);
	return 0;
}

void Statistic(int& demthang1, int& demthang2, int& demluot1, int& demluot2)   //Hma xu li dem so luot + so van thang 
{
	char goc1 = 218, goc2 = 191, goc3 = 192, goc4 = 217;
	char doc = 179, ngang = 196;
	FixConsoleColor(250);
	GoToXY(82, 1);
	cout << "GAME CARO";
	GoToXY(77, 3);
	FixConsoleColor(241);
	cout << "******************";
	FixConsoleColor(240);
	GoToXY(68, 7);
	cout << goc1;
	GoToXY(72, 7);
	cout << goc2;
	GoToXY(68, 9);
	cout << goc3;
	GoToXY(72, 9);
	cout << goc4;
	for (int i = 69; i <= 71; i++)
	{
		GoToXY(i, 7);
		cout << ngang;
		GoToXY(i, 9);
		cout << ngang;
	}
	GoToXY(68, 8);
	cout << doc;
	GoToXY(72, 8);
	cout << doc;
	GoToXY(98, 7);
	cout << goc1;
	GoToXY(102, 7);
	cout << goc2;
	GoToXY(98, 9);
	cout << goc3;
	GoToXY(102, 9);
	cout << goc4;
	for (int i = 99; i <= 101; i++)
	{
		GoToXY(i, 7);
		cout << ngang;
		GoToXY(i, 9);
		cout << ngang;
	}
	GoToXY(98, 8);
	cout << doc;
	GoToXY(102, 8);
	cout << doc;
	FixConsoleColor(242);
	GoToXY(70, 8);
	cout << "X";
	FixConsoleColor(244);
	GoToXY(100, 8);
	cout << "O";
	FixConsoleColor(249);
	GoToXY(63, 11);
	cout << "NUMBER OF WINS : " << demthang1;
	GoToXY(62, 13);
	cout << "NUMBER OF STEPS : " << demluot1;
	FixConsoleColor(253);
	GoToXY(93, 11);
	cout << "NUMBER OF WINS : " << demthang2;
	GoToXY(92, 13);
	cout << "NUMBER OF STEPS : " << demluot2;
	FixConsoleColor(240);
	GoToXY(103, 28);
	cout << "L  : SAVE GAME";
	GoToXY(103, 29);
	cout << "ESC: EXIT";
	GoToXY(102, 27);
	cout << goc1;
	GoToXY(120, 27);
	cout << goc2;
	for (int i = 103; i < 120; i++)
	{
		GoToXY(i, 27);
		cout << ngang;
	}
	for (int i = 28; i < 30; i++)
	{
		GoToXY(102, i);
		cout << doc;
	}
}

void Name(string& name1, string& name2)   // Ham nhap ten nguoi choi
{
	system("cls");
	FixConsoleColor(243);
	GoToXY(40, 9);
	cout << " CHOOSE THE NAME: ";
	FixConsoleColor(242);
	GoToXY(40, 11);
	cout << " PLAYER 1: ";
	cin >> name1;
	FixConsoleColor(244);
	GoToXY(40, 13);
	cout << " PLAYER 2: ";
	cin >> name2;
}

void Exit()   // Ham thoat game
{
	system("cls");
	FixConsoleColor(241);
	GoToXY(5, 5);
	cout << "00000000000  000     000      00000       00000    000  000    000     000       000   00000000    000     000"; Sleep(75);
	FixConsoleColor(242);
	GoToXY(5, 6);
	cout << "00000000000  000     000     000 000      000000   000  000  000        000     000   0000000000   000     000"; Sleep(75);
	FixConsoleColor(243);
	GoToXY(5, 7);
	cout << "    000      00000000000    000   000     000 000  000  00000            000   000   000      000  000     000"; Sleep(75);
	FixConsoleColor(244);
	GoToXY(5, 8);
	cout << "    000      00000000000   00000000000    000  000 000  00000               000      000      000  000     000"; Sleep(75);
	FixConsoleColor(245);
	GoToXY(5, 9);
	cout << "    000      000     000  0000000000000   000   000000  000  000            000       0000000000    000000000"; Sleep(75);
	FixConsoleColor(246);
	GoToXY(5, 10);
	cout << "    000      000     000 000         000  000    00000  000    000          000        00000000      0000000"; Sleep(75);
	GoToXY(0, 19);
	FixConsoleColor(240);
	exit(0);
}


void loading()
{
	system("color f0");
	for (int i = 249; i < 253; i++) {
		GoToXY(36, 1);
		FixConsoleColor(i);
		cout << "   000000000   000000000   000         000   000000000";
		GoToXY(36, 2);
		FixConsoleColor(i);
		cout << "000            000   000   000000   000000   000";
		GoToXY(36, 3);
		FixConsoleColor(i);
		cout << "000            000   000   000000   000000   000";
		GoToXY(36, 4);
		FixConsoleColor(i);
		cout << "000            000000000   000000000000000   000000000";
		GoToXY(36, 5);
		FixConsoleColor(i);
		cout << "000   000000   000   000   000   000   000   000";
		GoToXY(36, 6);
		FixConsoleColor(i);
		cout << "000      000   000   000   000         000   000";
		GoToXY(36, 7);
		FixConsoleColor(i);
		cout << "   000000000   000   000   000         000   000000000";


		GoToXY(36, 9);
		FixConsoleColor(i);
		cout << "   000000      000000000   000000000000      000000";
		GoToXY(36, 10);
		FixConsoleColor(i);
		cout << "000      000   000   000   000      000   000      000";
		GoToXY(36, 11);
		FixConsoleColor(i);
		cout << "000      000   000   000   000      000   000      000";
		GoToXY(36, 12);
		FixConsoleColor(i);
		cout << "000            000000000   000000000      000      000";
		GoToXY(36, 13);
		FixConsoleColor(i);
		cout << "000            000   000   000   000      000      000";
		GoToXY(36, 14);
		FixConsoleColor(i);
		cout << "000      000   000   000   000   000      000      000";
		GoToXY(36, 15);
		FixConsoleColor(i);
		cout << "   000000      000   000   000      000      000000";


		GoToXY(20, 19);
		FixConsoleColor(i);
		cout << "000         000   000   000      000000      000         000      000000   000000000";
		GoToXY(20, 20);
		FixConsoleColor(i);
		cout << "000000      000   000   000   000      000   000000   000000   000000000   000000   000000";
		GoToXY(20, 21);
		FixConsoleColor(i);
		cout << "000000      000000000   000   000      000   000000   000000   000000000            000000";
		GoToXY(20, 22);
		FixConsoleColor(i);
		cout << "000000000   000   000000000   000      000   000000000000000      000000         000000";
		GoToXY(20, 23);
		FixConsoleColor(i);
		cout << "000   000000000   000   000   000      000   000   000   000      000000            000000";
		GoToXY(20, 24);
		FixConsoleColor(i);
		cout << "000      000000   000   000   000      000   000         000      000000   000000   000000";
		GoToXY(20, 25);
		FixConsoleColor(i);
		cout << "000         000   000   000      000000      000         000      000000      000000000";


		Sleep(100);
	}
	system("cls");
	system("color f0");
	GoToXY(36, 1);
	FixConsoleColor(244);
	cout << "   000000000   000000000   000         000   000000000";
	GoToXY(36, 2);
	FixConsoleColor(244);
	cout << "000            000   000   000000   000000   000";
	GoToXY(36, 3);
	FixConsoleColor(244);
	cout << "000            000   000   000000   000000   000";
	GoToXY(36, 4);
	FixConsoleColor(244);
	cout << "000            000000000   000000000000000   000000000";
	GoToXY(36, 5);
	FixConsoleColor(244);
	cout << "000   000000   000   000   000   000   000   000";
	GoToXY(36, 6);
	FixConsoleColor(244);
	cout << "000      000   000   000   000         000   000";
	GoToXY(36, 7);
	FixConsoleColor(244);
	cout << "   000000000   000   000   000         000   000000000";
	GoToXY(36, 9);
	FixConsoleColor(244);
	cout << "   000000      000000000   000000000000      000000";
	GoToXY(36, 10);
	FixConsoleColor(244);
	cout << "000      000   000   000   000      000   000      000";
	GoToXY(36, 11);
	FixConsoleColor(244);
	cout << "000      000   000   000   000      000   000      000";
	GoToXY(36, 12);
	FixConsoleColor(244);
	cout << "000            000000000   000000000      000      000";
	GoToXY(36, 13);
	FixConsoleColor(244);
	cout << "000            000   000   000   000      000      000";
	GoToXY(36, 14);
	FixConsoleColor(244);
	cout << "000      000   000   000   000   000      000      000";
	GoToXY(36, 15);
	FixConsoleColor(244);
	cout << "   000000      000   000   000      000      000000";

	char a = 219;
	GoToXY(36, 20);
	cout << " Loading...\n";
	GoToXY(36, 22);
	for (int i = 1; i <= 50; i++)
	{
		for (int t = 0; t <= 8888888; t++);
		FixConsoleColor(244);
		cout << a;
	}

}
