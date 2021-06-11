#include "Bubble.h"
#include "Special.h"
#include "Feld.h"
#include <vector>
using std::vector;

class Steuerung
{
private:
	string colors[5] = {"red","yellow","blue","green","purple"};
	enum abilities
	{
		none,
		bomb,
		lineH,
		lineV,
		colorbomb
	};
	int score;
public:
	void *bubs[12][12];
	string compArray[12][12];
	Feld feld;
	Steuerung();
	void createBubble(int x, int y,string color = "white");
	bool update();
	bool makemove(int x, int y, char input);
	void analyze();
	int check_neighbour(int xcur, int ycur, int xcheck, int ycheck);
	void fall(int column);
	void setscore(int s);
	bool checkRow(int y);
	bool checkColumn(int x);
	int checkValidInput(int x, int y, char direction);
};
