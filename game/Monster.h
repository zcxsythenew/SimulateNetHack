#pragma once
#include "stdafx.h"

class Monster
{
public:
	Monster(int, int, bool = true);
	~Monster();

	void Show();
	void Hurt();
	void Kill();
	void MoveTo(int, int);

	bool IsAlive();

	int GetX();
	int GetY();

private:
	int currentX; //¶ÔÓÚÆÁÄ»¶øÑÔ
	int currentY;
	int hp;
};

