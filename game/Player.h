#pragma once
#include "stdafx.h"
#include "Square.h"

class Player
{
public:
	Player(const int & = 15);
	void Place(const int &, const int &);
	void Place(const int &, const int &, Square &);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveY();
	void MoveU();
	void MoveB();
	void MoveN();
	void Rest();
	void ApplyDagger();
	void ShowPlace(const bool & = false);
	const int &GetX();
	const int &GetY();
	~Player();
private:
	int hp;
	int moves;
	int currentX; //¶ÔÓÚÆÁÄ»¶øÑÔ
	int currentY;
	int dagger;
	int medicalAid;
	void MoveTo(const int, const int);
	void Hurt(const string &);
	void ShowTools(char = '\0');
	void ShowAns();
	bool CheckPlaceForMonster(Point, Point);
	void CallMonsters();
	Square *square;
	
};

