#include "Steuerung.h"
#include "Feld.h"
#include <iostream>

int main()
{
	Steuerung strg;
	bool clean=false;
	strg.feld.drawField(strg.bubs, 0);
	int zug=0; // temporary
	while (1)
	{
		clean = false;
		//strg.update();
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
		strg.makemove();
		strg.analyze();
	}

	return 0;
}