#include "Steuerung.h"
#include "Feld.h"
#include <iostream>

int main()
{
	Steuerung strg;
	
	strg.update();
	while (1)
	{
		strg.makemove();
		strg.analyze();
		strg.update();
	}

	//strg.bubs[1][1].setx(4);
	//std::cout << strg.bubs[1][1].getx();
	//std::cout << strg.feld.bubs[1][1].getx();
	return 0;
}