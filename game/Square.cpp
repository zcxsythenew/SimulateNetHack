#include "Square.h"

Square::Square(const int &x, const int &y, const int &height, const int &width, const int &walls, const int &traps, const int &monsters) : uplimit(y), downlimit(y + height - 1), leftlimit(x), rightlimit(x + width - 1), height(height), width(width)
{
	srand(time(NULL));
	map = new char*[height];
	for (int i = 0; i < height; i++)
	{
		map[i] = new char[width];
		for (int j = 0; j < width; j++)
		{
			map[i][j] = '.';
		}
	}

	//Build Walls
	for (int i = 0; i < walls; i++)
	{
		int x, y, direction;
		do
		{
			x = rand() % width;
			y = rand() % height;
		} while (!CheckWallAvailable(x, y));
		while (rand() > (RAND_MAX) / 100)
		{
			direction = rand() % 3;
			if (CheckWallAvailable(x, y, direction + 1))
			{
				DirectionHelper(x, y, direction + 1);
				map[y][x] = '#';
			}
			else
			{
				direction = rand() % 3;
				if (CheckWallAvailable(x, y, direction + 1))
				{
					DirectionHelper(x, y, direction + 1);
					map[y][x] = '#';
				}
				else
				{
					direction = rand() % 3;
					if (CheckWallAvailable(x, y, direction + 1))
					{
						DirectionHelper(x, y, direction + 1);
						map[y][x] = '#';
					}
					else
					{
						direction = rand() % 3;
						if (CheckWallAvailable(x, y, direction + 1))
						{
							DirectionHelper(x, y, direction + 1);
							map[y][x] = '#';
						}
						else
						{
							direction = rand() % 3;
							if (CheckWallAvailable(x, y, direction + 1))
							{
								DirectionHelper(x, y, direction + 1);
								map[y][x] = '#';
							}
							else
							{
								direction = rand() % 3;
								if (CheckWallAvailable(x, y, direction + 1))
								{
									DirectionHelper(x, y, direction + 1);
									map[y][x] = '#';
								}
								else
								{
									if (CheckWallAvailable(x, y, direction + 1))
									{
										DirectionHelper(x, y, direction + 1);
										map[y][x] = '#';
									}
									else
									{
										if (CheckWallAvailable(x, y, direction + 1))
										{
											DirectionHelper(x, y, direction + 1);
											map[y][x] = '#';
										}
										else
										{
											if (CheckWallAvailable(x, y, direction + 1))
											{
												DirectionHelper(x, y, direction + 1);
												map[y][x] = '#';
											}
											else
											{
												break;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	//place ring
	int maxWall = 0, tmpWall, targetX, targetY;
	for (int j = 0; j < width; j++)
	{
		for (int i = 0; i < height; i++)
		{
			if (map[i][j] != '#')
			{
				tmpWall = CheckWallNum(j, i);
				if (tmpWall > maxWall && !(i == j && i == 10))
				{
					maxWall = tmpWall;
					targetX = j;
					targetY = i;
				}
				else if (tmpWall == maxWall && !(i == j && i == 10) && rand() < (RAND_MAX / 3))
				{
					maxWall = tmpWall;
					targetX = j;
					targetY = i;
				}
			}
		}
	}
	map[targetY][targetX] = '&';
	tX = targetX;
	tY = targetY;

	//place traps
	//use '_' to represent unknown traps and '^' for known traps

	for (int i = 0; i < traps; i++)
	{
		int x = rand() % width;
		int y = rand() % height;
		if (map[y][x] == '.' && !(x == y && x == 10))
		{
			map[y][x] = '_';
		}
		else
		{
			i--;
		}
	}

	//place monsters and show
	for (int i = 0; i < monsters; i++)
	{
		int x = rand() % width;
		int y = rand() % height;
		if (map[y][x] == '.' || map[y][x] == '_')
		{
			monster.push_back(Monster(x + leftlimit, y + uplimit));
		}
		else
		{
			i--;
		}
	}
}

int Square::CheckWallNum(int x, int y)
{
	int ans = 0;
	if (x > 0)
	{
		if (y > 0)
		{
			ans += map[y - 1][x - 1] == '#';
		}
		ans += map[y][x - 1] == '#';
		if (y < height - 1)
		{
			ans += map[y + 1][x - 1] == '#';
		}
	}
	if (y > 0)
	{
		ans += map[y - 1][x] == '#';
	}
	if (y < height - 1)
	{
		ans += map[y + 1][x] == '#';
	}
	if (x < width - 1)
	{
		if (y > 0)
		{
			ans += map[y - 1][x + 1] == '#';
		}
		ans += map[y][x + 1] == '#';
		if (y < height - 1)
		{
			ans += map[y + 1][x + 1] == '#';
		}
	}
	return ans;
}

void Square::DirectionHelper(int &x, int &y, const int &direction)
{
	switch (direction)
	{
	case 1: //上
		y = y - 1;
		break;
	case 2: //下
		y = y + 1;
		break;
	case 3: //右
		x = x + 1;
		break;
	case 4: //左
		x = x - 1;
		break;
	}
}

bool Square::CheckWallAvailable(int x, int y, const int &direction)
{
	DirectionHelper(x, y, direction);
	if (x == y && x == 10)
	{
		return false;
	}
	bool ok = x < width - 1 && y < height - 1 && x > 0 && y > 0;
	if (!ok)
	{
		return false;
	}
	switch (direction)
	{
	case 0: //无方向
		ok = ok && map[y - 1][x - 1] == '.' && map[y - 1][x] == '.' && map[y - 1][x + 1] == '.' &&
			map[y][x - 1] == '.' && map[y][x + 1] == '.' &&
			map[y + 1][x - 1] == '.' && map[y + 1][x] == '.' && map[y + 1][x + 1] == '.';
		break;
	case 1: //上
		ok = ok && map[y - 1][x - 1] == '.' && map[y - 1][x] == '.' && map[y - 1][x + 1] == '.' &&
			map[y][x - 1] == '.' && map[y][x + 1] == '.';
		break;
	case 2: //下
		ok = ok && map[y][x - 1] == '.' && map[y][x + 1] == '.' &&
			map[y + 1][x - 1] == '.' && map[y + 1][x] == '.' && map[y + 1][x + 1] == '.';
		break;
	case 3: //右
		ok = ok && map[y - 1][x] == '.' && map[y - 1][x + 1] == '.' &&
			map[y][x + 1] == '.' &&
			map[y + 1][x] == '.' && map[y + 1][x + 1] == '.';
		break;
	case 4: //左
		ok = ok && map[y - 1][x - 1] == '.' && map[y - 1][x] == '.' &&
			map[y][x - 1] == '.' &&
			map[y + 1][x - 1] == '.' && map[y + 1][x] == '.';
		break;
	}
	return ok;
}


void Square::ShowMonsters()
{
	for (list<Monster>::iterator i = monster.begin(); i != monster.end(); i++)
	{
		if (i->IsAlive())
		{
			i->Show();
		}
	}
}

char **Square::GetMap()
{
	return map;
}

void Square::MoveMonster(Monster &m, int x, int y)
{
	cout << "\033[" << m.GetY() << ";" << m.GetX() << "H";
	ShowPoint(map[m.GetY() - uplimit][m.GetX() - leftlimit], true);
	m.MoveTo(x, y);
}

Square::~Square()
{
	if (map != NULL)
	{
		for (int i = 0; i < height; i++)
		{
			delete[] map[i];
		}
		delete[] map;
	}
}