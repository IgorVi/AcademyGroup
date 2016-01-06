#include <Windows.h>
#include <iostream>
#include <conio.h>

#include "Menu.h"

Menu::Menu(unsigned int n, const menu_item *list, COORD c) :
Nmenu(n),
list(list),
c(c)
{
	h = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Menu::MenuShow() const
{
	SetConsoleCursorPosition(h, c);
	int key, n = 0;

	do{
		SetConsoleCursorPosition(h, c);
		for (unsigned int i = 0; i < Nmenu; ++i)
		{
			if (i == n){
				SetConsoleTextAttribute(h, 0xA);
				std::cout << "# " << list[i].text << std::endl;
				SetConsoleTextAttribute(h, 0x7);
			}
			else
				std::cout << "  " << list[i].text << "\n";
		}

		key = _getch();
		if(key == ENTER)
		{
			if(!list[n].command())
				break;
		}
		else if (key == 224)
		{
			key = _getch();
			switch (key)
			{
			case UP:
				n == 0 ? n = Nmenu - 1 : n--;
				break;
			case DOWN:
				n == Nmenu - 1 ? n = 0 : n++;
				break;
			}
		}
	} while (key != ESC);
}