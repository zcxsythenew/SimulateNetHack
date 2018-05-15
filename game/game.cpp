#include "stdafx.h"
#include "Square.h"
#include "Player.h"

int status = 0;

void StartGame()
{
	system("clear");
	cout << "You are lucky! Full moon tonight." << endl;
	Square s(1, 5, 20, 80);
	Player player;
	player.Place(10, 10, s);
	cout << "\033[" << player.GetY() << ";" << player.GetX() << "H";
	unsigned long long c = 0;
	while (status == 0)
	{
		c = _getch();
		if (c == 27)
		{
			c = _getch();
			if (c == 91)
			{
				c = _getch();
				c -= 65;
			}
		}
		cout << "\033[" << player.GetY() << ";" << player.GetX() << "H";
		switch (c)
		{
		case 0: //up
		case '8':
			player.MoveUp();
			break;
		case 1: //down
		case '2':
			player.MoveDown();
			break;
		case 2: //right
		case '6':
			player.MoveRight();
			break;
		case 3: //left
		case '4':
			player.MoveLeft();
			break;
		case 'y':
		case 'Y':
		case '7':
			player.MoveY();
			break;
		case 'u':
		case 'U':
		case '9':
			player.MoveU();
			break;
		case 'b':
		case 'B':
		case '1':
			player.MoveB();
			break;
		case 'n':
		case 'N':
		case '3':
			player.MoveN();
			break;
		case '.':
		case '5':
			player.Rest();
			break;
		case 'a':
		case 'A':
			player.ApplyDagger();
			break;
		}
		//cout << (unsigned long long)c << endl;
	}
	if (status == 2)
	{
		cout << "\033[" << 2 << ";" << 1 << "H";
		cout << "Bye.                              " << endl;
	}
}