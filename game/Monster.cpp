#include "Monster.h"

Monster::Monster(int x, int y, bool show) : currentX(x), currentY(y), hp(2)
{
	if (show)
	{
		Show();
	}
}


Monster::~Monster()
{
}

void Monster::Show()
{
	cout << "\033[" << currentY << ";" << currentX << "H";
	if (hp == 1)
	{
		cout << "\033[31m";
	}
	else
	{
		cout << "\033[32m";
	}
	cout << "M";
	cout << "\033[0m";
}

void Monster::Hurt()
{
	hp--;
}

void Monster::Kill()
{
	hp = 0;
}

void Monster::MoveTo(int x, int y)
{
	currentX = x;
	currentY = y;
	//Show();
}

bool Monster::IsAlive()
{
	return hp > 0;
}

int Monster::GetX()
{
	return currentX;
}

int Monster::GetY()
{
	return currentY;
}
