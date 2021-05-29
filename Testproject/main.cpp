#include "Steuerung.h"
#include "Feld.h"
#include <iostream>

int main()
{
	Steuerung strg;
	
	strg.update();
	
	strg.makemove();

	//strg.bubs[1][1].setx(4);
	//std::cout << strg.bubs[1][1].getx();
	//std::cout << strg.feld.bubs[1][1].getx();
	return 0;
}