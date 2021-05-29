#include "Bubble.h"
#include "Special.h"
#include "Feld.h"

class Steuerung
{
private:
	string colors[5] = {"red","yellow","blue","green","purple"};
public:
	void *bubs[12][12];
	Feld feld;
	Steuerung();
	void createBubble(int x, int y);
	void update();
	bool makemove();
	void analyze();
	int check_neighbour(int xcur, int ycur, int xcheck, int ycheck);

};
