#include "Steuerung.h"
#include "Feld.h"
#include <iostream>

int main()
{
	Steuerung strg;
	bool clean=false;
	strg.feld.drawField(strg.bubs);
	while (1)
	{
		clean = false;
		//strg.update();
		while (clean == false)
		{
			clean = strg.update();
			
		}
		strg.makemove();
		strg.analyze();
		
	}

	//strg.bubs[1][1].setx(4);
	//std::cout << strg.bubs[1][1].getx();
	//std::cout << strg.feld.bubs[1][1].getx();
	return 0;
}