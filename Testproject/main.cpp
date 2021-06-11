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
		if (zug == 0)
		{
			strg.setscore(0);
			strg.update();
			zug++;
		}
		std::cout << "X Variable 1 eingeben!";
		std::cin >> x;

		std::cout << "Y Variable 1 eingeben!";
		std::cin >> y;

		if (static_cast<Bubble*>(strg.bubs[x][y])->getcol() != "purple")
		{

			std::cout << "Where to move bubble? (L=left;R=right;U=up;D=down)";

			std::cin >> input;
		}

		
		if (strg.checkValidInput(x,y,input)==1) {
			strg.makemove(x, y, input);
		}

		strg.analyze();
	}

	return 0;
}