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
	while (1) {
		clean = false;
		while (clean == false)
		{
			clean = strg.update();
		}
		//------
		std::cout << "X Variable 1 eingeben!";
		std::cin >> x;

		std::cout << "Y Variable 1 eingeben!";
		std::cin >> y;

		std::cout << "Where to move bubble? (L=left;R=right;U=up;D=down)";
		std::cin >> input;


		if (strg.checkValidInput(x, y, input) == 1) {
			strg.makemove(x, y, input);
		}
		//------
		strg.update();
		
	}

	//strg.bubs[1][1].setx(4);
	//std::cout << strg.bubs[1][1].getx();
	//std::cout << strg.feld.bubs[1][1].getx();
	return 0;
}