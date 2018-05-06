#include "Player.h"

Player::Player(const int &hp) : hp(hp), currentX(0), currentY(0), square(NULL)
{

}

void Player::Place(const int &x, const int &y)
{
	cout << "\033[" << y << ";" << x << "H";
	cout << "@";
	currentX = x;
	currentY = y;
	ShowPlace();
}

void Player::Place(const int &x, const int &y, Square &placement)
{
	square = &placement;
	Place(x, y);
}

void Player::MoveUp()
{
	if (currentY > square->uplimit)
	{
		MoveTo(currentX, currentY - 1);
	}
	else
	{
		cout << "\033[" << currentY << ";" << currentX << "H";
	}
}

void Player::MoveDown()
{
	if (currentY < square->downlimit)
	{
		MoveTo(currentX, currentY + 1);
	}
	else
	{
		cout << "\033[" << currentY << ";" << currentX << "H";
	}
}

void Player::MoveLeft()
{
	if (currentX > square->leftlimit)
	{
		MoveTo(currentX - 1, currentY);
	}
	else
	{
		cout << "\033[" << currentY << ";" << currentX << "H";
	}
}

void Player::MoveRight()
{
	if (currentX < square->rightlimit)
	{
		MoveTo(currentX + 1, currentY);
	}
	else
	{
		cout << "\033[" << currentY << ";" << currentX << "H";
	}
}

void Player::ShowPlace(const bool &gray)
{
	if (currentY - 1 >= square->uplimit)
	{
		if (currentX - 1 >= square->leftlimit)
		{
			cout << "\033[" << currentY - 1 << ";" << currentX - 1 << "H";
			ShowPoint(square->GetMap()[currentY - 1 - square->uplimit][currentX - 1 - square->leftlimit], gray);
		}
		cout << "\033[" << currentY - 1 << ";" << currentX << "H";
		ShowPoint(square->GetMap()[currentY - 1 - square->uplimit][currentX - square->leftlimit], gray);
		if (currentX + 1 <= square->rightlimit)
		{
			cout << "\033[" << currentY - 1 << ";" << currentX + 1 << "H";
			ShowPoint(square->GetMap()[currentY - 1 - square->uplimit][currentX + 1 - square->leftlimit], gray);
		}
	}
	if (currentX - 1 >= square->leftlimit)
	{
		cout << "\033[" << currentY << ";" << currentX - 1 << "H";
		ShowPoint(square->GetMap()[currentY - square->uplimit][currentX - 1 - square->leftlimit], gray);
	}
	if (currentX + 1 <= square->rightlimit)
	{
		cout << "\033[" << currentY << ";" << currentX + 1 << "H";
		ShowPoint(square->GetMap()[currentY - square->uplimit][currentX + 1 - square->leftlimit], gray);
	}
	if (currentY + 1 <= square->downlimit)
	{
		if (currentX - 1 >= square->leftlimit)
		{
			cout << "\033[" << currentY + 1 << ";" << currentX - 1 << "H";
			ShowPoint(square->GetMap()[currentY + 1 - square->uplimit][currentX - 1 - square->leftlimit], gray);
		}
		cout << "\033[" << currentY + 1 << ";" << currentX << "H";
		ShowPoint(square->GetMap()[currentY + 1 - square->uplimit][currentX - square->leftlimit], gray);
		if (currentX + 1 <= square->rightlimit)
		{
			cout << "\033[" << currentY + 1 << ";" << currentX + 1 << "H";
			ShowPoint(square->GetMap()[currentY + 1 - square->uplimit][currentX + 1 - square->leftlimit], gray);
		}
	}
	
}

void Player::ShowPoint(const char &chr, const bool &gray)
{
	if (chr == '&')
	{
		cout << "\033[33m";
	}
	else if (gray)
	{
		cout << "\033[36m";
	}
	if (chr == '_')
	{
		cout << '.';
	}
	else
	{
		cout << chr;
	}
	cout << "\033[0m";
}

const int &Player::GetX()
{
	return currentX;
}

const int &Player::GetY()
{
	return currentY;
}

void Player::MoveTo(const int x, const int y)
{
	switch (square->GetMap()[y - square->uplimit][x - square->leftlimit])
	{
	case '.':
		ShowPlace(true);
		currentX = x;
		currentY = y;
		Place(currentX, currentY);
		cout << "\033[" << currentY << ";" << currentX << "H";
		break;
	case '&':
		cout << "\033[" << 1 << ";" << 1 << "H";
		cout << "You win!                         " << endl;
		status = 1;
		break;
	case '_':
	case '^':
		cout << "\033[" << 1 << ";" << 1 << "H";
		hp--;
		cout << "You are caught by a trap! HP = " << hp << endl;
		ShowPlace(true);
		currentX = x;
		currentY = y;
		Place(currentX, currentY);
		square->GetMap()[y - square->uplimit][x - square->leftlimit] = '^';
		if (hp <= 0)
		{
			status = 2;
			cout << "\033[" << square->tY + square->uplimit << ";" << square->tX + square->leftlimit << "H";
			ShowPoint(square->GetMap()[square->tY][square->tX]);
			cout << "\033[" << 2 << ";" << 1 << "H";
			cout << "Bye." << endl;
		}
		else
		{
			cout << "\033[" << currentY << ";" << currentX << "H";
		}
		break;
	default:
		cout << "\033[" << currentY << ";" << currentX << "H";
		break;
	}
}

Player::~Player()
{

}
