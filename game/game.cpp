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
	cout << "\033[" << player.GetX() << ";" << player.GetY() << "H";
	unsigned long long c = 0;
	while (status == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			c = _getch();
		}
		cout << "\033[" << player.GetX() << ";" << player.GetY() << "H";
		switch (c)
		{
		case 65: //up
			player.MoveUp();
			break;
		case 66: //down
			player.MoveDown();
			break;
		case 67: //right
			player.MoveRight();
			break;
		case 68: //left
			player.MoveLeft();
			break;
		}
		//cout << (unsigned long long)c << endl;
	}
}