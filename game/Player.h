#pragma once
#include "stdafx.h"
#include "Square.h"

class Player
{
public:
	Player(const int & = 5);
	void Place(const int &, const int &);
	void Place(const int &, const int &, Square &);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void ShowPlace(const bool & = false);
	void ShowPoint(const char &, const bool & = false);
	const int &GetX();
	const int &GetY();
	~Player();
private:
	int hp;
	int currentX;
	int currentY;
	void MoveTo(const int, const int);
	Square *square;
	
};

