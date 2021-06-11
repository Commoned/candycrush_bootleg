#include "Steuerung.h"
#include "Feld.h"
#include <iostream>

int x, y;
char input;

int main()
{
	Steuerung strg;
	bool clean=false;
	strg.feld.drawField(strg.bubs, 0);
	int zug=0; // temporary
	while (1)
	{
		clean = false;
		while (clean == false)
		{
			clean = strg.update();
		}

		std::cout << "X Variable 1 eingeben!";
		std::cin >> x;

		std::cout << "Y Variable 1 eingeben!";
		std::cin >> y;

		std::cout << "Where to move bubble? (L=left;R=right;U=up;D=down)";
		std::cin >> input;


		if (strg.checkValidInput(x, y, input) == 1) {
			strg.makemove(x, y, input);
		}
		else {
			std::cout << "Invalid Input" << std::endl;
		}
		strg.analyze();
	}

	return 0;
}