#include "stdafx.h"

ifstream initializeFile;
string username;
bool fail = false;

char _getch()
{
	struct termios stored_settings;
	struct termios new_settings;
	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);

	char c;

	c = getchar();

	tcsetattr(0, TCSANOW, &stored_settings);

	return c;
}

bool TryAppendTextToFile(const string &fileName, const string &content, const bool &appendEndl = true)
{
	ofstream file;
	file.open(fileName, std::ios_base::openmode::_S_app);
	if (file.is_open())
	{
		file << content;
		if (appendEndl)
		{
			file << endl;
		}
		if (!file.fail())
		{
			file.close();
			return true;
		}
		else
		{
			file.close();
			return false;
		}
	}
	else
	{
		return false;
	}
}

void Initialize()
{
	if (!fail)
	{
		initializeFile.open("userInfo.txt");
		if (initializeFile.is_open())
		{
			initializeFile >> username;
			cout << "Hello " << username << "!" << endl;
			cout << "You are going to find the ring(&)." << endl;
			cout << "--More--";
			_getch();
			StartGame();
		}
		else
		{
			// The file does not exist. Take user to OOBE.

			ofstream oobeFile;
			oobeFile.open("userInfo.txt");
			oobeFile.close();
			cout << "Copyright 2018 Zcxsythenew" << endl;
			cout << endl;
			cout << "Who are you? ";
			getline(cin, username);
			if (TryAppendTextToFile("userInfo.txt", username))
			{
				Initialize();
			}
			else
			{
				remove("userInfo.txt");
				cout << "Errors occur when initializing the game. It has to exit." << endl;
				fail = true;
			}
		}
	}
}

int main()
{
	system("stty -echo");
	Initialize();
	system("stty echo");
    return 0;
}