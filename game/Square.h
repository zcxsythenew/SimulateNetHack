#pragma once
#include "stdafx.h"
#include "Monster.h"

class Square
{
public:
	Square(const int &, const int &, const int &, const int &, const int & = 20, const int & = 15, const int & = 1, const int & = 100);
	const int uplimit;
	const int downlimit;
	const int leftlimit;
	const int rightlimit;
	int tX;
	int tY;
	list<Monster> monster;
	void ShowMonsters();
	char **GetMap();
	void MoveMonster(Monster &, int, int);
	void AddMonster(Point avoid = { 0,0 });
	~Square();

private:
	char **map;
	const int height;
	const int width;
	int CheckWallNum(int x, int y);
	void DirectionHelper(int &, int &, const int &);
	bool CheckWallAvailable(int, int, const int & = 0);
	
};

