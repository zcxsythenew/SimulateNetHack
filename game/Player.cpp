#include "Player.h"

Player::Player(const int &hp) : hp(hp), moves(0), currentX(0), currentY(0), dagger(0), medicalAid(0), square(NULL)
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

void Player::MoveY()
{
	if (currentX > square->leftlimit && currentY > square->uplimit)
	{
		MoveTo(currentX - 1, currentY - 1);
	}
	else
	{
		cout << "\033[" << currentY << ";" << currentX << "H";
	}
}

void Player::MoveU()
{
	if (currentX < square->rightlimit && currentY > square->uplimit)
	{
		MoveTo(currentX + 1, currentY - 1);
	}
	else
	{
		cout << "\033[" << currentY << ";" << currentX << "H";
	}
}

void Player::MoveB()
{
	if (currentX > square->leftlimit && currentY < square->downlimit)
	{
		MoveTo(currentX - 1, currentY + 1);
	}
	else
	{
		cout << "\033[" << currentY << ";" << currentX << "H";
	}
}

void Player::MoveN()
{
	if (currentX < square->rightlimit && currentY < square->downlimit)
	{
		MoveTo(currentX + 1, currentY + 1);
	}
	else
	{
		cout << "\033[" << currentY << ";" << currentX << "H";
	}
}

void Player::Rest()
{
	MoveTo(currentX, currentY);
}

void Player::ApplyDagger()
{
	if (dagger > 0)
	{
		int targetX;
		int targetY;
		cout << "\033[" << 2 << ";" << 1 << "H";
		cout << "                             ";
		cout << "\033[" << 2 << ";" << 1 << "H";
		cout << "In what direction? ";
		char c = _getch();
		if (c == 27)
		{
			c = _getch();
			if (c == 91)
			{
				c = _getch();
				c -= 65;
			}
		}
		switch (c)
		{
		case 0: //up
		case '8':
			targetX = currentX;
			targetY = currentY - 1;
			break;
		case 1: //down
		case '2':
			targetX = currentX;
			targetY = currentY + 1;
			break;
		case 2: //right
		case '6':
			targetX = currentX + 1;
			targetY = currentY;
			break;
		case 3: //left
		case '4':
			targetX = currentX - 1;
			targetY = currentY;
			break;
		case 'y':
		case 'Y':
		case '7':
			targetX = currentX - 1;
			targetY = currentY - 1;
			break;
		case 'u':
		case 'U':
		case '9':
			targetX = currentX + 1;
			targetY = currentY - 1;
			break;
		case 'b':
		case 'B':
		case '1':
			targetX = currentX - 1;
			targetY = currentY + 1;
			break;
		case 'n':
		case 'N':
		case '3':
			targetX = currentX + 1;
			targetY = currentY + 1;
			break;
		default:
			cout << "\033[" << 2 << ";" << 1 << "H";
			cout << "Invalid option.          ";
			cout << "\033[" << currentY << ";" << currentX << "H";
			return;
			break;
		}
		for (list<Monster>::iterator i = square->monster.begin(); i != square->monster.end(); i++)
		{
			if (i->GetX() == targetX && i->GetY() == targetY && i->IsAlive())
			{
				dagger--;
				i->Kill();
				cout << "\033[" << 2 << ";" << 1 << "H";
				cout << "The monster is killed.";
				ShowPlace();
				square->ShowMonsters();
				ShowTools();
				cout << "\033[" << currentY << ";" << currentX << "H";
				return;
			}
		}
		cout << "\033[" << 2 << ";" << 1 << "H";
		cout << "Monsters not found.          ";
		cout << "\033[" << currentY << ";" << currentX << "H";
	}
	else
	{
		cout << "\033[" << 2 << ";" << 1 << "H";
		cout << "                             ";
		cout << "\033[" << 2 << ";" << 1 << "H";
		cout << "You have no dagger. Pick one.";
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
	for (list<Monster>::iterator i = square->monster.begin(); i != square->monster.end(); i++)
	{
		if (i->IsAlive() && y == i->GetY() && x == i->GetX())
		{
			srand(time(NULL));
			if (rand() > (RAND_MAX / 3))
			{
				i->Hurt();
				CallMonsters();
			}
			else
			{
				CallMonsters();
				hp++;
				Hurt("You missed the monster! The monster bites!");
				if (hp <= 0)
				{
					return;
				}
			}
			ShowPlace();
			square->ShowMonsters();
			cout << "\033[" << currentY << ";" << currentX << "H";
			return;
		}
	}
	switch (square->GetMap()[y - square->uplimit][x - square->leftlimit])
	{
	case '.':
		ShowPlace(true);
		currentX = x;
		currentY = y;
		Place(currentX, currentY);
		CallMonsters();
		square->ShowMonsters();
		cout << "\033[" << currentY << ";" << currentX << "H";
		break;
	case '&':
		cout << "\033[" << 1 << ";" << 1 << "H";
		cout << "You win!                                         " << endl;
		status = 1;
		break;
	case '_':
	case '^':
		if (medicalAid > 0)
		{
			medicalAid--;
			hp++;
			ShowTools();
		}
		cout << "\033[" << 1 << ";" << 1 << "H";
		Hurt("You are caught by a trap!");
		ShowPlace(true);
		currentX = x;
		currentY = y;
		Place(currentX, currentY);
		CallMonsters();
		square->ShowMonsters();
		square->GetMap()[y - square->uplimit][x - square->leftlimit] = '^';
		cout << "\033[" << currentY << ";" << currentX << "H";
		break;
	case '(':
	case ')':
		*this += (square->GetMap()[y - square->uplimit][x - square->leftlimit]);
		square->GetMap()[y - square->uplimit][x - square->leftlimit] = '.';
		ShowPlace(true);
		currentX = x;
		currentY = y;
		Place(currentX, currentY);
		CallMonsters();
		square->ShowMonsters();
		cout << "\033[" << currentY << ";" << currentX << "H";
		break;
	default:
		square->ShowMonsters();
		cout << "\033[" << currentY << ";" << currentX << "H";
		break;
	}
}

void Player::Hurt(const string &tip)
{
	cout << "\033[" << 1 << ";" << 1 << "H";
	hp--;
	cout << tip << " HP = " << hp << "                             " << endl;
	if (hp <= 0)
	{
		ShowAns();
		status = 2;
	}
	else
	{
		square->ShowMonsters();
		cout << "\033[" << currentY << ";" << currentX << "H";
	}
}

void Player::ShowTools(char chr)
{
	cout << "\033[" << 30 << ";" << 1 << "H";
	if (chr == '(')
	{
		dagger++;
		cout << "You got a new dagger!     " << endl;
	}
	else if(chr == ')')
	{
		medicalAid++;
		cout << "You got a medical aid!     " << endl;
	}
	cout << "\033[" << 31 << ";" << 1 << "H";
	cout << "You now have: " << endl;
	cout << dagger << " daggers - You can use it to kill monsters by the probability of 100%.  " << endl << "    Press 'a' to apply it." << endl;
	cout << medicalAid << " medical aids - Your HP will recover after you're caught by a trap.  " << endl << "    It will be automatically used." << endl;
}

void Player::ShowAns()
{
	cout << "\033[" << square->tY + square->uplimit << ";" << square->tX + square->leftlimit << "H";
	ShowPoint(square->GetMap()[square->tY][square->tX]);
}

bool Player::CheckPlaceForMonster(Point newPoint, Point oldPoint)
{
		int mapy = newPoint.y - square->uplimit;
		int mapx = newPoint.x - square->leftlimit;
		if (square->GetMap()[mapy][mapx] == '.' || square->GetMap()[mapy][mapx] == '_' || square->GetMap()[mapy][mapx] == '^' || square->GetMap()[mapy][mapx] == '(' || square->GetMap()[mapy][mapx] == ')')
		{
			for (list<Monster>::iterator i = square->monster.begin(); i != square->monster.end(); i++)
			{
				if (i->GetY() == newPoint.y && i->GetX() == newPoint.x && i->IsAlive())
				{
					if (oldPoint.x == currentX && oldPoint.y == currentY)
					{
						Hurt("The monster bites!");
					}
					else
					{
						square->MoveMonster(*i, oldPoint.x, oldPoint.y);
					}
				}
			}
			return true;
		}
		else
		{
			return false;
		}
}

void Player::CallMonsters()
{
	int height = square->downlimit - square->uplimit + 1;
	int width = square->rightlimit - square->leftlimit + 1;
	bool map[200][200];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			map[i][j] = false;
		}
	}

	queue<Point> q;
	
	map[currentY - square->uplimit][currentX - square->downlimit] = true;
	q.push({ currentX, currentY });

	while (!q.empty())
	{
		Point p = q.front();
		q.pop();

		if (p.x > square->leftlimit)
		{
			if (p.y > square->uplimit)
			{
				if (!map[p.y - 1 - square->uplimit][p.x - 1 - square->leftlimit] && CheckPlaceForMonster({ p.x - 1,p.y - 1 }, p))
				{
					map[p.y - 1 - square->uplimit][p.x - 1 - square->leftlimit] = true;
					q.push({ p.x - 1,p.y - 1 });
				}
			}
			if (!map[p.y - square->uplimit][p.x - 1 - square->leftlimit] && CheckPlaceForMonster({ p.x - 1,p.y }, p))
			{
				map[p.y - square->uplimit][p.x - 1 - square->leftlimit] = true;
				q.push({ p.x - 1,p.y });
			}
			if (p.y < square->downlimit)
			{
				if (!map[p.y + 1 - square->uplimit][p.x - 1 - square->leftlimit] && CheckPlaceForMonster({ p.x - 1,p.y + 1 }, p))
				{
					map[p.y + 1 - square->uplimit][p.x - 1 - square->leftlimit] = true;
					q.push({ p.x - 1,p.y + 1 });
				}
			}
		}
		if (p.y > square->uplimit)
		{
			if (!map[p.y - 1 - square->uplimit][p.x - square->leftlimit] && CheckPlaceForMonster({ p.x,p.y - 1 }, p))
			{
				map[p.y - 1 - square->uplimit][p.x - square->leftlimit] = true;
				q.push({ p.x,p.y - 1 });
			}
		}
		if (p.y < square->downlimit)
		{
			if (!map[p.y + 1 - square->uplimit][p.x - square->leftlimit] && CheckPlaceForMonster({ p.x,p.y + 1 }, p))
			{
				map[p.y + 1 - square->uplimit][p.x - square->leftlimit] = true;
				q.push({ p.x,p.y + 1 });
			}
		}
		if (p.x < square->rightlimit)
		{
			if (p.y > square->uplimit)
			{
				if (!map[p.y - 1 - square->uplimit][p.x + 1 - square->leftlimit] && CheckPlaceForMonster({ p.x + 1,p.y - 1 }, p))
				{
					map[p.y - 1 - square->uplimit][p.x + 1 - square->leftlimit] = true;
					q.push({ p.x + 1,p.y - 1 });
				}
			}
			if (!map[p.y - square->uplimit][p.x + 1 - square->leftlimit] && CheckPlaceForMonster({ p.x + 1,p.y }, p))
			{
				map[p.y - square->uplimit][p.x + 1 - square->leftlimit] = true;
				q.push({ p.x + 1,p.y });
			}
			if (p.y < square->downlimit)
			{
				if (!map[p.y + 1 - square->uplimit][p.x + 1 - square->leftlimit] && CheckPlaceForMonster({ p.x + 1,p.y + 1 }, p))
				{
					map[p.y + 1 - square->uplimit][p.x + 1 - square->leftlimit] = true;
					q.push({ p.x + 1,p.y + 1 });
				}
			}
		}
	}
	moves++;
	moves %= 10;
	if (moves == 0)
	{
		square->AddMonster({ currentX - square->leftlimit,currentY - square->uplimit });
	}
}

Player::~Player()
{

}
