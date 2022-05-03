
#include "VIEW.h"
#include "MODEL.h"
#include "CONTROL.h"

int _COMMAND; // Bien nhan gia tri phim nguoi dung nhap
int _X, _Y; //Toa do hien hanh tren man hinh ban co
bool _TURN;//true: nguoi thu nhat, false: nguoi thu hai
_POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma tran ban co
fstream myfile;
string name1; // ten nguoi choi 1
string name2; // ten nguoi choi 2

void main()
{
	PlaySound(TEXT("NEN.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	system("cls");
	loading();
	FixConsoleWindow();
	bool validEnter = true; //bien kiem tra o co da danh dau chua
	int Limit = 0; //bien gioi han ban co
	int Check; //bien kiem tra thang thua
	int control; //bien danh dau con co
	int demthang1, demthang2; //dem so van thang cua nguoi choi
	int demluot1 = 0, demluot2 = 0; //dem so nuoc ma nguoi choi da di
	int line; // dong trong menu
	bool Saved = false; // da luu game tu truoc
	string currentFileName = "";

	while (1)
	{
	X:FixConsoleColor(255);
		
		ResetData(_COMMAND, _X, _Y, _TURN, _A);
		Menu(_COMMAND, _X, _A, line);
		if (_COMMAND == 13)
		{
			if (line == 13) //tro choi moi
			{
				Name(name1, name2);
				StartGame(_COMMAND, _X, _Y, _TURN, _A);
				demthang1 = 0;
				demthang2 = 0;
				Saved = false;
			Y:Statistic(demthang1, demthang2, demluot1, demluot2);
				while (1)
				{
					control = Control(_TURN, _X, _Y, _A, _COMMAND, name1, name2);
					if ((control == 13) || (control == 32))		// Nguoi dung danh dau man hinh tren ban co
					{
						switch (CheckBoard(_X, _Y, _TURN, _A))
						{
						case -1:
							PlaySound(TEXT("DANH.wav"), NULL, SND_FILENAME |SND_ASYNC);
							FixConsoleColor(242);
							cout << 'X';
							Limit++;
							demluot1++;
							Check = TestBoard(Limit, _A, _X, _Y, -1);
							break;
						case 1:
							PlaySound(TEXT("DANH.wav"), NULL, SND_FILENAME | SND_ASYNC);
							FixConsoleColor(244);
							cout << 'O';
							Limit++;
							demluot2++;
							Check = TestBoard(Limit, _A, _X, _Y, 1);
							break;
						case 0: validEnter = false; // Khi danh vao o da danh roi
						}
						Statistic(demthang1, demthang2, demluot1, demluot2);
						if (validEnter == true)
						{
							switch (ProcessFinish(Check, _X, _Y, _TURN, _A, demthang1, demthang2, name1, name2))
						case 1: case -1: case 0:
							{
								Statistic(demthang1, demthang2, demluot1, demluot2);
								_COMMAND = Continue();
								ResetData(_COMMAND, _X, _Y, _TURN, _A);
								demluot1 = 0;
								demluot2 = 0;
								Limit = 0;

								if (Saved == true)
								{
									Save(currentFileName, myfile, _X, _Y, _TURN, Limit, demthang1, demthang2, demluot1, demluot2, _A, name1, name2);
									GoToXY(75, 24);
									cout << "YOUR GAME IS SAVED!!!";
									toupper(_getch());
									goto X;
								}
									
								GoToXY(75, 22);	
								cout << "SAVING THE GAME!!";
								GoToXY(75, 23);
								cout << "Enter your file name: ";
								string fileName;
								cin >> fileName;
								GoToXY(75, 24);
								Save(fileName, myfile, _X, _Y, _TURN, Limit, demthang1, demthang2, demluot1, demluot2, _A, name1, name2);
								GoToXY(75, 25);
								cout << "YOUR GAME IS SAVED!!!";
								toupper(_getch());
								goto X;					
							}
						}
						validEnter = true;  // Mo khoa
					}
					else if (control == 'L')
					{
						if (Saved == true)
						{
							
							Save(currentFileName, myfile, _X, _Y, _TURN, Limit, demthang1, demthang2, demluot1, demluot2, _A, name1, name2);
							GoToXY(75, 19);
							cout << "YOUR GAME IS SAVED!!!";
							toupper(_getch());
							break;
						}

						GoToXY(75, 16);
						cout << "SAVING THE GAME!!";
						GoToXY(75, 17);
						cout << "Enter your file name: ";
						string fileName;
						cin >> fileName;
						GoToXY(75, 18);
						Save(fileName, myfile, _X, _Y, _TURN, Limit, demthang1, demthang2, demluot1, demluot2, _A, name1, name2);
						GoToXY(75, 19);
						cout << "YOUR GAME IS SAVED!!!";
						toupper(_getch());
						goto X;
					}
				}
			}
			else if (line == 15)
			{
				string fileName;
				bool hasError = false;
				Saved = true;
				do {
					system("cls");
					Sleep(100);
					LoadGame(fileName, myfile, _COMMAND, _X, _A, line);

					if (hasError) {
						GoToXY(45, 17);
						FixConsoleColor(252);
						cout << "Do not have that game!!!" << endl;
					}
					//FixConsoleColor(236);
					GoToXY(40, 15);
					FixConsoleColor(240);
					cout << "Enter game's name: ";
					cin >> fileName;
					if (isFileExist(fileName)) {
						FixConsoleColor(255);
						Load(fileName, myfile, _X, _Y, _TURN, Limit, demthang1, demthang2, demluot1, demluot2, _A, name1, name2);
						currentFileName = fileName;
					}
					else {
						hasError = true;
					}
				} while (!isFileExist(fileName));

				goto Y;
			}
			else if (line == 17)
			{
				_COMMAND = Help();
				if (_COMMAND == 27)
				{
					Exit();
				}
			}
			else if (line == 19)
			{
				Exit();
			}
		}
	}
}
