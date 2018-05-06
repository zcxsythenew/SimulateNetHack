#pragma once
#include "stdafx.h"

class Square
{
public:
	Square(const int &, const int &, const int &, const int &, const int & = 20, const int & = 15);
	const int uplimit;
	const int downlimit;
	const int leftlimit;
	const int rightlimit;
	int tX;
	int tY;
	char **GetMap();
	~Square();

private:
	char **map;
	const int height;
	const int width;
	int CheckWallNum(int x, int y);
	void DirectionHelper(int &, int &, const int &);
	bool CheckWallAvailable(int, int, const int & = 0);
};

