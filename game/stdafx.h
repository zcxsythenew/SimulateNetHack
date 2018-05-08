#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <termios.h>
#include <list>
#include <queue>

using namespace std;

void StartGame();
char _getch();
void ShowPoint(const char &, const bool & = false);

extern int status;

struct Point
{
	int x;
	int y;
};