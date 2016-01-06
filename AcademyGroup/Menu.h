#pragma once

#include <Windows.h>

struct menu_item
{
	char *text;
	bool (*command)();
};

class Menu
{
	COORD c;
	const menu_item *list;
	HANDLE h;
	enum keys{ ESC = 27, UP = 72, DOWN = 80, ENTER = 13 };
	const unsigned int Nmenu;
public:
	Menu(unsigned int n, const menu_item *list, COORD c = { 0, 0 });
	void MenuShow() const;	//	меню
};

