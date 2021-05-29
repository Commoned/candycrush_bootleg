#include "Bubble.h"
#include "Special.h"
#include "Feld.h"

class Steuerung
{
private:
	string colors[5] = {"red","yellow","blue","green","purple"};
public:
	Bubble bubs[12][12];
	Feld feld;
	Steuerung();
	void createBubble(int x, int y);
	void update();
	bool makemove();
};
